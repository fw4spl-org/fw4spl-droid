/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2015.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#include "visuVTKDroidAdaptor/SVideoAdapter.hpp"

#include <fwCom/Slot.hpp>
#include <fwCom/Slot.hxx>
#include <fwCom/Slots.hpp>
#include <fwCom/Slots.hxx>

#include <fwData/Image.hpp>

#include <fwServices/Base.hpp>
#include <fwServices/registry/ObjectService.hpp>

#include <fwComEd/fieldHelper/MedicalImageHelpers.hpp>

#include <fwData/Boolean.hpp>

#include <fwVtkIO/vtk.hpp>

#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkImageData.h>
#include <vtkRenderer.h>
#include <vtkTexture.h>
#include <vtkProperty.h>


fwServicesRegisterMacro( ::fwRenderVTK::IVtkAdaptorService, ::visuVTKDroidAdaptor::SVideoAdapter, ::fwData::Image );


namespace visuVTKDroidAdaptor
{

static const ::fwCom::Slots::SlotKeyType s_UPDATE_IMAGE_SLOT         = "updateImage";
static const ::fwCom::Slots::SlotKeyType s_UPDATE_IMAGE_OPACITY_SLOT = "updateImageOpacity";

//------------------------------------------------------------------------------

SVideoAdapter::SVideoAdapter() throw() :
    m_imageData(vtkImageData::New()),
    m_texture(vtkTexture::New()),
    m_actor(vtkActor::New()),
    m_isTextureInit(false)
{
    newSlot(s_UPDATE_IMAGE_SLOT, &SVideoAdapter::updateImage, this);
    newSlot(s_UPDATE_IMAGE_OPACITY_SLOT, &SVideoAdapter::updateImageOpacity, this);
}

//------------------------------------------------------------------------------

SVideoAdapter::~SVideoAdapter() throw()
{
    m_actor->Delete();
    m_actor = nullptr;
}

//------------------------------------------------------------------------------

void SVideoAdapter::configuring() throw(fwTools::Failed)
{
    SLM_TRACE_FUNC();
    assert(m_configuration->getName() == "config");
    this->setRenderId( m_configuration->getAttributeValue("renderer") );
}

//------------------------------------------------------------------------------


void SVideoAdapter::doStart() throw(fwTools::Failed)
{
    this->setVtkPipelineModified();
    this->doUpdate();
}

//------------------------------------------------------------------------------

void SVideoAdapter::doUpdate() throw(fwTools::Failed)
{
    ::fwData::Image::sptr image = this->getObject< ::fwData::Image >();
    bool imageIsValid = ::fwComEd::fieldHelper::MedicalImageHelpers::checkImageValidity( image );

    if (!imageIsValid)
    {
        return;
    }

    ::fwVtkIO::toVTKImage(image, m_imageData);

    if(!m_isTextureInit)
    {
        this->removeAllPropFromRenderer();

        ::fwData::Image::SizeType size = image->getSize();

        m_texture->SetInputData( m_imageData );
        m_isTextureInit = true;

        this->getRenderer()->TexturedBackgroundOn();
        this->getRenderer()->SetBackgroundTexture(m_texture);
    }
    m_imageData->Modified();
    this->setVtkPipelineModified();
}

//------------------------------------------------------------------------------

void SVideoAdapter::doSwap() throw(fwTools::Failed)
{
    this->doUpdate();
}

//------------------------------------------------------------------------------

void SVideoAdapter::doStop() throw(fwTools::Failed)
{
    this->unregisterServices();
    this->removeAllPropFromRenderer();
}

//------------------------------------------------------------------------------

void SVideoAdapter::updateImageOpacity()
{
    ::fwData::Image::sptr img = this->getObject< ::fwData::Image >();
    if(img->getField( "TRANSPARENCY" ) )
    {
        ::fwData::Integer::sptr transparency = img->getField< ::fwData::Integer >( "TRANSPARENCY" );
        double imageOpacity = (100 - (*transparency) ) / 100.0;
        m_actor->GetProperty()->SetOpacity(imageOpacity);
    }
    if(img->getField( "VISIBILITY" ) )
    {
        ::fwData::Boolean::sptr visible = img->getField< ::fwData::Boolean >( "VISIBILITY" );
        m_actor->SetVisibility(*visible);
    }

    this->setVtkPipelineModified();
}

//------------------------------------------------------------------------------

void SVideoAdapter::updateImage()
{
    m_isTextureInit = false;
    this->updating();
}

//------------------------------------------------------------------------------

::fwServices::IService::KeyConnectionsType SVideoAdapter::getObjSrvConnections() const
{
    KeyConnectionsType connections;
    connections.push_back( std::make_pair(::fwData::Image::s_MODIFIED_SIG, s_UPDATE_IMAGE_SLOT));
    connections.push_back( std::make_pair(::fwData::Image::s_VISIBILITY_MODIFIED_SIG, s_UPDATE_IMAGE_OPACITY_SLOT));
    connections.push_back( std::make_pair(::fwData::Image::s_TRANSPARENCY_MODIFIED_SIG, s_UPDATE_IMAGE_OPACITY_SLOT));
    connections.push_back( std::make_pair(::fwData::Image::s_BUFFER_MODIFIED_SIG, s_UPDATE_SLOT));

    return connections;
}

} //namespace visuVTKDroidAdaptor
