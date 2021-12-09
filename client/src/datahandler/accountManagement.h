#pragma once
#include <string>
#include <vector>
#include "datahandler/getData.h"
#include "lib/json.hpp"
using json = nlohmann::json;

//user/create/:username/:phone/:email/:perm/:flname
class User
{
    public:
        std::string id,user, phone, email,perm,flname;

        User(std::string id,std::string user, std::string phone, std::string email,std::string perm,std::string flname)
        {
            this->id = id;
            this->user  = user;
            this->phone = phone;
            this->email = email;
            this->perm = perm;
            this->flname = flname;
        }
};

class custAcc : public User
{
    public:
        custAcc(std::string id,std::string user, std::string phone, std::string email,std::string perm,std::string flname) :
        User(id,user, phone, email, perm, flname)
        {
            //Constructor of Customer
        }

};

class workerEmp : public User
{
    public:
        workerEmp(std::string id,std::string user, std::string phone, std::string email,std::string perm,std::string flname) :
        User(id,user, phone, email, perm, flname)
        {
            //Constructor of Customer
        }
};

class accountManagement {    
  private:
  //CUSTOMER FUNCTIONS
    bool checkphoneNum(std::string phoneNum);
    bool isChar(char c);
    bool isDigit(const char c);
    bool is_valid(std::string email);
    
    //EMP & SUP FUNCTIONS
    const std::string URL;
    getData* getEmp;
    std:: string empName,empID,empPosition; 

  public:

    //user/create/:username/:phone/:email/:perm/:flname
    std::vector<workerEmp> vectEmp;
    std::vector<custAcc> vectCust;
    std::vector<User> vUser;

    bool checkPhoneEmail(std::string phoneNum, std::string email);
    
    bool allUserData(json userData); 
    bool checkName(std::string flname);
    
    bool changeUserName(std::string id,std::string newName);
    bool changePhone(std::string id,std::string newPhone);
    bool changeEmail(std::string id,std::string  newEmail);
    bool changePerm(std::string id,std::string newPerm);
    bool changeFlname(std::string id,std::string  newFlname);
    bool changePassword(std::string id,std::string newPassword);
   
    
    
};