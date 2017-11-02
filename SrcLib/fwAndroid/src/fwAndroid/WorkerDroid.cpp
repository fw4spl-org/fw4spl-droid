/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2017.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#include "fwAndroid/WorkerDroid.hpp"

#include <fwCore/TimeStamp.hpp>

#include <fwServices/registry/ActiveWorkers.hpp>

#include <fwThread/Timer.hpp>
#include <fwThread/Worker.hpp>

#include <android_native_app_glue.h>

#include <boost/asio/deadline_timer.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/optional.hpp>

namespace fwAndroid
{

/**
 * @brief Private Timer implementation for Android using ::boost::asio.
 */
class TimerDroid : public ::fwThread::Timer
{
public:

    /// Constructs a TimerAsio from given io_service.
    TimerDroid(::boost::asio::io_service& ioSrv) :
        m_timer(ioSrv),
        m_duration(std::chrono::seconds(1)),
        m_oneShot(false),
        m_running(false)
    {
    }

    virtual ~TimerDroid()
    {
    }

    /// Starts or restarts the timer.
    void start()
    {
        ::fwCore::mt::ScopedLock lock(m_mutex);
        this->rearmNoLock(m_duration);
        m_running = true;
    }

    /// Stops the timer and cancel all pending operations.
    void stop()
    {
        ::fwCore::mt::ScopedLock lock(m_mutex);
        if (m_running )
        {
            m_running = false;
            this->cancelNoLock();
        }
    }

    /// Sets time duration.
    void setDuration(TimeDurationType duration)
    {
        ::fwCore::mt::ScopedLock lock(m_mutex);
        m_duration = duration;
    }

    /// Returns if the timer mode is 'one shot'.
    bool isOneShot() const
    {
        ::fwCore::mt::ScopedLock lock(m_mutex);
        return m_oneShot;
    }

    /// Sets timer mode.
    void setOneShot(bool oneShot)
    {
        ::fwCore::mt::ScopedLock lock(m_mutex);
        m_oneShot = oneShot;
    }

    /// Returns true if the timer is currently running.
    bool isRunning() const
    {
        ::fwCore::mt::ScopedLock lock(m_mutex);
        return m_running;
    }

protected:

    //------------------------------------------------------------------------------

    void cancelNoLock()
    {
        m_timer.cancel();
    }

    //------------------------------------------------------------------------------

    void rearmNoLock(TimeDurationType duration)
    {
        this->cancelNoLock();
        std::chrono::microseconds msec =
            std::chrono::duration_cast< std::chrono::microseconds >(duration);
        ::boost::posix_time::time_duration d = ::boost::posix_time::microseconds(msec.count());
        m_timer.expires_from_now( d );
        m_timer.async_wait( std::bind(&TimerDroid::call, this, std::placeholders::_1));
    }

    //------------------------------------------------------------------------------

    void call(const ::boost::system::error_code& error)
    {
        if(!error)
        {
            TimeDurationType duration;
            bool oneShot;
            {
                ::fwCore::mt::ScopedLock lock(m_mutex);
                oneShot  = m_oneShot;
                duration = m_duration;
            }

            if (!oneShot)
            {
                this->rearmNoLock(duration);
                m_function();
            }
            else
            {
                m_function();
                ::fwCore::mt::ScopedLock lock(m_mutex);
                m_running = false;
            }
        }
    }

    /// Copy constructor forbidden.
    TimerDroid( const TimerDroid& ) = delete;

    /// Copy operator forbidden.
    TimerDroid& operator=( const TimerDroid& ) = delete;

    /// Timer object.
    ::boost::asio::deadline_timer m_timer;

    /// Time to wait until timer's expiration.
    TimeDurationType m_duration;

    /// Timer's mode.
    bool m_oneShot;

    /// Timer's state.
    bool m_running;
};

//-----------------------------------------------------------------------------

/**
 * @brief Private implementation of fwThread::Worker using Android event loop.
 */
class WorkerDroid : public ::fwThread::Worker
{
public:
    using ios = ::boost::asio::io_service;
    typedef std::thread ThreadType;

    WorkerDroid();

    void init( android_app* app );

    virtual ~WorkerDroid();

    void stop();

    void post(TaskType handler);

