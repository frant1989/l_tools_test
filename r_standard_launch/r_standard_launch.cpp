#include "r_standard_launch.h"
///пространство имен логгера
using namespace r_logger;

R_standard_launch::R_standard_launch(QString i_obj_name):
     m_Name(i_obj_name)
    , m_log(false)

{
    R_Debug::Write(info,m_Name,__PRETTY_FUNCTION__);
}



R_standard_launch::~R_standard_launch()
{
    R_Debug::Write(info,m_Name,__PRETTY_FUNCTION__);

}
bool R_standard_launch::ParseCmd(QStringList i_arguments, OPTIONS_STANDARD_LAUNCH &i_o_options)
{

    R_Debug::Write(info,m_Name,__PRETTY_FUNCTION__);
    //кол-во параметров
    int kol_arguments = i_arguments.size();
   //идем по циклу и определяем параметры запуска приложения
   for (int i=1; i < kol_arguments; i++)
   {

       if (i_arguments[i]==help_cmd)
       {
           i_o_options.m_help = true;
       }
       else if (i_arguments[i]==log_cmd)
       {
           i_o_options.m_log = true;
       }
       else if (i_arguments[i]==debug_level)
       {
           int next = i+1;
           if (next<kol_arguments)
           {
               QString argument = i_arguments[next];
               QRegExp rx("[,]");// match a comma or a space
               QStringList list = argument.split(rx, QString::SkipEmptyParts);
               R_Debug::SetLevels(list);
               i++;
           }
       }
       else if (i_arguments[i]==log_path_cmd)
       {
           i_o_options.m_log = true;
           int next = i+1;
           if (next<kol_arguments)
           {
               QVariant argument = i_arguments[next];
               i_o_options.m_log_path = argument.toString();
               i++;
           }
       }
       else
           continue;
    }
   return true;
}

bool R_standard_launch::PrintHelp()
{
    R_Debug::Write(info,m_Name,__PRETTY_FUNCTION__);
    QString mes;
    mes.push_back("\n");
    mes.push_back("Use --help key for help");
    mes.push_back("\n");
    mes.push_back("Use --log key for write log near exe");
    mes.push_back("\n");
    mes.push_back("Use --log_path key for set path to log file");
    mes.push_back("\n");
    mes.push_back("Use --add_debug_leve key for set levels for debug");
    mes.push_back("\n");
    qDebug()<< mes;
    return true;
}

bool R_standard_launch::CreateLogger(OPTIONS_STANDARD_LAUNCH &i_options, QString i_name_file, R_logger &o_logger)
{
    R_Debug::Write(info,m_Name,__PRETTY_FUNCTION__);
    //если хотим писать логи
    if (i_options.m_log == false || i_name_file.isEmpty() )
    {
        R_Debug::Write(warn,m_Name,__PRETTY_FUNCTION__,"Dont write logs or i_name_file.isEmpty()!!!");
        return false;
    }
    //признак создания лог файла
    bool create_logger = false;
    if (i_options.m_log_path.isEmpty() ==true)
    {
        //путь к приложению
        QString path_app =  qApp->applicationDirPath();
        //создаем логгер в папке с приложением
        create_logger =  o_logger.CreateLogFile(i_name_file,path_app);
    }
    else
        //создаем логгер в указанной папке
        create_logger = o_logger.CreateLogFile(i_name_file,i_options.m_log_path);

    //если не смогли создать
    if (create_logger == false)
    {
        R_Debug::Write(warn,m_Name,__PRETTY_FUNCTION__,"Can not create logger!!!");
        return false;
    }
    else
    {
        o_logger.WriteLogFile("Logger Start!!!",common);
        R_Debug::Write(info,m_Name,__PRETTY_FUNCTION__,"Logger Start!!!");
        return true;
    }
    return false;
}




