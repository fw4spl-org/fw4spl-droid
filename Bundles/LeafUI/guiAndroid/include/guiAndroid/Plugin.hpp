/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2014-2015.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef __GUIANDROID_PLUGIN_HPP__
#define __GUIANDROID_PLUGIN_HPP__

#include "guiAndroid/config.hpp"

#include <fwRuntime/Plugin.hpp>

namespace guiAndroid
{
/**
 * @brief   This class is started when the bundles is loaded.
 * @class   Plugin
 */
struct GUIANDROID_CLASS_API Plugin : public ::fwRuntime::Plugin
{
    /**
     * @brief   destructor
     */
    GUIANDROID_API ~Plugin() throw();

    // Overrides
    GUIANDROID_API void start() throw(::fwRuntime::RuntimeException);

    // Overrides
    GUIANDROID_API void stop() throw();

};

} // namespace guiDroid

#endif //__GUIANDROID_PLUGIN_HPP__
