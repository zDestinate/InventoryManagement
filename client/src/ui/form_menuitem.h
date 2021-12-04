#pragma once

#include <Windows.h>
#include <commctrl.h>
#include <string>
#include "ui/content/content.h"

using namespace std;

class form_menuitem
{
    private:
        static LRESULT CALLBACK ButtonProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData);

        HWND hwndParent;

        bool bHover = false;
        HFONT hFont;
        int minx, miny, maxx, currentx, locx, locy;
        UINT IDT_HOVER_TIMER_CHECK;

    public:
        HWND hwndbutton;
        content* Content = nullptr;
        
        wstring IconText, ButtonText;
        COLORREF ButtonColorRGB = RGB(0, 0, 0);
        COLORREF ButtonColorRGB_Hover = RGB(0, 0, 0);
        COLORREF TextColorRGB = RGB(255, 255, 255);
        COLORREF TextColorRGB_Hover = RGB(255, 255, 255);
        bool bItemExtended = false;

        form_menuitem(HWND hwndParent, int lpParam, int x, int y, int width, int height, UINT timerID);

        void SetFont(HFONT hFont);
        void SetMaxWidth(int nMaxWidth);
};