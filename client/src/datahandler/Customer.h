#pragma once
#include <string>

class Customer {    
  private:
    bool checkphoneNum(std::string phoneNum);
    bool isChar(char c);
    bool isDigit(const char c);
    bool is_valid(std::string email);
    
  public:
    bool createCustomer(std::string name, std::string phoneNum, std::string email);
};