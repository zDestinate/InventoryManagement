#include <iostream>
#include <Windows.h>
#include "datahandler/Employee.h"

using namespace std;

using json = nlohmann::json;
double price = 0;
int quantity = 0;
string productname,widxlen,description,empName,empID,empPosition; 

string Employee::getUserData()
{
    EstablishConnection();
	string data = ConnectTo("/gvhjgvjhgvjhg");
	json datajson = json::parse(data);

    empName = "gaggsa";
    empID = "gasgsag";
    empPosition = "agsagas";

    return "geg";
}

