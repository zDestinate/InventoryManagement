#include <iostream>
#include <Windows.h>
#include <string>
#include "datahandler/mainHeader.h"

using namespace std;

mainClass::mainClass()
{
    //For login
    estabLogIn = new UserLogIn();

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
        string strResult = DataGrabber->ConnectTo("/user/login" + estabLogIn->strUsername + "/" + estabLogIn->strPassword);
    }
}

/*bool mainClass::CreateAccoount();
string mainClass::AddItem()
{
    return "Failed: Item exist";
}
*/