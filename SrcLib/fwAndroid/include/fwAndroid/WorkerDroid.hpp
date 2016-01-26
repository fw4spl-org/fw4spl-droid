/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2015.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef __FWANDROID_WORKERDROID_HPP__
#define __FWANDROID_WORKERDROID_HPP__

#include <fwThread/Worker.hpp>

#include "fwAndroid/config.hpp"

class android_app;

namespace fwAndroid
{

/**
 * @brief Get a worker for the android app
 * @param app: a android_native_app_glue
 * @return a worker
 */
FWANDROID_API ::fwThread::Worker::sptr getDroidWorker( android_app* app );

} // namespace fwAndroid

#endif //__FWANDROID_WORKERDROID_HPP__
