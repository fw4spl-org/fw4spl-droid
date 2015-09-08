/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2015.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#include "fwGuiAndroid/container/DroidContainer.hpp"

namespace fwGuiAndroid
{
namespace container
{

//-----------------------------------------------------------------------------

DroidContainer::DroidContainer(::fwGui::GuiBaseObject::Key key) throw()
{
}

//-----------------------------------------------------------------------------

DroidContainer::~DroidContainer() throw()
{
}

//-----------------------------------------------------------------------------

void DroidContainer::clean()
{
}

//-----------------------------------------------------------------------------

void DroidContainer::destroyContainer()
{
}

//-----------------------------------------------------------------------------

bool DroidContainer::isShownOnScreen()
{
    return true;
}

//-----------------------------------------------------------------------------

void DroidContainer::setVisible(bool isVisible)
{
    SLM_WARN("This container cannot be invisible");
}

//-----------------------------------------------------------------------------

} // namespace container
} // namespace fwGuiAndroid
