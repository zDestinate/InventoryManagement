#include <codecvt>
#include "ui/objects.h"
#include "ui/form_menuuser.h"

#pragma comment(lib, "comctl32.lib")

form_menuuser::form_menuuser(HWND hwndParent, int lpParam, int x, int y, int width, int height)
{
    hwnd = CreateWindow("BUTTON", "", ES_CENTER | WS_CHILD | WS_VISIBLE | WS_TABSTOP, x, y, width, height, hwndParent, (HMENU)lpParam, NULL, NULL);
    SetWindowSubclass(hwnd, ButtonProc, lpParam, (DWORD_PTR)this);

    hFontIcon = CreateFont(50, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, 
        OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, 
        DEFAULT_PITCH | FF_MODERN, TEXT("Font Awesome 6 Pro Solid"));
}

LRESULT form_menuuser::ButtonProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
    //Using the dwRefData we passed from and create this pointer
    form_menuuser* pThis = (form_menuuser*) dwRefData;

    switch (message)
    {
    case WM_PAINT:
        {
            //Get the current HWND Rect
            RECT rc;
            GetClientRect(hwnd, &rc);

            RECT rectIcon;
            GetClientRect(hwnd, &rectIcon);
            rectIcon.left += 20;

            RECT rectName;
            GetClientRect(hwnd, &rectName);
            rectName.left = rectIcon.left + 70;
            rectName.top = 20;

            RECT rectID;
            GetClientRect(hwnd, &rectID);
            rectID.left = rectName.left;
            rectID.top = rectName.top + 25;

            PAINTSTRUCT ps;
            HDC hdc;

            //Start painting the line base on the focus status
            hdc = BeginPaint(hwnd, &ps);
            SetBkMode(hdc, TRANSPARENT);
            
            HBRUSH hBackgroundColor;
            if(pThis->bHover)
            {
                hBackgroundColor = CreateSolidBrush(pThis->ButtonColorRGB_Hover);  
            }
            else
            {
                hBackgroundColor = CreateSolidBrush(pThis->ButtonColorRGB);  
            }
                
            SelectObject(hdc, hBackgroundColor);
            FillRect(hdc, &rc, hBackgroundColor);
            DeleteObject(hBackgroundColor);

            //Grab current font
            HFONT hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);

            //Set specific font and draw the text
            if(pThis->bHover)
            {
                SetTextColor(hdc, pThis->NameTextColorRGB_Hover);
            }
            else
            {
                SetTextColor(hdc, pThis->NameTextColorRGB);
            }
            
            SelectObject(hdc, pThis->hFontIcon);
            DrawTextW(hdc, (LPCWSTR)pThis->IconText.c_str(), pThis->IconText.length(), &rectIcon,  DT_VCENTER | DT_SINGLELINE);

            SelectObject(hdc, pThis->hFontName);
            DrawTextW(hdc, (LPCWSTR)pThis->NameText.c_str(), pThis->NameText.length(), &rectName,  DT_LEFT);

            SelectObject(hdc, pThis->hFontID);
            DrawTextW(hdc, (LPCWSTR)pThis->IDText.c_str(), pThis->IDText.length(), &rectID,  DT_LEFT);

            //Restore the font and end painting
            SelectObject(hdc, hFont);
            EndPaint(hwnd, &ps);
        }
        break;
    case WM_MOUSEMOVE:
        {
            pThis->bHover = true;
            //RedrawWindow(hwnd, 0, 0, RDW_ERASE | RDW_UPDATENOW);
        }
        break;
    case WM_MOUSELEAVE:
        {
            pThis->bHover = false;
            //RedrawWindow(hwnd, 0, 0, RDW_ERASE | RDW_UPDATENOW);
        }
        break;
    }

    return DefSubclassProc(hwnd, message, wParam, lParam);
}