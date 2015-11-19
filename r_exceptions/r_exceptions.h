#ifndef R_EXCEPTIONS
#define R_EXCEPTIONS


// --------------------------------------------------------------------------
/*! \file
 *    \brief �������� ������������ ����������� ����������
 *  \author Roman Ayupov copied from Pavel Vainerman
*/

// ---------------------------------------------------------------------------
#include <ostream>
#include <iostream>
#include <exception>

// ---------------------------------------------------------------------



namespace r_exaception_types
{


// namespase ExaceptionTypes

/*!
    ������� ����� ��� ���� ���������� � ����������
    \note ��� ����� ����������� ���������� ������� ������������� �� ���� ��� ��� ��������
*/
class Exception:
    public std::exception
{
public:
    void printException()
    {
        std::cerr << "Exception: " << text << std::endl;
    }

    Exception(const std::string& txt):text(txt.c_str()){}
    Exception():text("Exception"){}
    virtual ~Exception() throw(){}

    friend std::ostream& operator<<(std::ostream& os, Exception& ex )
    {
        os << ex.text;
        return os;
    }

    virtual const char* what() { return text.c_str(); }

protected:
    const std::string text;
};


class PermissionDenied: public Exception
{
public:
    PermissionDenied():Exception("PermissionDenied"){}
};

class NotEnoughMemory: public Exception
{
public:
    NotEnoughMemory():Exception("NotEnoughMemory"){}
};


class OutOfRange: public Exception
{
public:
    OutOfRange():Exception("OutOfRange"){}
    OutOfRange(const std::string& err):Exception(err){}
};


class ErrorHandleResource: public Exception
{
public:
    ErrorHandleResource():Exception("ErrorHandleResource"){}
};

/*!
    ����������, �������������� ��� ���������� ����������� ����������� ����� ���������
    �������� ��� �������
*/
class LimitWaitingPTimers: public Exception
{
public:
    LimitWaitingPTimers():Exception("LimitWaitingPassiveTimers"){}

    /*! �����������, ����������� ������� � ��������� �� ������ �������������� ���������� err */
    LimitWaitingPTimers(const std::string& err):Exception(err){}
};


/*!
    ����������, �������������� ��������� ����������� ��������.
    �������� �������� ��� ������ ��� ����������� � ����������� ��������.
*/
class ORepFailed: public Exception
{
public:
    ORepFailed():Exception("ORepFailed"){}

    /*! �����������, ����������� ������� � ��������� �� ������ �������������� ���������� err */
    ORepFailed(const std::string& err):Exception(err){}
};


/*!
    ��������� ������
*/
class SystemError: public Exception
{
public:
    SystemError():Exception("SystemError"){}

    /*! �����������, ����������� ������� � ��������� �� ������ �������������� ���������� err */
    SystemError(const std::string& err):Exception(err){}
};

class CRCError: public Exception
{
public:
    CRCError():Exception("CRCError"){}
};


/*!
    ������ ����������
*/
class CommFailed: public Exception
{
public:
    CommFailed():Exception("CommFailed"){}

    /*! �����������, ����������� ������� � ��������� �� ������ �������������� ���������� err */
    CommFailed(const std::string& err):Exception(err){}
};


/*!
    ����������, �������������� ���������, ������������� ��������� �����,
    ��� ������������� ������� �������� ����� �� �������� �����.
*/
class TimeOut: public CommFailed
{
    public:
        TimeOut():CommFailed("TimeOut") {}

    /*! �����������, ����������� ������� � ��������� �� ������ �������������� ���������� err */
    TimeOut(const std::string& err):CommFailed(err){}

};

/*!
    ���������� �������������� ��� ������ ������������� ������� �����������
*/
class ResolveNameError: public ORepFailed
{
    public:
        ResolveNameError():ORepFailed("ResolveNameError"){}
        ResolveNameError(const std::string& err):ORepFailed(err){}
};


class NSResolveError: public ORepFailed
{
    public:
        NSResolveError():ORepFailed("NSResolveError"){}
        NSResolveError(const std::string& err):ORepFailed(err){}
};


/*!
    ����������, �������������� ��������� ����������� ��������.
    ������� ���������������� ������ ��� ��� ������������ ������
*/
class ObjectNameAlready: public ResolveNameError
{
public:
    ObjectNameAlready():ResolveNameError("ObjectNameAlready"){}

    /*! �����������, ����������� ������� � ��������� �� ������ �������������� ���������� err */
    ObjectNameAlready(const std::string& err):ResolveNameError(err){}
};

/*!
    ����������, �������������� � ������ �������� ������������ ���������� ��� ������
    � ���������(���������) �����/������
*/
class IOBadParam: public Exception
{
    public:
    IOBadParam():Exception("IOBadParam"){}

    /*! �����������, ����������� ������� � ��������� �� ������ �������������� ���������� err */
    IOBadParam(const std::string& err):Exception(err){}
};

/*!
    ����������, �������������� � ������ ����������� � ����� ������������ ��������.
    ��. UniSetTypes::BadSymbols[]
*/
class InvalidObjectName: public ResolveNameError
{
    public:
        InvalidObjectName():ResolveNameError("InvalidObjectName"){}
        InvalidObjectName(const std::string& err):ResolveNameError(err){}
};

/*! ����������, �������������� � ������ ���� �� ������� ���������� ���������� ������� */
class NotSetSignal: public Exception
{
    public:
        NotSetSignal():Exception("NotSetSignal"){}
        NotSetSignal(const std::string& err):Exception(err){}
};

class NameNotFound: public ResolveNameError
{
public:
    NameNotFound():ResolveNameError("NameNotFound"){}
    NameNotFound(const std::string& err):ResolveNameError(err){}
};
//end of UniSetException group..
class RNotEnoughMemory: public Exception
{
public:
    RNotEnoughMemory(const std::string& txt):Exception(txt){}
};

//end of UniSetException group..
class RDBException: public Exception
{
public:
    RDBException(const std::string& txt):Exception(txt){}
};


template<typename T, typename T1, typename... _Args >
 T make_exeption(const T1& i_param, _Args&&... __args ) {

    return T(i_param,std::forward<_Args>(__args)...);
}
template<typename T, template<typename, typename> class C, typename E, typename... _Args >
 T make_exeption_param(const C<E, std::allocator<E> >& i_param, _Args&&... __args ) {

    std::string text;
    for (int i = 0; i < i_param.size();i++ )
        text.push_back(i_param[i]);
    return T(text,std::forward<_Args>(__args)...);
}


}



#endif // R_EXCEPTIONS

