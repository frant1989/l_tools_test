#ifndef R_PARSER_H
#define R_PARSER_H


#include <QFont>
#include <QColor>
#include <QFile>
#include <QString>
#include <QObject>
#include <QtXmlPatterns/QtXmlPatterns>
#include <QtXml/QXmlSimpleReader>
#include <QDomDocument>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QDomDocument>
#include "../r_debug/r_debug.h"
#include "../r_global/r_global.h"
#include "../r_dir/r_dir.h"

///структура тэга для записи
struct TAG
{
    ///имя тэга
    QString name;
    ///номер с начала
    int id;
    /// аттрибут
    QVariant attr;
    TAG()
    {
        id=0;
        attr = -1;
    }
};


/**
@class R_parser
* Класс для парсинга xml файл с помощбю DOM
* Класс предназначен для создания, чтения и выставления аттрибутов из xml файла
*/
class R_parser:public QObject
{
    Q_OBJECT
public:

    /**
         * Конструктор класса
         */
    explicit R_parser(QString i_obj_name,bool i_log);

    R_parser(const R_parser&) = delete;

    /**
         * Деструктор класса
         */

    virtual ~R_parser();

    /**
         * Метод создания и инициализация парсера
         * @param QString i_path - путь к директории
         * @param QString i_name - имя файла
         */
    bool CreateParser(QString i_path, QString i_name, QIODevice::OpenModeFlag i_mode_flag);

    /**
         * Метод создания и инициализация парсера
         * @param QString i_path - путь к директории
         * @param QString i_name - имя файла
         */
    bool CreateParser(QString i_full_path, QIODevice::OpenModeFlag i_mode_flag);

    /**
         * Метод возвращающий кол-во тэгов
         * @param QVector<TAG> i_tags - путь к тэгу
         */
    int GetTagCount(QVector<TAG> i_tags);

    /**
         * Метод заполнения тега атрибутом
         * @param QVector<TAG> i_tags - путь к тэгу
         */
    bool SetTagsAttr(QVector<TAG> i_tags);

    /**
         * Метод заполнения тега атрибутом
         * @param QVector<TAG> i_tags - путь к тэгу, заполняется все арттрибуты TAG.attr
         */
    bool GetTagsAttr(QVector<TAG> &i_o_tags, QString i_value = QString());



    /**
         * Метод возвражающий список атрибутов
         * @param QVector<TAG> i_tags - путь к тэгу, заполняется все арттрибуты TAG.attr
         * @param QStringList i_list_attr  - список атрибутов
         */
    QVector <QVariant> GetTagsAttr(QVector<TAG> &i_o_tags,QStringList i_list_attr );

    /**
         * Метод открытия только для чтения улучшает быстродействие при чтении
         */
    bool OpenForRead();

    /**
         * Метод закрытия только для чтения
         */
    bool CloseForRead();

protected:

     /**
         * Метод инициализации файла
         */
    bool InitFile();

    /**
         * Метод проверки наличия главного тега
         * @param QDomElement i_docElem -элемент который проверяем
         * @param QString i_Main - имя главного тега
         */
    bool ExistMainTag(QDomElement i_docElem, QString i_Main);

    /**
        * Метод проверки создания файла
        */
    bool CheckCreateFile();

    ///признак создания
    bool m_create;
    ///признак открытия для чтения
    bool m_open_read;

    ///имя файла
    QString m_FileName;
    ///Путь к файлу
    QString m_file_path;
    ///Полный путь  путь к файлу + Имя
    QString m_FullName;

    QIODevice::OpenModeFlag m_mode_flag;


    QDomDocument m_opt;

    QFile m_ifile;

//нужно генерить
    /// имя обьекта
    QString m_Name;
    ///признак выводить логов
    bool m_log;
};


/*
 *
 *  //атрибуты шрифта

    QString m_Font;
    QString att_family_font;
    QString att_point_font;
    QString att_pixel_font;
    QString att_styleHint_font;
    QString att_weight_font;
    QString att_bold_font;
    QString att_kerning_font;
    QString att_italic_font ;
    QString att_overline_font ;
    QString att_underline_font ;
    QString att_strike_out;
//-----конец атрибутов

//атрибутты цвета
    QString att_rgb_red;
    QString att_rgb_green;
    QString att_rgb_blue;
//
**
     * Метод создания тега
     * @param QVector<QString> i_tags - путь к тэгу
     /
bool SetTags(QVector<QString> i_tags);
**
     * Метод иницализации шрифта
     * @param QVector<QString> i_tags - путь к тэгу
     /
bool InitFontDOM(QVector<QString> i_tags);

**
     * Метод сохранения шрифта
     * @param QFont i_font - шрифт который сохраняем
     * @param QVector<QString> i_tags - путь к тэгу
    /
bool SetFontDOM(QFont i_font, QVector<QString> i_tags);

**
     * Метод получения шрифта
     * @param (QFont **i_font - шрифт который создаем
     * @param QVector<QString> i_tags - путь к тэгу
     /
bool GetFontDOM(QFont **i_font,QVector<QString> i_tags);


bool InitColor(QVector<QString> i_tags);
**
     * Метод сохранения шрифта
     * @param QFont i_font - шрифт который сохраняем
     * @param QVector<QString> i_tags - путь к тэгу
     /
bool SetColor(QColor i_color, QVector<QString> i_tags);

**
     * Метод получчения цвета
     * @param QColor **i_color - цвет который получаем
     * @param QVector<QString> i_tags - путь к тэгу
     /
bool GetColor(QColor **i_color, QVector<QString> i_tags);


**
     * Метод проверки пути к тэгу
     * @param QVector<QString> i_tags - путь к тэгу
     /
bool CheckTags(QVector<QString> i_tags);
*/
#endif // R_PARSER_H
