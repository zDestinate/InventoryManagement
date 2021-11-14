#pragma once
#include <Windows.h>

class Form
{
    private:
        HINSTANCE hInstMainWin;
        HWND hwndMain;
        HWND txtboxUsername, txtboxPassword;

        bool CenterWindow(HWND hwndWindow);

        static LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
        LRESULT CALLBACK RealWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
    public:
        int CreateForm();
        
};