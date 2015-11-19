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

///��������� ���� ��� ������
struct TAG
{
    ///��� ����
    QString name;
    ///����� � ������
    int id;
    /// ��������
    QVariant attr;
    TAG()
    {
        id=0;
        attr = -1;
    }
};


/**
@class R_parser
* ����� ��� �������� xml ���� � ������� DOM
* ����� ������������ ��� ��������, ������ � ����������� ���������� �� xml �����
*/
class R_parser:public QObject
{
    Q_OBJECT
public:

    /**
         * ����������� ������
         */
    explicit R_parser(QString i_obj_name,bool i_log);

    R_parser(const R_parser&) = delete;

    /**
         * ���������� ������
         */

    virtual ~R_parser();

    /**
         * ����� �������� � ������������� �������
         * @param QString i_path - ���� � ����������
         * @param QString i_name - ��� �����
         */
    bool CreateParser(QString i_path, QString i_name, QIODevice::OpenModeFlag i_mode_flag);

    /**
         * ����� �������� � ������������� �������
         * @param QString i_path - ���� � ����������
         * @param QString i_name - ��� �����
         */
    bool CreateParser(QString i_full_path, QIODevice::OpenModeFlag i_mode_flag);

    /**
         * ����� ������������ ���-�� �����
         * @param QVector<TAG> i_tags - ���� � ����
         */
    int GetTagCount(QVector<TAG> i_tags);

    /**
         * ����� ���������� ���� ���������
         * @param QVector<TAG> i_tags - ���� � ����
         */
    bool SetTagsAttr(QVector<TAG> i_tags);

    /**
         * ����� ���������� ���� ���������
         * @param QVector<TAG> i_tags - ���� � ����, ����������� ��� ���������� TAG.attr
         */
    bool GetTagsAttr(QVector<TAG> &i_o_tags, QString i_value = QString());



    /**
         * ����� ������������ ������ ���������
         * @param QVector<TAG> i_tags - ���� � ����, ����������� ��� ���������� TAG.attr
         * @param QStringList i_list_attr  - ������ ���������
         */
    QVector <QVariant> GetTagsAttr(QVector<TAG> &i_o_tags,QStringList i_list_attr );

    /**
         * ����� �������� ������ ��� ������ �������� �������������� ��� ������
         */
    bool OpenForRead();

    /**
         * ����� �������� ������ ��� ������
         */
    bool CloseForRead();

protected:

     /**
         * ����� ������������� �����
         */
    bool InitFile();

    /**
         * ����� �������� ������� �������� ����
         * @param QDomElement i_docElem -������� ������� ���������
         * @param QString i_Main - ��� �������� ����
         */
    bool ExistMainTag(QDomElement i_docElem, QString i_Main);

    /**
        * ����� �������� �������� �����
        */
    bool CheckCreateFile();

    ///������� ��������
    bool m_create;
    ///������� �������� ��� ������
    bool m_open_read;

    ///��� �����
    QString m_FileName;
    ///���� � �����
    QString m_file_path;
    ///������ ����  ���� � ����� + ���
    QString m_FullName;

    QIODevice::OpenModeFlag m_mode_flag;


    QDomDocument m_opt;

    QFile m_ifile;

//����� ��������
    /// ��� �������
    QString m_Name;
    ///������� �������� �����
    bool m_log;
};


/*
 *
 *  //�������� ������

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
//-----����� ���������

//��������� �����
    QString att_rgb_red;
    QString att_rgb_green;
    QString att_rgb_blue;
//
**
     * ����� �������� ����
     * @param QVector<QString> i_tags - ���� � ����
     /
bool SetTags(QVector<QString> i_tags);
**
     * ����� ������������ ������
     * @param QVector<QString> i_tags - ���� � ����
     /
bool InitFontDOM(QVector<QString> i_tags);

**
     * ����� ���������� ������
     * @param QFont i_font - ����� ������� ���������
     * @param QVector<QString> i_tags - ���� � ����
    /
bool SetFontDOM(QFont i_font, QVector<QString> i_tags);

**
     * ����� ��������� ������
     * @param (QFont **i_font - ����� ������� �������
     * @param QVector<QString> i_tags - ���� � ����
     /
bool GetFontDOM(QFont **i_font,QVector<QString> i_tags);


bool InitColor(QVector<QString> i_tags);
**
     * ����� ���������� ������
     * @param QFont i_font - ����� ������� ���������
     * @param QVector<QString> i_tags - ���� � ����
     /
bool SetColor(QColor i_color, QVector<QString> i_tags);

**
     * ����� ���������� �����
     * @param QColor **i_color - ���� ������� ��������
     * @param QVector<QString> i_tags - ���� � ����
     /
bool GetColor(QColor **i_color, QVector<QString> i_tags);


**
     * ����� �������� ���� � ����
     * @param QVector<QString> i_tags - ���� � ����
     /
bool CheckTags(QVector<QString> i_tags);
*/
#endif // R_PARSER_H
