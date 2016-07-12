/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2014-2016.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#include "droidTools/STransformManager.hpp"

#include <fwCom/Signal.hxx>
#include <fwCom/Slots.hxx>

#include <fwData/TransformationMatrix3D.hpp>
#include <fwDataTools/TransformationMatrix3D.hpp>

#include <fwServices/macros.hpp>

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>


namespace droidTools
{

fwServicesRegisterMacro( ::fwServices::IController, ::droidTools::STransformManager, ::fwData::TransformationMatrix3D);

//------------------------------------------------------------------------------

const ::fwCom::Slots::SlotKeyType STransformManager::s_INCREMENT_SLOT = "increment";

//------------------------------------------------------------------------------

STransformManager::STransformManager() throw() :
    m_tx(0),
    m_ty(0),
    m_tz(0)
{

    newSlot(s_INCREMENT_SLOT, &STransformManager::increment, this);
}

//------------------------------------------------------------------------------

STransformManager::~STransformManager() throw()
{
    //---
}

//------------------------------------------------------------------------------

void STransformManager::configuring() throw(::fwTools::Failed)
{
    //---
}

//------------------------------------------------------------------------------

void STransformManager::starting() throw(::fwTools::Failed)
{
    //---
}

//------------------------------------------------------------------------------

void STransformManager::stopping() throw(::fwTools::Failed)
{
    //---
}

//------------------------------------------------------------------------------

void STransformManager::updating() throw(::fwTools::Failed)
{
    ::fwData::TransformationMatrix3D::sptr matrix = this->getObject< ::fwData::TransformationMatrix3D >();


    double tx = m_tx;
    double ty = m_ty;
    double tz = m_tz;

    ::glm::dmat4x4 mat;
    mat = ::glm::translate(mat, ::glm::dvec3(tx, ty, tz));

    ::fwDataTools::TransformationMatrix3D::setTF3DFromMatrix(matrix, mat);

    auto sig = matrix->signal< ::fwData::Object::ModifiedSignalType >(::fwData::Object::s_MODIFIED_SIG);
    {
        ::fwCom::Connection::Blocker block(sig->getConnection(m_slotUpdate));
        sig->asyncEmit();
    }
}

//------------------------------------------------------------------------------

void STransformManager::increment(std::string axis,int value)
{
    if(axis == "x")
    {
        m_tx += value;
    }
    else if(axis == "y")
    {
        m_ty += value;
    }
    else if(axis == "z")
    {
        m_tz += value;
    }
    else
    {
        SLM_ERROR(axis + " is not supported ");
    }

    this->update();
}

//------------------------------------------------------------------------------

} // namespace droidTools
