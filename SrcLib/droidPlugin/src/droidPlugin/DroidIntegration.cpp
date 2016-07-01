/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2016.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#include "droidPlugin/DroidIntegration.hpp"

#include "droidPlugin/DroidWindow.hpp"
#include "droidPlugin/DroidBackingstore.hpp"
#include "droidPlugin/DroidEvent.hpp"
#include "droidPlugin/DroidTheme.hpp"
#include "droidPlugin/DroidScreen.hpp"

#include <fwRuntime/profile/Profile.hpp>

// Qt
#include <QtGui/QSurfaceFormat>
#include <QtGui/QOpenGLContext>
#include <QtGui/QScreen>

// Internal Qt
#include <QGuiApplication>
#include <QtPlatformSupport/private/qgenericunixeventdispatcher_p.h>
#include <qpa/qplatformwindow.h>


#include <EGL/egl.h>

DroidIntegration::DroidIntegration() :
    mScreen(new DroidScreen(EGL_DEFAULT_DISPLAY))
{

    ::fwRuntime::profile::Profile::sptr profile = ::fwRuntime::profile::getCurrentProfile();
    android_app* app = profile->getApp();
    app->onInputEvent = DroidEvent::handleInput;
    app->onAppCmd     = DroidEvent::handleCommand;

    screenAdded(mScreen);
}

//-----------------------------------------------------------------------------

DroidIntegration::~DroidIntegration()
{
    destroyScreen(mScreen);

}

//-----------------------------------------------------------------------------

bool DroidIntegration::hasCapability(QPlatformIntegration::Capability cap) const
{
    switch (cap)
    {
        case ThreadedPixmaps: return true;
        case OpenGL: return true;
        case ThreadedOpenGL: return true;
        case ApplicationState: return true;
        case NativeWidgets: return true;
        case ForeignWindows: return true;
        default: return QPlatformIntegration::hasCapability(cap);
    }
}

//-----------------------------------------------------------------------------

QPlatformWindow *DroidIntegration::createPlatformWindow(QWindow *window) const
{
    QPlatformWindow *w = new DroidWindow(window);
    w->requestActivateWindow();

    return w;
}

//-----------------------------------------------------------------------------

QPlatformBackingStore *DroidIntegration::createPlatformBackingStore(QWindow *window) const
{
    return new DroidBackingStore(window);
}

//-----------------------------------------------------------------------------

QPlatformOpenGLContext *DroidIntegration::createPlatformOpenGLContext(QOpenGLContext *context) const
{
    return static_cast<DroidScreen *>(context->screen()->handle())->platformContext();
}

//-----------------------------------------------------------------------------

QAbstractEventDispatcher *DroidIntegration::createEventDispatcher() const
{
    return createUnixEventDispatcher();
}

//-----------------------------------------------------------------------------

QPlatformTheme *DroidIntegration::createPlatformTheme(const QString &name) const
{
    return new DroidTheme();
}

