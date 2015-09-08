/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2015.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

 #include "fwGuiAndroid/layoutManager/FrameLayoutManager.hpp"

#include <fwCore/base.hpp>
#include <fwGui/registry/macros.hpp>

#include <fwServices/registry/ObjectService.hpp>

fwGuiRegisterMacro( ::fwGui::FrameLayoutManager, ::fwGui::layoutManager::IFrameLayoutManager::REGISTRY_KEY );


namespace fwGui
{

//-----------------------------------------------------------------------------

FrameLayoutManager::FrameLayoutManager(::fwGui::GuiBaseObject::Key key)
{
}

//-----------------------------------------------------------------------------

FrameLayoutManager::~FrameLayoutManager()
{
}

//-----------------------------------------------------------------------------

void FrameLayoutManager::createFrame()
{
    ::fwGuiAndroid::container::DroidContainer::sptr container = ::fwGuiAndroid::container::DroidContainer::New();
    m_container                                               = container;

    ::fwGuiAndroid::container::DroidContainer::sptr frameContainer = ::fwGuiAndroid::container::DroidContainer::New();
    m_frame                                                        = frameContainer;
}

//-----------------------------------------------------------------------------

void FrameLayoutManager::destroyFrame()
{
    m_container->clean();
    m_container->destroyContainer();

    m_frame->clean();
    m_frame->destroyContainer();
}

//-----------------------------------------------------------------------------

} // namespace fwGui
