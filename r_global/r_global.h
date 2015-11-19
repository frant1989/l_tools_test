#ifndef R_GLOBAL
#define R_GLOBAL
#include <QString>
#include <QDebug>
#include <QTime>
#include <QDate>


#define FF -1


static std::string debug_any = "any";
static std::string debug_info = "info";
static std::string debug_warn = "warn";
static std::string debug_crit = "crit";
static std::string debug_level1 = "level1";
static std::string debug_level2 = "level2";
static std::string debug_level3 = "level3";
static std::string debug_level4 = "level4";
static std::string debug_level5 = "level5";
static std::string debug_level6 = "level6";
static std::string debug_level7 = "level7";
static std::string debug_level8 = "level8";
static std::string debug_level9 = "level9";
static std::string debug_level10 = "level10";

enum r_deb_levels
{
    any = 1 ,//все логи
    warn,//предупреждения (без которых можем работать но не желательно)
    crit,//критические (приводят к ошибкам в командах)
    info,//информационные (обычно информационное сообщение)
    //далее идут детальный вывод по вложению информации
    level1,
    level2,
    level3,
    level4,
    level5,
    level6,
    level7,
    level8,//резервируется под PRETTY_FUNCTION
    level9,//резервируется под частый вызов PRETTY_FUNCTION
    level10,//резервируется под еще более частый вызов PRETTY_FUNCTION
    end_deb_levels
};
inline std::ostream& operator<< (std::ostream & os, r_deb_levels const & levels)
{
    switch (levels)
    {
        case r_deb_levels::any :
            return os << debug_any ;
        case r_deb_levels::warn:
            return os << debug_warn;
        case r_deb_levels::crit:
            return os << debug_crit;
        case r_deb_levels::info:
            return os << debug_info;
        case r_deb_levels::level1:
            return os << debug_level1;
        case r_deb_levels::level2:
            return os << debug_level2;
        case r_deb_levels::level3:
            return os << debug_level3;
        case r_deb_levels::level4:
            return os << debug_level4;
        case r_deb_levels::level5:
            return os << debug_level5;
        case r_deb_levels::level6:
            return os << debug_level6;
        case r_deb_levels::level7:
            return os << debug_level7;
        case r_deb_levels::level8:
            return os << debug_level8;
        case r_deb_levels::level9:
            return os << debug_level9;
        case r_deb_levels::level10:
            return os << debug_level10;
        case r_deb_levels::end_deb_levels:
            return os << "";
    }
        // omit default case to trigger compiler warning for missing cases
    return os << "";
};


#define PRELOG_PF(i_str) \
(\
qDebug()<<QDate::currentDate().toString("dd.MM.yyyy")<< " " <<QTime::currentTime().toString("hh:mm:ss:zzz") <<": " <<i_str <<" "<<__PRETTY_FUNCTION__<<" "\
)


#define STR_DEB_FUNC(o_str,i_level,i_obj_name, i_function) \
 ( \
    (o_str.push_back(QDate::currentDate().toString("dd.MM.yyyy"))), \
    (o_str.push_back('"')), \
    (o_str.push_back("   ")), \
    (o_str.push_back('"')), \
    (o_str.push_back(QTime::currentTime().toString("hh:mm:ss:zzz"))), \
    (o_str.push_back('"')), \
    (o_str.push_back(" : ")), \
    (o_str.push_back('"')), \
    (o_str.push_back(i_level)), \
    (o_str.push_back('"')), \
    (o_str.push_back(" : ")), \
    (o_str.push_back('"')), \
    (o_str.push_back(i_obj_name)), \
    (o_str.push_back('"')), \
    (o_str.push_back(" : ")), \
    (o_str.push_back('"')), \
    (o_str.push_back(i_function)), \
    (qDebug()<<o_str)  \
 )
#define STR_DEB_TEXT(o_str,i_level,i_obj_name, i_function, i_str) \
 ( \
    (o_str.push_back(QDate::currentDate().toString("dd.MM.yyyy"))), \
    (o_str.push_back('"')), \
    (o_str.push_back("   ")), \
    (o_str.push_back('"')), \
    (o_str.push_back(QTime::currentTime().toString("hh:mm:ss:zzz"))), \
    (o_str.push_back('"')), \
    (o_str.push_back(" : ")), \
    (o_str.push_back('"')), \
    (o_str.push_back(i_level)), \
    (o_str.push_back('"')), \
    (o_str.push_back(" : ")), \
    (o_str.push_back('"')), \
    (o_str.push_back(i_obj_name)), \
    (o_str.push_back('"')), \
    (o_str.push_back(" : ")), \
    (o_str.push_back('"')), \
    (o_str.push_back(i_function)), \
    (o_str.push_back('"')), \
    (o_str.push_back(" : ")), \
    (o_str.push_back('"')), \
    (o_str.push_back(i_str)), \
    (qDebug()<<o_str)  \
 )

