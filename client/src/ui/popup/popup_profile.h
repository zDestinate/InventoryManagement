#pragma once

#include <Windows.h>
#include "ui/form_underlinetxtbox.h"
#include "ui/form_button.h"

class popup_profile
{
    private:
        HINSTANCE hInstMainWin;
        HWND hwndMain;

        HFONT hFont, hFontButton;

        bool CenterWindow(HWND hwndWindow);

        static LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
        LRESULT CALLBACK RealWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

        form_underlinetxtbox* txtCurrentPassword, *txtNewPassword, *txtConfirmPassword;
        int txtboxWidth, txtboxHeight, nCenterX, nY;

        form_button* btnChange, *btnCancel;
        int nButtonWidth, nButtonHeight;

    public:
        HWND hwnd;

        popup_profile(HWND hwndMain);
        int CreateFormMain();
        static DWORD WINAPI CreateThread(void* Param);
        DWORD ThreadStart(void);

        void SetFont(HFONT hFont);
};