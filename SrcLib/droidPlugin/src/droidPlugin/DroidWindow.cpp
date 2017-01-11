/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2016.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#include "droidPlugin/DroidWindow.hpp"

#include "droidPlugin/DroidIntegration.hpp"
#include "droidPlugin/DroidScreen.hpp"

#include <fwServices/macros.hpp>

// Internal Qt
#include <qpa/qwindowsysteminterface.h>

DroidWindow::DroidWindow(QWindow *w)
    : QPlatformWindow(w)
{
    SLM_TRACE_FUNC();
    static int serialNo = 0;
    m_winid = ++serialNo;

    QRect screenGeometry(screen()->availableGeometry());
    OSLM_DEBUG(" screenGeometry: "<<screenGeometry.width()<<" , "<<screenGeometry.height());
    SLM_TRACE_FUNC();
    if (w->geometry() != screenGeometry)
    {
        QWindowSystemInterface::handleGeometryChange(w, screenGeometry);
    }
    w->setSurfaceType(QSurface::OpenGLSurface);

}

//-----------------------------------------------------------------------------

void DroidWindow::setGeometry(const QRect &)
{
    SLM_TRACE_FUNC();
    // We only support full-screen windows
    QRect rect(screen()->availableGeometry());
    OSLM_DEBUG(" screenGeometry: "<<rect.width()<<" , "<<rect.height());

    QWindowSystemInterface::handleGeometryChange(window(), rect);
    QPlatformWindow::setGeometry(rect);
}

WId DroidWindow::winId() const
{
    SLM_TRACE_FUNC();
    return m_winid;
}

//-----------------------------------------------------------------------------

void DroidWindow::setParent(const QPlatformWindow *window)
{
    Q_UNUSED(window);
}

//-----------------------------------------------------------------------------

void DroidWindow::propagateSizeHints()
{
    //shut up warning from default implementation
}

//-----------------------------------------------------------------------------
