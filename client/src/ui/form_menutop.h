#pragma once

#include <Windows.h>
#include <commctrl.h>
#include <string>
#include "ui/form_menuuser.h"

using namespace std;

class form_menutop
{
    private:
        static LRESULT CALLBACK MenuTopProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData);
        HFONT hFontTitle, hFontName, hFontID;

        int nBottomBorderHeight = 1;

        form_menuuser* MenuUser;
        int MenuTop_UserWidth = 220;

    public:
        HWND hwndmenutop;
        COLORREF BackgroundColorRGB;
        COLORREF BottomBorderColorRGB;
        COLORREF TitleTextColorRGB;
        wstring TitleText;
        int nTitleIndent, nTitleWidth;

        form_menutop(HWND hwndParent, int lpParam, int x, int y, int width, int height);
        void SetNameText(wstring Name);
        void SetIDText(wstring ID);
};