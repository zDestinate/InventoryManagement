#include <codecvt>
#include "ui/objects.h"
#include "ui/form_menuitem.h"

#pragma comment(lib, "comctl32.lib")

form_menuitem::form_menuitem(HWND hwndParent, int lpParam, int x, int y, int width, int height, UINT timerID)
{
    hwndbutton = CreateWindow("BUTTON", "", ES_CENTER | WS_CHILD | WS_VISIBLE | WS_TABSTOP, x, y, width, height, hwndParent, (HMENU)lpParam, NULL, NULL);
    SetWindowSubclass(hwndbutton, ButtonProc, lpParam, (DWORD_PTR)this);

    hFont = CreateFont(17, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, 
        OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, 
        DEFAULT_PITCH | FF_MODERN, TEXT("Arial"));
    
    minx = width;
    miny = height;
    maxx = width;
    locx = x;
    locy = y;
    currentx = width;

    IDT_HOVER_TIMER_CHECK = timerID;

    SetTimer(hwndbutton, IDT_HOVER_TIMER_CHECK, 30, (TIMERPROC)NULL);
}

LRESULT form_menuitem::ButtonProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
    //Using the dwRefData we passed from and create this pointer
    form_menuitem* pThis = (form_menuitem*) dwRefData;

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
            
            //Icon
            HFONT hFontIcon = CreateFont(20, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, 
                OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, 
                DEFAULT_PITCH | FF_MODERN, TEXT("Font Awesome 6 Pro Regular"));
            
            SelectObject(hdc, hFontIcon);
            RECT rectIcon;
            GetClientRect(hwnd, &rectIcon);
            rectIcon.right = pThis->minx;
            DrawTextW(hdc, (LPCWSTR)pThis->IconText.c_str(), pThis->IconText.length(), &rectIcon, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
            SelectObject(hdc, hFontIcon);

            //Text
            SelectObject(hdc, pThis->hFont);
            if(!pThis->bItemExtended)
            {
                rc.left = pThis->minx;
                rc.right = pThis->maxx;
            }
            DrawTextW(hdc, (LPCWSTR)pThis->ButtonText.c_str(), pThis->ButtonText.length(), &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
            

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
    case WM_TIMER:
        {
            if(!pThis->bItemExtended)
            {
                if(pThis->bHover)
                {
                    if(pThis->currentx < pThis->maxx)
                    {
                        pThis->currentx += 15;
                    }
                    else
                    {
                        pThis->currentx = pThis->maxx;
                    }
                }
                else
                {
                    pThis->currentx = pThis->minx;
                }

                SetWindowPos(hwnd, NULL, pThis->locx, pThis->locy, pThis->currentx, pThis->miny, NULL);
            }
            else
            {
                SetWindowPos(hwnd, NULL, pThis->locx, pThis->locy, pThis->maxx, pThis->miny, NULL);
            }
        }
        break;
    case WM_DESTROY:
        KillTimer(hwnd, pThis->IDT_HOVER_TIMER_CHECK);
        break;
    }

    return DefSubclassProc(hwnd, message, wParam, lParam);
}

void form_menuitem::SetFont(HFONT hFont)
{
    this->hFont = hFont;
}

void form_menuitem::SetMaxWidth(int nMaxWidth)
{
    if(nMaxWidth >= minx)
    {
        maxx = nMaxWidth;
    }
}