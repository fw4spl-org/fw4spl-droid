/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2016.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef __UIDROIDQT_PLUGIN_HPP__
#define __UIDROIDQT_PLUGIN_HPP__

#include <fwRuntime/Plugin.hpp>

namespace uiDroidQt
{

struct Plugin : public ::fwRuntime::Plugin
{
    /**
     * @brief   destructor
     */
    ~Plugin() noexcept
    {
    }

    // Overrides
    void start()
    {
    }

    // Overrides
    void stop() noexcept
    {
    }
};

} // namespace uiDroidQt

#endif //__UIDROIDQT_PLUGIN_HPP__
