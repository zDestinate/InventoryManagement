#include <iostream>
#include <codecvt>
#include "ui/objects.h"
#include "ui/form_menutop.h"

#pragma comment(lib, "comctl32.lib")

form_menutop::form_menutop(HWND hwndParent, int lpParam, int x, int y, int width, int height)
{
    hwndmenutop = CreateWindow("STATIC", "", ES_CENTER | WS_CHILD | WS_VISIBLE, x, y, width, height, hwndParent, (HMENU)lpParam, NULL, NULL);
    SetWindowSubclass(hwndmenutop, MenuTopProc, lpParam, (DWORD_PTR)this);

    hFontTitle = CreateFont(30, 0, 0, 0, FW_THIN, FALSE, FALSE, FALSE, DEFAULT_CHARSET, 
        OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, 
        DEFAULT_PITCH | FF_MODERN , TEXT("Arial"));

    hFontName = CreateFont(22, 0, 0, 0, FW_THIN, FALSE, FALSE, FALSE, DEFAULT_CHARSET, 
        OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, 
        DEFAULT_PITCH | FF_MODERN , TEXT("Arial"));

    hFontID = CreateFont(16, 0, 0, 0, FW_THIN, FALSE, FALSE, FALSE, DEFAULT_CHARSET, 
        OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, 
        DEFAULT_PITCH | FF_MODERN , TEXT("Arial"));

    BackgroundColorRGB = RGB(255, 255, 255);
    BottomBorderColorRGB = RGB(217, 217, 217);
    TitleTextColorRGB = RGB(0, 0, 0);

    nTitleIndent = 60;
    nTitleWidth = 400;


    //Menu user
    MenuTop_UserWidth = 220;

    MenuUser = new form_menuuser(hwndmenutop, FormObjects::MENU_TOP_USER, width - MenuTop_UserWidth, 0, MenuTop_UserWidth, height - nBottomBorderHeight);
    MenuUser->ButtonColorRGB = BackgroundColorRGB;
    MenuUser->ButtonColorRGB_Hover = RGB(0, 154, 229);
    MenuUser->IconText = L"\uf2bd";
    MenuUser->hFontName = hFontName;
    MenuUser->hFontID = hFontID;
    MenuUser->IDTextColorRGB = RGB(146, 146, 146);


    //Move Menu user base on the size
    RECT rc;
    GetClientRect(hwndmenutop, &rc);

    int nMenuTopWidth = rc.right - rc.left;
    int nMenuTopHeight = rc.bottom - rc.top;

    if(MenuUser->hwnd != nullptr)
    {
        if(nMenuTopWidth >= 950)
        {
            SetWindowPos(MenuUser->hwnd, NULL, rc.right - MenuTop_UserWidth, 0, NULL, NULL, SWP_NOZORDER | SWP_NOSIZE);
        }
        else
        {
            SetWindowPos(MenuUser->hwnd, NULL, rc.right - MenuTop_UserWidth + 116, 0, NULL, NULL, SWP_NOZORDER | SWP_NOSIZE);
        }
    }
}

LRESULT form_menutop::MenuTopProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
    //Using the dwRefData we passed from and create this pointer
    form_menutop* pThis = (form_menutop*) dwRefData;

    switch (message)
    {
    case WM_ERASEBKGND:
        {
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
            SetBkMode(hdc, TRANSPARENT);

            //Paint background
            HBRUSH hBackgroundColor;
            hBackgroundColor = CreateSolidBrush(pThis->BackgroundColorRGB);
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

            //Grab current font
            HFONT hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);

            //Set title font and text
            SetTextColor(hdc, pThis->TitleTextColorRGB);
            SelectObject(hdc, pThis->hFontTitle);

            RECT rcTitle;
            GetClientRect(hwnd, &rcTitle);
            rcTitle.left = pThis->nTitleIndent;
            rcTitle.right = pThis->nTitleIndent + pThis->nTitleWidth;

            DrawTextW(hdc, (LPCWSTR)pThis->TitleText.c_str(), pThis->TitleText.length(), &rcTitle, DT_VCENTER | DT_SINGLELINE);


            //Paint bottom border
            HBRUSH hBottomBorder;
            hBottomBorder = CreateSolidBrush(pThis->BottomBorderColorRGB);
            SelectObject(hdc, hBottomBorder);

            RECT rcBottomBorder;
            GetClientRect(hwnd, &rcBottomBorder);
            rcBottomBorder.top = rcBottomBorder.bottom - pThis->nBottomBorderHeight;

            FillRect(hdc, &rcBottomBorder, hBottomBorder);
            DeleteObject(hBottomBorder);

            SelectObject(hdc, hFont);
            EndPaint(hwnd, &ps);
        }
        break;
    case WM_SIZE:
        {
            RECT rc;
            GetClientRect(hwnd, &rc);

            int nMenuTopWidth = rc.right - rc.left;
            int nMenuTopHeight = rc.bottom - rc.top;

            if(pThis->MenuUser->hwnd != nullptr)
            {
                if(nMenuTopWidth >= 950)
                {
                    SetWindowPos(pThis->MenuUser->hwnd, NULL, rc.right - pThis->MenuTop_UserWidth, 0, NULL, NULL, SWP_NOZORDER | SWP_NOSIZE);
                }
                else
                {
                    SetWindowPos(pThis->MenuUser->hwnd, NULL, rc.right - pThis->MenuTop_UserWidth + 116, 0, NULL, NULL, SWP_NOZORDER | SWP_NOSIZE);
                }
            }
        }
        break;
    }

    return DefSubclassProc(hwnd, message, wParam, lParam);
}

void form_menutop::SetNameText(wstring Name)
{
    MenuUser->NameText = Name;
}

void form_menutop::SetIDText(wstring ID)
{
    MenuUser->IDText = ID;
}