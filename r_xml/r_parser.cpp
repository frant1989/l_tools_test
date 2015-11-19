#include "r_parser.h"

R_parser::R_parser(QString i_obj_name, bool i_log):
      m_create(false)
    , m_open_read(false)
    , m_mode_flag(QIODevice::OpenModeFlag::NotOpen)
    , m_Name(i_obj_name)
    , m_log(i_log)
{
     R_Debug::Write(level8,m_Name,__PRETTY_FUNCTION__);
}

R_parser::~R_parser()
{
     R_Debug::Write(level8,m_Name,__PRETTY_FUNCTION__);
}

bool R_parser::CreateParser(QString i_path, QString i_name, QIODevice::OpenModeFlag i_mode_flag)
{
    R_Debug::Write(level8,m_Name,__PRETTY_FUNCTION__);
    if (i_path.isEmpty() || i_name.isEmpty() || m_create == true)
    {
        R_Debug::Write(warn,m_Name,__PRETTY_FUNCTION__,QString("i_path.isEmpty() or i_name.isEmpty() or  m_create == true"));
        return false;
    }

    if (R_dir::CheckExistDir(i_path) ==false)
    {
        R_Debug::Write(warn,m_Name,__PRETTY_FUNCTION__,QString("Path does not exist!!!"));
        return false;
    }
    m_file_path = i_path;
    //имя файла
    m_FileName = i_name;
    //полный путь к файлу
    m_FullName = m_file_path;
    m_FullName.push_back(m_FileName);

    //режим открытия
    m_mode_flag = i_mode_flag;

    if (InitFile() == false)
    {
        R_Debug::Write(warn,m_Name,__PRETTY_FUNCTION__,QString("InitFile() ==false!!!"));
        return false;
    }

    QDomDocument opt;
    QFile iFile(m_FullName);
    iFile.open(QFile::ReadOnly);
    opt.setContent(&iFile);
    //если нет начального тега то уходим
    QDomElement docElem = opt.documentElement();
    //если нет начального тега то уходим
    if (ExistMainTag(docElem,m_FileName)==false)
    {
        iFile.close();
        return false;
    }
    iFile.close();
    m_create = true;
    return true;
}

bool R_parser::CreateParser(QString i_full_path, QIODevice::OpenModeFlag i_mode_flag)
{
    R_Debug::Write(level8,m_Name,__PRETTY_FUNCTION__);
    if (i_full_path.isEmpty() || m_create == true)
    {
        R_Debug::Write(warn,m_Name,__PRETTY_FUNCTION__,QString("i_full_path.isEmpty()  or  m_create == true"));
        return false;
    }

    if (R_dir::CheckExistFile(i_full_path) ==false)
    {
        R_Debug::Write(warn,m_Name,__PRETTY_FUNCTION__,QString("file does not exist!!!"));
        return false;
    }
    //полный путь к файлу
    m_FullName = i_full_path;
    //режим открытия
    m_mode_flag = i_mode_flag;

    if (InitFile() == false)
    {
        R_Debug::Write(warn,m_Name,__PRETTY_FUNCTION__,QString("InitFile() ==false!!!"));
        return false;
    }

    QDomDocument opt;
    QFile iFile(m_FullName);

    QFileInfo fileInfo(iFile.fileName());

    m_file_path = fileInfo.filePath();

    m_FileName = fileInfo.fileName();

    iFile.open(QFile::ReadOnly);
    opt.setContent(&iFile);
    //если нет начального тега то уходим
    QDomElement docElem = opt.documentElement();
    //если нет начального тега то уходим
    if (ExistMainTag(docElem,m_FileName)==false)
    {
        iFile.close();
        return false;
    }
    iFile.close();
    m_create = true;
    return true;
}


int R_parser::GetTagCount(QVector<TAG> i_tags)
{
    R_Debug::Write(level9,m_Name,__PRETTY_FUNCTION__);
    if (!CheckCreateFile())
        return 0;

    // нет тэгов уходим
    int kol_tags = i_tags.size();
    if (kol_tags == 0)
        return 0;

    QDomDocument opt;
    QFile iFile;
    if (m_open_read)
    {
        opt = m_opt;
    }
    else
    {
        iFile.setFileName(m_FullName);
        iFile.open(QFile::ReadOnly);
        opt.setContent(&iFile);
    }



    //кол-во элементов
    int count_element = 0;
    //родительский элемент
    QDomElement root_element = opt.documentElement();
    //продолжаю поиск по списку тэгов
    for (int i=0;i < kol_tags; i++)
    {

        //ищем первый дочерний элемент из списка с этим именем
        QDomNodeList child = root_element.elementsByTagName( i_tags[i].name );
        //кол-во найденных
        int count_root =child.size();
        //если индекс не совпал с кол-вом
        if ( i_tags[i].id >= count_root)
        {
            if (!m_open_read)
                iFile.close();
            return 0;
        }
        //дочерний элемент становиться родительский
        root_element  = child.at(i_tags[i].id).toElement();
        //если это последний элемент
        if (i == kol_tags-1)
        {
            count_element = count_root;
        }
    }

    if (!m_open_read)
        iFile.close();
    return count_element;
}

