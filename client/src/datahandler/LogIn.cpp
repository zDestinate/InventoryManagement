#include <iostream>
#include <Windows.h>
#include <string>
#include "datahandler/LogIn.h"
#include "lib/json.hpp"
#include<fstream>


using namespace std;

using json = nlohmann::json;

bool UserLogIn::searchUser(string username)
{
     char temp;

        if(isdigit(username[username.length()-2] == false) &&isdigit(username[username.length()-1] == false))
        {
           return false;
        }

        for(int i = 0; i <= username.length()-2; i++)
           {
               temp = username[i];
               if((temp >= 65 && temp < 90) || (temp >= 97 && temp <= 122) || (temp >= 48 && temp <= 57))
               {
                   return true;
               }
           }
            return false;
}

bool UserLogIn::LoginUser(string username)
{
    int invalid = 5; //log in attempts variable
    
     
        if(username.length() < 8 || !searchUser(username)) //if length less than 8 or username there a special character invalid
        {
            invalid--; // deduct remaining attempts
            //cout << "Invalid Login\n" << "Attempts left:" << invalid << endl;

                if(invalid == 0)//if attemps = 0 exit
                {
                  return false;
                }
        }

        strUsername = username;
        return true; 
}

bool UserLogIn::LoginPass(string password)
{
    
    int Upper = 0;  //upper case letter variable counter
    char c; //letter holder

    for(int i = 0; i <= password.length(); i++)
    {
         c = password[i];
        

            //if c is a upper case letter upper++
            if(isupper(c))
            {
                Upper++;
            }
    }
    //if length less than 8 or no upper case character or no special character invalid password 
    if(password.length() < 8 || Upper == 0)
    {
        return false; 
    }

    strPassword = password;
    return true;
}

void UserLogIn::LogOut()
{
    
    std::fstream ofs;

    ofs.open("token", std::ofstream::out | std::ofstream::trunc);
    ofs.close();  
}

