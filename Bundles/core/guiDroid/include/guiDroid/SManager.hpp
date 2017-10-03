/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2014-2017.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef __GUIDROID_SMANAGER_HPP__
#define __GUIDROID_SMANAGER_HPP__

#include "guiDroid/config.hpp"

#include <fwServices/IService.hpp>

#include <JUIView.h>

namespace guiDroid
{

struct WidgetConfig
{
    enum Type
    {
        TYPE_BUTTON = 0,
        TYPE_TEXTVIEW,
        TYPE_COUNT
    };

    WidgetConfig() :
        m_label(""),
        m_textSize(10.f),
        m_margins{40, 40, 40, 40},
        m_width(0),
        m_height(0),
        m_type(TYPE_COUNT)
    {

    }

    std::string m_label;                         ///< button label.
    std::pair<std::string, std::string>  m_slotPair;

    float m_textSize;

    int m_margins[4];
    int m_width;
    int m_height;

    Type m_type;
    ndkGui::LayoutParameterType m_vAlign;
    ndkGui::LayoutParameterType m_hAlign;

};

struct WidgetData
{

    WidgetData() :
        m_state(true)
    {

    }
    ::fwCom::SlotBase::sptr m_slot;
    bool m_state;
    WidgetConfig m_config;
};

/**
 * @brief   Description of the class.
 */
class GUIDROID_CLASS_API SManager : public ::fwServices::IService
{

public:

    fwCoreServiceClassDefinitionsMacro( (SManager)(::fwServices::IService) );

    /// Constructor.
    GUIDROID_API SManager() noexcept;

    /// Destructor. Does nothing
    GUIDROID_API virtual ~SManager() noexcept;

protected:

    /**
     * @brief method description:
     * @code{.xml}
        <service uid="SManagerInstance" impl="::guiDroid::SManager" type="::fwServices::IService">
        <gui>
             <widget sid="readerButton" type="button" label="load" align="top|left" >
                <width>100</width>
                <height>50</height>
                <margins>40,40,40,40</margins>
                <slot>meshReader/update</slot>
            </widget>

        </gui>
        </service>]
       @endcode
     * - \b layout : layout definition and attributes.
     * - \b widget : widget definition and attributes.
     */
    GUIDROID_API virtual void configuring() override;

    /// FILL ME.
    GUIDROID_API virtual void starting() override;

    /// FILL ME.
    GUIDROID_API virtual void stopping() override;

    /// FILL ME.
    GUIDROID_API virtual void updating() override;

private:

    std::vector< WidgetData* > m_widgets;
};

} // guiDroid

#endif // __GUIDROID_SMANAGER_HPP__
