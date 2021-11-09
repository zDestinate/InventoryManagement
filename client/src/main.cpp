#include <iostream>
#include <Windows.h>
#include <fstream>
#include <conio.h>
#include "api/api.h"
#include "ui/form.h"

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
	HWND hwndConsole = GetConsoleWindow();
	DWORD dwProcessId;
	GetWindowThreadProcessId(hwndConsole, &dwProcessId);
	if (GetCurrentProcessId() == dwProcessId)
	{
		SetConsoleTitle("InventoryManagement");
	}
	else
	{
		ShowWindow(hwndConsole, SW_HIDE);
	}

	if (!ifstream(ApplicationPath() + "/libcurl.dll"))
	{
		MessageBox(NULL, "Error 0x1001\nPlease make sure you have the libcurl.dll file.", "ERROR", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);
		exit(0);
		return 1;
	}

	Form* MainWindow = new Form();
	return MainWindow->CreateForm();
}