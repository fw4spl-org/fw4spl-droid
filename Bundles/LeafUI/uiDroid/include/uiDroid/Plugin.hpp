/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2014-2015.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef __UIDROID_PLUGIN_HPP__
#define __UIDROID_PLUGIN_HPP__

#include <fwRuntime/Plugin.hpp>

namespace uiDroid
{

struct Plugin : public ::fwRuntime::Plugin
{
    /**
     * @brief   destructor
     */
    ~Plugin() throw()
    {
    }

    // Overrides
    void start() throw(::fwRuntime::RuntimeException);

    // Overrides
    void stop() throw()
    {
    }
};

} // namespace uiDroid

#endif //__UIDROID_PLUGIN_HPP__
