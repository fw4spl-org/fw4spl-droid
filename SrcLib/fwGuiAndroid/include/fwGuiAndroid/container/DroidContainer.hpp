/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2015.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef __FWGUIANDROID_CONTAINER_DROIDCONTAINER_HPP__
#define __FWGUIANDROID_CONTAINER_DROIDCONTAINER_HPP__

#include "fwGuiAndroid/config.hpp"

#include <fwCore/base.hpp>
#include <fwTools/Object.hpp>

#include <fwGui/container/fwContainer.hpp>


namespace fwGuiAndroid
{
namespace container
{

/**
 * @brief   Defines the android container for IHM.
 */
class FWGUIANDROID_CLASS_API DroidContainer : public ::fwGui::container::fwContainer
{

public:

    fwCoreClassDefinitionsWithFactoryMacro( (DroidContainer)(::fwGui::container::fwContainer),
                                            (()),
                                            ::fwGui::factory::New< DroidContainer > );

    FWGUIANDROID_API DroidContainer(::fwGui::GuiBaseObject::Key key) throw();

    FWGUIANDROID_API virtual ~DroidContainer() throw();


    FWGUIANDROID_API virtual void clean();
    FWGUIANDROID_API virtual void destroyContainer();

    FWGUIANDROID_API virtual bool isShownOnScreen();

    FWGUIANDROID_API virtual void setVisible(bool isVisible);
};

} // namespace container
} // namespace fwGuiAndroid

#endif /*__FWGUIANDROID_CONTAINER_DROIDCONTAINER_HPP__*/
