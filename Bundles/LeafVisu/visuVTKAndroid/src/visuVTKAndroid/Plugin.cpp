/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2015.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#include "visuVTKAndroid/Plugin.hpp"

#include <fwAndroid/WorkerDroid.hpp>

#include <fwGui/registry/worker.hpp>

#include <fwRuntime/profile/Profile.hpp>
#include <fwRuntime/utils/GenericExecutableFactoryRegistrar.hpp>

#include <fwThread/Worker.hpp>

#include <functional>

namespace visuVTKAndroid
{

static ::fwRuntime::utils::GenericExecutableFactoryRegistrar<Plugin> registrar("::visuVTKAndroid::Plugin");

Plugin::~Plugin() throw()
{
}

//-----------------------------------------------------------------------------

void Plugin::start() throw(::fwRuntime::RuntimeException)
{
    ::fwRuntime::profile::Profile::sptr profile = ::fwRuntime::profile::getCurrentProfile();
    SLM_ASSERT("Profile is not initialized", profile);

    m_worker = ::fwAndroid::getDroidWorker(profile->getApp());
    ::fwGui::registry::worker::init(m_worker);

    ::fwRuntime::profile::getCurrentProfile()->setRunCallback(std::bind(&Plugin::run, this));
}

//-----------------------------------------------------------------------------

void Plugin::stop() throw()
{
}

//-----------------------------------------------------------------------------

void setup()
{
    ::fwRuntime::profile::getCurrentProfile()->setup();
}

//-----------------------------------------------------------------------------

int Plugin::run() throw()
{
    m_worker->post( std::bind( &setup ) );
    m_worker->getFuture().wait(); // This is required to start Worker loop

    ::fwRuntime::profile::getCurrentProfile()->cleanup();
    int result = ::boost::any_cast<int>(m_worker->getFuture().get());

    return result;
}

//-----------------------------------------------------------------------------


} // namespace visuVTKAndroid
