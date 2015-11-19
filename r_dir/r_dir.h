#ifndef R_DIR_H
#define R_DIR_H

#include <QObject>
#include <QDir>
#include <QFile>
/**
@class R_logger
* ����� ��� ������ � ������������
*/
class R_dir : public QObject
{
    Q_OBJECT
public:


    /**
         * ����� ������������ ������������ ���������� �� ���������� ����
         * @param QString i_path - ����
         */
    static bool CheckExistDir(QString i_path)
    {

        QDir dir;
        dir.setPath(i_path);
        if (dir.exists() == true)
            return true;
        else
            return false;
    }

    /**
         * ����� �������� ���������� �� ���������� ����
         * @param QString i_path - ����
         */
    static bool CreateDir(QString i_path)
    {
        if (CheckExistDir(i_path) == true)
            return false;
        QDir dir;
        dir.setPath(i_path);
        dir.mkdir(i_path);
        return true;
    }
    /**
         * ����� �������� ������������� ����� � ���������� �� ���������� ����
         * @param QString i_path - ����
         */
    static bool CheckExistFile(QString i_path,QString i_file)
    {
        if (CheckExistDir(i_path) == false)
            return false;
        QString file_name;
        file_name.push_back(i_path);
        file_name.push_back(i_file);       
        return  CheckExistFile(file_name);;

    }

    /**
         * ����� �������� ������������� �����  �� ������� ����
         * @param QString i_path - ����
         */
    static bool CheckExistFile(QString i_full_path)
    {
        QFile file;
        file.setFileName(i_full_path);
        return file.exists();

    }
private:
    ///�������� ����������� �� ���������
    R_dir() ;
    ///�������� ����������� �����������
    R_dir(const R_dir&) = delete;
};

#endif // R_DIR_H
