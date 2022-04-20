#include <iostream>
#include <stack>
#include <cstring>
#include<iomanip>
using namespace std;
class SavingsAccount
{
    public:
    stack<double> datestack;
    stack<double> balancestack;
    int lastDate;
    int id;
    double balance,rate,accumulation;
    void record(int date,double amount);
    double accumulate(int date);
    int getId();
    void getTotal();
    double getBalance();
    double getRate();
    void show();
    void deposit(int date,double amount);
    void withdraw(int date,double amount);
    void settle(int date);
    SavingsAccount(int date,int Id,double Rate)
    {
        id=Id;rate=Rate;
        cout<<date<<" #"<<id<<" "<<" is created"<<endl;
    }
};
