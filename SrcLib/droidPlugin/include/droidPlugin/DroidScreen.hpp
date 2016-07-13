/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2016.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef __DROIDPLUGIN_DROIDSCREEN_HPP__
#define __DROIDPLUGIN_DROIDSCREEN_HPP__

#include "droidPlugin/DroidContext.hpp"


//Qt
#include <QtCore/QTextStream>

// Internal Qt
#include <qpa/qplatformscreen.h>
#include <QtPlatformSupport/private/qeglplatformscreen_p.h>
#include <EGL/egl.h>
#include <GLES2/gl2.h>

#include <android_native_app_glue.h>

class QPlatformOpenGLContext;

class DroidScreen : public QEGLPlatformScreen
{

public:
    DroidScreen(EGLNativeDisplayType display);
    ~DroidScreen();

    QRect geometry() const Q_DECL_OVERRIDE;
    int depth() const Q_DECL_OVERRIDE;
    QImage::Format format() const Q_DECL_OVERRIDE;

    QPlatformOpenGLContext *platformContext() const;

    EGLSurface surface() const;

private:
    void createAndSetPlatformContext() const;
    void createAndSetPlatformContext();

    QRect m_geometry;
    int m_depth;
    QImage::Format m_format;
    QPlatformOpenGLContext *m_platformContext;
    EGLDisplay m_dpy;
    EGLSurface m_surface;
};

#endif // __DROIDPLUGIN_DROIDSCREEN_HPP__
