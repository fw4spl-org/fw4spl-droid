/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2016.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef __DROIDPLUGIN_DROIDBACKINGSTORE_HPP__
#define __DROIDPLUGIN_DROIDBACKINGSTORE_HPP__

#include <qpa/qplatformbackingstore.h>

class QOpenGLContext;
class QOpenGLPaintDevice;

class DroidBackingStore : public QPlatformBackingStore
{

public:
    DroidBackingStore(QWindow *window);
    ~DroidBackingStore();

    QPaintDevice *paintDevice() Q_DECL_OVERRIDE;

    void beginPaint(const QRegion &) Q_DECL_OVERRIDE;
    void endPaint() Q_DECL_OVERRIDE;

    void flush(QWindow *window, const QRegion &region, const QPoint &offset) Q_DECL_OVERRIDE;
    void resize(const QSize &size, const QRegion &staticContents) Q_DECL_OVERRIDE;

private:
    QOpenGLContext *m_context;
    QOpenGLPaintDevice *m_device;
};


#endif // __DROIDPLUGIN_DROIDBACKINGSTORE_HPP__
