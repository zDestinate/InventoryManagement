#pragma once
#include <string>
#include "curl/curl.h"
#include "datahandler/getData.h"
#include "datahandler/LogIn.h"

class mainClass {    
  private:
    const std::string URL = "http://157.245.0.156";

    getData* DataGrabber;
    UserLogIn* LogIn;

  public:
    mainClass();
    void test();
};