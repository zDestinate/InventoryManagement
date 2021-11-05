#include <iostream>
#include <Windows.h>
#include <fstream>
#include <conio.h>
#include "api/api.h"

using namespace std;

string ApplicationPath() 
{
	char buffer[MAX_PATH];
	GetModuleFileName(NULL, buffer, MAX_PATH);
	int pos = string(buffer).find_last_of("\\/");
	return string(buffer).substr(0, pos);
}

int main()
{
    SetConsoleTitle("SPTrade");

    if (!ifstream(ApplicationPath() + "/libcurl.dll"))
	{
		MessageBox(NULL, "Error 0xFF01\nPlease make sure you have the libcurl.dll file.", "ERROR", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);
		exit(0);
	}

    printf("Test\nTest2\n");

    api* test = new api();

    _getch();
}