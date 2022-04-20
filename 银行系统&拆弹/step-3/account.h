#ifndef _B_
#define _B_
#include <iostream>
#include <stack>
#include <cstring>
#include<cmath>
#include "date.h"
#include<iomanip>
using namespace std;
class Account
{
    public:
    static double total;
    string id;
    double balance;
    Account(Date date,string id){};
    Account(){};
    int getId();
    double getBalance();
    void record(int date,double amount);
    virtual void show()=0;
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
    int lastDate;
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
        id=Id;rate=Rate;balance=0;
        cout<<date.year<<"-"<<date.month<<"-"<<date.day<<" #"<<id<<" created"<<endl;
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
    int temp;
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
        id=Id;credit=Credit;rate=Rate;fee=Fee;
        cout<<date.year<<"-"<<date.month<<"-"<<date.day<<" #"<<id<<" created"<<endl;
        datestack.push(date);
    }
};
#endif
