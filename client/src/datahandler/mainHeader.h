#pragma once
#include <string>
#include "curl/curl.h"
#include "datahandler/getData.h"
#include "datahandler/LogIn.h"
#include "datahandler/Customer.h"
#include "datahandler/Employee.h"
#include "datahandler/Inventory.h"
#include "datahandler/Sales.h"

class mainClass {    
  private:
    const std::string URL = "http://157.245.0.156";

    getData* DataGrabber;
    UserLogIn* estabLogIn;
    Customer* custcreate;
    Sales* addCart;

  public:
    mainClass();
    void test();
    bool LogIn(std::string username, std::string password);
    bool makeCust(std::string name, std::string phonenum, std::string email);
    int addToCart(std::string productSku);
};