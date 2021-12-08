#include <iostream>
#include <Windows.h>
#include <string>
#include "global.h"
#include "datahandler/mainHeader.h"
#include "lib/json.hpp"

using namespace std;
using json = nlohmann::json;

mainClass::mainClass()
{
    URL = LinkURL;

    //For login
    estabLogIn = new UserLogIn();
    //addingToCart
    addCart = new Sales();
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
            return false;
        }

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

void mainClass::logOut()
{
    DataGrabber->ConnectTo("/user/logout");
    DataGrabber->ClearCookies();
    estabLogIn->LogOut();
}

/*bool mainClass::CreateAccoount(std::string username,std::string password,std::string phonenum,std::string email, std::string perm,std::string flname)
{

    bool busername = estabLogIn->LoginUser(username);
    bool bpassword = estabLogIn->LoginPass(password);
    bool namecheck = manageAcc ->checkName(flname);
    bool check1 = manageAcc->createCustomer(phonenum, email);

    if(busername && bpassword && namecheck)
    {
       // string strResult = DataGrabber->ConnectTo("/user/login/" + estabLogIn->strUsername + "/" + estabLogIn->strPassword + "/" + fname + "/" + lname + "/" + position);
        return true;
    }

    return false;
    
}
*/
bool mainClass::deleteAcc(std::string id)
{
    string strResult = DataGrabber->ConnectTo("/user/logout");
    return true;    
}


bool mainClass::returnUserData()
{
    string strResult = DataGrabber->ConnectTo("/user/logout");

    json datajson = json::parse(strResult);
    bool getDataResult = manageAcc->allUserData(datajson);

    if(getDataResult){
        cout<< "successful" << endl;
        return true;
    }
    cout<< "failed" << endl;
    return false;
}

int mainClass::addToCart(string productSku)
{
    string item = productSku;
    
   // string strResult = DataGrabber->ConnectTo("/inventory/item" + addCart->item);
    /* json datajson = json::parse(strResult);
        if(datajson.at("code") == 200)
        {

        }
    */
   return 0;
}

bool mainClass::addItemToDB(std::string name, std::string sku, int price)
{

   string strResult = DataGrabber->ConnectTo("/user/logout");
    return true;
}

