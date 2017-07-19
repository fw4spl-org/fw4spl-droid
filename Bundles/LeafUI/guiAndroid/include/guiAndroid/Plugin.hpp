/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2014-2015.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef __GUIANDROID_PLUGIN_HPP__
#define __GUIANDROID_PLUGIN_HPP__

#include "guiAndroid/config.hpp"

#include <fwRuntime/Plugin.hpp>

namespace fwThread
{
class Worker;
} //namespace fwThread

namespace guiAndroid
{
/**
 * @brief   This class is started when the bundles is loaded.
 * @class   Plugin
 */
class GUIANDROID_CLASS_API Plugin : public ::fwRuntime::Plugin
{
public:
    /**
     * @brief   Destructor
     */
    GUIANDROID_API ~Plugin() noexcept;

    /**
     * @brief Start method.
     *
     * @exception ::fwRuntime::RuntimeException.
     * This method is used by runtime to initialize the bundle.
     */
    GUIANDROID_API void start();

    /**
     * @brief Stop method.
     *
     * This method is used by runtime to stop the bundle.
     */
    GUIANDROID_API void stop() noexcept;

    GUIANDROID_API int run() noexcept;

private:

    SPTR(::fwThread::Worker) m_worker;
};

} // namespace guiDroid

#endif //__GUIANDROID_PLUGIN_HPP__