bool R_parser::SetTagsAttr(QVector<TAG> i_tags)
{
    R_Debug::Write(level9,m_Name,__PRETTY_FUNCTION__);
    if (!CheckCreateFile())
        return 0;

    //если нет тэгов тоже уходим
    int kol_tags = i_tags.size();
    if (kol_tags == 0)
        return false;

    //КОПИЯ В domm
    QDomDocument opt;
    QFile iFile(m_FullName);
    iFile.open(QFile::ReadOnly);
    opt.setContent(&iFile);




    //родительский элемент
    QDomElement root_element = opt.documentElement();
    //продолжаю поиск по списку тэгов
    for (int i=0;i < kol_tags; i++)
    {

        //ищем первый дочерний элемент из списка с этим именем
        QDomNodeList child = root_element.elementsByTagName( i_tags[i].name );
        //кол-во найденных
        int count_root =child.size();

        // 1) если номер идекс равен кол-ву (т.е. нужно создать по порядку)
        if ( i_tags[i].id == count_root)
        {

            for (int j = i; j < kol_tags;j++)
            {
                QDomNodeList new_tags = root_element.elementsByTagName( i_tags[j].name );
                QDomElement new_tag = opt.createElement(i_tags[j].name);
                //и есть новый атрибут
                if(i_tags[j].attr != -1)
                    new_tag.setAttribute("v",i_tags[j].attr.toString());
                root_element.appendChild(new_tag);
                root_element  = new_tags.at(i_tags[j].id).toElement();
            }
            break;
        }
        // 2)если такой тэг уже есть
        else if ( i_tags[i].id < count_root)
        {
            //и есть новый атрибут
            if(i_tags[i].attr != -1)
            {
                //дочерний элемент становиться родительский
                root_element  = child.at(i_tags[i].id).toElement();
                root_element.setAttribute("v",i_tags[i].attr.toString());
            }
        }
        //3) если ничего из перечисленного уходим
        else
        {
             iFile.close();
             return false;
        }

        //дочерний элемент становиться родительский
        root_element  = child.at(i_tags[i].id).toElement();
    }



    QFile oFile(m_FullName);
    oFile.open(QFile::ReadWrite | QFile::Truncate);
    //DOM вывод в файл
    QTextStream out(&oFile);
    out.setCodec( QTextCodec::codecForName("UTF-8") );
    opt.save(out, 5, QDomNode::EncodingFromTextStream);
    oFile.close();
    iFile.close();
    return true;
}

bool R_parser::GetTagsAttr(QVector<TAG> &i_o_tags, QString i_value)
{
    R_Debug::Write(level9,m_Name,__PRETTY_FUNCTION__);
    if (!CheckCreateFile())
        return false;

    //если нет тэгов тоже уходим
    int kol_tags = i_o_tags.size();
    if (kol_tags <= 0)
        return false;
    QDomDocument opt;
    QFile iFile;
    if (m_open_read)
    {
        opt = m_opt;
    }
    else
    {
        iFile.setFileName(m_FullName);
        iFile.open(QFile::ReadOnly);
        opt.setContent(&iFile);
    }
    //родительский элемент
    QDomElement root_element = opt.documentElement();
    //продолжаю поиск по списку тэгов
    for (int i=0;i < kol_tags; i++)
    {

        //ищем первый дочерний элемент из списка с этим именем
        QDomNodeList child = root_element.elementsByTagName( i_o_tags[i].name );
        //кол-во найденных
        int count_root =child.size();
        //если индекс не совпал с кол-вом
        if ( i_o_tags[i].id >= count_root)
        {
            if (!m_open_read)
                iFile.close();
            return false;
        }

        //дочерний элемент становиться родительский
        root_element  = child.at(i_o_tags[i].id).toElement();
        QVariant attr;
        if (i_value.isEmpty())
            attr = root_element.attribute("v");
        else
            attr = root_element.attribute(i_value);
        i_o_tags[i].attr = attr;

    }

     if (!m_open_read)
        iFile.close();
    return true;
}

