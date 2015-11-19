#include "r_process.h"

R_process::R_process(QString i_name_obj):
    m_Name(i_name_obj)
{
    R_Debug::Write(level8,m_Name,__PRETTY_FUNCTION__);

}

R_process::~R_process()
{
    R_Debug::Write(level8,m_Name,__PRETTY_FUNCTION__);
    if(state() == QProcess::Running)
        kill();
}

