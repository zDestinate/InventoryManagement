#include <iostream>
#include <Windows.h>
#include "datahandler/getData.h"
#include "lib/json.hpp"

using namespace std;

using json = nlohmann::json;

getData::getData(string URL)
{
    this->URL = URL;
}

string getData::ApplicationPath() 
{
	char buffer[MAX_PATH];
	GetModuleFileName(NULL, buffer, MAX_PATH);
	int pos = string(buffer).find_last_of("\\/");
	return string(buffer).substr(0, pos);
}

size_t WriteCallback(char *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

void getData::EstablishConnection()
{
    curlObj = curl_easy_init();
}

string getData::ConnectTo(string link)
{
    string strPath = URL + link;
    string strData;

    //convert URL string into C string
    curl_easy_setopt(curlObj, CURLOPT_URL, strPath.c_str());
    curl_easy_setopt(curlObj, CURLOPT_COOKIEFILE, ApplicationPath() + "/cookie.txt");
    curl_easy_setopt(curlObj, CURLOPT_COOKIEJAR, ApplicationPath() + "/cookie.txt");
    curl_easy_setopt(curlObj, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curlObj, CURLOPT_WRITEDATA, &strData);

    curl_easy_perform(curlObj);

    return strData;
}

string getData::getUserData()
{
    EstablishConnection();
	string data = ConnectTo("/gvhjgvjhgvjhg");
	json datajson = json::parse(data);
    return "NOTHING";
}