#pragma once
#include <string>
#include "curl/curl.h"
#include "datahandler/getData.h"
#include "datahandler/LogIn.h"
#include "datahandler/accountManagement.h"
#include "datahandler/Inventory.h"
#include "datahandler/Sales.h"
#include <vector>

class mainClass {    
  private:
    std::string URL;

    getData* DataGrabber;
    UserLogIn* estabLogIn;
    accountManagement* manageAcc;
    Sales* Cart;
   
    bool severStatus = true;
    std::string strResult;
  public:
    mainClass();
    
    void LogIn(std::string username, std::string password);
    bool completeLogIn();
    void logOut();
    bool exeCheck();
    
    bool removeFromCart(std::string productSku);
    bool addToCart(std::string productSku);
    bool addItemToDB(std::string name, std::string sku, std::string price);
    void checkout();

    
    bool returnUserData();
    std::vector<User> returnUserVector();
    std::vector<custAcc> returnCusVector();
    std::vector<workerEmp> returnEmpVector();
    
    bool makeCust(std::string fname,std::string lname, std::string phonenum, std::string email);
    bool deleteAcc(std::string id);
    bool CreateAccoount(std::string username,std::string password,std::string phonenum,std::string email,std::string perm,std::string flname);
    
    bool editUserName(std::string id,std::string newName);
    bool editPhone(std::string id,std::string newPhone);
    bool editEmail(std::string id,std::string  newEmail);
    bool editPerm(std::string id,std::string newPerm);
    bool editFlname(std::string id,std::string  newFlname);
    bool editPassword(std::string id,std::string newPassword);
};