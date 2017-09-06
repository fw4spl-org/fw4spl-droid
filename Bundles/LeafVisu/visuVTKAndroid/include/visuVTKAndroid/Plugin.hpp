/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2015.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef __VISUVTKANDROID_PLUGIN_HPP__
#define __VISUVTKANDROID_PLUGIN_HPP__

#include "visuVTKAndroid/config.hpp"

#include <fwRuntime/Plugin.hpp>

/**
 * @brief   This class is started when the bundles is loaded.
 * @class   Plugin
 */
namespace visuVTKAndroid
{
class Plugin : public ::fwRuntime::Plugin
{
public:
    /**
     * @brief   Destructor
     */
    VISUVTKANDROID_API ~Plugin() noexcept;

    /**
     * @brief Start method.
     *
     * @exception ::fwRuntime::RuntimeException.
     * This method is used by runtime to initialize the bundle.
     */
    VISUVTKANDROID_API void start();

    /**
     * @brief Stop method.
     *
     * This method is used by runtime to stop the bundle.
     */
    VISUVTKANDROID_API void stop() noexcept;

    VISUVTKANDROID_API int run() noexcept;
};

} // namespace visuVTKAndroid

#endif //__VISUVTKANDROID_PLUGIN_HPP__
