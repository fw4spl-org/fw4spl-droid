/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2016.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef __DROIDPLUGIN_DROIDWINDOW_HPP__
#define __DROIDPLUGIN_DROIDWINDOW_HPP__

#include <qpa/qplatformwindow.h>


class DroidWindow : public QPlatformWindow
{

public:
    DroidWindow(QWindow *w);

    void setGeometry(const QRect &rect) Q_DECL_OVERRIDE;
    WId winId() const Q_DECL_OVERRIDE;
    void setParent(const QPlatformWindow *window);
    void propagateSizeHints();

private:
    WId m_winid;
};

#endif // __DROIDPLUGIN_DROIDWINDOW_HPP__
