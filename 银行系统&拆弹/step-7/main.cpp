#include "account.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include<fstream>
using namespace std;
int loginjudge=1;string name,password;
void Login()
{
    while (true)
    {
        ofstream write;int judge=0;
        ifstream fin;
        cout<<"Please input your name:"<<endl;
        cin>>name;
        cout<<"Please input your password:"<<endl;
        cin>>password;
        write.open("allaccounts.txt",ios::app);write.close();
        fin.open("allaccounts.txt",ios::in);
        string s,Option1;
        int Flag=0;
        while(getline(fin,s))
        {
            if(s==name)
            {
                Flag=1;
                break;
            }
        }
        fin.close();
        if(Flag==0)
        {
            cout<<"UnRegistered !"<<endl;loginjudge=0;break;
        }
        if(Flag==1)
        {
            string str;
            fin.open(name+".txt",ios::in);
            getline(fin,str);
            getline(fin,str);
            string d=("password:"+password);
            if(str==d)
            {cout<<"Login Successfully !"<<endl;fin.close();break;}
            else
            {
                cout<<"User name or password is incorrect !"<<endl;
                cout<<"1.Retry"<<endl;
                cout<<"2.Exit"<<endl;
                cin>>Option1;
                while(Option1=="1")
                {
                    cout<<"Please input your name:"<<endl;
                    cin>>name;
                    cout<<"Please input your password:"<<endl;
                    cin>>password;
                    d=("password:"+password);
                    if(str==d)
                    {cout<<"Login Successfully !"<<endl;judge=1;fin.close();break;}
                    else
                    {
                        cout<<"User name or password is incorrect !"<<endl;
                        cout<<"1.Retry"<<endl;
                        cout<<"2.Exit"<<endl;
                        fin.close();string Option1;
                        cin>>Option1;
                    }
                }
                if(Option1=="2")
                loginjudge=-1;
            }
        }
        if(judge==1 || Option1=="2")
        break;
    }
}
void Register()
{
    cout<<"Please input your name:"<<endl;
    cin>>name;
    cout<<"Please input your password:(If you do not want to register now,Please input 'q'  !)"<<endl;
    cin>>password;
    //int length=password.length();
    /*while(length<=3)
    {
        if(password=="q")
        {loginjudge=0;break;}
        cout<<"The length of this password is too short ! Please make sure the length longer than 3 !"<<endl;
        cin>>password;
    }*/
    if(password=="q")
        {loginjudge=0;}
    if(password!="q")
    {ofstream write;
    write.open("allaccounts.txt",ios::app);
    write<<name<<endl;
    write.close();
    write.open(name+".txt",ios::app);
    write<<"name:"<<name<<endl;
    write<<"password:"<<password<<endl;
    write.close();
    cout<<"Register Successfully !"<<endl;loginjudge=1;}
}
int main()
{
    ifstream fin;ofstream write;string path,str;
    char type;
    int index, day;
    double amount, credit, rate, fee;
    string id, desc;int registerjudge=1;
    Date date1, date2;
    Date date(2008,1,1);vector<Account *> accounts;//创建账户数组，元素个数为0
    while(true)
    {
        cout<<"Welcome to use MyBank !"<<endl;
        cout<<"Please input your option:"<<endl;
        cout<<"1. Login."<<endl;
        cout<<"2. Register."<<endl;
        cout<<"3. Exit."<<endl;
        string Option;
        cin>>Option;
        if(Option=="1")
        {
            Login();
            while(loginjudge==0)//unregistered
            {
               string Choice;
               cout<<"Please input your option to continue:"<<endl;
                cout<<"1. Register."<<endl;
                cout<<"2. Exit."<<endl;
                cin>>Choice;
                if(Choice=="1")
                Register();
                else
                {registerjudge=0;break;}
            }
            if (loginjudge==-1 || registerjudge==0)//incorrect or failed registered
            break;
            else
            {
                //Redirect read
                write.open(name+"commands.txt",ios::app);write.close();
                fin.open(name+"commands.txt",ios::in);
                streambuf *oldcin;
                oldcin=cin.rdbuf(fin.rdbuf());
                char cmd;Account* account;
                cin>>cmd;
                do {
                switch (cmd) {
                case 'a'://增加账户
                cin >> type >> id;
                if (type == 's') {
                cin >> rate;
                account = new SavingsAccount(date, id, rate);}
                else 
                {
                    cin >> credit >> rate >> fee;
                    account = new CreditAccount(date, id, credit, rate, fee);
                }
                accounts.push_back(account);
                break;
                case 'd'://存入现金
                cin >> index >> amount;
                getline(cin, desc);
                accounts[index]->deposit(date, amount, desc);
                break;
                case 'w'://取出现金
                cin >> index >> amount;
                getline(cin, desc);
                accounts[index]->withdraw(date, amount, desc);
                break;
                case 's'://查询各账户信息
                for (size_t i = 0; i < accounts.size(); i++) {
                    cout << "[" << i << "] ";
                    accounts[i]->show();
                    cout << endl;
                    }
                break;
                case 'c'://改变日期
                cin >> day;
                if (day < date.getDay())
                cout << "You cannot specify a previous day";
                else if (day > date.getMaxDay())
                cout << "Invalid day";
                else
                date = Date(date.getYear(), date.getMonth(), day);
                break;
                case 'n'://进入下个月
                if (date.getMonth() == 12)
                date = Date(date.getYear() + 1, 1, 1);
                else
                date = Date(date.getYear(), date.getMonth() + 1, 1);
                accounts[index]->settle(date);
                break;
                case 'q'://查询一段时间内的账目，以时间顺序
                date1 = Date::read();
                date2 = Date::read();
                Account::query(date1, date2);
                break;
                case 'b'://查询一段时间内的账目，以交易金额大小顺序
                date1 = Date::read();
                date2 = Date::read();
                Account::queryByAmount(date1,date2);
                break;
                case 'e':
                break;}
                } while (cin>>cmd);

                //Remind
                cout<<endl;
                for (size_t i = 0; i < accounts.size(); i++)
                {
                    if((accounts[i]->balance)<0)
                    cout<<"You need to repay the credit ~"<<endl;
                }

                //Console input
                cin.rdbuf(oldcin);
                fin.close();
                write.open(name+"commands.txt",ios::app|ios::out);
                cout<<"Bank Instructions:"<<endl;
                cout<<"Input 'a' to add a account;"<<endl;
                cout<<"Input 'd' to deposit;"<<endl;
                cout<<"Input 'w' to withdraw;"<<endl;
                cout<<"Input 's' to show details of your accounts;"<<endl;
                cout<<"Input 'c' to change the day;"<<endl;
                cout<<"Input 'n' to get into the next month;"<<endl;
                cout<<"Input 'q' to queryByTime;"<<endl;
                cout<<"Input 'b' to queryByAmount;"<<endl;
                cout<<"Input 'e' to exit;"<<endl;
                do {//显示日期和总金额
                date.show();
                cout << "\tTotal: " << Account::getTotal() << "\tcommand> ";
                cin >> cmd;
                if(cmd=='q' || cmd=='b' || cmd=='s' || cmd=='e')
                write<<endl;
                else
                write<<endl<<cmd;
                switch (cmd) {
                case 'a'://增加账户
                cin >> type >> id;
                if (type == 's') {
                    cin >> rate;write<<" "<<type<<" "<<id<<" "<<rate<<endl;
                    account = new SavingsAccount(date, id, rate);
                    }
                    else {
                        cin >> credit >> rate >> fee;write<<" "<<type<<" "<<id<<" "<<credit<<" "<<rate<<" "<<fee<<endl;
                        account = new CreditAccount(date, id, credit, rate, fee);
                        }
                        accounts.push_back(account);
                        break;
                case 'd'://存入现金
                cin >> index >> amount;getline(cin,desc);write<<" "<<index<<" "<<amount<<" "<<desc<<endl;
                accounts[index]->deposit(date, amount, desc);
                break;
                case 'w'://取出现金
                cin >> index >> amount;getline(cin,desc);
                accounts[index]->withdraw(date, amount, desc);
                while(account->flag==1)
                {
                    cout<<"Failed Withdraw ! Please Re-enter the amount !"<<endl;
                    cin>>amount;
                    account->withdraw(date,amount,desc);
                    }
                write<<" "<<index<<" "<<amount<<" "<<desc<<endl;
                break;
                case 's'://查询各账户信息
                for (size_t i = 0; i < accounts.size(); i++) {
                cout << "[" << i << "] ";
                accounts[i]->show();
                cout << endl;
                }
                break;
                case 'c'://改变日期
                cin >> day;write<<day<<endl;
                if (day < date.getDay())
                cout << "You cannot specify a previous day";
                else if (day > date.getMaxDay())
                cout << "Invalid day"<<endl;
                else
                date = Date(date.getYear(), date.getMonth(), day);
                break;
                case 'n'://进入下个月
                if (date.getMonth() == 12)
                date = Date(date.getYear() + 1, 1, 1);
                else
                date = Date(date.getYear(), date.getMonth() + 1, 1);
                accounts[index]->settle(date);
                break;
                case 'q'://查询一段时间内的账目
                date1 = Date::read();
                date2 = Date::read();
                Account::query(date1, date2);
                break;
                case 'b'://查询一段时间内的账目，以交易金额大小顺序
                date1 = Date::read();
                date2 = Date::read();
                Account::queryByAmount(date1,date2);
                break;} 
                }while (cmd != 'e');write.close();
            }
        }
        if(Option=="2")
        {
            Account* account;
            Register();
        }
        if(Option=="3")
        break;
    }
    return 0;
}