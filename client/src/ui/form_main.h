#pragma once

#include <Windows.h>
#include "ui/form_underlinetxtbox.h"
#include "ui/form_staticlabel.h"
#include "ui/form_button.h"

class form_main
{
    private:
        HINSTANCE hInstMainWin;
        HWND hwndLogin;

        bool CenterWindow(HWND hwndWindow);

        static LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
        LRESULT CALLBACK RealWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

    public:
        HWND hwndMain;

        form_main(HWND hwndLogin);
        int CreateFormMain();
        
};