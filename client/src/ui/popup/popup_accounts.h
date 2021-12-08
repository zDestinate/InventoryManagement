#pragma once

#include <Windows.h>
#include "ui/form_underlinetxtbox.h"
#include "ui/form_button.h"

class popup_accounts
{
    private:
        HINSTANCE hInstMainWin;
        HWND hwndContent;

        HFONT hFont, hFontButton;

        bool CenterWindow(HWND hwndWindow);

        static LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
        LRESULT CALLBACK RealWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

        form_underlinetxtbox* txtUsername, *txtPassword, *txtFullname, *txtPhone, *txtEmail, *txtPermission;
        int txtboxWidth, txtboxHeight, nCenterX, nY;

        form_button* btnFirstButton, *btnCancel;
        int nButtonWidth, nButtonHeight;

    public:
        HWND hwnd;

        popup_accounts(HWND hwndContent);
        int CreateFormMain();
        static DWORD WINAPI CreateThread(void* Param);
        DWORD ThreadStart(void);

        bool bShowPassword, bShowPersonalInfo;
        void SetFont(HFONT hFont);
};