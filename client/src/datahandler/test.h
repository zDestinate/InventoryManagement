#pragma once
#include <string>

class MyClass {    
  private:
    bool searchUser(std::string username);
  
  public:
    std::string strUsername, strPassword;
 
    bool LoginUser(std::string username);
    bool LoginPass(std::string password);
    string MemberID(std::string memID);
};