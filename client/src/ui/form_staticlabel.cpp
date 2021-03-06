#include <iostream>
#include <codecvt>
#include "ui/form_staticlabel.h"

#pragma comment(lib, "comctl32.lib")

form_staticlabel::form_staticlabel(HWND hwndParent, int lpParam, int x, int y, int width, int height)
{
    hwndstatic = CreateWindow("STATIC", "", ES_CENTER | WS_CHILD | WS_VISIBLE, x, y, width, height, hwndParent, (HMENU)lpParam, NULL, NULL);
    SetWindowSubclass(hwndstatic, StaticProc, lpParam, (DWORD_PTR)this);

    hFont = CreateFont(17, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, 
        OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, 
        DEFAULT_PITCH | FF_MODERN, TEXT("Arial"));
}

LRESULT form_staticlabel::StaticProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
    //Using the dwRefData we passed from and create this pointer
    form_staticlabel* pThis = (form_staticlabel*) dwRefData;

    switch (message)
    {
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
            SetBkMode(hdc, TRANSPARENT);

            //Paint background
            HBRUSH hBackgroundColor;
            hBackgroundColor = CreateSolidBrush(pThis->BackgroundColorRGB); 
            SelectObject(hdc, hBackgroundColor);
            FillRect(hdc, &rc, hBackgroundColor);
            DeleteObject(hBackgroundColor);

            //Paint Border
            if(pThis->bUseBorder)
            {
                HBRUSH hBorderColor;
                hBorderColor = CreateSolidBrush(pThis->BorderColorRGB);

                RECT rcBorder;

                //Top
                GetClientRect(hwnd, &rcBorder);
                rcBorder.bottom = rcBorder.top + pThis->BorderSize;
                FillRect(hdc, &rcBorder, hBorderColor);

                //Bottom
                GetClientRect(hwnd, &rcBorder);
                rcBorder.top = rcBorder.bottom - pThis->BorderSize;
                FillRect(hdc, &rcBorder, hBorderColor);

                //Left
                GetClientRect(hwnd, &rcBorder);
                rcBorder.right = rcBorder.left + pThis->BorderSize;
                FillRect(hdc, &rcBorder, hBorderColor);

                //Right
                GetClientRect(hwnd, &rcBorder);
                rcBorder.left = rcBorder.right - pThis->BorderSize;
                FillRect(hdc, &rcBorder, hBorderColor);
            }

            //Grab current font
            HFONT hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);

            //Set specific font and draw the text
            SetTextColor(hdc, pThis->TextColorRGB);
            SelectObject(hdc, pThis->hFont);
            DrawTextW(hdc, (LPCWSTR)pThis->StaticText.c_str(), pThis->StaticText.length(), &rc, DT_CENTER | DT_VCENTER);

            //Restore the font and end painting
            SelectObject(hdc, hFont);
            EndPaint(hwnd, &ps);
        }
        break;
    }

    return DefSubclassProc(hwnd, message, wParam, lParam);
}

void form_staticlabel::SetFont(HFONT hFont)
{
    this->hFont = hFont;
}

void form_staticlabel::Show(bool bShow)
{
    if(bShow)
    {
        ShowWindow(hwndstatic, SW_SHOW);
    }
    else
    {
        ShowWindow(hwndstatic, SW_HIDE);
    }
}