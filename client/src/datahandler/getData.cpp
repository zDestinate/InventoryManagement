#include <iostream>
#include <Windows.h>
#include "datahandler/getData.h"
#include "lib/json.hpp"

using namespace std;

using json = nlohmann::json;
double price = 0;
int quantity = 0;
string productname,widxlen,description,empName,empID,empPosition; 


getData::getData(string URL)
{
    this->URL = URL;
}

string getData::ApplicationPath() 
{
	char buffer[MAX_PATH];
	GetModuleFileName(NULL, buffer, MAX_PATH);
	int pos = string(buffer).find_last_of("\\/");
	return string(buffer).substr(0, pos);
}

size_t WriteCallback(char *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

void getData::EstablishConnection()
{
    curlObj = curl_easy_init();
}

string getData::ConnectTo(string link)
{
    string strPath = URL + link;
    string strData;

    //convert URL string into C string
    curl_easy_setopt(curlObj, CURLOPT_URL, strPath.c_str());
    curl_easy_setopt(curlObj, CURLOPT_COOKIEFILE, ApplicationPath() + "/cookie.txt");
    curl_easy_setopt(curlObj, CURLOPT_COOKIEJAR, ApplicationPath() + "/cookie.txt");
    curl_easy_setopt(curlObj, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curlObj, CURLOPT_WRITEDATA, &strData);

    curl_easy_perform(curlObj);

    return strData;
}

string getData::getUserData()
{
    EstablishConnection();
	string data = ConnectTo("/gvhjgvjhgvjhg");
	json datajson = json::parse(data);

    empName = "gaggsa";
    empID = "gasgsag";
    empPosition = "agsagas";

    return "geg";
}

void getData::getProductData(string sku)
{
    price = 0, quantity = 0;
    EstablishConnection();
	string product = ConnectTo("/gvhjgvjhgvjhg");
	json productjson = json::parse(product);

     price = 29.99;
     quantity = 12;
     productname = "Dark Blue Men's Jeans";
     description = "Dark blue jeans for men";
     widxlen ="34x30";   

     
}

string getData::inventoryOrder()
{
    EstablishConnection();
	string invenOrder = ConnectTo("/gvhjgvjhgvjhg");
	json invenOrderjson = json::parse(invenOrder);

    return "sga";
}

bool getData::checkphoneNum(string phoneNum)
{
    int flag = 0;

    if(phoneNum.length() != 10)
    {
        return false;
    }
    for(int i = 0; i < phoneNum.length(); i++)
    {
        if(!isdigit(phoneNum[i]))
        {
            flag++;
        }

        if(flag > 0)
        {
            return false;
        }
    }

    return true;
}

bool getData::isChar(char c)
{
    return ((c >= 'a' && c <= 'z')
            || (c >= 'A' && c <= 'Z'));
}

bool getData::isDigit(const char c)
{
    return (c >= '0' && c <= '9');
}

bool getData::is_valid(string email)
{
    // Check the first character
    // is an alphabet or not
    if (!isChar(email[0])) {
  
        // If it's not an alphabet
        // email id is not valid
        return 0;
    }
    // Variable to store position
    // of At and Dot
    int At = -1, Dot = -1;
  
    // Traverse over the email id
    // string to find position of
    // Dot and At
    for (int i = 0;
         i < email.length(); i++) {
  
        // If the character is '@'
        if (email[i] == '@') {
  
            At = i;
        }
  
        // If character is '.'
        else if (email[i] == '.') {
  
            Dot = i;
        }
    }
  
    // If At or Dot is not present
    if (At == -1 || Dot == -1)
        return 0;
  
    // If Dot is present before At
    if (At > Dot)
        return 0;
  
    // If Dot is present at the end
    return !(Dot >= (email.length() - 1));
}

bool getData::createCustomer(string name, string phoneNum, string email)
{
    bool check1,check2;
    
    check1 = is_valid(email);
    check2 = checkphoneNum(phoneNum);

    if((check1 == true) && (check2 == true))
    {
        //send information to server
        return true;
    }

    return false;
}
