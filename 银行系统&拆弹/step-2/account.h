#ifndef _B_
#define _B_
#include <iostream>
#include <stack>
#include <cstring>
#include<cmath>
#include "date.h"
#include<iomanip>
using namespace std;
class SavingsAccount:public Date
{
    public:
    static double total;
    stack<int>daystack;
    stack<int>realdaystack;
    stack<Date>datestack;
    stack<double> balancestack;
    stack<double>usermoney;
    int lastDate;
    int temp;
    string id;
    double balance,rate,accumulation;
    void record(int date,double amount);
    double accumulate(int date);
    int getId();
    double getBalance();
    double getRate();
    void show();
    void deposit(Date date,double amount,string remarks);
    void withdraw(Date date,double amount,string remarks);
    void settle(Date date);
    void DayCalculate();
    SavingsAccount(Date date,string Id,double Rate)
    {
        id=Id;rate=Rate;balance=0;
        cout<<date.year<<"-"<<date.month<<"-"<<date.day<<" #"<<id<<"  created"<<endl;
        datestack.push(date);
    }
    static double getTotal()
    {
        return total;
    }
};
#endif