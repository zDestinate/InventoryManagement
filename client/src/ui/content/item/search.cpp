#include <iostream>
#include <codecvt>
#include "ui/content/item/search.h"

#pragma comment(lib, "comctl32.lib")

content_item_search::content_item_search(HWND hwndParent, int lpParam, int x, int y, int width, int height)
{
    hwnd = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_TABSTOP, x, y, width, height, hwndParent, (HMENU)lpParam, NULL, NULL);
    SetWindowSubclass(hwnd, UnderLineTxtBoxProc, lpParam, (DWORD_PTR)this);
    
    this->hwndParent= hwndParent;

    hFont = CreateFont(17, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, 
        OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, 
        DEFAULT_PITCH | FF_MODERN, TEXT("Arial"));
    SetFont(hFont);

    wstrIcon = L"\uf002";
    nIconX = 30;
    bSolidIcon = false;
}

LRESULT CALLBACK content_item_search::UnderLineTxtBoxProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
    //Using the dwRefData we passed from and create this pointer
    content_item_search* pThis = (content_item_search*) dwRefData;

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
            HPEN hPen;

            //Start painting the line base on the focus status
            hdc = BeginPaint(hwnd, &ps);
            if(pThis->bFocus)
            {
                //Blue
                hPen = CreatePen(PS_SOLID, 3, RGB(36, 164, 255));
            }
            else
            {
                //Black
                hPen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
            }

            SelectObject(hdc, hPen);

            //Starting location
            MoveToEx(hdc, rc.left - pThis->nIconX, rc.bottom + 1, 0);

            //Ending location
            LineTo(hdc, rc.right - rc.left, rc.bottom + 1);

            //Delete the HPEN and finish painting
            DeleteObject(hPen);


            //Grab current font
            HFONT hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);

            if(pThis->bFocus)
            {
                SetTextColor(hdc, RGB(36, 164, 255));
            }
            else
            {
                SetTextColor(hdc, RGB(0, 0, 0));
            }

            //Icon
            HFONT hFontIcon;

            if(pThis->bSolidIcon)
            {
                hFontIcon = CreateFont(22, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, 
                OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, 
                DEFAULT_PITCH | FF_MODERN, TEXT("Font Awesome 6 Pro Solid"));
            }
            else
            {
                hFontIcon = CreateFont(22, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, 
                OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, 
                DEFAULT_PITCH | FF_MODERN, TEXT("Font Awesome 6 Pro Regular"));
            }
            
            SelectObject(hdc, hFontIcon);
            RECT rectIcon;
            GetClientRect(hwnd, &rectIcon);
            rectIcon.left -= pThis->nIconX;
            rectIcon.top -= 7;
            DrawTextW(hdc, (LPCWSTR)pThis->wstrIcon.c_str(), pThis->wstrIcon.length(), &rectIcon, DT_VCENTER | DT_SINGLELINE);

            //Reset color
            SetTextColor(hdc, RGB(0, 0, 0));

            //Font for placeholder
            SelectObject(hdc, hFont);
            EndPaint(hwnd, &ps);

            pThis->SetPlaceHolder(pThis->PlaceHolder);
        }
        break;
    case WM_SETFOCUS:
        {
            pThis->bFocus = true;
        }
        break;
    case WM_KILLFOCUS:
        {
            pThis->bFocus = false;
        }
        break;
    case WM_COMMAND:
        {
            switch(HIWORD(wParam))
            {
                case EN_CHANGE:
                {
                    SendMessage(pThis->hwndParent, WM_COMMAND, wParam, NULL);
                }
                break;
            }
        }
        break;
    }

    return DefSubclassProc(hwnd, message, wParam, lParam);
}

void content_item_search::SetFont(HFONT hFont)
{
    if(IsWindow(hwnd))
    {
        SendMessage(hwnd, WM_SETFONT, (WPARAM)hFont, TRUE);
    }
}

void content_item_search::SetPlaceHolder(string strPlaceHolder)
{
    if(IsWindow(hwnd))
    {
        wstring wstrPlaceHolder = wstring_convert<codecvt_utf8<wchar_t>>().from_bytes(strPlaceHolder);
        SendMessage(hwnd, EM_SETCUEBANNER, FALSE, (LPARAM)wstrPlaceHolder.c_str());
    }
}