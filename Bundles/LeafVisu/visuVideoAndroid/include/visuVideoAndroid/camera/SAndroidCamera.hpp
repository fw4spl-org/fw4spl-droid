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
/**
 * @brief SAndroidCamera service handle the camera on Android platform.
 *
 * @section Signals Signals
 * - \b cameraOpened(int format,int width,int height) : Emitted when the android camera is openned.
 *
 * @section Slots Slots
 * - \b startOrStop(bool state) : if state = true the camera will be started, else the camera will be stopped.
 * - \b startCamera() : Start the camera.
 * - \b stopCamera() : Stop the camera.
 *
 * @section XML XML Configuration
 *
 * @code{.xml}
        <service type="::visuVideoAndroid::camera::SAndroidCamera">
            <inout key="frameTL" uid="frameTL" />
            <cameraId>0</cameraId>
            <autoFocus>true</autoFocus>
            <width>640</width>
            <height>480</height>
            <fps>60</fps>
       </service>
   @endcode
 *
 * @subsection In-Out In-Out
 * - \b frameTL [::extData::FrameTL]: Timeline used to register frames.
 *
 * @subsection Configuration Configuration
 * - \b cameraId defines the android ID of the camera (usualy 0 is the back camera, and 1 the front one).
 * - \b autoFocus defines if the autofocus is enable or not.
 * - \b width defines the width resolution.
 * - \b height defines the height resolution.
 * - \b fps defines the desired framerate.
 */
class VISUVIDEOANDROID_CLASS_API SAndroidCamera : public ::fwServices::IService
{

public:

    fwCoreServiceClassDefinitionsMacro ( (SAndroidCamera)(::fwServices::IService) );

    VISUVIDEOANDROID_API SAndroidCamera() noexcept;
    VISUVIDEOANDROID_API virtual ~SAndroidCamera() noexcept;

    VISUVIDEOANDROID_API static const ::fwCom::Signals::SignalKeyType s_CAMERA_OPENED_SIG;
    typedef ::fwCom::Signal<void (int,int,int)> CameraOpenedSignalType;

protected:

    VISUVIDEOANDROID_API virtual void configuring();
    VISUVIDEOANDROID_API virtual void starting();
    VISUVIDEOANDROID_API virtual void stopping();
    VISUVIDEOANDROID_API virtual void updating();
    VISUVIDEOANDROID_API virtual void info(std::ostream &_sstream );

private:

    void startOrStop(bool state = true);
    void startCamera();
    void stopCamera();
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
