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

bool mainClass::LogIn(string username, string password)
{
    bool busername = estabLogIn->LoginUser(username);
    bool bpassword = estabLogIn->LoginPass(password);

    //string product = getData -> getProductData("sagasgsa");

    if(busername && bpassword)
    {
        //Response from the site
        string strResult = DataGrabber->ConnectTo("/user/login/" + estabLogIn->strUsername + "/" + estabLogIn->strPassword);

        if(!DataGrabber->bSuccessfullyConnected)
        {
            severStatus = false;
            return false;
        }
        severStatus = true;

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
        severStatus = true;

    DataGrabber->ClearCookies();
    estabLogIn->LogOut();
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
        severStatus = true;

    if(busername && bpassword && namecheck && check1)
    {
         ///user/create/:username/:password/:phone/:perm/:flname
       string strResult = DataGrabber->ConnectTo("/user/create/" + username + "/" + password + "/" + phonenum + "/" + email + "/" + perm + "/" + flname);
       returnUserData();
       return true;
    }
    return false;   
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

bool mainClass::returnUserData()
{
    string strResult = DataGrabber->ConnectTo("/user");
    if(!DataGrabber->bSuccessfullyConnected)
        {
            severStatus = false;
        }
        severStatus = true;

    json datajson = json::parse(strResult);
    bool getDataResult = manageAcc->allUserData(datajson);

    if(getDataResult){
        cout<< "successful" << endl;
        return true;
    }
    cout<< "failed" << endl;
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

bool mainClass::addToCart(std::string productSku)
{   
    string strResult = DataGrabber->ConnectTo("/inventory/item" + productSku);
    json datajson = json::parse(strResult);
       
    bool addResult = Cart->addToCart(datajson);
    if(addResult)
    {
        return true;
    }
    return false;
}

bool mainClass::removeFromCart(std::string productSku)
{
    bool remove = Cart->removeFromCart(productSku);
    
    if(remove){
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
        severStatus = true;
   
    Cart->clearCart();
}

bool mainClass::addItemToDB(std::string name, std::string sku, std::string price)
{

   string strResult = DataGrabber->ConnectTo("/user/logout");
   if(!DataGrabber->bSuccessfullyConnected)
        {
            severStatus = false;
        }
        severStatus = true;
    return true;
}

bool mainClass::editUserName(std::string id,std::string newName)
{   
    bool editName = manageAcc->changeUserName(id, newName);
        
        if(editName)
        {
            string strResult = DataGrabber->ConnectTo("/user/login/" + id + "/" +newName);

            if(!DataGrabber->bSuccessfullyConnected)
        {
            severStatus = false;
        }
            severStatus = true;

            return true;
        }
        
    return false;
}

bool mainClass::editPhone(std::string id,std::string newPhone)
{
   bool editName = manageAcc->changeUserName(id, newPhone);
        
        if(editName)
        {
            string strResult = DataGrabber->ConnectTo("/user/login/" + id + "/" + newPhone);
            return true;
        }
        
    return false;
}

bool mainClass::editEmail(std::string id,std::string  newEmail)
{
    bool editName = manageAcc->changeUserName(id, newEmail);
        
        if(editName)
        {
            string strResult = DataGrabber->ConnectTo("/user/login/" + id + "/" +newEmail);
            return true;
        }
        
    return false;
}

bool mainClass::editPerm(std::string id,std::string newPerm)
{
    bool editName = manageAcc->changeUserName(id, newPerm);
        
        if(editName)
        {
            string strResult = DataGrabber->ConnectTo("/user/login/" + id + "/" +newPerm);
            return true;
        }
        
    return false;
}

bool mainClass::editFlname(std::string id,std::string  newFlname)
{
    bool editName = manageAcc->changeUserName(id, newFlname);
        
        if(editName)
        {
            string strResult = DataGrabber->ConnectTo("/user/login/" + id + "/" +newFlname);
            return true;
        }
        
    return false;
}

bool mainClass::editPassword(std::string id,std::string newPassword)
{
    bool editName = manageAcc->changeUserName(id, newPassword);
        
        if(editName)
        {
            string strResult = DataGrabber->ConnectTo("/user/login/" + id + "/" +newPassword);
            return true;
        }
        
    return false;
}





/*  -NEED TO FINISH SALES AND HOW TO SEND THAT
    -NEED TO FINISH INVENTORY AND UPDATING AFTER SALE
    -NEED TO FINISH ACCOUNT MANAGEMENT CHANGING PASSWORDS
    -NEED TO ADD ROUTES
*/