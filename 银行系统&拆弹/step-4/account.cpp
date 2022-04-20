#include <iostream>
#include "account.h"
using namespace std;

//Account
double Account::total = 0;


//SavingsAccount

void SavingsAccount::deposit(Date date,double amount,string remarks)
{
    amount = floor(amount * 100 + 0.5) / 100;
    balance+=amount;Account::total+=amount;
    balancestack.push(balance);
    cout<<date.year<<"-"<<date.month<<"-"<<date.day<<" #"<<id<<" "<<amount<<" "<<balance<<" "<<remarks<<endl;
    datestack.push(date);
}
void SavingsAccount::settle(Date date)
{
    if(date.month==1 && date.day==1)
    {
    datestack.push(date);lastdate=datestack.top();
    SavingsAccount::DayCalculate();if(SETTLE==0){daystack.pop();}
    while(!(daystack.empty()))
    {
        temp=daystack.top();
        realdaystack.push(temp);
        daystack.pop();
    }
    double sum=0;
    while(!(balancestack.empty()))
    {
        sum+=realdaystack.top()*balancestack.top();
        realdaystack.pop();
        balancestack.pop();
    }
    double interest=0;
    if((createdate.year%4==0 && createdate.year%100!=0) || (createdate.year%400==0))
    interest=sum*rate/366;
    else
    interest=sum*rate/365;
    interest=floor(interest*100+0.5)/100;
    balance+=interest;Account::total+=interest;balancestack.push(balance);
    if(interest!=0)
    cout<<date.year<<"-"<<date.month<<"-"<<date.day<<" #"<<id<<" "<<interest<<" "<<balance<<" interest"<<endl;
    }
}
void SavingsAccount::withdraw(Date date,double amount,string remarks)
{
    datestack.push(date);
    amount = floor(amount * 100 + 0.5) / 100;
    balance-=amount;Account::total-=amount;
    balancestack.push(balance);
    cout<<date.year<<"-"<<date.month<<"-"<<date.day<<" #"<<id<<" -"<<amount<<" "<<balance<<" "<<remarks<<endl;
}
void SavingsAccount::DayCalculate()
{
    int year1,year2;
    int month1,month2;
    int day1,day2;
    int sumday=0;
    int flag=0;
    while(!(datestack.empty()))
{   
    int Day[12]={31,28,31,30,31,30,31,31,30,31,30,31};
    year2=datestack.top().year;
    month2=datestack.top().month;
    day2=datestack.top().day;
    datestack.pop();
    if(datestack.empty())
    {datestack.push(lastdate);break;}
    year1=datestack.top().year;
    month1=datestack.top().month;
    day1=datestack.top().day;
    if((year1%4==0 && year1%100!=0) || (year1%400==0))
    flag=0;  //leapyear
    else
    flag=1; //non-leapyear
    if(year1==year2 && flag==0) //leapyear and the same year
    {
        Day[1]=29;
        if(month1==month2)
        {
            daystack.push(day2-day1);
        }
        else if(month1!=month2)
        {
            sumday=Day[month1-1]-day1;
            for(int i=month1;i<month2-1;i++)
            sumday+=Day[i];
            sumday+=day2;
            daystack.push(sumday);
        }
    }
    else if(year1==year2 && flag==1) //non-leapyear and the same year
    {
        if(month1==month2)
        {
            daystack.push(day2-day1);
        }
        else if(month1!=month2)
        {
            sumday=Day[month1-1]-day1;
            for(int i=month1;i<month2-1;i++)
            sumday+=Day[i];
            sumday+=day2;
            daystack.push(sumday);
        }
    }
    else if(year1!=year2 && flag==0) //leapyear and the different year
    {
        Day[1]=29;
        sumday=Day[month1-1]-day1;
        for(int i=month1;i<12;i++)
        sumday+=Day[i];
        for(int i=year1+1;i<year2;++i)
        {
            if((i%4==0 && i%100!=0) || (i%400==0))
            sumday+=366;
            else
            sumday+=365;
        }
        for(int i=0;i<month2-1;++i)
        sumday+=Day[i];
        sumday+=day2;
        daystack.push(sumday);
    }
    else if(year1!=year2 && flag==1)//non-leapyear and the different year
    {
        sumday=Day[month1-1]-day1;
        for(int i=month1;i<12;i++)
        sumday+=Day[i];
        for(int i=year1+1;i<year2;++i)
        {
            if((i%4==0 && i%100!=0) || (i%400==0))
            sumday+=366;
            else
            sumday+=365;
        }
        for(int i=0;i<month2-1;++i)
        sumday+=Day[i];
        sumday+=day2;
        daystack.push(sumday);
    }
}
}


