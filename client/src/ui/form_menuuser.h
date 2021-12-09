#pragma once

#include <Windows.h>
#include <commctrl.h>
#include <string>
#include "ui/popup/popup_profile.h"

using namespace std;

class form_menuuser
{
    private:
        static LRESULT CALLBACK ButtonProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData);

        bool bHover = false;
        HFONT hFontIcon;
        
        DWORD dwThreadID_PopUp_Profile;

    public:
        HWND hwnd;
        HFONT hFontName, hFontID;
        wstring IconText, NameText, IDText;
        COLORREF ButtonColorRGB = RGB(0, 0, 0);
        COLORREF ButtonColorRGB_Hover = RGB(0, 0, 0);
        COLORREF NameTextColorRGB = RGB(0, 0, 0);
        COLORREF NameTextColorRGB_Hover = RGB(255, 255, 255);
        COLORREF IDTextColorRGB = RGB(0, 0, 0);
        COLORREF IDTextColorRGB_Hover = RGB(255, 255, 255);

        popup_profile* FormProfile = nullptr;

        form_menuuser(HWND hwndParent, int lpParam, int x, int y, int width, int height);
        void SetProfilePopup(HWND hwndMain);
};