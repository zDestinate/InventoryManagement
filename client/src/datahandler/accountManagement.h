#pragma once
#include <string>
#include <vector>
#include "datahandler/getData.h"
#include "lib/json.hpp"
using json = nlohmann::json;

//user/create/:username/:phone/:email/:perm/:flname
class workerEmp
{
    public:
    std::string username,phone,email,perm,flname;

    workerEmp(std::string user, std::string num, std::string ema,std::string per, std::string flnm)
    {
        username = user;
        phone = num;
        email = ema;
        perm = per;
        flname = flnm;
    }
    
    std::string getUser()
    {
        return username;
    }
    std::string getPhone()
    {
        return phone;
    }
    std::string getEmail()
    {
        return email;
    }
    std::string getPerm()
    {
        return perm;
    }
    std::string getName()
    {
        return flname;
    }
    
    void setUser(std::string use)
    {
        username = use;
    }
    void setPhone(std::string pho)
    {
        phone = pho;
    }
    void setEmail(std::string ema)
    {
        email = ema;
    }
    void setPerm(std::string pe)
    {
        perm = pe;
    }
    void setName(std::string nm)
    {
        flname = nm;
    }
};

class custAcc
{
    public:
    std::string username,phone,email,perm,flname;

    custAcc(std::string user, std::string num, std::string ema,std::string per, std::string flnm)
    {
        username = user;
        phone = num;
        email = ema;
        perm = per;
        flname = flnm;
    }
    
    std::string getUser()
    {
        return username;
    }
    std::string getPhone()
    {
        return phone;
    }
    std::string getEmail()
    {
        return email;
    }
    std::string getPerm()
    {
        return perm;
    }
    std::string getName()
    {
        return flname;
    }
    
    void setUser(std::string use)
    {
        username = use;
    }
    void setPhone(std::string pho)
    {
        phone = pho;
    }
    void setEmail(std::string ema)
    {
        email = ema;
    }
    void setPerm(std::string pe)
    {
        perm = pe;
    }
    void setName(std::string nm)
    {
        flname = nm;
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