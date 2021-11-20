#pragma once
#include <string>
#include "curl/curl.h"
#include "datahandler/getData.h"
#include "datahandler/test.h"

class mainClass {    
  private:
    const std::string URL = "http://157.245.0.156";

    getData* DataGrabber;
    MyClass* LogIn;

  public:
    mainClass();
    void test();
};