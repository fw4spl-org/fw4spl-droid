/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2016.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef __DROIDPLUGIN_DROIDCONTEXT_HPP__
#define __DROIDPLUGIN_DROIDCONTEXT_HPP__

#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <android/log.h>


/**
 * @brief OpenGL context handler
 * The class handles OpenGL and EGL context based on Android activity life cycle
 * The caller needs to call corresponding methods for each activity life cycle
 * events as it's done in sample codes.
 *
 * Also the class initializes OpenGL ES3 when the compatible driver is installed
 * in the device.
 * getGLVersion() returns 3.0~ when the device supports OpenGLES3.0
 *
 * Thread safety: OpenGL context is expecting used within dedicated single
 * thread,
 * thus GLContext class is not designed as a thread-safe
 */
class DroidContext
{

public:
    static DroidContext *getInstance()
    {
        //Singleton
        static DroidContext instance;
        return &instance;
    }

    bool init(ANativeWindow *window, const int32_t msaa = 1);
    EGLint swap();
    bool invalidate();

    void suspend();
    EGLint resume(ANativeWindow *window);

    int32_t getWidth()
    {
        return m_width;
    }
    int32_t getHeight()
    {
        return m_height;
    }

    int32_t getColorSize()
    {
        return m_colorSize;
    }
    int32_t getDepthSize()
    {
        return m_depthSize;
    }
    int32_t getMSAASize()
    {
        return m_msaaSize;
    }

    float getGLVersion()
    {
        return m_glVersion;
    }
    bool checkExtension(const char *extension);

    EGLSurface getSurface()
    {
        return m_surface;
    }
    EGLDisplay getDisplay()
    {
        return m_display;
    }

    /*
     * Set SwapInterval to EGL context
     * SwapInterval:1 indicates that frame rate is synchronous to vblank interval
     * which is usually 59.94hz.
     * In API 17 (JellyBeans)~, the API accepts value of 0, which does not sync to
     * vblank.
     * This mode is useful while performance tuning.
     */
    void setSwapInterval(const int32_t interval)
    {
        eglSwapInterval(m_display, interval);
        m_swapInterval = interval;
    }

private:
    //EGL configurations
    ANativeWindow *m_window;
    EGLDisplay m_display;
    EGLSurface m_surface;
    EGLContext m_context;
    EGLConfig m_config;

    //Screen parameters
    int32_t m_width;
    int32_t m_height;
    int32_t m_colorSize;
    int32_t m_depthSize;
    int32_t m_msaaSize;

    //EGL Swap interval
    bool m_restoreInterval;
    int32_t m_swapInterval;

    //Flags
    bool m_glesInitialized;
    bool m_eglContextInitialized;
    float m_glVersion;
    bool m_contextValid;

    void initGLES();
    void terminate();
    bool initEGLSurface();
    bool initEGLContext();

    DroidContext(DroidContext const &);
    void operator=(DroidContext const &);
    DroidContext();
    virtual ~DroidContext();

};

#endif /* __DROIDPLUGIN_DROIDCONTEXT_HPP__ */
