
#include "account.h"

#include <iostream>

#include <vector>

#include <algorithm>
#include<fstream>
using namespace std;

int main()
{

Date date(2008, 11, 1);//起始日期

vector<Account *> accounts;//创建账户数组，元素个数为0

ifstream fin;
fin.open("commands.txt",ios::in);
ofstream write;
streambuf *oldcin;
oldcin=cin.rdbuf(fin.rdbuf());
char cmd;
cin>>cmd;
do {

char type;

int index, day;

double amount, credit, rate, fee;

string id, desc;

Account* account;

Date date1, date2;

switch (cmd) {

case 'a'://增加账户

cin >> type >> id;

if (type == 's') {

cin >> rate;

account = new SavingsAccount(date, id, rate);

}

else {

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

for (vector<Account*>::iterator iter = accounts.begin(); iter != accounts.end(); ++iter)

(*iter)->settle(date);

break;

case 'q'://查询一段时间内的账目

date1 = Date::read();

date2 = Date::read();

Account::query(date1, date2);

break;
case 'e':
return 0;
}

} while (cin>>cmd);

cin.rdbuf(oldcin);
fin.close();
write.open("commands.txt",ios::out|ios::app);

cout << "(a)add account (d)deposit (w)withdraw (s)show (c)change day (n)next month (q)query (e)exit" << endl;



do {

//显示日期和总金额

date.show();

cout << "\tTotal: " << Account::getTotal() << "\tcommand> ";


char type;

int index, day;

double amount, credit, rate, fee;

string id, desc;

Account* account;

Date date1, date2;


cin >> cmd;
if(cmd!='e')
write<<endl<<cmd;

switch (cmd) {

case 'a'://增加账户

cin >> type >> id;write<<" "<<type<<" "<<id<<endl;

if (type == 's') {

cin >> rate;write<<" "<<rate<<endl;

account = new SavingsAccount(date, id, rate);

}

else {

cin >> credit >> rate >> fee;write<<" "<<credit<<" "<<rate<<" "<<fee<<endl;

account = new CreditAccount(date, id, credit, rate, fee);

}

accounts.push_back(account);

break;

case 'd'://存入现金

cin >> index >> amount;getline(cin, desc);write<<" "<<index<<" "<<amount<<" "<<desc<<endl;

accounts[index]->deposit(date, amount, desc);

break;

case 'w'://取出现金

cin >> index >> amount;getline(cin, desc);write<<" "<<index<<" "<<amount<<" "<<desc<<endl;

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

cin >> day;write<<day<<endl;

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

for (vector<Account*>::iterator iter = accounts.begin(); iter != accounts.end(); ++iter)

(*iter)->settle(date);

break;

case 'q'://查询一段时间内的账目

date1 = Date::read();

date2 = Date::read();

Account::query(date1, date2);

break;
default:
cmd='e';
break;
}

} while (cmd != 'e');
write.close();
return 0;

}
