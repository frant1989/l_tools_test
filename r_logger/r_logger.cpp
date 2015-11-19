#include "r_logger.h"
//пример использования функции malloc
#include <iostream>
#include <cstdlib>
// использую пространство имен логгера
using namespace r_logger;

//использую простанство имен исключений
using namespace r_exaception_types;
///гланый логер приложения
R_logger logger("Main Logger");

R_logger::R_logger(QString i_name_obj, QObject *parent) :
    QObject(parent)
  ,m_file_log(nullptr)
  ,m_create_file (false)
  ,m_Name(i_name_obj)
{
   // g=1;
    R_Debug::Write(level8,m_Name,__PRETTY_FUNCTION__);

}

R_logger::~R_logger()
{
    R_Debug::Write(level8,m_Name,__PRETTY_FUNCTION__);
    m_create_file= false;
}

bool R_logger::CreateLogFile2()
{
    char *a, *b;
        my_alloc(&a, &b);
}

void R_logger::my_alloc(char **a, char **b)
{

    char * buffer = (char*) malloc(11 + 1);
    *a = (char*)malloc(13);
    *b = (char*)malloc(42);
}

bool R_logger::CreateLogFile(QString i_name, QString i_path)
{
    R_Debug::Write(level8,m_Name,__PRETTY_FUNCTION__);
    if (m_create_file == true)
    {
        R_Debug::Write(warn,m_Name,__PRETTY_FUNCTION__,QString("m_create_file == true logger already exist!!!"));
        return false;
    }
    //если есть путь где сохранить файл
    if (!i_path.isEmpty())
    {
        if (R_dir::CheckExistDir(i_path)==false)
        {
            if (R_dir::CreateDir(i_path)==false)
            {
                 R_Debug::Write(warn,m_Name,__PRETTY_FUNCTION__,QString("CreateLogFile Dir to log file can not be create!!!"));
                 return false;
            }
            else
                R_Debug::Write(info,m_Name,__PRETTY_FUNCTION__,QString("CreateLogFile to log file created!!!"));
        }
        else
            R_Debug::Write(info,m_Name,__PRETTY_FUNCTION__,QString("CreateLogFile Dir to log file Exist!!!"));
    }
    else
        return false;


    m_full_file.clear();
    m_full_file.push_back(i_path);
    QString date = R_date::GetLocalCurrentDate();
    m_full_file.push_back(date);
    m_full_file.push_back("_");
    m_full_file.push_back( i_name);


    m_file_log = make_object_qt_sh_pointer<QFile>(m_full_file);
    if (m_file_log == nullptr)
    {
        QString text = m_Name;
        text.push_back(" : FAILED! m_file_log == nullptr");
        R_Debug::Write(crit,m_Name,__PRETTY_FUNCTION__,QString("throw RNotEnoughMemory!!!"));
        throw RNotEnoughMemory(text.toStdString());
    }
    if(!m_file_log.data()->open(QIODevice::WriteOnly))
    {
        QString text = m_Name;
        text.push_back(" : FAILED! !m_file_log.data()->open(QIODevice::WriteOnly)");
        R_Debug::Write(crit,m_Name,__PRETTY_FUNCTION__,QString("throw Exception!!!"));
        throw Exception(text.toStdString());
    }

    m_file_log.data()->close();
    m_create_file = true;

    return true;
}

bool R_logger::WriteLogFile(QString i_text,warning i_war)
{
    R_Debug::Write(level9,m_Name,__PRETTY_FUNCTION__);

    if (m_create_file == false)
    {
        R_Debug::Write(warn,m_Name,__PRETTY_FUNCTION__,QString("File is not created!!!"));

        return false;
    }
    if(m_file_log.data()->open(QIODevice::Append  | QIODevice::Text))
    {
        QTextStream out(m_file_log.data());

        QString text;
        text.push_back(R_date::GetLocalCurrentDate());
        text.push_back(" level: ");
        QVariant level = i_war;
        text.push_back(level.toString());
        text.push_back(" ");
        text.push_back(i_text);
        out << "\n";
        out <<text;

        m_file_log.data()->close();
        return true;
    }
    else
    {
        QString text = m_Name;
        text.push_back(" : FAILED! !m_file_log.data()->open(QIODevice::WriteOnly)");
        R_Debug::Write(crit,m_Name,__PRETTY_FUNCTION__,QString("throw Exception!!!"));

        throw Exception(text.toStdString());
    }

    return false;
}

bool R_logger::WriteCommon(QString i_text)
{
    R_Debug::Write(level9,m_Name,__PRETTY_FUNCTION__);

    return WriteLogFile(i_text,common);
}

bool R_logger::WriteNormal(QString i_text)
{
    R_Debug::Write(level9,m_Name,__PRETTY_FUNCTION__);

    return WriteLogFile(i_text,normal);
}

bool R_logger::WriteCritical(QString i_text)
{
    R_Debug::Write(level9,m_Name,__PRETTY_FUNCTION__);

    return WriteLogFile(i_text,critical);
}

bool R_logger::WriteLog1(QString i_text)
{
    R_Debug::Write(level9,m_Name,__PRETTY_FUNCTION__);
    return WriteLogFile(i_text,loglevel1);
}

bool R_logger::WriteLog2(QString i_text)
{
    R_Debug::Write(level9,m_Name,__PRETTY_FUNCTION__);
    return WriteLogFile(i_text,loglevel2);
}

bool R_logger::WriteLog3(QString i_text)
{
    R_Debug::Write(level9,m_Name,__PRETTY_FUNCTION__);
    return WriteLogFile(i_text,loglevel3);
}



