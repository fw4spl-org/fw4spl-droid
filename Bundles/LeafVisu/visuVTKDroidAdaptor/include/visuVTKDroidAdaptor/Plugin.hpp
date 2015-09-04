/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2015.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef __VISUVTKDROIDADAPTOR_PLUGIN_HPP__
#define __VISUVTKDROIDADAPTOR_PLUGIN_HPP__

#include <fwRuntime/Plugin.hpp>

#include "visuVTKDroidAdaptor/config.hpp"

namespace visuVTKDroidAdaptor
{

/**
 * @brief   This class is started when the bundles is loaded.
 * @class   Plugin
 */
struct Plugin : public ::fwRuntime::Plugin
{
    /**
     * @brief   destructor
     */
    ~Plugin() throw();

    // Overrides
    void start() throw(::fwRuntime::RuntimeException);

    // Overrides
    void stop() throw();

};

} // namespace visuVTKDroidAdaptor

#endif // __VISUVTKDROIDADAPTOR_PLUGIN_HPP__
