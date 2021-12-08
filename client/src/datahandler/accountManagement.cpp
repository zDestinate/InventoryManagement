#include <iostream>
#include <Windows.h>
#include "datahandler/accountManagement.h"
#include "global.h"
#include "lib/json.hpp"
#include <vector>

using namespace std;
using json = nlohmann::json;

accountManagement::accountManagement()
{

}

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

bool accountManagement::createCustomer(string phoneNum, string email)
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
    int j = 0, val= -1,count = 0;
    string first,last,value;

   if(datajson.is_array())
    {
        for(int i = 0; i < datajson.size(); i++)
        {
            if(count == 0)
            {
                first = datajson[i].at("code").get<string>();
                count ++;
            }

            if(count == 1)
            {
                last = datajson[i].at("code").get<string>();
                count ++;
            }

            if(count == 2)
            {
                value = datajson[i].at("code").get<string>();
                val = stoi(value);

                if(val == 0)
                {
                    custAcc Cust(first,last,val);
                    vectCust.push_back(Cust);
                }
                if((val == 1) || (val == 2))
                {
                    workerEmp Emp(first,last,val);
                    vectEmp.push_back(Emp);
                }
                count = 0;
            }
        }
        return true;
    }
    return true;
}

bool accountManagement::changePassword(std::string id)
{

    return false;
}

bool accountManagement::searchAcc(std::string id)
{

    return false;
}

bool accountManagement::checkName(std::string fname, std::string lname)
{
    
    for(int i = 0; i <= fname.length(); i++ )
    {
        if(isdigit(fname[i])){
            return false;
        }
    }
    
    for(int i = 0; i <= lname.length(); i++ )
    {
        if(isdigit(lname[i])){
            return false;
        }
    }
    return true;
}