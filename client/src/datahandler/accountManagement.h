#pragma once
#include <string>
#include <vector>
#include "datahandler/getData.h"
#include "lib/json.hpp"
using json = nlohmann::json;

class workerEmp
{
    public:
    std::string fname,lname;
    int value;

    workerEmp(std::string x, std::string y, int z)
    {
        fname = x;
        lname = y;
        value =z;
    }
    
    std::string getfname()
    {
        return fname;
    }
    std::string getlname()
    {
        return lname;
    }
    int getValue()
    {
        return value;
    }
    
    void setFname(std::string Fname)
    {
        fname = Fname;
    }
    
    void getLname(std::string Lname)
    {
        lname = Lname;
    }
    
    void setValue(int Value)
    {
        value = Value;
    }
    
};

class custAcc
{
    public:
    std::string fname,lname;
    int value;

    custAcc(std::string x, std::string y, int z)
    {
        fname = x;
        lname = y;
        value =z;
    }
    
    std::string getfname()
    {
        return fname;
    }
    std::string getlname()
    {
        return lname;
    }
    int getValue()
    {
        return value;
    }
    
    void setFname(std::string Fname)
    {
        fname = Fname;
    }
    
    void getLname(std::string Lname)
    {
        lname = Lname;
    }
    
    void setValue(int Value)
    {
        value = Value;
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

    std::vector<workerEmp> vectEmp;
    std::vector<custAcc> vectCust;

    accountManagement();
    
    bool createCustomer(std::string phoneNum, std::string email);
    
    bool allUserData(json userData); 
    bool searchAcc(std::string id);
    bool changePassword(std::string id);
    bool accountManagement::checkName(std::string fname, std::string lname);
    
};