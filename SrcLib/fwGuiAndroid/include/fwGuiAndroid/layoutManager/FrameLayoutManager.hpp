/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2015.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef __FWGUIANDROID_LAYOUTMANAGER_FRAMELAYOUTMANAGER_HPP__
#define __FWGUIANDROID_LAYOUTMANAGER_FRAMELAYOUTMANAGER_HPP__

#include "fwGuiAndroid/config.hpp"
#include "fwGuiAndroid/container/DroidContainer.hpp"

#include <fwCore/base.hpp>

#include <fwGui/layoutManager/IFrameLayoutManager.hpp>

namespace fwGui
{

/**
 * @brief   Defines the android frame manager.
 */
class FWGUIANDROID_CLASS_API FrameLayoutManager : public ::fwGui::layoutManager::IFrameLayoutManager
{

public:

    fwCoreClassDefinitionsWithFactoryMacro( (FrameLayoutManager)(::fwGui::layoutManager::IFrameLayoutManager),
                                            (()),
                                            ::fwGui::factory::New< FrameLayoutManager > );

    FWGUIANDROID_API FrameLayoutManager(::fwGui::GuiBaseObject::Key key);

    FWGUIANDROID_API virtual ~FrameLayoutManager();

    /**
     * @brief Instantiate frame.
     */
    FWGUIANDROID_API virtual void createFrame();

    /**
     * @brief Destroy local frame with sub containers.
     */
    FWGUIANDROID_API virtual void destroyFrame();

};

} // namespace fwGui

#endif /*__FWGUIANDROID_LAYOUTMANAGER_FRAMELAYOUTMANAGER_HPP__*/
