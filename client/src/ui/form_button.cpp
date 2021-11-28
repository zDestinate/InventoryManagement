#include <codecvt>
#include "ui/form_button.h"
#include "ui/objects.h"

#pragma comment(lib, "comctl32.lib")

form_button::form_button(HWND hwndParent, int lpParam, int x, int y, int width, int height)
{
    hwndbutton = CreateWindow("BUTTON", "", ES_CENTER | WS_CHILD | WS_VISIBLE | WS_TABSTOP, x, y, width, height, hwndParent, (HMENU)lpParam, NULL, NULL);
    SetWindowSubclass(hwndbutton, ButtonProc, lpParam, (DWORD_PTR)this);
}

LRESULT form_button::ButtonProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
    //Using the dwRefData we passed from and create this pointer
    form_button* pThis = (form_button*) dwRefData;

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
                SetTextColor(hdc, pThis->TextColorRGB_Hover);
            }
            else
            {
                SetTextColor(hdc, pThis->TextColorRGB);
            }
            
            SelectObject(hdc, pThis->hFont);
            DrawText(hdc, (LPCSTR)pThis->ButtonText.c_str(), pThis->ButtonText.length(), &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

            //Restore the font and end painting
            SelectObject(hdc, hFont);
            EndPaint(hwnd, &ps);
        }
        break;
    case WM_MOUSEMOVE:
        {
            pThis->bHover = true;
            
        }
        break;
    case WM_MOUSELEAVE:
        {
            pThis->bHover = false;
        }
        break;
    }

    return DefSubclassProc(hwnd, message, wParam, lParam);
}

void form_button::SetFont(HFONT hFont)
{
    this->hFont = hFont;
}