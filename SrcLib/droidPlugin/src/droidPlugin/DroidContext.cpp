/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2016.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#include "droidPlugin/DroidContext.hpp"

#include <fwServices/macros.hpp>

//--------------------------------------------------------------------------------

const int32_t SWAPINTERVAL_DEFAULT = 1;

//--------------------------------------------------------------------------------

DroidContext::DroidContext() :
    m_window(nullptr),
    m_display(EGL_NO_DISPLAY),
    m_surface(EGL_NO_SURFACE),
    m_context(EGL_NO_CONTEXT),
    m_width(0),
    m_height(0),
    m_msaaSize(1),
    m_restoreInterval(false),
    m_swapInterval(SWAPINTERVAL_DEFAULT),
    m_glesInitialized(false),
    m_eglContextInitialized(false),
    m_glVersion(0),
    m_contextValid(false)
{
    SLM_TRACE_FUNC();
    //----
}

//--------------------------------------------------------------------------------

void DroidContext::initGLES()
{
    SLM_TRACE_FUNC();
    if (m_glesInitialized)
    {
        return;
    }

    m_glVersion       = 3.0f;
    m_glesInitialized = true;
}

//--------------------------------------------------------------------------------

DroidContext::~DroidContext()
{
    terminate();
}

//--------------------------------------------------------------------------------

bool DroidContext::init(ANativeWindow *window, const int32_t msaa)
{
    SLM_TRACE_FUNC();
    if (m_glesInitialized)
    {
        return true;
    }

    //
    //Initialize EGL
    //
    m_window   = window;
    m_msaaSize = msaa;
    initEGLSurface();
    initGLES();

    m_glesInitialized = true;

    return true;

}

//--------------------------------------------------------------------------------

bool DroidContext::initEGLSurface()
{
    // This could be replaced by the egl helper from the ndk
    SLM_TRACE_FUNC();
    m_display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    eglInitialize(m_display, 0, 0);

    /*
     * Here specify the attributes of the desired configuration.
     * Below, we select an EGLConfig with at least 8 bits per color
     * component compatible with on-screen windows
     */
    const EGLint attribs[] = {
        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT, //Request opengl ES2.0
        EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
        EGL_BLUE_SIZE, 8,
        EGL_GREEN_SIZE, 8,
        EGL_RED_SIZE, 8,
        EGL_DEPTH_SIZE,24,
        EGL_SAMPLES, m_msaaSize,
        EGL_NONE
    };

    m_colorSize = 8;
    m_depthSize = 24;


    EGLint num_configs;
    eglChooseConfig(m_display, attribs, &m_config, 1, &num_configs);

    if (m_msaaSize > 1 && !num_configs)
    {
        SLM_WARN("No EGL config with MSAA");
        //Fall back to non MSAA
        const EGLint attribs[] = {
            EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT, //Request opengl ES2.0
            EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
            EGL_BLUE_SIZE, 8,
            EGL_GREEN_SIZE, 8,
            EGL_RED_SIZE, 8,
            EGL_DEPTH_SIZE, 24,
            EGL_NONE
        };

        m_msaaSize = 1;
        eglChooseConfig(m_display, attribs, &m_config, 1, &num_configs);
    }

    if (!num_configs)
    {
        SLM_WARN("No 24bit depth buffer");

        //Fall back to 16bit depth buffer
        const EGLint attribs[] = {
            EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT, //Request opengl ES2.0
            EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
            EGL_BLUE_SIZE, 8,
            EGL_GREEN_SIZE, 8,
            EGL_RED_SIZE, 8,
            EGL_DEPTH_SIZE, 16,
            EGL_NONE
        };

        eglChooseConfig(m_display, attribs, &m_config, 1, &num_configs);
        m_depthSize = 16;
    }

    if (!num_configs)
    {
        SLM_WARN("Unable to retrieve EGL config");
        return false;
    }

    m_surface = eglCreateWindowSurface(m_display, m_config, m_window, NULL);
    eglQuerySurface(m_display, m_surface, EGL_WIDTH, &m_width);
    eglQuerySurface(m_display, m_surface, EGL_HEIGHT, &m_height);

    /* EGL_NATIVE_VISUAL_ID is an attribute of the EGLConfig that is
    * guaranteed to be accepted by ANativeWindow_setBuffersGeometry().
    * As soon as we picked a EGLConfig, we can safely reconfigure the
    * ANativeWindow buffers to match, using EGL_NATIVE_VISUAL_ID. */
    EGLint format;
    eglGetConfigAttrib( m_display, m_config, EGL_NATIVE_VISUAL_ID, &format );
    ANativeWindow_setBuffersGeometry( m_window, 0, 0, format );

    return true;
}

