#include <iostream>
#include <Windows.h>
#include "datahandler/Employee.h"
#include "lib/json.hpp"
using namespace std;

using json = nlohmann::json;

void Employee::getUserData(string username)
{

    empName = "gaggsa";
    empID = "gasgsag";
    empPosition = "agsagas";

}

string Employee::returnName()
{
    return empName;
}


