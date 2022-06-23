#include "Date.h"
#include<ctime>

Date::Date()
{
    day = 1;
    month = 1;
    year = 1900;
}

Date::Date(int _day, int _month, int _year)
{
    day = _day;
    month = _month;
    year = _year;
}

Date::~Date()
{
}

void Date::setDay(int _day)
{
    day = _day;
}

void Date::setMonth(int _month)
{
    month = _month;
}

void Date::setYear(int _year)
{
    year = _year;
}

void Date::setDate()
{
    int a, b, c;
    cout << "\nВведите дату в формате ДД.ММ.ГГГГ: ";
    cin >> a >> b >> c;
    setDay(a);
    setMonth(b);
    setYear(c);
    cout << "\nДата установлена!\n\n";
}

int Date::getDay() const
{
    return day;
}

int Date::getMonth() const
{
    return month;
}

int Date::getYear() const
{
    return year;
}

void Date::showDate()const
{
    cout << "\nДата: " << day/10 << day%10 << "." << month/10 << month%10 << "." << year << endl << endl;
}

void Date::getNowDate()
{
    class tm* tim = new tm;
    time_t tt = time(NULL);
    localtime_s(tim, &tt);

    day = tim->tm_mday;
    month = 1 + tim->tm_mon;
    year = 1900 + tim->tm_year;
}

char* Date::toString()
{
    char* str = new char[11];
    sprintf_s(str, 11, "%d%d.%d%d.%d", day / 10, day % 10, month / 10, month % 10, year);
    return str;
}

bool Date::isLeapYear()
{
    if (year % 4 == 0 && !(year % 100 == 0 && year % 400 != 0))
        return true;
    else
        return false;
}

