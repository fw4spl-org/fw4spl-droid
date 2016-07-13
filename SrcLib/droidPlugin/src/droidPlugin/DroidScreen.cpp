/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2016.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#include "droidPlugin/DroidScreen.hpp"
#include "droidPlugin/DroidWindow.hpp"

#include <QtPlatformSupport/private/qeglconvenience_p.h>
#include <QtPlatformSupport/private/qeglplatformcontext_p.h>
#include <private/qopenglcontext_p.h>
#include <fwRuntime/profile/Profile.hpp>

class DroidPlatformContext : public QEGLPlatformContext
{

public:
    DroidPlatformContext(const QSurfaceFormat &format, QPlatformOpenGLContext *share, EGLDisplay display)
        : QEGLPlatformContext(format, share, display)
    {
        SLM_TRACE_FUNC();
    }

    EGLSurface eglSurfaceForPlatformSurface(QPlatformSurface *surface) Q_DECL_OVERRIDE
    {
        SLM_TRACE_FUNC();
        DroidWindow *window = static_cast<DroidWindow *>(surface);
        DroidScreen *screen = static_cast<DroidScreen *>(window->screen());
        return screen->surface();
    }

    bool makeCurrent(QPlatformSurface *surface)
    {
        bool ret                     = QEGLPlatformContext::makeCurrent(surface);
        QOpenGLContextPrivate *ctx_d = QOpenGLContextPrivate::get(context());
        if (!ctx_d->workaround_brokenFBOReadBack)
        {
            ctx_d->workaround_brokenFBOReadBack = true;
        }

        return ret;
    }
};

//-----------------------------------------------------------------------------

DroidScreen::DroidScreen(EGLNativeDisplayType display) :
    QEGLPlatformScreen(display),
    m_depth(32),
    m_format(QImage::Format_Invalid),
    m_platformContext(nullptr),
    m_surface(nullptr)
{
    SLM_TRACE_FUNC();
}

//-----------------------------------------------------------------------------

DroidScreen::~DroidScreen()
{
    SLM_TRACE_FUNC();

    DroidContext* eglContext = DroidContext::getInstance();
    eglContext->invalidate();

}

//-----------------------------------------------------------------------------

void DroidScreen::createAndSetPlatformContext() const
{
    const_cast<DroidScreen *>(this)->createAndSetPlatformContext();
}

//-----------------------------------------------------------------------------

void DroidScreen::createAndSetPlatformContext()
{
    SLM_TRACE_FUNC();
    QSurfaceFormat platformFormat;


    ::fwRuntime::profile::Profile::sptr profile = ::fwRuntime::profile::getCurrentProfile();
    EGLNativeWindowType eglWindow = profile->getApp()->window;

    if(eglWindow)
    {
        DroidContext* eglContext = DroidContext::getInstance();
        eglContext->init(eglWindow);
        m_surface = eglContext->getSurface();

        platformFormat.setDepthBufferSize(eglContext->getDepthSize());
        platformFormat.setRedBufferSize(eglContext->getColorSize());
        platformFormat.setGreenBufferSize(eglContext->getColorSize());
        platformFormat.setBlueBufferSize(eglContext->getColorSize());
        m_depth  = eglContext->getDepthSize();
        m_format = QImage::Format_ARGB32;


        QEGLPlatformContext *platformContext = new DroidPlatformContext(platformFormat, 0, eglContext->getDisplay());
        m_platformContext = platformContext;


        OSLM_DEBUG(" w = "<<eglContext->getWidth()<<" h = "<<eglContext->getHeight());
        m_geometry = QRect(0,0,eglContext->getWidth(),eglContext->getHeight());
    }
    else
    {
        SLM_ERROR(" Android native app window is not initialized yet");
    }

}

//-----------------------------------------------------------------------------

QRect DroidScreen::geometry() const
{
    SLM_TRACE_FUNC();
    if (m_geometry.isNull())
    {
        createAndSetPlatformContext();
    }
    return m_geometry;
}

//-----------------------------------------------------------------------------

int DroidScreen::depth() const
{
    SLM_TRACE_FUNC();
    return m_depth;
}

//-----------------------------------------------------------------------------

QImage::Format DroidScreen::format() const
{
    SLM_TRACE_FUNC();
    if (m_format == QImage::Format_Invalid)
    {
        createAndSetPlatformContext();
    }
    return m_format;
}

//-----------------------------------------------------------------------------

QPlatformOpenGLContext *DroidScreen::platformContext() const
{
    SLM_TRACE_FUNC();
    if (!m_platformContext)
    {
        DroidScreen *screen = const_cast<DroidScreen *>(this);
        screen->createAndSetPlatformContext();
    }
    return m_platformContext;
}

//-----------------------------------------------------------------------------

EGLSurface DroidScreen::surface() const
{
    SLM_TRACE_FUNC();
    return m_surface;
}

//-----------------------------------------------------------------------------
