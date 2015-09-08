/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2014-2015.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#include "guiAndroid/Plugin.hpp"

#include <fwGuiAndroid/container/DroidContainer.hpp>

#include <fwRuntime/profile/Profile.hpp>
#include <fwRuntime/utils/GenericExecutableFactoryRegistrar.hpp>


namespace guiAndroid
{

static ::fwRuntime::utils::GenericExecutableFactoryRegistrar<Plugin> registrar("::guiAndroid::Plugin");

//-----------------------------------------------------------------------------

Plugin::~Plugin() throw()
{
}

//-----------------------------------------------------------------------------

void Plugin::start() throw(::fwRuntime::RuntimeException)
{
    // load fwGuiAndroid lib
    ::fwGuiAndroid::container::DroidContainer::sptr container = ::fwGuiAndroid::container::DroidContainer::New();
}

//-----------------------------------------------------------------------------

void Plugin::stop() throw()
{
}

} // namespace guiDroid
