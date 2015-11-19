#ifndef R_TEMPLATE
#define R_TEMPLATE
#include <QSharedPointer>
#include <QPointer>
#include <memory>
#include <r_exceptions/r_exceptions.h>
using namespace r_exaception_types;
template<typename T, typename... _Args>
QSharedPointer<T> make_object_qt_sh_pointer( _Args&&... __args )
{
    return QSharedPointer< T>(new T(std::forward<_Args>(__args)...), &QObject::deleteLater);
}

template<typename T, typename... _Args>
QSharedPointer< T > make_object_qsh_pointer_exaception(QString i_name,QString i_obj_name, _Args&&... __args )
{
    QSharedPointer< T> object =  QSharedPointer< T>(new T(std::forward<_Args>(__args)...), &QObject::deleteLater);
    if (object == nullptr)
    {
        QString text_ex = i_name;
        text_ex.push_back(" :FAILED!!! ");
        text_ex.push_back(i_obj_name);
        text_ex.push_back("== nullptr!!!!");
        throw make_exeption<RNotEnoughMemory,std::string>(text_ex.toStdString());
    }
    return object;
}

template<typename T, typename... _Args>
QPointer< T > make_object_q_pointer_exaception(QString i_name,QString i_obj_name, _Args&&... __args )
{
    QPointer< T> object =  new T(std::forward<_Args>(__args)...);
    if (object == nullptr)
    {
        QString text_ex = i_name;
        text_ex.push_back(" :FAILED!!! ");
        text_ex.push_back(i_obj_name);
        text_ex.push_back("== nullptr!!!!");
        throw make_exeption<RNotEnoughMemory,std::string>(text_ex.toStdString());
    }
    return object;
}
template<typename T, typename... _Args>
std::shared_ptr<T> make_object( _Args&&... __args )
{
     return std::make_shared<T>(std::forward<_Args>(__args)...);
}

template<typename T, typename... _Args>
std::shared_ptr<T> make_object_excaption( QString i_name,QString i_obj_name, _Args&&... __args )
{
     std::shared_ptr <T>  object =  std::make_shared<T>(std::forward<_Args>(__args)...);
     if (object == nullptr)
     {
         QString text_ex = i_name;
         text_ex.push_back(" :FAILED!!! ");
         text_ex.push_back(i_obj_name);
         text_ex.push_back("== nullptr!!!!");
         throw make_exeption<RNotEnoughMemory,std::string>(text_ex.toStdString());
     }
     return object;
}

#endif // R_TEMPLATE