    ::fwThread::Worker::FutureType getFuture();

    virtual ::fwThread::ThreadIdType getThreadId() const;

    SPTR(::fwThread::Timer) createTimer();

    virtual void processTasks();

    virtual void processTasks(PeriodType maxtime);

protected:

    android_app* m_app;
    bool m_done;
    ::fwThread::ThreadIdType m_threadId;
    ios m_ioService;
    ::boost::optional<ios::work> m_work;

    int eventLoop();

    /// Copy constructor forbidden
    WorkerDroid( const WorkerDroid& );

    /// Copy operator forbidden
    WorkerDroid& operator=( const WorkerDroid& );
};

//-----------------------------------------------------------------------------

::fwThread::Worker::sptr getDroidWorker( android_app* app )
{
    SPTR(WorkerDroid) workerDroid = std::make_shared< WorkerDroid >();
    workerDroid->init(app);
    ::fwServices::registry::ActiveWorkers::getDefault()
    ->addWorker(::fwServices::registry::ActiveWorkers::s_DEFAULT_WORKER, workerDroid);

    return workerDroid;
}

//------------------------------------------------------------------------------
// WorkerDroid private implementation
//-----------------------------------------------------------------------------

WorkerDroid::WorkerDroid() :
    m_app(nullptr),
    m_done(false),
    m_threadId( ::fwThread::getCurrentThreadId() ),
    m_ioService(),
    m_work(ios::work(m_ioService))
{
}

//-----------------------------------------------------------------------------

void WorkerDroid::init( android_app* app )
{
    OSLM_TRACE("Init WorkerDroid" << ::fwThread::getCurrentThreadId() <<" Start");
    m_app = app;
    OSLM_TRACE("Init WorkerDroid" << ::fwThread::getCurrentThreadId() <<" Finish");
}

//-----------------------------------------------------------------------------

WorkerDroid::~WorkerDroid()
{
    m_work.reset();
    //m_ioService.run(); // to completion
    this->stop();
}

//-----------------------------------------------------------------------------

int WorkerDroid::eventLoop()
{
    m_done = false;
    while (!m_done)
    {
        // Read all pending events.
        int ident;
        int events;
        struct android_poll_source* source;
        while ((ident = ALooper_pollAll(0, NULL, &events, (void**)&source)) >= 0)
        {
            if (ident >= 0)
            {
                SLM_TRACE("Processing Event");
                // Process this event.
                if (source != NULL)
                {
                    source->process(m_app, source);
                }

                // Check if we are exiting.
                if (m_app->destroyRequested != 0)
                {
                    return 1;
                }
            }
        }
        if(m_app->window)
        {
            m_ioService.poll_one();
        }
    }
    return 1;
}

//-----------------------------------------------------------------------------

::fwThread::Worker::FutureType WorkerDroid::getFuture()
{
    if (!m_future.valid() )
    {
        std::packaged_task< ExitReturnType() > task(std::bind(&WorkerDroid::eventLoop, this));
        std::future< ExitReturnType > ufuture = task.get_future();
        m_future = std::move(ufuture);
        task();
    }
    return m_future;
}

//-----------------------------------------------------------------------------

::fwThread::ThreadIdType WorkerDroid::getThreadId() const
{
    return m_threadId;
}

//-----------------------------------------------------------------------------

void WorkerDroid::stop()
{
    m_done = true;
}

//-----------------------------------------------------------------------------

SPTR(::fwThread::Timer) WorkerDroid::createTimer()
{
    return std::make_shared< TimerDroid >(std::ref(m_ioService));
}

//-----------------------------------------------------------------------------

void WorkerDroid::post(TaskType handler)
{
    if(m_work)
    {
        m_ioService.post(handler);
    }
}

//-----------------------------------------------------------------------------

void WorkerDroid::processTasks()
{
    m_ioService.poll();
}

//-----------------------------------------------------------------------------

void WorkerDroid::processTasks(PeriodType maxtime)
{
    ::fwCore::TimeStamp timeStamp;
    timeStamp.setLifePeriod(maxtime);
    timeStamp.modified();
    while(timeStamp.periodExpired())
    {
        m_ioService.poll_one();
    }
}

} //namespace fwAndroid

