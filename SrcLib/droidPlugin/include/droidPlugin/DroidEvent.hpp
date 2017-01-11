/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2016.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef __DROIDPLUGIN_DROIDEVENT_HPP__
#define __DROIDPLUGIN_DROIDEVENT_HPP__

#include <stdint.h>

#include <QTouchDevice>
#include <android_native_app_glue.h>

class DroidEvent
{

public:
    static DroidEvent& getInstance();
    void handleEvent(
        int actionType, int actionId, int numPtrs,
        int *xPtr, int *yPtr, int *idPtr,float *areas, float* pressures, int metaState);

    // C++ 11
    // =======
    // technique of deleting the methods
    DroidEvent(DroidEvent const&)     = delete;
    void operator=(DroidEvent const&) = delete;

    static int32_t handleInput(struct android_app* app, AInputEvent* event);
    static void handleCommand(struct android_app* app, int32_t cmd);

private:
    DroidEvent();
    ~DroidEvent();

    QTouchDevice m_touchDevice;
};

#endif /*__DROIDPLUGIN_DROIDEVENT_HPP__*/
