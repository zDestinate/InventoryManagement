#pragma once

#include <Windows.h>
#include <commctrl.h>
#include <string>
#include "ui/form_menuitem.h"
#include "ui/content/content_dashboard.h"

using namespace std;

class form_menubar
{
    private:
        static LRESULT CALLBACK StaticProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData);
        int MenuBarWidth;

        form_menuitem* MenuItem_Dashboard, *MenuItem_Item, *MenuItem_PointOfSale, *MenuItem_Promotion, *MenuItem_Accounts, *MenuItem_Settings;
        int* FocusContentFormObj = nullptr;
        content* Content = nullptr;
        content_dashboard* ContentDashboard;

    public:
        HWND hwndmenubar;
        HWND hwndParent;

        COLORREF BackgroundColorRGB = RGB(255, 255, 255);
        int ItemWidth, ItemHeight, ItemMaxWidth;
        bool bItemExtended = false;

        form_menubar(HWND hwndParent, int lpParam, int x, int y, int width, int height, int ItemMinWidth, int ItemMaxWidth, int &FocusContentFormObj);

        void SetCurrentContent(content* FocusContent);
};