//CreditAccount

void CreditAccount::deposit(Date date,double amount,string remarks)
{
    amount = floor(amount * 100 + 0.5) / 100;
    balance+=amount;Account::total+=amount;
    balancestack.push(balance);
    cout<<date.year<<"-"<<date.month<<"-"<<date.day<<" #"<<id<<" "<<amount<<" "<<balance<<" "<<remarks<<endl;
    datestack.push(date);
}
void CreditAccount::withdraw(Date date,double amount,string remarks)
{
    datestack.push(date);
    amount = floor(amount * 100 + 0.5) / 100;
    balance-=amount;Account::total-=amount;
    balancestack.push(balance);
    cout<<date.year<<"-"<<date.month<<"-"<<date.day<<" #"<<id<<" -"<<amount<<" "<<balance<<" "<<remarks<<endl;
}
void CreditAccount::settle(Date date)
{
    if(date.day==1)
    {
    datestack.push(date);lastdate=datestack.top();
    balance=balancestack.top();
    if(date.day==1 && balancestack.top()!=0)
    {
    CreditAccount::DayCalculate();if(SETTLE==0){daystack.pop();}
    while(!(daystack.empty()))
    {
        temp=daystack.top();
        realdaystack.push(temp);
        daystack.pop();
    }
    double sum=0,interest=0,tempbalance=0,allinterest=0;
    while(!(realdaystack.empty()))
    {
        tempbalance=balancestack.top();
        if(tempbalance<0)
        {
            for(int i=0;i<realdaystack.top();++i)
            {
                interest=tempbalance*rate;
                allinterest+=interest;
            }
            realdaystack.pop();
            balancestack.pop();
        }
        else
        break;
    }
    allinterest=floor(allinterest*100+0.5)/100;
    balance+=allinterest;Account::total+=allinterest;balancestack.push(balance);
    if(allinterest!=0)
    cout<<date.year<<"-"<<date.month<<"-"<<date.day<<" #"<<id<<" "<<allinterest<<" "<<balance<<" interest"<<endl;
    }
    if(date.month==1 && date.day==1)
    {CreditAccount::withdraw(date,50,"annual fee");}
    }
    SETTLE=1;
}
void CreditAccount::DayCalculate()
{
    int year1,year2;
    int month1,month2;
    int day1,day2;
    int sumday=0;
    int flag=0;
    while(!(datestack.empty()))
{   
    int Day[12]={31,28,31,30,31,30,31,31,30,31,30,31};
    year2=datestack.top().year;
    month2=datestack.top().month;
    day2=datestack.top().day;
    datestack.pop();
    if(datestack.empty())
    {datestack.push(lastdate);break;}
    year1=datestack.top().year;
    month1=datestack.top().month;
    day1=datestack.top().day;
    if((year1%4==0 && year1%100!=0) || (year1%400==0))
    flag=0;  //leapyear
    else
    flag=1; //non-leapyear
    if( flag==0) 
    {
        Day[1]=29;
        int TEMP=Day[month1-1]-day1+day2;
        daystack.push(TEMP);
    }
    else if( flag==1) 
    {
        Day[1]=28;
       int TEMP=Day[month1-1]-day1+day2;cout<<month1<<endl;
        daystack.push(TEMP);
    }
}
}