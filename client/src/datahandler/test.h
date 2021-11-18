#pragma once
#include <string>
#include "curl/curl.h"

class MyClass {    
  private:
    const std::string URL = "http://157.245.0.156";
    CURL* curlObj;

    std::string ApplicationPath();

  public:
    void EstablishConnection();
    std::string ConnectTo(std::string link);
    int searchUser(std::string username);          
    bool Login(std::string username, std::string password);
};