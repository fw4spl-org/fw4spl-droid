/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2014-2016.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef __DROIDTOOLS_STRANSFORMMANAGER_HPP__
#define __DROIDTOOLS_STRANSFORMMANAGER_HPP__

#include "droidTools/config.hpp"

#include <fwServices/IController.hpp>

namespace droidTools
{
/**
 * @brief   This tools update translation of transformation matrix.
 */

class DROIDTOOLS_CLASS_API STransformManager : public ::fwServices::IController
{
public:
    fwCoreServiceClassDefinitionsMacro ( (STransformManager)(::fwServices::IController) );

    DROIDTOOLS_API static const ::fwCom::Slots::SlotKeyType s_INCREMENT_SLOT;

    /// Constructor. Do nothing.
    DROIDTOOLS_API STransformManager() noexcept;

    /// Destructor. Do nothing.
    DROIDTOOLS_API virtual ~STransformManager() noexcept;


protected:

    /**
     * @code{.xml}
       <service uid="..." impl="::droidTools::STransformManager" autoConnect="yes"/>
       @endcode
     */

    DROIDTOOLS_API virtual void configuring();

    ///This method launches the ::fwGui::IGuiContainerSrv::create method.
    DROIDTOOLS_API virtual void starting();

    ///This method launches the ::fwGui::IGuiContainerSrv::destroy method.
    DROIDTOOLS_API virtual void stopping();

    /// Updates Slider value
    DROIDTOOLS_API virtual void updating();

private:

    void increment(std::string axis,int value);

    int m_tx;
    int m_ty;
    int m_tz;

};

} // namespace droidTools

#endif // __DROIDTOOLS_STRANSFORMMANAGER_HPP__
