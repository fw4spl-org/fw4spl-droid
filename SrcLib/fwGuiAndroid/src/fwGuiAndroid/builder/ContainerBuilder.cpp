/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2015.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#include "fwGuiAndroid/builder/ContainerBuilder.hpp"
#include "fwGuiAndroid/container/DroidContainer.hpp"

#include <fwGui/registry/macros.hpp>


fwGuiRegisterMacro(::fwGui::builder::ContainerBuilder, ::fwGui::builder::IContainerBuilder::REGISTRY_KEY);

namespace fwGui
{
namespace builder
{

//-----------------------------------------------------------------------------

ContainerBuilder::ContainerBuilder(::fwGui::GuiBaseObject::Key key)
{
}

//-----------------------------------------------------------------------------

ContainerBuilder::~ContainerBuilder()
{
}

//-----------------------------------------------------------------------------

void ContainerBuilder::createContainer( ::fwGui::container::fwContainer::sptr parent )
{
    m_parent = ::fwGuiAndroid::container::DroidContainer::dynamicCast(parent);
    SLM_ASSERT("Sorry, the parent container is not a DroidContainer", m_parent);
    ::fwGuiAndroid::container::DroidContainer::sptr droidContainer = ::fwGuiAndroid::container::DroidContainer::New();
    m_container                                                    = droidContainer;
}

//-----------------------------------------------------------------------------

void ContainerBuilder::destroyContainer()
{
    SLM_ASSERT("Sorry, Container not initialized", m_container);
    SLM_ASSERT("Sorry, the parent container is not a DroidContainer", m_parent);

    m_container->destroyContainer();
    m_parent->clean();
}

//-----------------------------------------------------------------------------

void ContainerBuilder::setParent(::fwGui::container::fwContainer::sptr parent)
{
    SLM_ASSERT("Sorry, DroidContainer not yet initialized, cleaning impossible", m_container);
    ::fwGuiAndroid::container::DroidContainer::sptr parentContainer =
        ::fwGuiAndroid::container::DroidContainer::dynamicCast(parent);
    SLM_ASSERT("dynamicCast fwContainer to DroidContainer failed", parentContainer);
    ::fwGuiAndroid::container::DroidContainer::sptr container = ::fwGuiAndroid::container::DroidContainer::dynamicCast(
        m_container);
    SLM_ASSERT("dynamicCast fwContainer to DroidContainer failed", container);

    m_parent = parentContainer;
}

//-----------------------------------------------------------------------------

} // namespace builder
} // namespace fwGui
