/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2014-2016.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#include "visuVideoAndroid/camera/SAndroidCamera.hpp"

#include <fwCom/Slots.hxx>
#include <fwCom/Signal.hxx>

#include <fwTools/fwID.hpp>

#include <fwServices/macros.hpp>

#include <sstream>

namespace visuVideoAndroid
{
namespace camera
{

//-----------------------------------------------------------------------------

fwServicesRegisterMacro( ::fwServices::IService, ::visuVideoAndroid::camera::SAndroidCamera, ::extData::FrameTL );

//-----------------------------------------------------------------------------
const ::fwCom::Signals::SignalKeyType SAndroidCamera::s_CAMERA_OPENED_SIG = "cameraOpened";

const ::fwCom::Slots::SlotKeyType s_START_OR_STOP_SLOT = "startOrStop";
const ::fwCom::Slots::SlotKeyType s_START_CAMERA_SLOT  = "startCamera";
const ::fwCom::Slots::SlotKeyType s_STOP_CAMERA_SLOT   = "stopCamera";
//-----------------------------------------------------------------------------

SAndroidCamera::SAndroidCamera() throw() : m_cameraId(0),
                                           m_width(320),
                                           m_height(240),
                                           m_frameRate(60),
                                           m_autoFocus(true),
                                           m_camIsStarted(false)
{
    SLM_TRACE_FUNC();
    m_sigCameraOpened = newSignal< CameraOpenedSignalType >( s_CAMERA_OPENED_SIG );


    newSlot(s_START_OR_STOP_SLOT, &SAndroidCamera::startOrStop, this);
    newSlot(s_STOP_CAMERA_SLOT, &SAndroidCamera::stopCamera, this);
    newSlot(s_START_CAMERA_SLOT, &SAndroidCamera::startCamera, this);
}

//-----------------------------------------------------------------------------

SAndroidCamera::~SAndroidCamera() throw()
{
    SLM_TRACE_FUNC();
}

//-----------------------------------------------------------------------------

void SAndroidCamera::configuring() throw( ::fwTools::Failed )
{
    SLM_TRACE_FUNC();

    ::fwRuntime::ConfigurationElement::sptr cfg;
    cfg = m_configuration->findConfigurationElement("cameraId");
    std::istringstream(cfg->getValue()) >> m_cameraId;

    cfg = m_configuration->findConfigurationElement("autoFocus");
    std::istringstream(cfg->getValue()) >> std::boolalpha >> m_autoFocus;

    cfg = m_configuration->findConfigurationElement("width");
    std::istringstream(cfg->getValue()) >> m_width;

    cfg = m_configuration->findConfigurationElement("height");
    std::istringstream(cfg->getValue()) >> m_height;

    cfg = m_configuration->findConfigurationElement("fps");
    std::istringstream(cfg->getValue()) >> m_frameRate;
}

//-----------------------------------------------------------------------------

void SAndroidCamera::starting() throw(::fwTools::Failed)
{
    SLM_TRACE_FUNC();

    m_timeline = this->getObject< ::extData::FrameTL >();

    m_camera = new ::arAndroidTools::Camera();
    m_camera->m_sigFrameFetched.connect(bind(&SAndroidCamera::fetchFrame, this, _1));
    m_camera->setWidth(m_width);
    m_camera->setHeight(m_height);
    m_camera->setFrameRate(m_frameRate);
    m_camera->setAutoFocus(m_autoFocus);

}

//-----------------------------------------------------------------------------

void SAndroidCamera::stopping() throw(::fwTools::Failed)
{
    SLM_TRACE_FUNC();
    if(m_camIsStarted)
    {
        m_camera->release();
    }
}

//-----------------------------------------------------------------------------

void SAndroidCamera::info(std::ostream &_sstream )
{
    SLM_TRACE_FUNC();
}

//-----------------------------------------------------------------------------

void SAndroidCamera::updating() throw(::fwTools::Failed)
{
    SLM_TRACE_FUNC();
    this->startCamera();
}

//-----------------------------------------------------------------------------

void SAndroidCamera::startOrStop(bool state)
{
    SLM_TRACE_FUNC();
    if(state)
    {
        m_camera->open(m_cameraId);

        m_sigCameraOpened->asyncEmit( m_camera->getFormat(), m_camera->getWidth(), m_camera->getHeight() );

        const size_t width  = static_cast<size_t>(m_camera->getWidth());
        const size_t height = static_cast<size_t>(m_camera->getHeight());
        m_timeline->setMaximumSize(10);
        m_timeline->initPoolSize(width, height, ::fwTools::Type::s_UINT8, 4);

        m_camera->startPreview();
        m_camIsStarted = true;
    }
    else
    {
        m_camera->stopPreview();
        m_camIsStarted = false;
    }
}

//-----------------------------------------------------------------------------

void SAndroidCamera::fetchFrame(unsigned char* rgb)
{
    // Recopy of frame grabber ...
    SLM_TRACE_FUNC();
    const ::fwCore::HiResClock::HiResClockType timestamp = ::fwCore::HiResClock::getTimeInMilliSec();

    SPTR(::extData::FrameTL::BufferType) buffer = m_timeline->createBuffer(timestamp);

    ::boost::uint32_t* destBuffer = reinterpret_cast< ::boost::uint32_t* >( buffer->addElement(0) );

    const int width  = m_camera->getWidth();
    const int height = m_camera->getHeight();

    OSLM_DEBUG(" Fetched frame size = "<<m_camera->getWidth()<<" x "<< m_camera->getHeight());
    OSLM_DEBUG(" Fetched frame rate = "<<m_camera->getFrameRate());

    const ::boost::uint32_t* frameBuffer = reinterpret_cast< const ::boost::uint32_t *>( rgb );
    const unsigned int size              = static_cast<unsigned int>(width*height);

    std::copy(frameBuffer,frameBuffer+size,destBuffer);

    delete[] rgb;

    //push buffer
    m_timeline->pushObject(buffer);

    //Notify
    ::extData::TimeLine::ObjectPushedSignalType::sptr sig;
    sig = m_timeline->signal< ::extData::TimeLine::ObjectPushedSignalType >(::extData::TimeLine::s_OBJECT_PUSHED_SIG );
    sig->asyncEmit(timestamp);
}

//-----------------------------------------------------------------------------

void SAndroidCamera::startCamera()
{
    this->startOrStop(true);
}

//-----------------------------------------------------------------------------

void SAndroidCamera::stopCamera()
{
    this->startOrStop(false);
    this->stopping();
}

//-----------------------------------------------------------------------------

} //namespace camera
} //namespace visuVideoAndroid

