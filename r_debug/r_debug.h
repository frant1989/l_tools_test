#ifndef R_DEBUG_H
#define R_DEBUG_H
#include <QObject>

#include "r_global/r_global.h"
#include <sstream>
#include <iostream>

// опережающее объ€вление
class R_Debug_Singleton;




class R_Debug_Singleton_Destroyer
{
  private:
    R_Debug_Singleton* p_instance;
  public:
    ~R_Debug_Singleton_Destroyer();
    void initialize( R_Debug_Singleton* p );
};


class R_Debug_Singleton
{

public:
      static R_Debug_Singleton& getInstance();
      bool Write(const r_deb_levels i_level,const QString i_obj_name,const QString i_function = 0,const QString i_text=0 );
      bool SetLevels(QStringList i_levels);
private:

    static R_Debug_Singleton* p_instance;

    static R_Debug_Singleton_Destroyer destroyer;

protected:

    R_Debug_Singleton() { }

    R_Debug_Singleton( const R_Debug_Singleton& );

    R_Debug_Singleton& operator=( R_Debug_Singleton& );

    ~R_Debug_Singleton() { }

    friend class R_Debug_Singleton_Destroyer;

    QVector<r_deb_levels> m_levels;
};







class R_Debug: public QObject
{
    Q_OBJECT


public:
    static bool Write(const r_deb_levels i_level,const QString i_obj_name,const QString i_function = 0,const QString i_text=0 )
    {

        R_Debug_Singleton& singleton = R_Debug_Singleton::getInstance();
        return singleton.Write(i_level,i_obj_name,i_function,i_text);


    }
    static bool SetLevels(QStringList i_levels)
    {
        R_Debug_Singleton& singleton = R_Debug_Singleton::getInstance();
        return singleton.SetLevels(i_levels);

    }



};

#endif // R_DEBUG_H
