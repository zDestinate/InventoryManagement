#pragma once
#include <string>

class Employee {    
  private:
  std:: string empName,empID,empPosition; 
  public:

    void getUserData(std::string username); 
    std::string returnName();
};