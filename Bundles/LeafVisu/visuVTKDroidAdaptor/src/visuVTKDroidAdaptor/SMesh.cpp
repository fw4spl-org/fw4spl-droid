/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2015.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#include "visuVTKDroidAdaptor/SMesh.hpp"

#include <fwCom/Slots.hxx>

#include <fwServices/Base.hpp>
#include <fwVtkIO/helper/Mesh.hpp>

#include <vtkRenderer.h>

namespace visuVTKDroidAdaptor
{

fwServicesRegisterMacro( ::fwRenderVTK::IVtkAdaptorService, ::visuVTKDroidAdaptor::SMesh, ::fwData::Mesh );

static const ::fwCom::Slots::SlotKeyType s_MODIFY_OBJECT_SLOT       = "modifyObject";
static const ::fwCom::Slots::SlotKeyType s_UPDATE_POINT_COLORS_SLOT = "updatePointColors";
static const ::fwCom::Slots::SlotKeyType s_UPDATE_CELL_COLORS_SLOT  = "updateCellColors";
static const ::fwCom::Slots::SlotKeyType s_UPDATE_VERTEX_SLOT       = "updateVertex";
static const ::fwCom::Slots::SlotKeyType s_SHOW_POINT_COLORS_SLOT   = "showPointColors";
static const ::fwCom::Slots::SlotKeyType s_SHOW_CELL_COLORS_SLOT    = "showCellColors";
static const ::fwCom::Slots::SlotKeyType s_HIDE_COLORS_SLOT         = "hideColors";
static const ::fwCom::Slots::SlotKeyType s_VISIBILITY_SLOT          = "updateVisibility";

//-----------------------------------------------------------------------------

SMesh::SMesh() : m_autoResetCamera(true)
{
    m_mapper = vtkPolyDataMapper::New();
    m_actor  = vtkActor::New();

    newSlot( s_MODIFY_OBJECT_SLOT, &SMesh::modifyMesh, this );
    newSlot( s_UPDATE_POINT_COLORS_SLOT, &SMesh::updatePointColors, this );
    newSlot( s_UPDATE_CELL_COLORS_SLOT, &SMesh::updateCellColors, this );
    newSlot( s_UPDATE_VERTEX_SLOT, &SMesh::updateVertex, this );
    newSlot( s_SHOW_POINT_COLORS_SLOT, &SMesh::showPointColors, this );
    newSlot( s_SHOW_CELL_COLORS_SLOT, &SMesh::showCellColors, this );
    newSlot( s_HIDE_COLORS_SLOT, &SMesh::hideColors, this );
    newSlot(s_VISIBILITY_SLOT, &SMesh::updateVisibility, this);
}

//-----------------------------------------------------------------------------

SMesh::~SMesh()
{
    m_mapper->Delete();
    m_mapper = nullptr;

    m_transform->Delete();
    m_transform = nullptr;

    if(m_actor)
    {
        m_actor->Delete();
        m_actor = nullptr;
    }

    if (m_polyData)
    {
        m_polyData->Delete();
        m_polyData = nullptr;
    }
}

//-----------------------------------------------------------------------------

void SMesh::doStart() throw(fwTools::Failed)
{
    m_transform = vtkTransform::New();
    if(!this->getTransformId().empty())
    {
        vtkTransform *t = m_renderService.lock()->getOrAddVtkTransform(m_transformId);
        m_transform->Concatenate(t);
    }

    this->buildPipeline();
}

//-----------------------------------------------------------------------------

void SMesh::configuring() throw(fwTools::Failed)
{
    SLM_ASSERT("'config' not found",m_configuration->getName() == "config");

    if (m_configuration->hasAttribute("autoresetcamera") )
    {
        std::string autoresetcamera = m_configuration->getAttributeValue("autoresetcamera");
        m_autoResetCamera = (autoresetcamera == "yes");
    }

    this->setRenderId    ( m_configuration->getAttributeValue ( "renderer"  ) );
    this->setTransformId ( m_configuration->getAttributeValue ( "transform" ) );
}

//-----------------------------------------------------------------------------

void SMesh::doStop() throw(fwTools::Failed)
{
}

//-----------------------------------------------------------------------------

void SMesh::doSwap() throw(fwTools::Failed)
{
    ::fwData::Mesh::sptr mesh = this->getObject < ::fwData::Mesh >();
    this->updateMesh( mesh );
}

//-----------------------------------------------------------------------------

void SMesh::doUpdate() throw(fwTools::Failed)
{
    ::fwData::Mesh::sptr mesh = this->getObject < ::fwData::Mesh >();
    this->updateMesh( mesh );
}

//-----------------------------------------------------------------------------

void SMesh::buildPipeline()
{
    ::fwData::Mesh::sptr mesh = this->getObject < ::fwData::Mesh >();
    this->addToRenderer(m_actor);
    this->updateMesh( mesh );
    this->setVtkPipelineModified();
}

//-----------------------------------------------------------------------------

void SMesh::updateMesh( ::fwData::Mesh::sptr mesh )
{
    if (m_polyData)
    {
        m_polyData->Delete();
        m_polyData = 0;
    }
    m_polyData = vtkPolyData::New();
    ::fwVtkIO::helper::Mesh::toVTKMesh(mesh, m_polyData);

    m_mapper->SetInputData(m_polyData);
    m_actor->SetMapper(m_mapper);

    m_actor->SetUserTransform(m_transform);

    if (m_autoResetCamera)
    {
        this->getRenderer()->ResetCamera();
    }
    this->setVtkPipelineModified();
}


//------------------------------------------------------------------------------

void SMesh::updateVisibility( bool isVisible)
{
    if (m_actor)
    {
        m_actor->SetVisibility( isVisible );
    }

    // if (m_servicesStarterCallback)
    // {
    //     m_servicesStarterCallback->Execute(0, vtkCommand::UserEvent, &isVisible);
    // }
    this->setVtkPipelineModified();
    this->requestRender();
}

//------------------------------------------------------------------------------

void SMesh::setAutoResetCamera(bool autoResetCamera)
{
    m_autoResetCamera = autoResetCamera;
}

//------------------------------------------------------------------------------

void SMesh::modifyMesh()
{
    ::fwData::Mesh::sptr mesh = this->getObject < ::fwData::Mesh >();
    this->updateMesh( mesh );
}

//------------------------------------------------------------------------------

void SMesh::updatePointColors()
{
    ::fwData::Mesh::sptr mesh = this->getObject < ::fwData::Mesh >();
    SLM_ASSERT("m_polyData not instanced", m_polyData);

    ::fwVtkIO::helper::Mesh::updatePolyDataPointColor(m_polyData, mesh);
    this->setVtkPipelineModified();
    this->requestRender();
}

//------------------------------------------------------------------------------

void SMesh::updateCellColors()
{
    ::fwData::Mesh::sptr mesh = this->getObject < ::fwData::Mesh >();
    SLM_ASSERT("m_polyData not instanced", m_polyData);

    ::fwVtkIO::helper::Mesh::updatePolyDataCellColor(m_polyData, mesh);
    this->setVtkPipelineModified();
    this->requestRender();
}

//------------------------------------------------------------------------------

void SMesh::updateVertex()
{
    ::fwData::Mesh::sptr mesh = this->getObject < ::fwData::Mesh >();
    SLM_ASSERT("m_polyData not instanced", m_polyData);

    ::fwVtkIO::helper::Mesh::updatePolyDataPoints(m_polyData, mesh);

    if (m_autoResetCamera)
    {
        this->getRenderer()->ResetCamera();
    }
    this->setVtkPipelineModified();
}

//------------------------------------------------------------------------------

void SMesh::showPointColors()
{
    m_mapper->ScalarVisibilityOn();
    m_mapper->SetScalarModeToUsePointData();
    this->setVtkPipelineModified();
}

//------------------------------------------------------------------------------

void SMesh::showCellColors()
{
    m_mapper->ScalarVisibilityOn();
    m_mapper->SetScalarModeToUseCellData();
    this->setVtkPipelineModified();
}

//------------------------------------------------------------------------------

void SMesh::hideColors()
{
    m_mapper->ScalarVisibilityOff();
    this->setVtkPipelineModified();
}

//------------------------------------------------------------------------------

} //namespace visuVTKDroidAdaptor