#define PRELOG_PF_STR(o_str,i_obj_name,i_str) \
 ( \
    (o_str.push_back(QDate::currentDate().toString("dd.MM.yyyy"))), \
    (o_str.push_back('"')), \
    (o_str.push_back("   ")), \
    (o_str.push_back('"')), \
    (o_str.push_back(QTime::currentTime().toString("hh:mm:ss:zzz"))), \
    (o_str.push_back('"')), \
    (o_str.push_back(" : ")), \
    (o_str.push_back('"')), \
    (o_str.push_back(i_obj_name)), \
    (o_str.push_back('"')), \
    (o_str.push_back(" ")), \
    (o_str.push_back('"')), \
    (o_str.push_back(i_str)), \
    (o_str.push_back('"')), \
    (o_str.push_back("  ")), \
    (o_str.push_back(__PRETTY_FUNCTION__)), \
    (o_str.push_back(" ")) \
 )

#define PRELOG_PF_STR_DEB(o_str,i_obj_name,i_str) \
 ( \
    (o_str.push_back(QDate::currentDate().toString("dd.MM.yyyy"))), \
    (o_str.push_back('"')), \
    (o_str.push_back("   ")), \
    (o_str.push_back('"')), \
    (o_str.push_back(QTime::currentTime().toString("hh:mm:ss:zzz"))), \
    (o_str.push_back('"')), \
    (o_str.push_back(" : ")), \
    (o_str.push_back('"')), \
    (o_str.push_back(i_obj_name)), \
    (o_str.push_back('"')), \
    (o_str.push_back(" ")), \
    (o_str.push_back('"')), \
    (o_str.push_back(i_str)), \
    (o_str.push_back('"')), \
    (o_str.push_back("  ")), \
    (o_str.push_back(__PRETTY_FUNCTION__)), \
    (o_str.push_back(" ")), \
    (qDebug()<<o_str)  \
 )

#define PRELOG_F_STR(o_str,i_obj_name,i_str) \
 ( \
    (o_str.push_back(QDate::currentDate().toString("dd.MM.yyyy"))), \
    (o_str.push_back('"')), \
    (o_str.push_back("   ")), \
    (o_str.push_back('"')), \
    (o_str.push_back(QTime::currentTime().toString("hh:mm:ss:zzz"))), \
    (o_str.push_back('"')), \
    (o_str.push_back(" : ")), \
    (o_str.push_back('"')), \
    (o_str.push_back(i_obj_name)), \
    (o_str.push_back('"')), \
    (o_str.push_back(" ")), \
    (o_str.push_back('"')), \
    (o_str.push_back(i_str)), \
    (o_str.push_back('"')), \
    (o_str.push_back("  ")), \
    (o_str.push_back(__FUNCTION__)), \
    (o_str.push_back(" ")) \
 )

#define PRELOG_F_STR_DEB(o_str,i_obj_name,i_str) \
 ( \
    (o_str.push_back(QDate::currentDate().toString("dd.MM.yyyy"))), \
    (o_str.push_back('"')), \
    (o_str.push_back("   ")), \
    (o_str.push_back('"')), \
    (o_str.push_back(QTime::currentTime().toString("hh:mm:ss:zzz"))), \
    (o_str.push_back('"')), \
    (o_str.push_back(" : ")), \
    (o_str.push_back('"')), \
    (o_str.push_back(i_obj_name)), \
    (o_str.push_back('"')), \
    (o_str.push_back(" ")), \
    (o_str.push_back('"')), \
    (o_str.push_back(i_str)), \
    (o_str.push_back('"')), \
    (o_str.push_back("  ")), \
    (o_str.push_back(__FUNCTION__)), \
    (o_str.push_back(" ")), \
    (qDebug()<<o_str)  \
 )
/*
 * как пример)
#define MACRO(X,Y) \
do { \
    auto MACRO_tmp_1 = (X); \
    auto MACRO_tmp_2 = (Y); \
    using std::cout; \
    using std::endl; \
    cout << "1st arg is:" << (MACRO_tmp_1) << endl;    \
    cout << "2nd arg is:" << (MACRO_tmp_2) << endl;    \
    cout << "Sum is:" << (MACRO_tmp_1 + MACRO_tmp_2) << endl; \
} while(0)
*/
#endif // R_GLOBAL

