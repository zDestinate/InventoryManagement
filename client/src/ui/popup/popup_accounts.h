#pragma once

#include <Windows.h>
#include "ui/form_underlinetxtbox.h"
#include "ui/form_button.h"
#include "datahandler/mainHeader.h"

class popup_accounts
{
    private:
        HINSTANCE hInstMainWin;
        HWND hwndMain;

        HFONT hFont, hFontButton;

        bool CenterWindow(HWND hwndWindow);

        static LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
        LRESULT CALLBACK RealWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

        int txtboxWidth, txtboxHeight, nCenterX, nY;

        form_button* btnFirstButton, *btnCancel;
        int nButtonWidth, nButtonHeight;

    public:
        HWND hwnd;
        HWND hwndContent;
        form_underlinetxtbox* txtUsername, *txtPassword, *txtFullname, *txtPhone, *txtEmail, *txtPermission;
        int nEditVectorID;

        mainClass* DataHandler = nullptr;

        popup_accounts(HWND hwndMain);
        int CreateFormMain();
        static DWORD WINAPI CreateThread(void* Param);
        DWORD ThreadStart(void);

        bool bShowPassword, bShowPersonalInfo;
        void SetFont(HFONT hFont);
};