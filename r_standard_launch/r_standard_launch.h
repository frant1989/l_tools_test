#ifndef R_STANDARD_LAUNCH_H
#define R_STANDARD_LAUNCH_H

#include <QApplication>

//include l_logger
#include <r_logger/r_logger.h>

#include <r_debug/r_debug.h>
#include <r_template/r_template.h>

///�������� ��������� ������ �������
static QString help_cmd ="--help";
///�������� ��������� ������ ���
static QString log_cmd ="--log";
///�������� ��������� ������ debug
static QString debug_level ="--add_debug_level";
///�������� ��������� ������ ���� �������� ��� �����
static QString log_path_cmd ="--log_path";
///�������� ��������� ������ �������
static QString xml_path_cmd ="--xml_path";



///��������� ����� ������� ��� ����������
struct OPTIONS_STANDARD_LAUNCH
{
    /// �������� ������� �������
    bool m_help;
    /// �������� ������ �����
    bool m_log;
    /// ���� � ��� �����
    QString m_log_path;

    ///�����������
    OPTIONS_STANDARD_LAUNCH():
        m_help(false)
      , m_log(false)
    {}
};


class R_standard_launch
{
public:
    /**
         * �����������
         * @param QString i_obj_name - ��� ������������ �������
         */
    explicit  R_standard_launch(QString i_obj_name);
    R_standard_launch() = delete;

    virtual ~R_standard_launch();





    /**
         * ����� �������� ���������� ��������� ������
         * @param QStringList i_arguments- ������ ���������
         * @param OPTIONS_STANDARD_LAUNCH &i_options - ��������� ����� ������� ��� ����������
         */
    bool ParseCmd(QStringList i_arguments,OPTIONS_STANDARD_LAUNCH &i_o_options);


    /**
         * ����� ������ ������� �� ����������
         */
    bool PrintHelp();

    /**
         * ����� �������� ����� �����
         * @param OPTIONS_STANDARD_LAUNCH i_options - ����� ����������
         * @param QString i_name_file - ��� ����� ����
         */
    bool CreateLogger(OPTIONS_STANDARD_LAUNCH &i_options, QString i_name_file, R_logger &o_logger);

protected:
//����� ��������
    /// ��� �������
    QString m_Name;
    ///������� �������� �����
    bool m_log;
};

#endif // R_STANDARD_LAUNCH_H
