#pragma once
#include <string>

class UserLogIn {    
  private:
    bool searchUser(std::string username);
  
  public:
    std::string strUsername, strPassword;
 
    bool LoginUser(std::string username);
    bool LoginPass(std::string password);
    std::string MemberID(std::string memID);
};