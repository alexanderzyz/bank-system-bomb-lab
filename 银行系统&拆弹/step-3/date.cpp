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