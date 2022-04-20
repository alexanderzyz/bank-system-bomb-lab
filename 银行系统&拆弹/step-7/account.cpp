#include <iostream>
#include<cstring>
#include "account.h"
using namespace std;
//AccountException
string  AccountException::error;
//Account
double Account::total = 0;
vector<string> Account::recordvector;
vector<double> Account::amountvector;
void Account::query(Date date1,Date date2)
{
    stringstream ss;int tempdate1=date1.year*10000+date1.month*100+date1.day;int tempdate2=date2.year*10000+date2.month*100+date2.day;
    int tempyear,tempmonth,tempday;
    for(int i=0;i<recordvector.size();++i)
    {
        string s="";
        ss<<recordvector[i].substr(0,4);
        ss>>tempyear;//cout<<tempyear<<" ";
        ss.clear();int J=5;
        for(int j=5;j<recordvector[i].length();++j)
       {
            if(recordvector[i][j]!='-')
            {s+=recordvector[i][j];J++;}
            else
            {
                ss<<s;
                ss>>tempmonth;//cout<<tempmonth<<" ";
                ss.clear();s="";
                break;
            }
        }
        for(int j=J+1;j<recordvector[i].length();++j)
        {
            if(recordvector[i][j]!=' ')
            s+=recordvector[i][j];
            else
            break;
        }
        ss<<s;
        ss>>tempday;//cout<<tempday<<endl;
        ss.clear();
        int tempdate=tempyear*10000+tempmonth*100+tempday;//cout<<tempdate1<<" "<<tempdate<<" "<<tempdate2<<endl;
        if(tempdate>=tempdate1 && tempdate<=tempdate2)
        {
            cout<<recordvector[i]<<endl;
        }
    }
}
void Account::queryByAmount(Date date1,Date date2)
{
    vector<string>queryvector;
    vector<double>amount;
    stringstream ss;int tempdate1=date1.year*10000+date1.month*100+date1.day;int tempdate2=date2.year*10000+date2.month*100+date2.day;
    int tempyear,tempmonth,tempday;
    for(int i=0;i<recordvector.size();++i)
    {
        string s="";
        ss<<recordvector[i].substr(0,4);
        ss>>tempyear;//cout<<tempyear<<" ";
        ss.clear();int J=5;
        for(int j=5;j<recordvector[i].length();++j)
       {
            if(recordvector[i][j]!='-')
            {s+=recordvector[i][j];J++;}
            else
            {
                ss<<s;
                ss>>tempmonth;//cout<<tempmonth<<" ";
                ss.clear();s="";
                break;
            }
        }
        for(int j=J+1;j<recordvector[i].length();++j)
        {
            if(recordvector[i][j]!=' ')
            s+=recordvector[i][j];
            else
            break;
        }
        ss<<s;
        ss>>tempday;//cout<<tempday<<endl;
        ss.clear();
        int tempdate=tempyear*10000+tempmonth*100+tempday;//cout<<tempdate1<<" "<<tempdate<<" "<<tempdate2<<endl;
        if(tempdate>=tempdate1 && tempdate<=tempdate2)
        {
            queryvector.push_back(recordvector[i]);
            amount.push_back(amountvector[i]);
        }
    }
    string tempquery;double tempamount;
    for(int i=0;i<queryvector.size()-1;++i)
    {
        for(int j=i;j<amount.size();++j)
        {
            if(amount[i]<amount[j])
            {
                tempamount=amount[i];
                amount[i]=amount[j];
                amount[j]=tempamount;
                tempquery=queryvector[i];
                queryvector[i]=queryvector[j];
                queryvector[j]=tempquery;
            }
        }
    }
    for(int i=0;i<queryvector.size();++i)
    cout<<queryvector[i]<<endl;
}

//SavingsAccount

