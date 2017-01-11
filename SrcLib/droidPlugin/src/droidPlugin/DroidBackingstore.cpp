/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2016.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#include "droidPlugin/DroidBackingstore.hpp"

#include <QtGui/QOpenGLContext>
#include <QtGui/QOpenGLPaintDevice>

#include <fwServices/macros.hpp>


DroidBackingStore::DroidBackingStore(QWindow *window)
    : QPlatformBackingStore(window)
      , m_context(new QOpenGLContext)
      , m_device(nullptr)
{
    SLM_TRACE_FUNC();
    m_context->setFormat(window->requestedFormat());
    m_context->setScreen(window->screen());
    m_context->create();
}

//--------------------------------------------------------------------------------


DroidBackingStore::~DroidBackingStore()
{
    SLM_TRACE_FUNC();
    delete m_context;
}

//--------------------------------------------------------------------------------

QPaintDevice *DroidBackingStore::paintDevice()
{
    SLM_TRACE_FUNC();
    return m_device;
}

//--------------------------------------------------------------------------------

void DroidBackingStore::flush(QWindow *window, const QRegion &region, const QPoint &offset)
{
    SLM_TRACE_FUNC();
    Q_UNUSED(region);
    Q_UNUSED(offset);

    OSLM_DEBUG("DroidBackingStore::flush "<< window);

    m_context->makeCurrent(window);
    m_context->swapBuffers(window);
}

//--------------------------------------------------------------------------------

void DroidBackingStore::beginPaint(const QRegion &)
{
    SLM_TRACE_FUNC();
    m_context->makeCurrent(window());
    m_device = new QOpenGLPaintDevice(window()->size());
}

//--------------------------------------------------------------------------------

void DroidBackingStore::endPaint()
{
    SLM_TRACE_FUNC();
    delete m_device;
}

//--------------------------------------------------------------------------------

void DroidBackingStore::resize(const QSize &size, const QRegion &staticContents)
{
    SLM_TRACE_FUNC();
    Q_UNUSED(size);
    Q_UNUSED(staticContents);
}

//--------------------------------------------------------------------------------
