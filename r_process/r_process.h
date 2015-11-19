#ifndef R_PROCESS_H
#define R_PROCESS_H


#include <QProcess>
#include "../r_debug/r_debug.h"
#include "../r_global/r_global.h"
class R_process :  public QProcess
{
public:
    explicit R_process(QString i_name_obj);
    virtual ~R_process();
protected:
    QString m_Name;

};

#endif // R_PROCESS_H
