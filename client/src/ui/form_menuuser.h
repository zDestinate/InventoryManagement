#pragma once

#include <Windows.h>
#include <commctrl.h>
#include <string>

using namespace std;

class form_menuuser
{
    private:
        static LRESULT CALLBACK ButtonProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData);

        bool bHover = false;
        HFONT hFontIcon;
        int minx, miny, maxx, currentx, locx, locy;

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
        bool bItemExtended = false;

        form_menuuser(HWND hwndParent, int lpParam, int x, int y, int width, int height);
        void SetMaxWidth(int nMaxWidth);
};