#include <iostream>
#include <cmath>
//#include <iomanip>
#include "account.h"
using namespace std;
void SavingsAccount::deposit(int date,double amount)
{
    amount = floor(amount * 100 + 0.5) / 100;
    balance+=amount;
    datestack.push(date);
    balancestack.push(balance);
    cout<<date<<" #"<<id<<" "<<amount<<" "<<balance<<endl;
}
void SavingsAccount::settle(int date)
{
    int date1,date2;
    double sum=0;
    datestack.push(date);
    while(!(balancestack.empty()))
    {
        date2=datestack.top();
        datestack.pop();
        date1=datestack.top();
        sum+=(date2-date1)*(balancestack.top());
        balancestack.pop();
    }
    double interest=sum*rate/365;
    interest=floor(interest*100+0.5)/100;
    balance+=interest;
    cout<<date<<" #"<<id<<" "<<interest<<" "<<balance<<endl;
    //cout<<date<<" #"<<id<<" "<<setiosflags(ios::fixed)<<setprecision(2)<<interest<<" "<<balance<<endl;
}
void SavingsAccount::show()
{
    cout<<"#"<<id<<" Balance:"<<balance<<endl;
}
void SavingsAccount::withdraw(int date,double amount)
{
    amount = floor(amount * 100 + 0.5) / 100;
    balance-=amount;
    datestack.push(date);
    balancestack.push(balance);
    cout<<date<<" #"<<id<<" -"<<amount<<" "<<balance<<endl;
}