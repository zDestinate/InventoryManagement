#include <iostream>
#include <codecvt>
#include "ui/content/content.h"

#pragma comment(lib, "comctl32.lib")

content::content(HWND hwndParent, int lpParam, int x, int y, int width, int height)
{
    hwnd = CreateWindow("STATIC", "", WS_CHILD | WS_VISIBLE , x, y, width, height, hwndParent, (HMENU)lpParam, NULL, NULL);
    this->hwndParent = hwndParent;
    //SetWindowSubclass(hwnd, ContentProc, lpParam, (DWORD_PTR)this);
}

LRESULT content::ContentProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
    //Using the dwRefData we passed from and create this pointer
    content* pThis = (content*) dwRefData;

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

            PAINTSTRUCT ps;
            HDC hdc;

            //Start painting the line base on the focus status
            hdc = BeginPaint(hwnd, &ps);

            HFONT hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);


            //Restore the font and end painting
            SelectObject(hdc, hFont);
            EndPaint(hwnd, &ps);
        }
        break;
    }

    return DefSubclassProc(hwnd, message, wParam, lParam);
}

void content::DrawBorder(HDC hdc, RECT rc, COLORREF BorderColorRGB, int BorderSize)
{
    HBRUSH hBorderColor;
    hBorderColor = CreateSolidBrush(BorderColorRGB);

    RECT rcBorder = rc;

    //Top
    rcBorder.bottom = rcBorder.top + BorderSize;
    FillRect(hdc, &rcBorder, hBorderColor);

    //Bottom
    rcBorder = rc;
    rcBorder.top = rcBorder.bottom - BorderSize;
    FillRect(hdc, &rcBorder, hBorderColor);

    //Left
    rcBorder = rc;
    rcBorder.right = rcBorder.left + BorderSize;
    FillRect(hdc, &rcBorder, hBorderColor);

    //Right
    rcBorder = rc;
    rcBorder.left = rcBorder.right - BorderSize;
    FillRect(hdc, &rcBorder, hBorderColor);
}