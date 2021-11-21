#pragma once

#include <Windows.h>
#include "ui/form_underlinetxtbox.h"
#include "ui/form_staticlabel.h"

class Form
{
    private:
        const int TXT_USERNAME = 1000;
        const int TXT_PASSWORD = 1001;
        const int LBL_TITLE = 2000;

    private:
        HINSTANCE hInstMainWin;
        HWND hwndMain;
        form_staticlabel* lblTitle;
        form_underlinetxtbox* txtboxUsername,* txtboxPassword;


        bool CenterWindow(HWND hwndWindow);

        static LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
        LRESULT CALLBACK RealWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

    public:
        int CreateForm();
        
};