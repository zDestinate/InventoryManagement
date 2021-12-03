#include <iostream>
#include <codecvt>
#include "ui/objects.h"
#include "ui/form_menubar.h"

#pragma comment(lib, "comctl32.lib")

form_menubar::form_menubar(HWND hwndParent, int lpParam, int x, int y, int width, int height, int ItemMinWidth, int ItemMaxWidth, int &FocusContentFormObj)
{
    hwndmenubar = CreateWindow("STATIC", "", ES_CENTER | WS_CHILD | WS_VISIBLE, x, y, width, height, hwndParent, (HMENU)lpParam, NULL, NULL);
    SetWindowSubclass(hwndmenubar, StaticProc, lpParam, (DWORD_PTR)this);

    MenuBarWidth = ItemMinWidth;
    ItemWidth = ItemMinWidth;
    ItemHeight = ItemMinWidth;
    this->ItemMaxWidth = ItemMaxWidth;
    this->FocusContentFormObj = &FocusContentFormObj;
    this->hwndParent = hwndParent;

    HFONT hFontButton = CreateFont(17, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, 
        OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, 
        DEFAULT_PITCH | FF_MODERN, TEXT("Arial"));

    MenuItem_Dashboard = new form_menuitem(hwndmenubar, FormObjects::MENU_DASHBOARD, 0, 0, ItemWidth, ItemHeight, FormTimers::MENU_DASHBOARD_TIMER);
    MenuItem_Dashboard->SetFont(hFontButton);
    MenuItem_Dashboard->IconText = L"\uf62c";
    MenuItem_Dashboard->ButtonText = L"Dashboard";
    MenuItem_Dashboard->ButtonColorRGB = RGB(0, 0, 0);
    MenuItem_Dashboard->ButtonColorRGB_Hover = RGB(0, 154, 229);
    MenuItem_Dashboard->SetMaxWidth(ItemMaxWidth);

    MenuItem_Item = new form_menuitem(hwndmenubar, FormObjects::MENU_ITEM, 0, ItemWidth * 1, ItemWidth, ItemHeight, FormTimers::MENU_ITEM_TIMER);
    MenuItem_Item->SetFont(hFontButton);
    MenuItem_Item->IconText = L"\uf468";
    MenuItem_Item->ButtonText = L"Item";
    MenuItem_Item->ButtonColorRGB = RGB(0, 0, 0);
    MenuItem_Item->ButtonColorRGB_Hover = RGB(0, 154, 229);
    MenuItem_Item->SetMaxWidth(ItemMaxWidth);

    MenuItem_PointOfSale = new form_menuitem(hwndmenubar, FormObjects::MENU_POINTOFSALE, 0, ItemWidth * 2, ItemWidth, ItemHeight, FormTimers::MENU_POINTOFSALE_TIMER);
    MenuItem_PointOfSale->SetFont(hFontButton);
    MenuItem_PointOfSale->IconText = L"\uf218";
    MenuItem_PointOfSale->ButtonText = L"Point Of Sale";
    MenuItem_PointOfSale->ButtonColorRGB = RGB(0, 0, 0);
    MenuItem_PointOfSale->ButtonColorRGB_Hover = RGB(0, 154, 229);
    MenuItem_PointOfSale->SetMaxWidth(ItemMaxWidth);

    MenuItem_Promotion = new form_menuitem(hwndmenubar, FormObjects::MENU_PROMOTION, 0, ItemWidth * 3, ItemWidth, ItemHeight, FormTimers::MENU_PROMOTION_TIMER);
    MenuItem_Promotion->SetFont(hFontButton);
    MenuItem_Promotion->IconText = L"\uf641";
    MenuItem_Promotion->ButtonText = L"Promotion";
    MenuItem_Promotion->ButtonColorRGB = RGB(0, 0, 0);
    MenuItem_Promotion->ButtonColorRGB_Hover = RGB(0, 154, 229);
    MenuItem_Promotion->SetMaxWidth(ItemMaxWidth);

    MenuItem_Accounts = new form_menuitem(hwndmenubar, FormObjects::MENU_ACCOUNTS, 0, ItemWidth * 4, ItemWidth, ItemHeight, FormTimers::MENU_ACCOUNTS_TIMER);
    MenuItem_Accounts->SetFont(hFontButton);
    MenuItem_Accounts->IconText = L"\uf509";
    MenuItem_Accounts->ButtonText = L"Accounts";
    MenuItem_Accounts->ButtonColorRGB = RGB(0, 0, 0);
    MenuItem_Accounts->ButtonColorRGB_Hover = RGB(0, 154, 229);
    MenuItem_Accounts->SetMaxWidth(ItemMaxWidth);

    MenuItem_Settings = new form_menuitem(hwndmenubar, FormObjects::MENU_SETTINGS, 0, ItemWidth * 5, ItemWidth, ItemHeight, FormTimers::MENU_SETTINGS_TIMER);
    MenuItem_Settings->SetFont(hFontButton);
    MenuItem_Settings->IconText = L"\uf7d9";
    MenuItem_Settings->ButtonText = L"Settings";
    MenuItem_Settings->ButtonColorRGB = RGB(0, 0, 0);
    MenuItem_Settings->ButtonColorRGB_Hover = RGB(0, 154, 229);
    MenuItem_Settings->SetMaxWidth(ItemMaxWidth);
}

