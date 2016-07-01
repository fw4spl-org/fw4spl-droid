/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2016.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef __DROIDPLUGIN_DROIDINTEGRATION_HPP__
#define __DROIDPLUGIN_DROIDINTEGRATION_HPP__

#include <qpa/qplatformintegration.h>
#include <qpa/qplatformscreen.h>

class DroidIntegration : public QPlatformIntegration
{

public:
    DroidIntegration();
    ~DroidIntegration();

    bool hasCapability(QPlatformIntegration::Capability cap) const Q_DECL_OVERRIDE;

    QPlatformWindow *createPlatformWindow(QWindow *window) const Q_DECL_OVERRIDE;
    QPlatformBackingStore *createPlatformBackingStore(QWindow *window) const Q_DECL_OVERRIDE;
    QPlatformOpenGLContext *createPlatformOpenGLContext(QOpenGLContext *context) const Q_DECL_OVERRIDE;

    QAbstractEventDispatcher *createEventDispatcher() const Q_DECL_OVERRIDE;
    QPlatformTheme *createPlatformTheme(const QString &name) const Q_DECL_OVERRIDE;

private:

    QPlatformScreen *mScreen;
};

QT_END_NAMESPACE

#endif // __DROIDPLUGIN_DROIDINTEGRATION_HPP__
