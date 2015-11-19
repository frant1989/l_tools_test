#include "r_thread.h"

R_Thread::R_Thread(QString i_obj_name) : QThread()
  , m_Name(i_obj_name)
{
   R_Debug::Write(level8,m_Name,__PRETTY_FUNCTION__);
}

R_Thread::~R_Thread()
{
    R_Debug::Write(level8,m_Name,__PRETTY_FUNCTION__);
}

bool R_Thread::Start()
{
    R_Debug::Write(level8,m_Name,__PRETTY_FUNCTION__);
    m_timer.start();
    start();
    return true;
}

double R_Thread::GetTimeElapsed()
{
    R_Debug::Write(level8,m_Name,__PRETTY_FUNCTION__);
    const qint64 nsecs = m_timer.nsecsElapsed();
    return nsecs / 1e6;
}

