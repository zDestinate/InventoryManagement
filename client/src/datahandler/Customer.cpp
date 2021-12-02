#include <iostream>
#include <Windows.h>
#include "datahandler/Customer.h"

using namespace std;

bool Customer::checkphoneNum(string phoneNum)
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

bool Customer::isChar(char c)
{
    return ((c >= 'a' && c <= 'z')
            || (c >= 'A' && c <= 'Z'));
}

bool Customer::isDigit(const char c)
{
    return (c >= '0' && c <= '9');
}

bool Customer::is_valid(string email)
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

bool Customer::createCustomer(string name, string phoneNum, string email)
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