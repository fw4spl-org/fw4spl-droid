/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2014-2016.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef __VISUVIDEOANDROID_CAMERA_SANDROIDCAMERA_HPP__
#define __VISUVIDEOANDROID_CAMERA_SANDROIDCAMERA_HPP__

#include <string>

#include <fwTools/Failed.hpp>
#include <fwServices/IService.hpp>

#include <fwCom/Slot.hpp>
#include <fwCom/Slots.hpp>

#include <fwCom/Signal.hpp>
#include <fwCom/Signals.hpp>

#include <arAndroidTools/Camera.hpp>

#include <extData/FrameTL.hpp>

#include "visuVideoAndroid/config.hpp"


namespace visuVideoAndroid
{
namespace camera
{

class VISUVIDEOANDROID_CLASS_API SAndroidCamera : public ::fwServices::IService
{

public:

    fwCoreServiceClassDefinitionsMacro ( (SAndroidCamera)(::fwServices::IService) );

    VISUVIDEOANDROID_API SAndroidCamera() throw();
    VISUVIDEOANDROID_API virtual ~SAndroidCamera() throw();

    VISUVIDEOANDROID_API static const ::fwCom::Signals::SignalKeyType s_CAMERA_OPENED_SIG;
    typedef ::fwCom::Signal<void (int,int,int)> CameraOpenedSignalType;

    VISUVIDEOANDROID_API static const ::fwCom::Slots::SlotKeyType s_START_CAMERA_SLOT;

protected:

    VISUVIDEOANDROID_API virtual void configuring() throw( ::fwTools::Failed );
    VISUVIDEOANDROID_API virtual void starting() throw(::fwTools::Failed);
    VISUVIDEOANDROID_API virtual void stopping() throw(::fwTools::Failed);
    VISUVIDEOANDROID_API virtual void updating() throw(::fwTools::Failed);
    VISUVIDEOANDROID_API virtual void info(std::ostream &_sstream );

private:

    void startCamera(bool state = true);
    void fetchFrame(unsigned char* rgb);

    unsigned int m_cameraId;

    int m_width;
    int m_height;
    int m_frameRate;

    bool m_autoFocus;
    bool m_camIsStarted;

    ::extData::FrameTL::sptr m_timeline;

    CameraOpenedSignalType::sptr m_sigCameraOpened;

    ::arAndroidTools::Camera* m_camera;
};

} //camera
} //visuVideoAndroid

#endif /*__VISUVIDEOANDROID_CAMERA_SANDROIDCAMERA_HPP__*/