void SavingsAccount::deposit(Date date,double amount,string remarks)
{
    amount = floor(amount * 100 + 0.5) / 100;
    balance+=amount;Account::total+=amount;
    balancestack.push(balance);
    cout<<date.year<<"-"<<date.month<<"-"<<date.day<<" #"<<id<<" "<<amount<<" "<<balance<<" "<<remarks<<endl;
    datestack.push(date);
    stringstream ss;
    ss<<amount;
    string Amount;
    ss>>Amount;
    ss.clear();
    ss<<balance;
    string Balance;
    ss>>Balance;
    ss.clear();
    Account::recordvector.push_back(to_string(date.year)+"-"+to_string(date.month)+"-"+to_string(date.day)+" #"+id+" "+Amount+" "+Balance);
    Account::amountvector.push_back(amount);
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
    stringstream ss;
    ss<<interest;
    string Interest;
    ss>>Interest;
    ss.clear();
    ss<<balance;
    string Balance;
    ss>>Balance;
    ss.clear();
    Account::recordvector.push_back(to_string(date.year)+"-"+to_string(date.month)+"-"+to_string(date.day)+" #"+id+" "+Interest+" "+Balance);
    Account::amountvector.push_back(interest);
    }
}
void SavingsAccount::withdraw(Date date,double amount,string remarks)
{
    try{
    if((balance-amount)<0)
    {flag=1;throw AccountException("Insufficient Balance !");}
    else
    {flag=0;datestack.push(date);
    amount = floor(amount * 100 + 0.5) / 100;
    balance-=amount;Account::total-=amount;
    balancestack.push(balance);
    cout<<date.year<<"-"<<date.month<<"-"<<date.day<<" #"<<id<<" -"<<amount<<" "<<balance<<" "<<remarks<<endl;
    stringstream ss;
    ss<<amount;
    string Amount;
    ss>>Amount;
    ss.clear();
    ss<<balance;
    string Balance;
    ss>>Balance;
    ss.clear();
    Account::recordvector.push_back(to_string(date.year)+"-"+to_string(date.month)+"-"+to_string(date.day)+" #"+id+" -"+Amount+" "+Balance);
    Account::amountvector.push_back(amount);
    }
    }
    catch(AccountException)
    {cout<<AccountException::error<<endl;}
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
    stringstream ss;
    ss<<amount;
    string Amount;
    ss>>Amount;
    ss.clear();
    ss<<balance;
    string Balance;
    ss>>Balance;
    ss.clear();
    Account::recordvector.push_back(to_string(date.year)+"-"+to_string(date.month)+"-"+to_string(date.day)+" #"+id+" "+Amount+" "+Balance);
    Account::amountvector.push_back(amount);
}
void CreditAccount::withdraw(Date date,double amount,string remarks)
{
    try{
    if((balance-amount+credit)<0)
    {flag=1;throw AccountException("Insufficient Credit !");}
    else
    {flag=0;datestack.push(date);
    amount = floor(amount * 100 + 0.5) / 100;
    balance-=amount;Account::total-=amount;
    balancestack.push(balance);
    cout<<date.year<<"-"<<date.month<<"-"<<date.day<<" #"<<id<<" -"<<amount<<" "<<balance<<" "<<remarks<<endl;
    stringstream ss;
    ss<<amount;
    string Amount;
    ss>>Amount;
    ss.clear();
    ss<<balance;
    string Balance;
    ss>>Balance;
    ss.clear();
    Account::recordvector.push_back(to_string(date.year)+"-"+to_string(date.month)+"-"+to_string(date.day)+" #"+id+" -"+Amount+" "+Balance);
    Account::amountvector.push_back(amount);
    }
    }
    catch(AccountException)
    {cout<<AccountException::error<<endl;}
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
            }//cout<<allinterest<<" "<<realdaystack.top()<<" "<<balancestack.top()<<endl;
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
    stringstream ss;
    ss<<allinterest;
    string Allinterest;
    ss>>Allinterest;
    ss.clear();
    ss<<balance;
    string Balance;
    ss>>Balance;
    ss.clear();
    Account::recordvector.push_back(to_string(date.year)+"-"+to_string(date.month)+"-"+to_string(date.day)+" #"+id+" "+Allinterest+" "+Balance);
    Account::amountvector.push_back(allinterest);
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