#pragma once
#include <string>
#include "curl/curl.h"
#include "datahandler/getData.h"
#include "datahandler/LogIn.h"
#include "datahandler/accountManagement.h"
#include "datahandler/Inventory.h"
#include "datahandler/Sales.h"

class mainClass {    
  private:
    std::string URL;

    getData* DataGrabber;
    UserLogIn* estabLogIn;
    accountManagement* manageAcc;
    Sales* addCart;
  
  public:
    mainClass();
    
    bool LogIn(std::string username, std::string password);
    void logOut();
    
    
    int addToCart(std::string productSku);
    bool addItemToDB(std::string name, std::string sku, int price);
    
    bool returnUserData();
    bool makeCust(std::string fname,std::string lname, std::string phonenum, std::string email);
    bool deleteAcc(std::string id);
     ///user/create/:username/:password/:phone/:perm/:flname
    bool CreateAccoount(std::string username,std::string password,std::string phonenum, std::string lname, int value);
    
};