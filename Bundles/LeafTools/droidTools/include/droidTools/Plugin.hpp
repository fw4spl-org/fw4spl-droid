/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2014-2016.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef __DROIDTOOLS_PLUGIN_HPP__
#define __DROIDTOOLS_PLUGIN_HPP__

#include <fwRuntime/Plugin.hpp>

namespace droidTools
{

struct Plugin : public ::fwRuntime::Plugin
{
    /**
     * @brief   destructor
     */
    ~Plugin() noexcept;

    // Overrides
    void start();

    // Overrides
    void stop() noexcept;

};

} // namespace droidTools

#endif //__DROIDTOOLS_PLUGIN_HPP__
