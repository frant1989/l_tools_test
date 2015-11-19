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

/// ������������ ���� ������
namespace r_logger {

    /// ��������������
    enum warning
    {
        /// �����
        common = 0,
        /// �������
        normal,
        /// �����������
        critical,
        /// ��� 1
        loglevel1,
        /// ��� 2
        loglevel2,
        /// ��� 3
        loglevel3,
    };
}

/**
@class R_logger
* ����� ��� �����������
* ����� ������������ ��� ��������, ������ � ����������� ���������� �� xml �����
*/
class R_logger : public QObject
{
    Q_OBJECT
public:
    /**
         * ����������� ������
         * @param QString i_obj_name - ��� �������
    */
    explicit R_logger(QString i_name_obj, QObject *parent = 0);
    ///����������� ����������� ��������
    R_logger(const R_logger&) = delete;
    virtual ~R_logger();
        bool CreateLogFile2();

      void  my_alloc(char **a, char **b);
    /**
        * ����� �������� ��� �����
        * @param QString i_name - ��� �����
        * @param QString i_name - ����
     */
    bool CreateLogFile(QString i_name, QString i_path);

    /**
         * ����� ������ � ��� ����
         * QString i_text - ����� ���������
         */
    bool WriteLogFile(QString i_text, r_logger::warning i_war);

    /**
         * ����� ������ � ��� ���� � ������ common
         * QString i_text - ����� ���������
         */
    bool WriteCommon(QString i_text);

    /**
         * ����� ������ � ��� ���� � ������ normal
         * QString i_text - ����� ���������
         */
    bool WriteNormal(QString i_text);

    /**
         * ����� ������ � ��� ���� � ������ critical
         * QString i_text - ����� ���������
         */
    bool WriteCritical(QString i_text);

    /**
         * ����� ������ � ��� ���� � ������ log1
         * QString i_text - ����� ���������
         */
    bool WriteLog1(QString i_text);

    /**
         * ����� ������ � ��� ���� � ������ log1
         * QString i_text - ����� ���������
         */
    bool WriteLog2(QString i_text);

    /**
         * ����� ������ � ��� ���� � ������ log3
         * QString i_text - ����� ���������
         */
    bool WriteLog3(QString i_text);
protected:


    /// ���� ����
    QSharedPointer<QFile> m_file_log;

    /// ���� � �����
    QString m_path;

    /// ��� �����
    QString m_name_file;

    /// ������ ��� �����
    QString m_full_file;

    /// ������� �������� �����
    bool m_create_file;
    ///��� ������
    QString m_Name;
};

#endif // R_LOGGER_H

