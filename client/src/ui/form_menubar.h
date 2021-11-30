#pragma once

#include <Windows.h>
#include <commctrl.h>
#include <string>
#include "ui/form_menuitem.h"

using namespace std;

class form_menubar
{
    private:
        static LRESULT CALLBACK StaticProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData);
        int MenuBarWidth;

        form_menuitem* MenuItem_Dashboard, *MenuItem_Item, *MenuItem_PointOfSale, *MenuItem_Promotion, *MenuItem_Accounts, *MenuItem_Settings;

    public:
        HWND hwndmenubar;
        COLORREF BackgroundColorRGB = RGB(255, 255, 255);
        int ItemWidth, ItemHeight, ItemMaxWidth;
        bool bItemExtended = false;

        form_menubar(HWND hwndParent, int lpParam, int x, int y, int width, int height, int ItemMinWidth, int ItemMaxWidth);
};