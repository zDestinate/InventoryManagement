#pragma once

#include <Windows.h>
#include "ui/form_menubar.h"
#include "ui/form_menutop.h"

class form_main
{
    private:
        HINSTANCE hInstMainWin;
        HWND hwndLogin;

        int MenuTopHeight = 80;
        form_menutop* Menu_Top;

        int ItemMinWidth = 55;
        int ItemMaxWidth = 220;
        form_menubar* Menu_Bar;

        bool CenterWindow(HWND hwndWindow);

        static LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
        LRESULT CALLBACK RealWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

    public:
        HWND hwndMain;

        form_main(HWND hwndLogin);
        int CreateFormMain();
        
};