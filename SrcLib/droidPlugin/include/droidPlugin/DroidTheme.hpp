/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2016.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef __DROIDPLUGIN_DROIDTHEME_HPP__
#define __DROIDPLUGIN_DROIDTHEME_HPP__

#include <qpa/qplatformtheme.h>
#include <QtGui/qfont.h>
#include <QtGui/qpalette.h>


class DroidTheme : public QPlatformTheme
{
public:
    DroidTheme();
    virtual ~DroidTheme();
    virtual const QPalette *palette(Palette type = SystemPalette) const;
    virtual const QFont *font(Font type = SystemFont) const;
    virtual QVariant themeHint(ThemeHint hint) const;

private:
    QPalette m_defaultPalette;
    QFont m_systemFont;
};

#endif // __DROIDPLUGIN_DROIDTHEME_HPP__
