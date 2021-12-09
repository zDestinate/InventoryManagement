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
    int j = 0,count = 0;
    string username,phone,email,perm,flname;

   if(datajson.is_array())
    {
        for(int i = 0; i < datajson.size(); i++)
        {
            if(count == 0)
            {
                username = datajson[i].at("code").get<string>();
                count ++;
            }

            if(count == 1)
            {
                phone = datajson[i].at("code").get<string>();
                count ++;
            }

            if(count == 2)
            {
                email = datajson[i].at("code").get<string>();
                count++;
            }
            if(count == 3)
            {
                perm = datajson[i].at("code").get<string>();
                count++;
            }
            if(count == 4)
            {
                flname = datajson[i].at("code").get<string>();
            
                if(perm == "cus")
                {
                    custAcc Cust(username,phone,email,perm,flname);
                    vectCust.push_back(Cust);
                }
                if((perm == "sup") || (perm == "emp"))
                {
                    workerEmp Emp(username,phone,email,perm,flname);
                    vectEmp.push_back(Emp);
                }
                count = 0;
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

//ISSUE WITH CHANGE PASSWORD what is their id?????
bool accountManagement::changePassword(std::string id,std::string password,std::string perm)
{
 /* for(int i = 0; i < vectEmp.size(); i++)
    {
        if(vectEmp[i].get
    }
 */
    return false;
}

bool accountManagement::changeUserName(std::string oldName,std::string newName,std::string perm)
{
    
    for(int i = 0; i < vectEmp.size(); i++)
    {
        //if
    }
    
return false;
}

bool accountManagement::changePhone(std::string oldPhone,std::string newPhone,std::string perm)
{   
    bool checkNewPhone = checkphoneNum(newPhone);
    
        if(checkNewPhone)
        {
            if(perm == "cus")
            {
                for(int i = 0; i < vectCust.size(); i++)
                {
                    if(vectCust[i].getPhone() == oldPhone)
                    {
                        vectCust[i].setPhone(newPhone);
                        return true;
                    }
                }
            }

            if(perm == "sup" || perm == "emp")
            {
                for(int i = 0; i < vectEmp.size(); i++)
                {
                    if(vectEmp[i].getPhone() == oldPhone)
                    {
                        vectEmp[i].setPhone(newPhone);
                        return true;
                    }
                }
            }
        }
    
    return false;
}

bool accountManagement::changeEmail(std::string oldEmail,std::string  newEmail,std::string perm)
{
    bool checkNewEmail = is_valid(newEmail);

        if(checkNewEmail)
        {
            if(perm == "cus")
            {
                for(int i = 0; i < vectCust.size(); i++)
                {
                    if(vectCust[i].getEmail() == oldEmail)
                    {
                        vectCust[i].setEmail(newEmail);
                        return true;
                    }
                }
            }

            if(perm == "sup" || perm == "emp")
            {
                for(int i = 0; i < vectEmp.size(); i++)
                {
                    if(vectEmp[i].getEmail() == oldEmail)
                    {
                        vectEmp[i].setEmail(newEmail);
                        return true;
                    }
                }
            }
        }

    return false;
}

bool accountManagement::changePerm(std::string id,std::string newPerm,std::string perm)
{
    if(perm == "cus")
    {

    }

    if(perm == "sup" || perm == "emp")
    {
        
    }
return false;
}

bool accountManagement::changeFlname(std::string id,std::string  newFlname,std::string perm)
{
    if(perm == "cus")
    {

    }

    if(perm == "sup" || perm == "emp")
    {
        
    }
return false;
}



