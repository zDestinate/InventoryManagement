#include <iostream>
#include <Windows.h>
#include "datahandler/accountManagement.h"
#include "global.h"
#include "lib/json.hpp"
#include <vector>

using namespace std;
using json = nlohmann::json;

bool accountManagement::isChar(char c)
{
    return ((c >= 'a' && c <= 'z')
            || (c >= 'A' && c <= 'Z'));
}

bool accountManagement::isDigit(const char c)
{
    return (c >= '0' && c <= '9');
}

bool accountManagement::is_valid(string email)
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

bool accountManagement::checkphoneNum(string phoneNum)
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

bool accountManagement::checkPhoneEmail(string phoneNum, string email)
{
     ///user/create/:username/:password/:phone/:perm/:flname
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

bool accountManagement::allUserData(json datajson)
{
    vectEmp.clear();
    vectCust.clear();
    vUser.clear();

    string id,username,phone,email,perm,flname;

   if(datajson.is_array())
    {
        for(int i = 0; i < datajson.size(); i++)
        {
            if(datajson[i].contains("_id"))
            {
                id = to_string(datajson[i].at("_id").get<int>());
            } 

            if(datajson[i].contains("username"))
            {
                username = datajson[i].at("username").get<string>();
            }
            
            if(datajson[i].contains("number"))
            {
                phone = datajson[i].at("number").get<string>();
            }

            if(datajson[i].contains("email"))
            {
                email = datajson[i].at("email").get<string>();
            }   

            if(datajson[i].contains("name"))
            {
                flname = datajson[i].at("name").get<string>();
            }   

            if(datajson[i].contains("perm"))
            {
                perm = datajson[i].at("perm").get<string>();

                if(datajson[i].at("perm").get<string>() == "cus")
                {
                    custAcc Cust(id," ",phone,email,perm,flname);
                    vectCust.push_back(Cust);
                    vUser.push_back(Cust);
                }
                if((datajson[i].at("perm").get<string>() == "sup") || (datajson[i].at("perm").get<string>() == "emp"))
                {
                    workerEmp Emp(id,username,phone,email,perm,flname);
                    vectEmp.push_back(Emp);
                    vUser.push_back(Emp);
                }           
            }
        }
        return true;
    }
    return false;
}

bool accountManagement::checkName(std::string flname)
{
    char nc;
    for(int i = 0; i <= flname.length(); i++ )
    {
        nc = flname[i];

        if(isdigit(flname[i]) ||(nc>=33 && nc<=64)||
                                (nc>=91 && nc<=96)||
                                (nc>=123 && nc<=126))
        {
            return false;
        }
    }
    return true;
}


