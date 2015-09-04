/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2015.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#include <fwRuntime/utils/GenericExecutableFactoryRegistrar.hpp>

#include <fwServices/Base.hpp>
#include <fwServices/macros.hpp>

#include "visuVTKDroidAdaptor/Plugin.hpp"


namespace visuVTKDroidAdaptor
{
using namespace ::fwRuntime::utils;
static GenericExecutableFactoryRegistrar<Plugin> registrar("::visuVTKDroidAdaptor::Plugin");


Plugin::~Plugin() throw()
{
}

void Plugin::start() throw(::fwRuntime::RuntimeException)
{
}

void Plugin::stop() throw()
{
}

} // namespace visuVTKDroidAdaptor
