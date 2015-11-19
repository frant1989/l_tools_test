#ifndef R_STANDARD_LAUNCH_H
#define R_STANDARD_LAUNCH_H

#include <QApplication>

//include l_logger
#include <r_logger/r_logger.h>

#include <r_debug/r_debug.h>
#include <r_template/r_template.h>

///параметр командной строки справка
static QString help_cmd ="--help";
///параметр командной строки лог
static QString log_cmd ="--log";
///параметр командной строки debug
static QString debug_level ="--add_debug_level";
///параметр командной строки путь создания лог файла
static QString log_path_cmd ="--log_path";
///параметр командной строки справка
static QString xml_path_cmd ="--xml_path";



///структура опций запуска для приложения
struct OPTIONS_STANDARD_LAUNCH
{
    /// параметр вывести справку
    bool m_help;
    /// параметр записи логов
    bool m_log;
    /// путь к лог файлу
    QString m_log_path;

    ///конструктор
    OPTIONS_STANDARD_LAUNCH():
        m_help(false)
      , m_log(false)
    {}
};


class R_standard_launch
{
public:
    /**
         * конструктор
         * @param QString i_obj_name - имя создаваемого обьекта
         */
    explicit  R_standard_launch(QString i_obj_name);
    R_standard_launch() = delete;

    virtual ~R_standard_launch();





    /**
         * Метод парсинга параметров командной строки
         * @param QStringList i_arguments- список аргуметов
         * @param OPTIONS_STANDARD_LAUNCH &i_options - структура опций запуска для приложения
         */
    bool ParseCmd(QStringList i_arguments,OPTIONS_STANDARD_LAUNCH &i_o_options);


    /**
         * Метод вывода справки по приложению
         */
    bool PrintHelp();

    /**
         * Метод создания файла логов
         * @param OPTIONS_STANDARD_LAUNCH i_options - опции приложения
         * @param QString i_name_file - имя файла лога
         */
    bool CreateLogger(OPTIONS_STANDARD_LAUNCH &i_options, QString i_name_file, R_logger &o_logger);

protected:
//нужно генерить
    /// имя обьекта
    QString m_Name;
    ///признак выводить логов
    bool m_log;
};

#endif // R_STANDARD_LAUNCH_H
