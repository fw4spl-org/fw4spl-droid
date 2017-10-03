/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2014-2017.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef __UIDROID_SBUTTON_HPP__
#define __UIDROID_SBUTTON_HPP__

#include "uiDroid/config.hpp"

#include <fwCom/Signal.hpp>
#include <fwCom/Signals.hpp>

#include <fwData/Object.hpp>

#include <fwServices/IService.hpp>

#include <fwTools/Failed.hpp>

namespace uiDroid
{
/**
 * @brief   SButton service allows to set a simple button in an android app
 *
 * Service registered details : \n
 * fwServicesRegisterMacro(::fwServices::IService, ::SButton::SButton, ::fwData::Object)
 */
class UIDROID_CLASS_API SButton : public ::fwServices::IService
{

public:
    fwCoreServiceClassDefinitionsMacro((SButton)(::fwServices::IService));

    /**
     * @name Signals API
     * @{
     */
    ///@}

    /**
     * @brief Constructor.
     */
    UIDROID_API SButton() noexcept;

    /**
     * @brief Destructor.
     */
    UIDROID_API ~SButton() noexcept;

    ///nothing
    UIDROID_API void configuring() override;

    /**
     * @brief Starting method : This method is used to initialize the service.
     */
    UIDROID_API void starting() override;

    /**
     * @brief Stopping method : This method is used to stop the service.
     */
    UIDROID_API void stopping() override;

    /**
     * @brief Updating method : This method is used to update the service.
     */
    UIDROID_API void updating() override;

protected:

    ///
    void onClicked();

    static const int UI_BUTTON_COUNT = 2;

private:

    std::string m_label; ///< button label.
    bool m_boolState;

    std::pair<std::string, std::string>  m_slotPair;
    ::fwCom::SlotBase::sptr m_slot;

};
} // namespace uiDroid

#endif // __UIDROID_SBUTTON_HPP__
