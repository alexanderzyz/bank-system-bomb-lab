#ifndef _B_
#define _B_
#include <iostream>
#include <stack>
#include <cstring>
#include<cmath>
#include "date.h"
#include<iomanip>
#include<vector>
#include<fstream>
using namespace std;
class Account
{
    public:
    static double total;
    static vector<string> recordvector;
    static vector<double>amountvector;
    string id;
    double balance;
    int flag=0;
    Account(Date date,string id){};
    Account(){};
    int getId();
    double getBalance();
    static void query(Date date1,Date date2);
    static void queryByAmount(Date date1,Date date2);
    virtual void show()=0;
    virtual void deposit(Date date,double amount,string remarks)=0;
    virtual void withdraw(Date date,double amount,string remarks)=0;
    virtual void settle(Date date)=0;
    void error(string msg);
    static double getTotal()
    {
        return total;
    }
};
class SavingsAccount:public Account,public Date
{
    public:
    stack<int>daystack;
    stack<int>realdaystack;
    stack<Date>datestack;
    stack<double> balancestack;
    stack<double>usermoney;
    Date createdate,lastdate;
    int lastDate,SETTLE=0;
    int temp;
    double rate;
   // Accumulator acc;
    double accumulate(int date);
    double getRate();
    void deposit(Date date,double amount,string remarks);
    void withdraw(Date date,double amount,string remarks);
    void settle(Date date);
    void DayCalculate();
    void show()
    {
        cout<<id<<" Balance:"<<balance<<endl;
    }
    SavingsAccount(Date date,string Id,double Rate)
    {
        id=Id;rate=Rate;balance=0;createdate=date;
        cout<<date.year<<"-"<<date.month<<"-"<<date.day<<" #"<<id<<" is created"<<endl;
        datestack.push(date);
    }
};
class CreditAccount:public Account,public Date
{
    public:
  //  Accumulator acc;
    stack<int>daystack;
    stack<int>realdaystack;
    stack<Date>datestack;
    stack<double> balancestack;
    stack<double>usermoney;
    Date createdate,lastdate;
    int temp,SETTLE=0;
    double credit,rate,fee;
    double getDebt();
    double getCredit();
    double getRate();
    double getFee();
    double getAvailableCredit();
    void show()
    {
        cout<<id<<" Balance:"<<balance<<" "<<"Available credit:"<<(balance<0?(credit+balance):credit)<<endl;
    }
    void DayCalculate();
    void deposit(Date date,double amount,string remarks);
    void withdraw(Date date,double amount,string remarks);
    void settle(Date date);
    CreditAccount(Date date,string Id,double Credit,double Rate,double Fee)
    {
        id=Id;credit=Credit;rate=Rate;fee=Fee;createdate=date;
        cout<<date.year<<"-"<<date.month<<"-"<<date.day<<" #"<<id<<" is created"<<endl;
        datestack.push(date);
    }
};
class AccountException:public exception
{
    public:
    AccountException(string mes)
    {
        error=mes;
    }
    static string error;
};

#endif