/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2016.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#include "droidPlugin/DroidTheme.hpp"
#include <QApplication>

#include <QVariant>
#include <QPalette>
#include <QStyleFactory>

#include <fwServices/macros.hpp>

#include <private/qguiapplication_p.h>

//-----------------------------------------------------------------------------

DroidTheme::DroidTheme()
{
    QApplication::setStyle(QStyleFactory::create("Fusion"));

    QColor background(229, 229, 229);
    QColor light = background.lighter(150);
    QColor mid(background.darker(130));
    QColor midLight = mid.lighter(110);
    QColor base(249, 249, 249);
    QColor disabledBase(background);
    QColor dark            = background.darker(150);
    QColor darkDisabled    = dark.darker(110);
    QColor text            = Qt::black;
    QColor highlightedText = Qt::black;
    QColor disabledText    = QColor(190, 190, 190);
    QColor button(241, 241, 241);
    QColor shadow(201, 201, 201);
    QColor highlight(148, 210, 231);
    QColor disabledShadow = shadow.lighter(150);

    m_defaultPalette = QPalette(Qt::black,background,light,dark,mid,text,base);
    m_defaultPalette.setBrush(QPalette::Midlight, midLight);
    m_defaultPalette.setBrush(QPalette::Button, button);
    m_defaultPalette.setBrush(QPalette::Shadow, shadow);
    m_defaultPalette.setBrush(QPalette::HighlightedText, highlightedText);

    m_defaultPalette.setBrush(QPalette::Disabled, QPalette::Text, disabledText);
    m_defaultPalette.setBrush(QPalette::Disabled, QPalette::WindowText, disabledText);
    m_defaultPalette.setBrush(QPalette::Disabled, QPalette::ButtonText, disabledText);
    m_defaultPalette.setBrush(QPalette::Disabled, QPalette::Base, disabledBase);
    m_defaultPalette.setBrush(QPalette::Disabled, QPalette::Dark, darkDisabled);
    m_defaultPalette.setBrush(QPalette::Disabled, QPalette::Shadow, disabledShadow);

    m_defaultPalette.setBrush(QPalette::Active, QPalette::Highlight, highlight);
    m_defaultPalette.setBrush(QPalette::Inactive, QPalette::Highlight, highlight);
    m_defaultPalette.setBrush(QPalette::Disabled, QPalette::Highlight, highlight.lighter(150));
    QApplication::setPalette(m_defaultPalette);


    // default in case the style has not set a font
    setenv("QT_QPA_FONTDIR","/system/fonts",false);
    m_systemFont = QFont(QLatin1String("Roboto"), 14.0 * 100 / 72); // keep default size the same after changing from 100 dpi to 72 dpi
    QApplication::setFont(m_systemFont);
}

//-----------------------------------------------------------------------------

DroidTheme::~DroidTheme()
{
    //----
}

//-----------------------------------------------------------------------------

static inline int paletteType(QPlatformTheme::Palette type)
{
    switch (type)
    {
        case QPlatformTheme::ToolButtonPalette:
        case QPlatformTheme::ButtonPalette:
            return QPlatformTheme::ButtonPalette;

        case QPlatformTheme::CheckBoxPalette:
            return QPlatformTheme::CheckBoxPalette;

        case QPlatformTheme::RadioButtonPalette:
            return QPlatformTheme::RadioButtonPalette;

        case QPlatformTheme::ComboBoxPalette:
            return QPlatformTheme::ComboBoxPalette;

        case QPlatformTheme::TextEditPalette:
        case QPlatformTheme::TextLineEditPalette:
            return QPlatformTheme::TextLineEditPalette;

        case QPlatformTheme::ItemViewPalette:
            return QPlatformTheme::ItemViewPalette;

        default:
            return QPlatformTheme::SystemPalette;
    }
}

//-----------------------------------------------------------------------------

const QPalette *DroidTheme::palette(Palette type) const
{
    return &m_defaultPalette;
}

//-----------------------------------------------------------------------------

static inline int fontType(QPlatformTheme::Font type)
{
    switch (type)
    {
        case QPlatformTheme::LabelFont:
            return QPlatformTheme::SystemFont;

        case QPlatformTheme::ToolButtonFont:
            return QPlatformTheme::PushButtonFont;

        default:
            return type;
    }
}

//-----------------------------------------------------------------------------

const QFont *DroidTheme::font(Font type) const
{
    if (type == QPlatformTheme::SystemFont)
    {
        return &m_systemFont;
    }
    return 0;
}

//-----------------------------------------------------------------------------

QVariant DroidTheme::themeHint(ThemeHint hint) const
{
    return QStringList("android");
}

//-----------------------------------------------------------------------------


