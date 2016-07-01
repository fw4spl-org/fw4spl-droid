/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2016.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifdef ANDROID

#include "droidPlugin/DroidEvent.hpp"

#include <fwRuntime/profile/Profile.hpp>

// Qt
#include <QApplication>
#include <QWidget>

// Internal Qt
#include <qpa/qwindowsysteminterface.h>


//------------------------------------------------------------------------------

DroidEvent& DroidEvent::getInstance()
{
    static DroidEvent instance;
    return instance;
}

//------------------------------------------------------------------------------

DroidEvent::DroidEvent()
{
    m_touchDevice.setType(QTouchDevice::TouchScreen);
    m_touchDevice.setCapabilities(QTouchDevice::Position
                                  | QTouchDevice::Area
                                  | QTouchDevice::Pressure
                                  | QTouchDevice::NormalizedPosition);
    QWindowSystemInterface::registerTouchDevice(&m_touchDevice);
}

//------------------------------------------------------------------------------

DroidEvent::~DroidEvent()
{
    //----
}

//------------------------------------------------------------------------------
void DroidEvent::handleEvent(
    int actionType, int actionId, int numPtrs,
    int *xPtr, int *yPtr, int *idPtr,float *areas,float* pressures, int metaState)
{

    OSLM_DEBUG(" actionType = "<<actionType);

    QPoint globalPos(xPtr[0],yPtr[0]);

    QWindowList wl      = QGuiApplication::topLevelWindows();
    QWindow *containing = 0;
    for(QWindow *w: wl)
    {
        if (w->isVisible() && w->geometry().contains(globalPos))
        {
            containing = w;
            break;
        }
    }

    QPoint localPos = containing ? (globalPos - containing->position()) : globalPos;


    QWidgetList widgetList = qApp->topLevelWidgets();
    OSLM_DEBUG("localPos = "<<localPos.x()<<" , "<<localPos.y());
    OSLM_DEBUG("globalPos = "<<globalPos.x()<<" , "<<globalPos.y());
    QWidget *containingW = 0;
    for(QWidget *widget: widgetList)
    {
        if (widget->isVisible() && widget->geometry().contains(localPos))
        {
            containingW = widget;
            break;
        }
    }

    Qt::TouchPointState state = Qt::TouchPointStationary;
    switch (actionType)
    {
        case 0:
            state = Qt::TouchPointPressed;
            break;
        case 1:
            state = Qt::TouchPointMoved;
            break;
        case 2:
            state = Qt::TouchPointStationary;
            break;
        case 3:
            state = Qt::TouchPointReleased;
            break;
    }

    QList<QWindowSystemInterface::TouchPoint> touchPoints;

    int dw = 1;
    int dh = 1;
    for (int i = 0; i < numPtrs; ++i)
    {
        OSLM_DEBUG(xPtr[i]<<" "<<yPtr[i]<<" "<<idPtr[i]);


        QWindowSystemInterface::TouchPoint touchPoint;
        touchPoint.id             = idPtr[i];
        touchPoint.normalPosition = QPointF(double(xPtr[i] / dw), double( yPtr[i] / dh));
        touchPoint.state          = state;
        touchPoint.area           = QRectF(xPtr[i] - double(dw*areas[i]) / 2.0,
                                           yPtr[i] - double(dh*areas[i]) / 2.0,
                                           double(dw*areas[i]),
                                           double(dh*areas[i]));
        touchPoint.pressure = pressures[i];
        touchPoints.push_back(touchPoint);
    }


//    QWindow *window = QGuiApplication::topLevelAt(touchPoints.at(0).area.center().toPoint());
    switch(actionType)
    {
        case AMOTION_EVENT_ACTION_MOVE:
        {
            SLM_DEBUG("AMOTION_EVENT_ACTION_MOVE");


//            QWindowSystemInterface::handleTouchEvent(containing,&m_touchDevice,touchPoints);
            QWindowSystemInterface::handleMouseEvent(containing,
                                                     localPos,
                                                     globalPos,
                                                     Qt::MouseButtons(Qt::LeftButton));

        }
        break;
        case AMOTION_EVENT_ACTION_DOWN:
        {
            OSLM_DEBUG("AMOTION_EVENT_ACTION_DOWN");

//            QWindowSystemInterface::handleTouchEvent(containing,&m_touchDevice,touchPoints);
            QWindowSystemInterface::handleMouseEvent(containing,
                                                     localPos,
                                                     globalPos,
                                                     Qt::MouseButtons(Qt::LeftButton));
        }
        break;

        case AMOTION_EVENT_ACTION_UP:
        {
            OSLM_DEBUG("AMOTION_EVENT_ACTION_UP");

//            QWindowSystemInterface::handleTouchEvent(containing,&m_touchDevice,touchPoints);
            QWindowSystemInterface::handleMouseEvent(containing,
                                                     localPos,
                                                     globalPos,
                                                     Qt::MouseButtons(Qt::NoButton));
        }
        break;

    } // end switch action
}

