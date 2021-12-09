#include <iostream>
#include <Windows.h>
#include <fstream>
#include <cassert>
#include <conio.h>
#include "global.h"
#include "ui/form.h"

#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

using namespace std;


string ProgramVersion = "Version 1.0.0.12";
string LinkURL = "http://157.245.0.156";
LPCTSTR FontNames[6];
string FontPaths[6];

string ApplicationPath() 
{
	char buffer[MAX_PATH];
	GetModuleFileName(NULL, buffer, MAX_PATH);
	int pos = string(buffer).find_last_of("\\/");
	return string(buffer).substr(0, pos);
}

bool fileExists(const std::string& fileName)
{
	fstream file;
	file.open(fileName.c_str(), ios::in);
	if (file.is_open() == true)
	{
		file.close();
		return true;
	}
	file.close();
	return false;
}

static void copyFile(const std::string& fileNameFrom, const std::string& fileNameTo)
{
	assert(fileExists(fileNameFrom));
	ifstream in (fileNameFrom.c_str());
	ofstream out (fileNameTo.c_str());
	out << in.rdbuf();
	out.close();
	in.close();
}

int main()
{
	//Check if it console
	HWND hwndConsole = GetConsoleWindow();
	DWORD dwProcessId;
	GetWindowThreadProcessId(hwndConsole, &dwProcessId);
	/*
	if (GetCurrentProcessId() != dwProcessId)
	{
		SetConsoleTitle("InventoryManagement - Developer Console");
	}
	else
	{
		ShowWindow(hwndConsole, SW_HIDE);
	}
	*/

	SetConsoleTitle("InventoryManagement - Developer Console");

	if(IsDebuggerPresent())
	{
		MessageBox(NULL, "Error 0x1001\nUnable to start due to security risk", "WARNING", MB_OK | MB_ICONWARNING | MB_SYSTEMMODAL);
		exit(1000);
		return 1;
	}

	//Check if curl exist
	if (!ifstream(ApplicationPath() + "/libcurl.dll"))
	{
		MessageBox(NULL, "Error 0x1002\nPlease make sure you have the libcurl.dll file.", "ERROR", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);
		exit(0);
		return 1;
	}

	//Check fonts
	if (!ifstream(ApplicationPath() + "/res/fonts/Font Awesome 6 Brands-Regular-400.otf"))
	{
		MessageBox(NULL, "Error 0x1003\nMissing some font files", "ERROR", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);
		exit(0);
		return 1;
	}

	if (!ifstream(ApplicationPath() + "/res/fonts/Font Awesome 6 Duotone-Solid-900.otf"))
	{
		MessageBox(NULL, "Error 0x1004\nMissing some font files", "ERROR", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);
		exit(0);
		return 1;
	}

	if (!ifstream(ApplicationPath() + "/res/fonts/Font Awesome 6 Pro-Light-300.otf"))
	{
		MessageBox(NULL, "Error 0x1005\nMissing some font files", "ERROR", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);
		exit(0);
		return 1;
	}

	if (!ifstream(ApplicationPath() + "/res/fonts/Font Awesome 6 Pro-Regular-400.otf"))
	{
		MessageBox(NULL, "Error 0x1006\nMissing some font files", "ERROR", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);
		exit(0);
		return 1;
	}

	if (!ifstream(ApplicationPath() + "/res/fonts/Font Awesome 6 Pro-Solid-900.otf"))
	{
		MessageBox(NULL, "Error 0x1007\nMissing some font files", "ERROR", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);
		exit(0);
		return 1;
	}

	if (!ifstream(ApplicationPath() + "/res/fonts/Font Awesome 6 Pro-Thin-100.otf"))
	{
		MessageBox(NULL, "Error 0x1008\nMissing some font files", "ERROR", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);
		exit(0);
		return 1;
	}

	/*
	FontPaths[0] = (ApplicationPath() + "\\res\\fonts\\fa-brands-400.ttf");
	FontPaths[1] = (ApplicationPath() + "\\res\\fonts\\fa-duotone-900.ttf");
	FontPaths[2] = (ApplicationPath() + "\\res\\fonts\\fa-light-300.ttf");
	FontPaths[3] = (ApplicationPath() + "\\res\\fonts\\fa-regular-400.ttf");
	FontPaths[4] = (ApplicationPath() + "\\res\\fonts\\fa-solid-900.ttf");

	FontNames[0] = "Font Awesome 5 Brands Regular (TrueType)";
	FontNames[1] = "Font Awesome 5 Duotone Solid (TrueType)";
	FontNames[2] = "Font Awesome 5 Pro Light (TrueType)";
	FontNames[3] = "Font Awesome 5 Pro Regular (TrueType)";
	FontNames[4] = "Font Awesome 5 Pro Solid (TrueType)";
	*/

	FontPaths[0] = (ApplicationPath() + "\\res\\fonts\\Font Awesome 6 Brands-Regular-400.otf");
	FontPaths[1] = (ApplicationPath() + "\\res\\fonts\\Font Awesome 6 Duotone-Solid-900.otf");
	FontPaths[2] = (ApplicationPath() + "\\res\\fonts\\Font Awesome 6 Pro-Light-300.otf");
	FontPaths[3] = (ApplicationPath() + "\\res\\fonts\\Font Awesome 6 Pro-Regular-400.otf");
	FontPaths[4] = (ApplicationPath() + "\\res\\fonts\\Font Awesome 6 Pro-Solid-900.otf");
	FontPaths[5] = (ApplicationPath() + "\\res\\fonts\\Font Awesome 6 Pro-Thin-100.otf");

	FontNames[0] = "Font Awesome 6 Brands Regular";
	FontNames[1] = "Font Awesome 6 Duotone Solid";
	FontNames[2] = "Font Awesome 6 Pro Light";
	FontNames[3] = "Font Awesome 6 Pro Regular";
	FontNames[4] = "Font Awesome 6 Pro Solid";
	FontNames[5] = "Font Awesome 6 Pro Thin";

	/*
	string FontPathNames[5];
	FontPathNames[0] = "fa-brands-400.ttf";
	FontPathNames[1] = "fa-duotone-900.ttf";
	FontPathNames[2] = "fa-light-300.ttf";
	FontPathNames[3] = "fa-regular-400.ttf";
	FontPathNames[4] = "fa-solid-900.ttf";

	string WindowsPath[5];

	//Start installing font to local appdata
	string AppDataLocal = getenv("LOCALAPPDATA");
	for(int i = 0; i < 5; i++)
	{
		copyFile(FontPaths[0], AppDataLocal + "\\Microsoft\\Windows\\Fonts\\" + FontPathNames[i]);
		WindowsPath[i] = AppDataLocal + "\\Microsoft\\Windows\\Fonts\\" + FontPathNames[i];
	}

	//Install it in the regedit
	HKEY hKey;
	LPCTSTR subkey = TEXT("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Fonts");
	LONG openRes = RegOpenKeyEx(HKEY_CURRENT_USER, subkey, 0, KEY_ALL_ACCESS , &hKey);
	if (openRes != ERROR_SUCCESS)
	{
		MessageBox(NULL, "Error 0x1005\nMissing some permission", "ERROR", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);
		exit(0);
		return 1;
	}

	for(int i = 0; i < 5; i++)
	{
		wchar_t value[255];
		DWORD BufferSize = sizeof(value);
		LONG result = RegGetValue(HKEY_CURRENT_USER, subkey, FontNames[i], RRF_RT_REG_SZ, NULL, (PVOID)&value, &BufferSize);
		if(result != ERROR_SUCCESS)
		{
			RegSetValueEx(hKey, FontNames[i], 0, REG_SZ, (LPBYTE)(WindowsPath[i].c_str()), WindowsPath[i].length() + 1);
		}
	}
	*/

	//Add fonts (This is just cache for this app)
	AddFontResourceEx((LPCSTR)FontPaths[0].c_str(), FR_PRIVATE, NULL);
	AddFontResourceEx((LPCSTR)FontPaths[1].c_str(), FR_PRIVATE, NULL);
	AddFontResourceEx((LPCSTR)FontPaths[2].c_str(), FR_PRIVATE, NULL);
	AddFontResourceEx((LPCSTR)FontPaths[3].c_str(), FR_PRIVATE, NULL);
	AddFontResourceEx((LPCSTR)FontPaths[4].c_str(), FR_PRIVATE, NULL);
	AddFontResourceEx((LPCSTR)FontPaths[5].c_str(), FR_PRIVATE, NULL);
    //SendMessage(HWND_BROADCAST, WM_FONTCHANGE, 0, 0);

	Form* MainWindow = new Form();
	return MainWindow->CreateForm();
}