#pragma once
#include <string>
#include "curl/curl.h"
#include "datahandler/getData.h"
#include "datahandler/LogIn.h"
#include "datahandler/accountManagement.h"
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
    
    void demoFillItems();
    bool demoCreateItem(std::string upc,std::string description, std::string quantity, std::string price);
    std::vector<itemObj> returnUpdatedDemo();
    std::vector<itemObj> returnUpdatedCart();


  //bool getDBItems();
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
    
    bool editUserInfo(int vectorId,std::string userName,std::string fullName,std::string email,std::string phoneNumber,std::string permission);
};