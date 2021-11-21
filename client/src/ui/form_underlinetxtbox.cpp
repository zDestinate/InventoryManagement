#include <iostream>
#include <codecvt>
#include "ui/form_underlinetxtbox.h"

#pragma comment(lib, "comctl32.lib")

form_underlinetxtbox::form_underlinetxtbox(HWND hwndParent, int lpParam, int x, int y, int width, int height)
{
    hwndTxtbox = CreateWindow("EDIT", "", ES_CENTER | WS_CHILD | WS_VISIBLE | WS_TABSTOP, x, y, width, height, hwndParent, (HMENU)lpParam, NULL, NULL);
    SetWindowSubclass(hwndTxtbox, UnderLineTxtBoxProc, lpParam, (DWORD_PTR)this);
}

form_underlinetxtbox::form_underlinetxtbox(HWND hwndParent, int lpParam, int x, int y, int width, int height, bool IsPassword)
{
    if(IsPassword)
    {
        hwndTxtbox = CreateWindow("EDIT", "", ES_CENTER | WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_PASSWORD, x, y, width, height, hwndParent, (HMENU)lpParam, NULL, NULL);
    }
    else
    {
        hwndTxtbox = CreateWindow("EDIT", "", ES_CENTER | WS_CHILD | WS_VISIBLE | WS_TABSTOP, x, y, width, height, hwndParent, (HMENU)lpParam, NULL, NULL);
    }
    
    SetWindowSubclass(hwndTxtbox, UnderLineTxtBoxProc, lpParam, (DWORD_PTR)this);
}

LRESULT CALLBACK form_underlinetxtbox::UnderLineTxtBoxProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
    //Using the dwRefData we passed from and create this pointer
    form_underlinetxtbox* pThis = (form_underlinetxtbox*) dwRefData;

    switch (message)
    {
    case WM_PAINT:
        {
            //Get the current HWND Rect
            RECT rc;
            GetClientRect(hwnd, &rc);

            //Clear all the painting and update the hwnd
            InvalidateRect(hwnd, &rc, TRUE);
            UpdateWindow(hwnd);
            RedrawWindow(hwnd, 0, 0, RDW_ERASE | RDW_UPDATENOW);

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
            MoveToEx(hdc, rc.left, rc.bottom + 1, 0);

            //Ending location
            LineTo(hdc, rc.right - rc.left, rc.bottom + 1);

            //Delete the HPEN and finish painting
            DeleteObject(hPen);
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
    }

    return DefSubclassProc(hwnd, message, wParam, lParam);
}

void form_underlinetxtbox::SetFont(HFONT hFont)
{
    if(IsWindow(hwndTxtbox))
    {
        SendMessage(hwndTxtbox, WM_SETFONT, (WPARAM)hFont, TRUE);
    }
}

void form_underlinetxtbox::SetPlaceHolder(string strPlaceHolder)
{
    if(IsWindow(hwndTxtbox))
    {
        wstring wstrPlaceHolder = wstring_convert<codecvt_utf8<wchar_t>>().from_bytes(strPlaceHolder);
        SendMessage(hwndTxtbox, EM_SETCUEBANNER, FALSE, (LPARAM)wstrPlaceHolder.c_str());
    }
}