QVector<QVariant> R_parser::GetTagsAttr(QVector<TAG> &i_o_tags, QStringList i_list_attr)
{
    R_Debug::Write(level9,m_Name,__PRETTY_FUNCTION__);
    QVector<QVariant> values;
    QVector<TAG> tags = i_o_tags;
    TAG last;
    last = tags.last();

    for (int i =0 ; i < i_list_attr.size(); i++)
    {
        //удаляю последний
        tags.pop_back();
        last.name = i_list_attr[i];
        tags.push_back(last);
        //ищем кол-во с таким тэгов в цепочке
        if (GetTagCount(tags) != 1)
            return values;
        //получаем атрибут
        if (!GetTagsAttr(tags))
            return values;
        values.push_back(tags.last().attr);
    }
    return values;
}
bool R_parser::OpenForRead()
{
    R_Debug::Write(level8,m_Name,__PRETTY_FUNCTION__);
    if (m_mode_flag != QIODevice::OpenModeFlag::ReadOnly)
        return false;
    //КОПИЯ В domm

    m_ifile.setFileName(m_FullName);
    m_ifile.open(QFile::ReadOnly);
    m_opt.setContent(&m_ifile);
    m_open_read = true;
    return true;
}

bool R_parser::CloseForRead()
{
    R_Debug::Write(level8,m_Name,__PRETTY_FUNCTION__);
    if (m_mode_flag != QIODevice::OpenModeFlag::ReadOnly)
        return false;
    m_ifile.close();
    m_open_read = false;
    return true;
}


bool R_parser::InitFile()
{
    R_Debug::Write(level8,m_Name,__PRETTY_FUNCTION__);
    auto file= new QFile(m_FullName);
    if(!file->open(m_mode_flag))
    {

        R_Debug::Write(crit,m_Name,__PRETTY_FUNCTION__,QString("Error::Can not open file!!!"));
        return false;
    }

    file->close();
    return true;
}


bool R_parser::ExistMainTag(QDomElement i_docElem,QString check_main)
{
    R_Debug::Write(level10,m_Name,__PRETTY_FUNCTION__);
    if (check_main != i_docElem.tagName())
    {
        QString str = " m_create false start tag = ";
        str.push_back(i_docElem.tagName());
        R_Debug::Write(warn,m_Name,__PRETTY_FUNCTION__,str);

        return false;
    }
    return true;
}