//--------------------------------------------------------------------------------

bool DroidContext::initEGLContext()
{
    SLM_TRACE_FUNC();
    const EGLint context_attribs[] = {
        EGL_CONTEXT_CLIENT_VERSION, 2, //Request opengl ES2.0
        EGL_NONE
    };

    m_context = eglCreateContext(m_display, m_config, NULL, context_attribs);

    if (eglMakeCurrent(m_display, m_surface, m_surface, m_context) == EGL_FALSE)
    {
        SLM_WARN("Unable to eglMakeCurrent");
        return false;
    }

    m_contextValid = true;
    return true;
}

//--------------------------------------------------------------------------------

EGLint DroidContext::swap()
{
    SLM_TRACE_FUNC();
    bool swapTest = eglSwapBuffers(m_display, m_surface);
    if (!swapTest)
    {
        EGLint error = eglGetError();
        if (error == EGL_BAD_SURFACE)
        {
            //Recreate surface
            initEGLSurface();
            error = EGL_SUCCESS; //Still consider QMinimalGLContext is valid
        }
        else if (error == EGL_CONTEXT_LOST || error == EGL_BAD_CONTEXT)
        {
            //Context has been lost!!
            m_contextValid = false;
            terminate();
            initEGLContext();
        }

        return error;
    }
    if (m_restoreInterval && m_swapInterval != SWAPINTERVAL_DEFAULT)
    {
        eglSwapInterval(m_display, m_swapInterval); //Restore Swap interval
    }
    return EGL_SUCCESS;
}

//--------------------------------------------------------------------------------

void DroidContext::terminate()
{
    SLM_TRACE_FUNC();
    if (m_display != EGL_NO_DISPLAY)
    {
        eglMakeCurrent(m_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);

        if (m_context != EGL_NO_CONTEXT)
        {
            eglDestroyContext(m_display, m_context);
        }

        if (m_surface != EGL_NO_SURFACE)
        {
            eglDestroySurface(m_display, m_surface);
        }
        eglTerminate(m_display);
    }

    m_display      = EGL_NO_DISPLAY;
    m_context      = EGL_NO_CONTEXT;
    m_surface      = EGL_NO_SURFACE;
    m_contextValid = false;

}

//--------------------------------------------------------------------------------

EGLint DroidContext::resume(ANativeWindow *window)
{
    SLM_TRACE_FUNC();
    if (m_eglContextInitialized == false)
    {
        init(window, m_msaaSize);
        return EGL_SUCCESS;
    }

    int32_t original_width  = m_width;
    int32_t original_height = m_height;

    //Create surface
    m_window  = window;
    m_surface = eglCreateWindowSurface(m_display, m_config, m_window, NULL);
    eglQuerySurface(m_display, m_surface, EGL_WIDTH, &m_width);
    eglQuerySurface(m_display, m_surface, EGL_HEIGHT, &m_height);

    if (m_width != original_width || m_height != original_height)
    {
        //Screen resized
        SLM_INFO("Screen resized");
    }

    if (eglMakeCurrent(m_display, m_surface, m_surface, m_context) == EGL_TRUE)
    {
        return EGL_SUCCESS;
    }

    EGLint error = eglGetError();
    OSLM_ERROR("Unable to eglMakeCurrent "<< error);

    if (error == EGL_CONTEXT_LOST)
    {
        //Recreate context
        SLM_INFO("Re-creating egl context");
        initEGLContext();
    }
    else
    {
        //Recreate surface
        terminate();
        initEGLSurface();
        initEGLContext();
    }

    return error;
}

//--------------------------------------------------------------------------------

void DroidContext::suspend()
{
    SLM_TRACE_FUNC();
    if (m_surface != EGL_NO_SURFACE)
    {
        eglDestroySurface(m_display, m_surface);
        m_surface = EGL_NO_SURFACE;
    }
    m_restoreInterval = true;
}

bool DroidContext::invalidate()
{
    SLM_TRACE_FUNC();
    terminate();

    m_eglContextInitialized = false;
    return true;
}

//--------------------------------------------------------------------------------

bool DroidContext::checkExtension(const char *extension)
{
    SLM_TRACE_FUNC();
    if (extension == NULL)
    {
        return false;
    }

    std::string extensions = std::string((char *)glGetString(GL_EXTENSIONS));
    std::string str        = std::string(extension);
    str.append(" ");

    size_t pos = 0;
    if (extensions.find(extension, pos) != std::string::npos)
    {
        return true;
    }

    return false;
}

//--------------------------------------------------------------------------------
