#ifndef R_THREAD_H
#define R_THREAD_H

#include <QObject>
#include <QThread>
#include <QElapsedTimer>
//#include l_tools
#include "../r_debug/r_debug.h"
#include "../r_global/r_global.h"
class R_Thread : public QThread
{
    Q_OBJECT
public:
    explicit R_Thread(QString i_obj_name);
    ~R_Thread();

    QElapsedTimer m_timer;

    bool Start();

    double GetTimeElapsed();
signals:
    bool Destroy();
public slots:
protected:
    QString m_Name;

};

#endif // R_THREAD_H
