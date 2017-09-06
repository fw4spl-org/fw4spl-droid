/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2016.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef __UIDROIDQT_SORGANMATERIALEDITOR_HPP__
#define __UIDROIDQT_SORGANMATERIALEDITOR_HPP__

#include "uiDroidQt/config.hpp"

#include <gui/editor/IEditor.hpp>

#include <QObject>
#include <QPointer>

#include <fwCom/Signal.hpp>
#include <fwCom/Signals.hpp>

#include <fwData/Object.hpp>

#include <fwTools/Failed.hpp>
#include <fwServices/IService.hpp>

class QButtonGroup;
class QPushButton;
class QSlider;

namespace uiDroidQt
{
/**
 * @brief   This editor regulates the position and rotation defined in a transformation matrix.
 * @section XML XML Configuration
 *
 * @code{.xml}
    <service uid="..." impl="::uiDroidQt::SOrganMaterialEditor" type="::gui::editor::IEditor" autoConnect="no">
        <organ>Liver</organ>
    </service>
   @endcode
 *
 * @subsection In-Out In-Out
 * - \b organ : name of the organ to work on
 */
class UIDROIDQT_CLASS_API SOrganMaterialEditor : public QObject,
                                                 public ::gui::editor::IEditor
{
Q_OBJECT;
public:

    fwCoreServiceClassDefinitionsMacro ( (SOrganMaterialEditor)(::gui::editor::IEditor) );

    /**
     * @brief Constructor.
     */
    UIDROIDQT_API SOrganMaterialEditor() noexcept;

    /**
     * @brief Destructor.
     */
    UIDROIDQT_API ~SOrganMaterialEditor() noexcept;

protected:

    ///nothing
    UIDROIDQT_API void configuring();

    /**
     * @brief Starting method : This method is used to initialize the service.
     */
    UIDROIDQT_API void starting();

    /**
     * @brief Stopping method : This method is used to stop the service.
     */
    UIDROIDQT_API void stopping();

    /**
     * @brief Updating method : This method is used to update the service.
     */
    UIDROIDQT_API void updating();

private:

    void changeOpacity( int _iValue = 50);


    QPointer<QSlider>   m_opacitySlider;
    QString m_organName;
};

} // namespace uiDroidQt

#endif // __UIDROIDQT_SORGANMATERIALEDITOR_HPP__
