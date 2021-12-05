#pragma once
#include <string>
#include "curl/curl.h"

class getData {    
  private:
    std::string URL;
    CURL* curlObj;

    std::string ApplicationPath();

  public:
    getData(std::string URL);

    bool bSuccessfullyConnected = false;
    void EstablishConnection();
    std::string ConnectTo(std::string link);            
};