#ifndef R_LOGGER_H
#define R_LOGGER_H

#include <QObject>
#include <QFile>
#include "../r_debug/r_debug.h"
#include "../r_global/r_global.h"
#include "../r_dir/r_dir.h"
#include "../r_date/r_date.h"
#include "../r_template/r_template.h"
#include "../r_exceptions/r_exceptions.h"

/// пространство имен логера
namespace r_logger {

    /// предупреждения
    enum warning
    {
        /// общий
        common = 0,
        /// средний
        normal,
        /// критический
        critical,
        /// лог 1
        loglevel1,
        /// лог 2
        loglevel2,
        /// лог 3
        loglevel3,
    };
}

/**
@class R_logger
* Класс для логирования
* Класс предназначен для создания, чтения и выставления аттрибутов из xml файла
*/
class R_logger : public QObject
{
    Q_OBJECT
public:
    /**
         * конструктор класса
         * @param QString i_obj_name - имя обьекта
    */
    explicit R_logger(QString i_name_obj, QObject *parent = 0);
    ///конструктор копирования запрещен
    R_logger(const R_logger&) = delete;
    virtual ~R_logger();
        bool CreateLogFile2();

      void  my_alloc(char **a, char **b);
    /**
        * Метод создания лог файла
        * @param QString i_name - имя файла
        * @param QString i_name - путь
     */
    bool CreateLogFile(QString i_name, QString i_path);

    /**
         * Метод записи в лог файл
         * QString i_text - текст сообщения
         */
    bool WriteLogFile(QString i_text, r_logger::warning i_war);

    /**
         * Метод записи в лог файл в секцию common
         * QString i_text - текст сообщения
         */
    bool WriteCommon(QString i_text);

    /**
         * Метод записи в лог файл в секцию normal
         * QString i_text - текст сообщения
         */
    bool WriteNormal(QString i_text);

    /**
         * Метод записи в лог файл в секцию critical
         * QString i_text - текст сообщения
         */
    bool WriteCritical(QString i_text);

    /**
         * Метод записи в лог файл в секцию log1
         * QString i_text - текст сообщения
         */
    bool WriteLog1(QString i_text);

    /**
         * Метод записи в лог файл в секцию log1
         * QString i_text - текст сообщения
         */
    bool WriteLog2(QString i_text);

    /**
         * Метод записи в лог файл в секцию log3
         * QString i_text - текст сообщения
         */
    bool WriteLog3(QString i_text);
protected:


    /// файл лога
    QSharedPointer<QFile> m_file_log;

    /// путь к файлу
    QString m_path;

    /// имя файла
    QString m_name_file;

    /// полное имя файла
    QString m_full_file;

    /// признак создания файла
    bool m_create_file;
    ///имя класса
    QString m_Name;
};

#endif // R_LOGGER_H

