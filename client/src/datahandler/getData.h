#pragma once
#include <string>
#include "curl/curl.h"

class getData {    
  private:
    std::string URL;
    CURL* curlObj;

    std::string ApplicationPath();
    
    bool checkphoneNum(std::string phoneNum);
    bool isChar(char c);
    bool isDigit(const char c);
    bool is_valid(std::string email);
    
     

  public:
    getData(std::string URL);
    
    void EstablishConnection();
    std::string ConnectTo(std::string link);         

    std::string getUserData(); 
    void getProductData(std::string sku);
    std::string inventoryOrder();
    bool createCustomer(std::string name, std::string phoneNum, std::string email);
};