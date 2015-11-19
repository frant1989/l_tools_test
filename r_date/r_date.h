#ifndef R_DATE_H
#define R_DATE_H

#include <QString>
#include <QDate>
#include <QVariant>

/**
@class R_logger
* Класс для работы с датами
* Примечание нажно добавить времена UTC, м.б. гринвич
*/
class R_date
{
public:
    //explicit R_date()= delete;
//    R_date(const R_date&) = delete;
    /**
         * Метод возвращающий текущее время ПК в текстовой форме
         */
    static QString GetLocalCurrentDate()
    {

        QString text;
        //get current date
        QDate date = QDate::currentDate();
        QVariant Year = date.year();
        QVariant Month = date.month();
        QVariant day = date.day();

        //get current tim
        QTime time = QTime::currentTime();
        QVariant hour = time.hour();
        QVariant min = time.minute();
        QVariant sec = time.second();
        text.push_back(day.toString());
        text.push_back("_");
        text.push_back(Month.toString());
        text.push_back("_");
        text.push_back(Year.toString());
        text.push_back("_");
        text.push_back(hour.toString());
        text.push_back("_");
        text.push_back(min.toString());
        text.push_back("_");
        text.push_back(sec.toString());
        return text;
    }
    static QTime TimeFormMSecond(int i_second)
    {
        QTime time(i_second/3600000,i_second%3600000/60000.0,i_second % 60000 / 1000.0,i_second % 1000);
        return time;
    }

    static double TimetoMSecond(QTime i_time)
    {
        double msecond = QTime(0,0).msecsTo(i_time);
        return msecond;
    }
};

#endif // R_DATE_H
