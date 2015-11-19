#ifndef R_DIR_H
#define R_DIR_H

#include <QObject>
#include <QDir>
#include <QFile>
/**
@class R_logger
* Класс для работы с директориями
*/
class R_dir : public QObject
{
    Q_OBJECT
public:


    /**
         * Метод возвращающий соуществание директории по указанному пути
         * @param QString i_path - путь
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
         * Метод создания директории по указанному пути
         * @param QString i_path - путь
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
         * Метод проверки существования файла в директории по указанному пути
         * @param QString i_path - путь
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
         * Метод проверки существования файла  по полному пути
         * @param QString i_path - путь
         */
    static bool CheckExistFile(QString i_full_path)
    {
        QFile file;
        file.setFileName(i_full_path);
        return file.exists();

    }
private:
    ///запрещаю конструктор по умолчанию
    R_dir() ;
    ///запрещаю конструктор копирования
    R_dir(const R_dir&) = delete;
};

#endif // R_DIR_H