//------------------------------------------------------------------------------

int32_t DroidEvent::handleInput(struct android_app* app, AInputEvent* event)
{

    switch (AInputEvent_getType(event))
    {
        case AINPUT_EVENT_TYPE_MOTION:
        {
            int action       = AMotionEvent_getAction(event);
            int metaState    = AMotionEvent_getMetaState(event);
            int numPtrs      = AMotionEvent_getPointerCount(event);
            int eventPointer = action >> AMOTION_EVENT_ACTION_POINTER_INDEX_SHIFT;
            action = action & AMOTION_EVENT_ACTION_MASK;

            int *xPtr        = new int[numPtrs]; //(int *)malloc(numPtrs*sizeof(int));
            int *yPtr        = new int[numPtrs];/*(int *)malloc(numPtrs*sizeof(int));*/
            int *idPtr       = new int[numPtrs];/*(int *)malloc(numPtrs*sizeof(int));*/
            float *areas     = new float[numPtrs];
            float *pressures = new float[numPtrs];
            for (int i = 0; i < numPtrs; ++i)
            {
                idPtr[i]     = AMotionEvent_getPointerId(event, i);
                xPtr[i]      = AMotionEvent_getX(event, i);
                yPtr[i]      = AMotionEvent_getY(event, i);
                areas[i]     = AMotionEvent_getSize(event, i);
                pressures[i] = AMotionEvent_getPressure(event,i);

            }
            int actionId = AMotionEvent_getPointerId(event, eventPointer);
            DroidEvent::getInstance().handleEvent(action, actionId, numPtrs,
                                                  xPtr, yPtr, idPtr,areas,pressures, metaState);
            delete[] xPtr;
            delete[] yPtr;
            delete[] idPtr;
            return 1;
        }
        break;
        case AINPUT_EVENT_TYPE_KEY:
        {
            int action    = AKeyEvent_getAction(event);
            int nChar     = AKeyEvent_getKeyCode(event);
            int metaState = AKeyEvent_getMetaState(event);
            int nRepCnt   = AKeyEvent_getRepeatCount(event);
            //      this->HandleKeyEvent(action == AKEY_EVENT_ACTION_DOWN,
            //        nChar,
            //        metaState,
            //        nRepCnt);
            return 1;
        }
        break;
    } // end switch event type motion versus key

    return 0;

}
//-----------------------------------------------------------------------------

/**
 * Process the next main command.
 */
void DroidEvent::handleCommand(struct android_app* app, int32_t cmd)
{
    switch (cmd)
    {
        case APP_CMD_SAVE_STATE:
            // The system has asked us to save our current state.  Do so.
            OSLM_DEBUG("APP_CMD_SAVE_STATE ");
            QWindowSystemInterface::handleApplicationStateChanged(Qt::ApplicationInactive);
            break;
        case APP_CMD_INIT_WINDOW:
            // The window is being shown, get it ready.
            OSLM_DEBUG("APP_CMD_INIT_WINDOW ");
            QWindowSystemInterface::handleApplicationStateChanged(Qt::ApplicationActive);
            break;
        case APP_CMD_TERM_WINDOW:
            // The window is being hidden or closed, clean it up.;
            break;
        case APP_CMD_GAINED_FOCUS:
            // When our app gains focus, we start monitoring the accelerometer.

            break;
        case APP_CMD_LOST_FOCUS:
            // When our app loses focus, we stop monitoring the accelerometer.
            // This is to avoid consuming battery while not being used.
            break;
        case APP_CMD_RESUME:
            OSLM_DEBUG("APP_CMD_RESUME ");
            QWindowSystemInterface::handleApplicationStateChanged(Qt::ApplicationActive);
            break;
        case APP_CMD_PAUSE:
            OSLM_DEBUG("APP_CMD_PAUSE ");
            QWindowSystemInterface::handleApplicationStateChanged(Qt::ApplicationInactive);
            break;
        case APP_CMD_STOP:
            OSLM_DEBUG("APP_CMD_STOP ");
            QWindowSystemInterface::handleApplicationStateChanged(Qt::ApplicationSuspended);
            break;
    }
}

//-----------------------------------------------------------------------------

#endif