bool R_parser::CheckCreateFile()
{
    R_Debug::Write(level10,m_Name,__PRETTY_FUNCTION__);
    if (m_create == false)
    {
        R_Debug::Write(warn,m_Name,__PRETTY_FUNCTION__,QString("m_create == false"));
        return false;
    }
    else
        return true;
}
/*
 *
 *
    //Атрибуты для шрифта
    m_Font = "Font";
    att_family_font = "Family";
    att_point_font = "Point";
    att_pixel_font= "Pixel";
    att_styleHint_font = "StyleHint";
    att_weight_font = "Weight";
    att_bold_font = "bold";
    att_kerning_font = "Kerning";
    att_italic_font = "Italic";
    att_overline_font = "Overline" ;
    att_underline_font= "Underline" ;
    att_strike_out = "Strike";
    //атрибуты для цвета
    att_rgb_red = "rgb_red";
    att_rgb_green = "rgb_green";
    att_rgb_blue = "rgb_blue";


bool R_parser::SetTags(QVector<QString> i_tags)
{
    qDebug()<< "bool R_parser::SetTags(QVector<QString> i_tags)";
    if (m_create == false)
    {
        qDebug()<< "bool R_parser::SetTags m_create == false";
        return false;
    }
    //если нет тэгов тоже уходим
    int kol_tags = i_tags.size();
    if (kol_tags == 0)
        return 0;
    //копия в dom
    QDomDocument opt;
    QFile iFile(m_FullName);
    iFile.open(QFile::ReadOnly);
    opt.setContent(&iFile);
    QFile oFile(m_FullName);
    oFile.open(QFile::ReadWrite | QFile::Truncate);

    QDomElement documentElement = opt.documentElement();
    QDomNodeList elements = documentElement.elementsByTagName( i_tags[0] );
    //если нет элемента то создаю его
    if( elements.size() == 0 )
    {
        QDomElement Tag = opt.createElement(i_tags[0]);
        documentElement.appendChild(Tag);
    }

    // ищу елемент с таким именем
    QDomNodeList find_element = documentElement.elementsByTagName( i_tags[0] );

    //цикл по тегам
    for (int i=1;i< kol_tags; i++)
    {
        //нашел элемент
        QDomElement elem  = find_element.at(0).toElement();
        //имя элемента
        QString tag = elem.tagName();
        // в этом элементе ищу следующий
        find_element = elem.elementsByTagName( i_tags[i] );
        //если есть такой элемент
        QDomNodeList el_next= find_element;
        int size_el = el_next.size();
        //если есть
        if( size_el == 0 )
        {
            QDomElement NewTag = opt.createElement(i_tags[i]);
            elem.appendChild(NewTag);
        }
    }





    //DOM вывод в файл
    QTextStream out(&oFile);
    out.setCodec( QTextCodec::codecForName("UTF-8") );
    opt.save(out, 5, QDomNode::EncodingFromTextStream);
    oFile.close();
    iFile.close();
    return true;
}



bool R_parser::InitFontDOM(QVector<QString> i_tags)
{
    qDebug()<< "bool R_parser::InitFontDOM(QVector<QString> i_tags)";
    if (m_create == false)
    {
        qDebug()<< "R_parser::InitFontDOM m_create == false";
        return false;
    }
    //есть ли тэги
    int kol_tags = i_tags.size();
    if (kol_tags == 0)
        return false;
    //проверка тэгов
    bool check_tags = CheckTags(i_tags);
    if (check_tags == false)
        return false;
    //КОПИЯ В domm
    QDomDocument opt;
    QFile iFile(m_FullName);
    iFile.open(QFile::ReadOnly);
    opt.setContent(&iFile);

    QFile oFile(m_FullName);
    oFile.open(QFile::ReadWrite | QFile::Truncate);

    //начало документа
    QDomElement documentElement = opt.documentElement();
    // ищу елемент с таким именем
    QDomNodeList find_element = documentElement.elementsByTagName( i_tags[0] );
    //цикл по тегам
    bool check = true;
    for (int i=1;i< kol_tags; i++)
    {
        //нашел элемент
        QDomElement elem  = find_element.at(0).toElement();
        //имя элемента
        QString tag = elem.tagName();
        // в этом элементе ищу следующий
        find_element = elem.elementsByTagName( i_tags[i] );
        //если есть такой элемент
        QDomNodeList el_next= find_element;
        int size_el = el_next.size();
        //если есть
        if( size_el != 1 )
        {
            check =  false;
            break;
        }
    }
    if (check == false)
        return false;


    //если есть такой элемент
    QDomNodeList elements = find_element;
    bool check_font = false;
    if( elements.size() == 1 )
    {

        QDomElement elem = elements.at(0).toElement();
        //если уже есть шрифт в тэге то не даю его инициализировать еще раз
        for(QDomNode n1 = elem.firstChild(); !n1.isNull(); n1 = n1.nextSiblingElement())
        {

            QDomElement elem_child= n1.toElement();
            QString tag = elem_child.tagName();
            if (tag == m_Font)
            {
                check_font = true;
                break;

            }
        }
        //если нет тэга шрифта
        if (check_font == false)
        {

            QDomElement Font = opt.createElement(m_Font);
            QDomElement family_font = opt.createElement(att_family_font);
            QDomElement point_font = opt.createElement(att_point_font);
            QDomElement pixel_font = opt.createElement(att_pixel_font);
            QDomElement styleHint_font = opt.createElement(att_styleHint_font);
            QDomElement weight_font = opt.createElement(att_weight_font);
            QDomElement bold_font = opt.createElement(att_bold_font);
            QDomElement kerning_font = opt.createElement(att_kerning_font);
            QDomElement italic_font = opt.createElement(att_italic_font);
            QDomElement overline_font = opt.createElement(att_overline_font);
            QDomElement underline_font = opt.createElement(att_underline_font);
            QDomElement strike_out = opt.createElement(att_strike_out);

            Font.appendChild(family_font);
            Font.appendChild(point_font);
            Font.appendChild(pixel_font);
            Font.appendChild(styleHint_font);
            Font.appendChild(weight_font);
            Font.appendChild(bold_font);
            Font.appendChild(kerning_font);
            Font.appendChild(italic_font);
            Font.appendChild(overline_font);
            Font.appendChild(underline_font);
            Font.appendChild(strike_out);
            elem.appendChild(Font);
        }
    }
    //DOM вывод в файл
    QTextStream out(&oFile);
    out.setCodec( QTextCodec::codecForName("UTF-8") );
    opt.save(out, 5, QDomNode::EncodingFromTextStream);
    oFile.close();
    iFile.close();

    if (check == false)
    {
        //Шрифт по умолчанию
        QFont cur_Font = QFont("Times new Roman", 12);
        SetFontDOM(cur_Font,i_tags);
    }
    return true;


}

bool R_parser::SetFontDOM(QFont i_font, QVector<QString> i_tags)
{
    qDebug()<< "bool R_parser::SetFontDOM(QFont i_font, QVector<QString> i_tags)";
    if (m_create == false)
    {
        qDebug()<< "bool R_parser::SetFontDOM m_create == false";
        return false;
    }
    //есть ли тэги
    int kol_tags = i_tags.size();
    if (kol_tags == 0)
        return false;
    //проверка тэгов
    bool check_tags = CheckTags(i_tags);
    if (check_tags == false)
        return false;
    //КОПИЯ В domm
    QDomDocument opt;
    QFile iFile(m_FullName);
    iFile.open(QFile::ReadOnly);
    opt.setContent(&iFile);


    QFile oFile(m_FullName);
    oFile.open(QFile::ReadWrite | QFile::Truncate);

    //начало документа
    QDomElement documentElement = opt.documentElement();
    // ищу елемент с таким именем
    QDomNodeList find_element = documentElement.elementsByTagName( i_tags[0] );
    //цикл по тегам
    bool check = true;
    for (int i=1;i< kol_tags; i++)
    {
        //нашел элемент
        QDomElement elem  = find_element.at(0).toElement();
        //имя элемента
        QString tag = elem.tagName();
        // в этом элементе ищу следующий
        find_element = elem.elementsByTagName( i_tags[i] );
        //если есть такой элемент
        QDomNodeList el_next= find_element;
        int size_el = el_next.size();
        //если есть
        if( size_el != 1 )
        {
            check =  false;
            break;
        }
    }
    if (check == false)
        return false;


    QDomNodeList elements = find_element;
    if( elements.size() == 1 )
    {
        QDomElement TagFont = elements.at(0).toElement();
        QDomElement Font =TagFont;
        bool check_font = false;
        for(QDomNode n1 = TagFont.firstChild(); !n1.isNull(); n1 = n1.nextSiblingElement())
        {
            QDomElement elem= n1.toElement();
            QString tag = elem.tagName();
            if (tag == m_Font)
            {
                check_font = true;
                Font =n1.toElement();
                break;
            }
        }
        if (check_font == false)
        {
            oFile.close();
            iFile.close();
            return false;
        }

        QVariant family_font = i_font.family();
        QVariant point_font = i_font.pointSize();
        QVariant pixel_font =  i_font.pixelSize ();
        QVariant styleHint_font = i_font.styleHint();
        QVariant weight_font= i_font.weight();
        QVariant bold_font =  i_font.bold();
        QVariant kerning_font = i_font.kerning();
        QVariant italic_font = i_font.italic();
        QVariant overline_font = i_font.overline();
        QVariant underline_font = i_font.underline();
        QVariant strike_out = i_font.strikeOut();

        for(QDomNode n1 = Font.firstChild(); !n1.isNull(); n1 = n1.nextSiblingElement())
        {
            QDomElement elem= n1.toElement();
            QString tag = elem.tagName();
            if (tag == att_family_font)
            {
                QString text = family_font.toString();
                elem.setAttribute("v",text);
                continue;
            }

            if (tag == att_point_font)
            {
                 QString text = point_font.toString();
                elem.setAttribute("v",point_font.toString());
                    continue;
            }
            if (tag == att_pixel_font)
            {
                 QString text = pixel_font.toString();
                elem.setAttribute("v",pixel_font.toString());
                    continue;
            }
            if (tag == att_styleHint_font)
            {
                 QString text =styleHint_font.toString();
                elem.setAttribute("v",styleHint_font.toString());
                    continue;
            }
            if (tag == att_weight_font)
            {
                QString text = weight_font.toString();
                elem.setAttribute("v",weight_font.toString());
                    continue;
            }
            if (tag == att_bold_font)
            {
                 QString text = bold_font.toString();
                elem.setAttribute("v",bold_font.toString());
                    continue;
            }
            if (tag == att_kerning_font)
            {
                 QString text = kerning_font.toString();
                elem.setAttribute("v",kerning_font.toString());
                    continue;
            }
            if (tag == att_italic_font)
            {
                 QString text = italic_font.toString();
                elem.setAttribute("v",italic_font.toString());
                    continue;
            }
            if (tag == att_overline_font)
            {
                 QString text = overline_font.toString();
                elem.setAttribute("v",overline_font.toString());
                    continue;
            }
            if (tag == att_underline_font)
            {
                 QString text = underline_font.toString();
                elem.setAttribute("v",underline_font.toString());
                    continue;
            }
            if (tag == att_strike_out)
            {
                QString text = strike_out.toString();
                elem.setAttribute("v",strike_out.toString());
                    continue;
            }

        }
    }
    //DOM вывод в файл
    QTextStream out(&oFile);
    out.setCodec( QTextCodec::codecForName("UTF-8") );
    opt.save(out, 5, QDomNode::EncodingFromTextStream);
    oFile.close();
    iFile.close();
     return true;
}

bool R_parser::GetFontDOM(QFont **i_font, QVector<QString> i_tags)
{
    qDebug()<< "bool R_parser::GetFontDOM(QFont **i_font, QVector<QString> i_tags)";
    if (m_create == false)
    {
        qDebug()<< "bool R_parser::GetFontDOM m_create == false";
        return false;
    }
    if (*i_font != NULL)
        return false;
    //есть ли тэги
    int kol_tags = i_tags.size();
    if (kol_tags == 0)
        return false;
    //проверка тэгов
    bool check_tags = CheckTags(i_tags);
    if (check_tags == false)
        return false;

    //КОПИЯ В domm
    QDomDocument opt;
    QFile iFile(m_FullName);
    iFile.open(QFile::ReadOnly);
    opt.setContent(&iFile);


    //начало документа
    QDomElement documentElement = opt.documentElement();
    // ищу елемент с таким именем
    QDomNodeList find_element = documentElement.elementsByTagName( i_tags[0] );
    //цикл по тегам
    bool check = true;
    for (int i=1;i< kol_tags; i++)
    {
        //нашел элемент
        QDomElement elem  = find_element.at(0).toElement();
        //имя элемента
        QString tag = elem.tagName();
        // в этом элементе ищу следующий
        find_element = elem.elementsByTagName( i_tags[i] );
        //если есть такой элемент
        QDomNodeList el_next= find_element;
        int size_el = el_next.size();
        //если есть
        if( size_el != 1 )
        {
            check =  false;
            break;
        }
    }
    if (check == false)
        return false;

    //найденный элемент
    QDomNodeList elements = find_element;
    if( elements.size() == 1 )
    {
        QDomElement Tag_font = elements.at(0).toElement();
        QDomElement Font = Tag_font;
        bool check = false;
        for(QDomNode n1 = Tag_font.firstChild(); !n1.isNull(); n1 = n1.nextSiblingElement())
        {
            QDomElement elem= n1.toElement();
            QString tag = elem.tagName();
            if (tag == m_Font)
            {
               check = true;
               Font = elem;
               break;
            }

        }
        if (check == false)
        {
            iFile.close();
            return false;
        }
        QVariant family_font;
        QVariant point_font ;
        QVariant pixel_font ;
        QVariant styleHint_font ;
        QVariant weight_font;
        QVariant bold_font ;
        QVariant kerning_font ;
        QVariant italic_font;
        QVariant overline_font ;
        QVariant underline_font;
        QVariant strike_out;
         for(QDomNode n1 = Font.firstChild(); !n1.isNull(); n1 = n1.nextSiblingElement())
         {
             QDomElement elem= n1.toElement();
             QString tag = elem.tagName();
             if (tag == att_family_font)
             {
                 family_font = elem.attribute("v");
             }

             if (tag == att_point_font)
             {
                  point_font = elem.attribute("v");
             }
             if (tag == att_pixel_font)
             {
                 pixel_font = elem.attribute("v");
             }
             if (tag == att_styleHint_font)
             {
                 styleHint_font = elem.attribute("v");
             }
             if (tag == att_weight_font)
             {
                 weight_font = elem.attribute("v");
             }
             if (tag == att_bold_font)
             {
                bold_font = elem.attribute("v");
             }
             if (tag == att_kerning_font)
             {
                  kerning_font = elem.attribute("v");
             }
             if (tag == att_italic_font)
             {
                  italic_font = elem.attribute("v");
             }
             if (tag == att_overline_font)
             {
                  overline_font = elem.attribute("v");
             }
             if (tag == att_underline_font)
             {
                  underline_font = elem.attribute("v");
             }
             if (tag == att_strike_out)
             {
                   strike_out = elem.attribute("v");
             }

         }

         if (family_font.toString() != "")
         {
             QString test =  bold_font.toString();

             *i_font = new QFont(family_font.toString(),point_font.toInt());
              (*i_font)->setPointSize(point_font.toInt());
              (*i_font)->setPixelSize(pixel_font.toInt());


              (*i_font)->setWeight(weight_font.toInt());
             if (bold_font.toString() == "false")
                  (*i_font)->setBold(false);
              else
                  (*i_font)->setBold(true);

             if (kerning_font.toString() == "false")
                  (*i_font)->setKerning(false);
              else
                  (*i_font)->setKerning(true);

             if (italic_font.toString() == "false")
                  (*i_font)->setItalic(false);
              else
                  (*i_font)->setItalic(true);

             if (overline_font.toString() == "false")
                  (*i_font)->setOverline(false);
              else
                  (*i_font)->setOverline(true);

             if (underline_font.toString() == "false")
                  (*i_font)->setUnderline(false);
              else
                  (*i_font)->setUnderline(true);

             if (strike_out.toString() == "false")
                  (*i_font)->setStrikeOut(false);
              else
                  (*i_font)->setStrikeOut(true);

         }
    }
    iFile.close();

    return true;
}

bool R_parser::InitColor(QVector<QString> i_tags)
{
    qDebug()<< "bool R_parser::InitColor(QVector<QString> i_tags)";
    if (m_create == false)
    {
        qDebug()<< "bool R_parser::InitColor m_create == false";
        return false;
    }
    //есть ли тэги
    int kol_tags = i_tags.size();
    if (kol_tags == 0)
        return false;
    //проверка тэгов
    bool check_tags = CheckTags(i_tags);
    if (check_tags == false)
        return false;

    //КОПИЯ В domm
    QDomDocument opt;
    QFile iFile(m_FullName);
    iFile.open(QFile::ReadOnly);
    opt.setContent(&iFile);

    QFile oFile(m_FullName);
    oFile.open(QFile::ReadWrite | QFile::Truncate);

    //начало документа
    QDomElement documentElement = opt.documentElement();
    // ищу елемент с таким именем
    QDomNodeList find_element = documentElement.elementsByTagName( i_tags[0] );
    //цикл по тегам
    bool check = true;
    for (int i=1;i< kol_tags; i++)
    {
        //нашел элемент
        QDomElement elem  = find_element.at(0).toElement();
        //имя элемента
        QString tag = elem.tagName();
        // в этом элементе ищу следующий
        find_element = elem.elementsByTagName( i_tags[i] );
        //если есть такой элемент
        QDomNodeList el_next= find_element;
        int size_el = el_next.size();
        //если есть
        if( size_el != 1 )
        {
            check =  false;
            break;
        }
    }
    if (check == false)
        return false;

    //если есть такой элемент
    QDomNodeList elements = find_element;
    if( elements.size() != 0 )
    {
        bool red = false;
        bool green = false;
        bool blue = false;
        QDomElement elem = elements.at(0).toElement();
        for(QDomNode n1 = elem.firstChild(); !n1.isNull(); n1 = n1.nextSiblingElement())
        {
            QDomElement elemchild= n1.toElement();
            QString tag = elemchild.tagName();
            if (tag == att_rgb_red)
                red = true;
            if (tag == att_rgb_green)
                green = true;
            if (tag == att_rgb_blue)
                blue = true;

        }
        if (red == false)
        {
            QDomElement rgb_red = opt.createElement(att_rgb_red);
            rgb_red.setAttribute("v",-1);
            elem.appendChild(rgb_red);
        }
        if (green == false)
        {
            QDomElement rgb_green = opt.createElement(att_rgb_green);
            rgb_green.setAttribute("v",-1);
            elem.appendChild(rgb_green);
        }
        if (blue == false)
        {
            QDomElement rgb_blue = opt.createElement(att_rgb_blue);
            rgb_blue.setAttribute("v",-1);
            elem.appendChild(rgb_blue);
        }

    }


    QTextStream out(&oFile);
    out.setCodec( QTextCodec::codecForName("UTF-8") );
    opt.save(out, 5, QDomNode::EncodingFromTextStream);
    oFile.close();
    iFile.close();
     return true;
}

bool R_parser::SetColor(QColor i_color,QVector <QString> i_tags)
{
    qDebug()<< "bool R_parser::SetColor(QColor i_color,QVector <QString> i_tags)";
    if (m_create == false)
    {
        qDebug()<< "bool R_parser::SetColor m_create == false";
        return false;
    }
    //есть ли тэги
    int kol_tags = i_tags.size();
    if (kol_tags == 0)
        return false;
    //проверка тэгов
    bool check_tags = CheckTags(i_tags);
    if (check_tags == false)
        return false;
    //КОПИЯ В domm
    QDomDocument opt;
    QFile iFile(m_FullName);
    iFile.open(QFile::ReadOnly);
    opt.setContent(&iFile);

    //открыли файл для записи
    QFile oFile(m_FullName);
    oFile.open(QFile::ReadWrite | QFile::Truncate);

    //начало документа
    QDomElement documentElement = opt.documentElement();
    // ищу елемент с таким именем
    QDomNodeList find_element = documentElement.elementsByTagName( i_tags[0] );
    //цикл по тегам
    bool check = true;
    for (int i=1;i< kol_tags; i++)
    {
        //нашел элемент
        QDomElement elem  = find_element.at(0).toElement();
        //имя элемента
        QString tag = elem.tagName();
        // в этом элементе ищу следующий
        find_element = elem.elementsByTagName( i_tags[i] );
        //если есть такой элемент
        QDomNodeList el_next= find_element;
        int size_el = el_next.size();
        //если есть
        if( size_el != 1 )
        {
            check =  false;
            break;
        }
    }
    if (check == false)
        return false;

    QVariant red =  i_color.red();
    QVariant green = i_color.green();
    QVariant blue = i_color.blue();

    QDomNodeList elements = find_element;
    if( elements.size() == 1 )
    {
        QDomElement elem = elements.at(0).toElement();
        for(QDomNode n1 = elem.firstChild(); !n1.isNull(); n1 = n1.nextSiblingElement())
        {
            QDomElement elem= n1.toElement();
            QString tag = elem.tagName();
            if (tag == att_rgb_red)
            {

                QString text = red.toString();
                elem.setAttribute("v",text);
                continue;
            }
            if (tag == att_rgb_green)
            {
                QString text = green.toString();
                elem.setAttribute("v",text);
                continue;
            }
            if (tag == att_rgb_blue)
            {
                QString text = blue.toString();
                elem.setAttribute("v",text);
                continue;
            }
        }
    }
    //DOM вывод в файл
    QTextStream out(&oFile);
    out.setCodec( QTextCodec::codecForName("UTF-8") );
    opt.save(out, 5, QDomNode::EncodingFromTextStream);
    oFile.close();
    iFile.close();
    return true;
}

bool R_parser::GetColor(QColor **i_color,QVector<QString> i_tags)
{
    qDebug()<< "bool R_parser::GetColor(QColor **i_color,QVector<QString> i_tags)";
    if (m_create == false)
    {
        qDebug()<< "bool R_parser::GetColor m_create == false";
        return false;
    }
    //есть ли тэги
    int kol_tags = i_tags.size();
    if (kol_tags == 0)
        return false;
    //проверка тэгов
    bool check_tags = CheckTags(i_tags);
    if (check_tags == false)
        return false;

    if ( *i_color  != NULL)
        return false;
    //КОПИЯ В domm
    QDomDocument opt;
    QFile iFile(m_FullName);
    iFile.open(QFile::ReadOnly);
    opt.setContent(&iFile);

    QVariant red =-1;
    QVariant green = -1;
    QVariant blue  =-1;


    QDomElement documentElement = opt.documentElement();
    // ищу елемент с таким именем
    QDomNodeList find_element = documentElement.elementsByTagName( i_tags[0] );
    //цикл по тегам
    bool check = true;
    for (int i=1;i< kol_tags; i++)
    {
        //нашел элемент
        QDomElement elem  = find_element.at(0).toElement();
        //имя элемента
        QString tag = elem.tagName();
        // в этом элементе ищу следующий
        find_element = elem.elementsByTagName( i_tags[i] );
        //если есть такой элемент
        QDomNodeList el_next= find_element;
        int size_el = el_next.size();
        //если есть
        if( size_el != 1 )
        {
            check =  false;
            break;
        }
    }
    if (check == false)
        return false;
    //найденный элемент
    QDomNodeList elements = find_element;
    if( elements.size() == 1 )
    {
        QDomElement elem = elements.at(0).toElement();
        for(QDomNode n1 = elem.firstChild(); !n1.isNull(); n1 = n1.nextSiblingElement())
        {
            QDomElement elem= n1.toElement();
            QString tag = elem.tagName();
            if (tag == att_rgb_red)
                red = elem.attribute("v");

            if (tag == att_rgb_green)
                green = elem.attribute("v");

            if (tag == att_rgb_blue)
                blue = elem.attribute("v");

        }
    }
    if (red.toInt()==-1 ||green.toInt() == -1|| blue.toInt() == -1)
    {
        iFile.close();
        return false;
    }
    *i_color= new QColor(red.toInt(),green.toInt(),blue.toInt());

    iFile.close();

    return true;
}

bool R_parser::CheckTags( QVector<QString> i_tags)
{
    qDebug()<< "bool R_parser::CheckTags( QVector<QString> i_tags)";
    if (m_create == false)
    {
        qDebug()<< "R_parser::CheckTags m_create == false";
        return false;
    }
    // нет тэгов уходим
    int kol_tags = i_tags.size();
    if (kol_tags == 0)
    {
        return false;
    }
    //КОПИЯ В domm
    QDomDocument opt;
    QFile iFile(m_FullName);
    iFile.open(QFile::ReadOnly);
    opt.setContent(&iFile);

    QDomElement documentElement = opt.documentElement();
    //если есть хоть один элемент
    QDomNodeList elements = documentElement.elementsByTagName( i_tags[0] );
    if( elements.size() == 0 )
    {
        iFile.close();
        return false;
    }

    // ищу елемент с таким именем
    QDomNodeList find_element = documentElement.elementsByTagName( i_tags[0] );
    //цикл по тегам
    bool check = true;
    for (int i=1;i< kol_tags; i++)
    {
        //нашел элемент
        QDomElement elem  = find_element.at(0).toElement();
        //имя элемента
        QString tag = elem.tagName();
        // в этом элементе ищу следующий
        find_element = elem.elementsByTagName( i_tags[i] );
        //если есть такой элемент
        QDomNodeList el_next= find_element;
        int size_el = el_next.size();
        //если есть
        if( size_el <= 0 )
        {
            check =  false;
            break;
        }

    }
    if (check == false)
    {
        iFile.close();
        return false;
    }
    iFile.close();
    return true;

}*/


