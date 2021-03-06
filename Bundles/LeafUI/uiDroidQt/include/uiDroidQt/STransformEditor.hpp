/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2016-2017.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef __UIDROIDQT_STRANSFORMEDITOR_HPP__
#define __UIDROIDQT_STRANSFORMEDITOR_HPP__

#include "uiDroidQt/config.hpp"

#include <fwCom/Signal.hpp>
#include <fwCom/Signals.hpp>

#include <fwData/Object.hpp>

#include <fwServices/IService.hpp>

#include <fwTools/Failed.hpp>

#include <gui/editor/IEditor.hpp>

#include <QObject>
#include <QPointer>

class QButtonGroup;
class QPushButton;

namespace uiDroidQt
{
/**
 * @brief   This editor regulates the position and rotation defined in a transformation matrix.
 * @section XML XML Configuration
 *
 * @code{.xml}
    <service uid="..." type="::uiDroidQt::STransformEditor" autoConnect="no">
        <inout key="matrix" uid="..."/>
    </service>
   @endcode
 *
 * @subsection In-Out In-Out
 * - \b matrix [::fwData::TransformationMatrix3D]: matrix modified by the editor
 */
class UIDROIDQT_CLASS_API STransformEditor : public QObject,
                                             public ::gui::editor::IEditor
{
Q_OBJECT;
public:

    fwCoreServiceClassDefinitionsMacro( (STransformEditor)(::gui::editor::IEditor) );

    /**
     * @brief Constructor.
     */
    UIDROIDQT_API STransformEditor() noexcept;

    /**
     * @brief Destructor.
     */
    UIDROIDQT_API ~STransformEditor() noexcept;

protected:

    ///nothing
    UIDROIDQT_API void configuring() override;

    /**
     * @brief Starting method : This method is used to initialize the service.
     */
    UIDROIDQT_API void starting() override;

    /**
     * @brief Stopping method : This method is used to stop the service.
     */
    UIDROIDQT_API void stopping() override;

    /**
     * @brief Updating method : This method is used to update the service.
     */
    UIDROIDQT_API void updating() override;

protected Q_SLOTS:
    void onChangeAxis(int axis);

private:
    void onIncrement();

    void onDecrement();

    std::string m_selectedAxis;
    int m_increment;

    QPointer <QButtonGroup> m_buttonGroupAxis;
    QPointer <QPushButton> m_buttonIncr;
    QPointer <QPushButton> m_buttonDecr;

    /// Signal emitted when button is pushed
    typedef ::fwCom::Signal< void (std::string, int) > IncrSignalType;
    IncrSignalType::sptr m_sigIncremented;
};

} // namespace uiDroidQt

#endif // __UIDROIDQT_STRANSFORMEDITOR_HPP__
