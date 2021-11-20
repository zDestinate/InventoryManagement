#include <iostream>
#include <Windows.h>
#include <string>
#include "datahandler/mainHeader.h"

using namespace std;

mainClass::mainClass()
{
    //For login
    LogIn = new MyClass;

    //For getting the data
    DataGrabber = new getData(URL);
    DataGrabber->EstablishConnection();
}

void mainClass::test()
{
    bool username = LogIn->LoginUser("kajdslfkjasdf");
    bool password = LogIn->LoginPass("kajdslfkjasdf");

    if(username && password)
    {
        //Response from the site
        string strResult = DataGrabber->ConnectTo("/user/login" + LogIn->strUsername + "/" + LogIn->strPassword);
    }
}
