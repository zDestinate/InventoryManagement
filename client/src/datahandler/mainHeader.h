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
    Sales* Cart;
  
  public:
    mainClass();
    
    bool LogIn(std::string username, std::string password);
    void logOut();
    
    bool removeFromCart(std::string productSku);
    bool addToCart(std::string productSku);
    bool addItemToDB(std::string name, std::string sku, std::string price);
    void checkout();


    bool returnUserData();
    bool makeCust(std::string fname,std::string lname, std::string phonenum, std::string email);
    bool deleteAcc(std::string id);
    bool CreateAccoount(std::string username,std::string password,std::string phonenum,std::string email,std::string perm,std::string flname);
    
};