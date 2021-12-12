#include <iostream>
#include <Windows.h>
#include <string>
#include "global.h"
#include "datahandler/mainHeader.h"
#include "lib/json.hpp"
#include <vector>

using namespace std;
using json = nlohmann::json;

mainClass::mainClass()
{
    URL = LinkURL;

    //For login
    estabLogIn = new UserLogIn();
    //addingToCart
    Cart = new Sales();
    //For account management
    manageAcc = new accountManagement();
  
    //For getting the data
    DataGrabber = new getData(URL);
    DataGrabber->EstablishConnection();
}

void mainClass::LogIn(string username, string password)
{
    bool busername = estabLogIn->LoginUser(username);
    bool bpassword = estabLogIn->LoginPass(password);

    if(busername && bpassword)
    {
        //Response from the site
        strResult = DataGrabber->ConnectTo("/user/login/" + estabLogIn->strUsername + "/" + estabLogIn->strPassword);

        if(!DataGrabber->bSuccessfullyConnected)
        {
            severStatus = false;
        }
        else
        { 
            severStatus = true;
        }
    }
}

bool mainClass::completeLogIn()
{   
    json datajson = json::parse(strResult);

        
        int nCode = stoi(datajson.at("code").get<string>());

        if(nCode == 0)
        {
            return false;
        }
        
        if(nCode == 10)
        {
            return true;
        }   

        if(nCode == 111)
        {
            return false;
        }
    return false;
}

bool mainClass::exeCheck()
{
    return severStatus;
}

void mainClass::logOut()
{
    DataGrabber->ConnectTo("/user/logout");
    if(!DataGrabber->bSuccessfullyConnected)
        {
            severStatus = false;
        }
    else
    {
        severStatus = true;
    }

    DataGrabber->ClearCookies();
    estabLogIn->LogOut();
}

bool mainClass::returnUserData()
{
    
    string strResult = DataGrabber->ConnectTo("/user");
        if(!DataGrabber->bSuccessfullyConnected)
        {
                severStatus = false;
        }
        else
        {
            severStatus = true;

            json datajson = json::parse(strResult);
            bool getDataResult = manageAcc->allUserData(datajson);
        
            if(getDataResult)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    return false;
}

vector<User> mainClass::returnUserVector()
 {
     return manageAcc->vUser;
 }

vector<workerEmp> mainClass::returnEmpVector()
 {
     return manageAcc->vectEmp;
 }

vector<custAcc> mainClass::returnCusVector()
{
    return manageAcc->vectCust;
}

/*
bool mainClass::getDBItems()
{
    string strResult = DataGrabber->ConnectTo("/item");
        if(!DataGrabber->bSuccessfullyConnected)
        {
                severStatus = false;
        }
        else
        {
            severStatus = true;

            json datajson = json::parse(strResult);
            bool getDataResult = Cart->getItemsData(datajson);
        
            if(getDataResult)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    return false;
}
*/
void mainClass::demoFillItems()
{
    Cart->demoItems();
}

vector<itemObj> mainClass::returnUpdatedDemo()
{
    return Cart->vItems;
}

vector<itemObj> mainClass::returnUpdatedCart()
{
    return Cart->shoppingCart;
}

bool mainClass::addToCart(std::string productUPC)
{   
    bool add = Cart->addItemToCart(productUPC);

        if(add)
        {
            returnUpdatedCart();
            return true;
        }

    return false;
}

bool mainClass::demoCreateItem(std::string itemId,std::string upc,std::string description, std::string quantity, float price)
{   
    bool check = Cart->createDemoItem(itemId,upc,description,quantity,price);
        if(check)
        { 
            returnUpdatedCart();
            return true;
        }
    return false;
}

bool mainClass::removeFromCart(std::string productUPC)
{
    bool remove = Cart->removeFromCart(productUPC);
    
    if(remove){
        returnUpdatedCart();
        return true;
    }
    return false;
}

void mainClass::checkout()
{
    Cart->shoppingCartToString();
    
    string strResult = DataGrabber->ConnectTo("/inventory/checkout" + Cart ->cartString);
    if(!DataGrabber->bSuccessfullyConnected)
        {
            severStatus = false;
        }
    else
    {
        severStatus = true;
    }
   
    Cart->clearCart();
}

bool mainClass::addItemToDB(std::string name, std::string sku, std::string price)
{

   string strResult = DataGrabber->ConnectTo("");
   if(!DataGrabber->bSuccessfullyConnected)
        {
            severStatus = false;
        }
    else
    {
        severStatus = true;
    }
    return true;
}

bool mainClass::CreateAccoount(std::string username,std::string password,std::string phonenum,std::string email, std::string perm,std::string flname)
{

    bool busername = estabLogIn->LoginUser(username);
    bool bpassword = estabLogIn->LoginPass(password);
    bool namecheck = manageAcc ->checkName(flname);
    bool check1 = manageAcc->checkPhoneEmail(phonenum, email);


    if(!DataGrabber->bSuccessfullyConnected)
        {
            severStatus = false;
        }
    else
    {
        severStatus = true;
    }
    if(busername && bpassword && namecheck && check1)
    {
         ///user/create/:username/:password/:phone/:perm/:flname
       string strResult = DataGrabber->ConnectTo("/user/create/" + username + "/" + password + "/" + phonenum + "/" + email + "/" + perm + "/" + flname);
       returnUserData();
       return true;
    }
    return false;   
}

bool mainClass::editUserInfo(int vectorId,std::string userName,std::string fullName,std::string email,std::string phoneNumber,std::string permission)
{
    /*Checks if passed info is valid
    bool checkUser;
    bool checkFLName;
    bool checkEmail;
    bool checkPhone;
    */
    string oldUser = manageAcc->vUser[vectorId].user;
    
    //'/user/edit/:username/:nusername/:nname/:nnum/:nemail/:nperm'
    string strResult = DataGrabber->ConnectTo("/user/edit/" + oldUser + "/" + userName + "/" + fullName + "/" + phoneNumber + "/" + email + "/" + permission);
    /*
    json datajson = json::parse(strResult);
    
    if(!DataGrabber->bSuccessfullyConnected)
    {
        severStatus = false;
    }
    else
    {
        severStatus = true;
    }
    */
        returnUserData();
    
    return true;
}

bool mainClass::deleteAcc(std::string id)
{   
    string strResult = DataGrabber->ConnectTo("/user/delete" + id);
    
    json datajson = json::parse(strResult);
    int nCode = stoi(datajson.at("code").get<string>());

    if(nCode = 0)
    {
        returnUserData();
        return true;
    }    
    return false;
}


/*  -NEED TO FINISH SALES AND HOW TO SEND THAT
    -NEED TO FINISH INVENTORY AND UPDATING AFTER SALE
    -NEED TO FINISH ACCOUNT MANAGEMENT CHANGING PASSWORDS
    -NEED TO ADD ROUTES
*/