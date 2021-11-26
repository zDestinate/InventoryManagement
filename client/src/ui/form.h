#pragma once

#include <Windows.h>
#include "ui/form_underlinetxtbox.h"
#include "ui/form_staticlabel.h"
#include "ui/form_button.h"
#include "ui/form_main.h"

class Form
{
    private:
        HINSTANCE hInstLoginWin;
        HWND hwndLogin;
        form_staticlabel* lblTitle, *lblVersion;
        form_underlinetxtbox* txtboxUsername, *txtboxPassword;
        form_button* btnLogin, *btnExit;
        form_main* formMain;


        bool CenterWindow(HWND hwndWindow);

        static LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
        LRESULT CALLBACK RealWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

    public:
        int CreateForm();
        
};