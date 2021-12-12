#pragma once

#include <Windows.h>
#include "datahandler/mainHeader.h"
#include "ui/form_underlinetxtbox.h"
#include "ui/form_button.h"

class popup_item
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
        form_underlinetxtbox* txtUPC, *txtDescription, *txtQuantity, *txtPrice;
        int nEditVectorID;

        mainClass* DataHandler = nullptr;

        popup_item(HWND hwndMain);
        int CreateFormMain();
        static DWORD WINAPI CreateThread(void* Param);
        DWORD ThreadStart(void);

        void SetFont(HFONT hFont);
};