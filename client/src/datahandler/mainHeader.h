#pragma once
#include <string>
#include "curl/curl.h"
#include "datahandler/getData.h"
#include "datahandler/LogIn.h"

class mainClass {    
  private:
    const std::string URL = "http://157.245.0.156";

    getData* DataGrabber;
    UserLogIn* estabLogIn;

  public:
    mainClass();
    void test();
    bool LogIn(std::string username, std::string password);
};