#include <iostream>
#include <Windows.h>
#include <string>
#include "datahandler/test.h"

using namespace std;

string MyClass::ApplicationPath() 
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

void MyClass::EstablishConnection()
{
    curlObj = curl_easy_init();
}

string MyClass::ConnectTo(string link)
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

int MyClass::searchUser(string username)
{
     char temp;

        if(isdigit(username[username.length()-2] == false) &&isdigit(username[username.length()-1] == false))
        {
           return 0;
        }

        for(int i = 0; i <= username.length()-2; i++)
           {
               temp = username[i];
               if((temp >= 65 && temp < 90) || (temp >= 97 && temp <= 122) || (temp >= 48 && temp <= 57))
               {
                   return 1;
               }
           }
            return 0;
}

bool MyClass::Login(string username, string password)
{
    int invalid = 5;
    
   while(invalid != 0)
   {    
        cout << "Enter UserName: ";
        cin >> username;

        if(username.length() < 8 || searchUser(username) == 0)
        {
            invalid--;
            cout << "Invalid Login\n" << "Attempts left:" << invalid;

                if(invalid == 0)
                {
                  return false;
                }
        }
        return true;
   }
   return true;
}