LRESULT form_menubar::StaticProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
    //Using the dwRefData we passed from and create this pointer
    form_menubar* pThis = (form_menubar*) dwRefData;

    switch (message)
    {
    case WM_ERASEBKGND:
        {
            //Get the current HWND Rect
            RECT rc;
            GetClientRect(hwnd, &rc);

            PAINTSTRUCT ps;
            HDC hdc;

            //Start painting the line base on the focus status
            hdc = BeginPaint(hwnd, &ps);
            SetBkMode(hdc, TRANSPARENT);

            //Paint background
            HBRUSH hBackgroundColor;
            hBackgroundColor = CreateSolidBrush(RGB(255, 255, 255)); 
            SelectObject(hdc, hBackgroundColor);
            FillRect(hdc, &rc, hBackgroundColor);
            DeleteObject(hBackgroundColor);

            EndPaint(hwnd, &ps);
        }
        break;
    case WM_PAINT:
        {
            //Get the current HWND Rect
            RECT rc;
            GetClientRect(hwnd, &rc);

            //Clear all the painting and update the hwnd
            //InvalidateRect(hwnd, &rc, TRUE);
            //UpdateWindow(hwnd);
            //RedrawWindow(hwnd, 0, 0, RDW_ERASE | RDW_UPDATENOW);

            PAINTSTRUCT ps;
            HDC hdc;

            //Start painting the line base on the focus status
            hdc = BeginPaint(hwnd, &ps);

            //Paint sidebar
            HBRUSH hMenuBarColor;
            hMenuBarColor = CreateSolidBrush(pThis->BackgroundColorRGB); 
            SelectObject(hdc, hMenuBarColor);
            rc.right = pThis->MenuBarWidth;
            FillRect(hdc, &rc, hMenuBarColor);
            DeleteObject(hMenuBarColor);

            //Other settings
            if(pThis->bItemExtended)
            {
                pThis->MenuBarWidth = pThis->ItemMaxWidth;
            }
            else
            {
                pThis->MenuBarWidth = pThis->ItemWidth;
            }

            pThis->MenuItem_Dashboard->bItemExtended = pThis->bItemExtended;
            pThis->MenuItem_Item->bItemExtended = pThis->bItemExtended;
            pThis->MenuItem_PointOfSale->bItemExtended = pThis->bItemExtended;
            pThis->MenuItem_Promotion->bItemExtended = pThis->bItemExtended;
            pThis->MenuItem_Accounts->bItemExtended = pThis->bItemExtended;
            pThis->MenuItem_Settings->bItemExtended = pThis->bItemExtended;

            pThis->MenuItem_Dashboard->SetMaxWidth(pThis->ItemMaxWidth);
            pThis->MenuItem_Item->SetMaxWidth(pThis->ItemMaxWidth);
            pThis->MenuItem_PointOfSale->SetMaxWidth(pThis->ItemMaxWidth);
            pThis->MenuItem_Promotion->SetMaxWidth(pThis->ItemMaxWidth);
            pThis->MenuItem_Accounts->SetMaxWidth(pThis->ItemMaxWidth);
            pThis->MenuItem_Settings->SetMaxWidth(pThis->ItemMaxWidth);


            EndPaint(hwnd, &ps);
        }
        break;
    case WM_COMMAND:
        {
            SendMessage(pThis->hwndParent, WM_COMMAND, wParam, NULL);

            switch(LOWORD(wParam))
            {
                
            }
        }
        break;
    }

    return DefSubclassProc(hwnd, message, wParam, lParam);
}

void form_menubar::SetCurrentContent(content* FocusContent)
{
    Content = FocusContent;
    MenuItem_Dashboard->Content = FocusContent;
    MenuItem_Item->Content = FocusContent;
    MenuItem_PointOfSale->Content = FocusContent;
    MenuItem_Promotion->Content = FocusContent;
    MenuItem_Accounts->Content = FocusContent;
    MenuItem_Settings->Content = FocusContent;
}