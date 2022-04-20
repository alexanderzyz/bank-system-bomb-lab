#include <iostream>
#include "date.h"
#include "account.h"
using namespace std;
Date::Date()
{};
Date::Date(int y,int m,int d)
{
    year=y;
    month=m;
    day=d;
}
void Date::show()
{
    cout<<year<<"-"<<month<<"-"<<day<<" ";
}
int Date::getDay()
{
    return day;
}
int Date::getMonth()
{
    return month;
}
int Date::getYear()
{
    return year;
}
int Date::getMaxDay()
{
    int Day[12]={31,28,31,30,31,30,31,31,30,31,30,31};
    if((year%4==0 && year%100!=0) || (year%400==0))
    {
        Day[1]=29;
        return Day[month-1];
    }
    else
    {
        Day[1]=28;
        return Day[month-1];
    }
}
