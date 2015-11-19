#include "r_debug.h"

R_Debug_Singleton * R_Debug_Singleton::p_instance = 0;
R_Debug_Singleton_Destroyer R_Debug_Singleton::destroyer;

R_Debug_Singleton_Destroyer::~R_Debug_Singleton_Destroyer()
{
    delete p_instance;
}
void R_Debug_Singleton_Destroyer::initialize( R_Debug_Singleton* p )
{
    p_instance = p;
}
R_Debug_Singleton& R_Debug_Singleton::getInstance()
{
    if(!p_instance)
    {
        p_instance = new R_Debug_Singleton();
        destroyer.initialize( p_instance);
    }
    return *p_instance;
}

bool R_Debug_Singleton::Write(const r_deb_levels i_level,const QString i_obj_name, const QString i_function, const QString i_text)
{
    //ищем уровень в допустимом выводе
    for (auto i : m_levels)
    {
        if (i == i_level)
        {
            QString str_debug;
            QString str_level;
            std::stringstream  ss;
            ss<<i_level;
            str_level.push_back(QString::fromStdString(ss.str()));
            if (i_text.isEmpty())
                STR_DEB_FUNC(str_debug,str_level,i_obj_name, i_function);
            else
                STR_DEB_TEXT(str_debug,str_level,i_obj_name, i_function,i_text);
            return true;
        }
    }
    return false;
}

bool R_Debug_Singleton::SetLevels( QStringList i_levels)
{
    for ( int j = any; j != end_deb_levels; j++ )
    {
       r_deb_levels level = static_cast<r_deb_levels>(j);
       std::stringstream  ss;
       ss<<level;
       QString str;
       str.push_back(QString::fromStdString(ss.str()));
       for (auto i : i_levels)
       {
           if (i == str && str.toStdString() != debug_any)
               m_levels.push_back(level);
           else if (i == str && str.toStdString() == debug_any)
           {
               m_levels.clear();
               for ( int k = any; k != end_deb_levels; k++)
               {
                    r_deb_levels level_any = static_cast<r_deb_levels>(k);
                    m_levels.push_back(level_any);
               }
               return true;
           }
       }
    }
    return true;
}
