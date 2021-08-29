#include <iostream>
#include <Windows.h>
#include <fstream>
#include "api/api.h"

using namespace std;

int main()
{
    SetConsoleTitle("SPTrade");

    if (!ifstream("libcurl.dll"))
	{
		MessageBox(NULL, "Error 0xFF01\nPlease make sure you have the libcurl.dll file locate within the lib folder.", "ERROR", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);
		exit(0);
	}

    printf("Test\nTest2\n");

    api* test = new api();
}