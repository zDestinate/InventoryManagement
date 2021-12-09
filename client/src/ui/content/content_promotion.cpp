#include "ui/content/content_promotion.h"

content_promotion::content_promotion(HWND hwndParent, int lpParam, int x, int y, int width, int height)
: content(hwndParent, lpParam, x, y, width, height)
{
    SetWindowSubclass(hwnd, ContentProc, lpParam, (DWORD_PTR)this);

    TEST = L"PROMOTION CONTENT";

    hFont = CreateFont(30, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, 
        OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, 
        DEFAULT_PITCH | FF_MODERN, TEXT("Arial"));
}

LRESULT CALLBACK content_promotion::ContentProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
    //Using the dwRefData we passed from and create this pointer
    content_promotion* pThis = (content_promotion*) dwRefData;

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


            SetTextColor(hdc, pThis->TextColorRGB);
            SelectObject(hdc, pThis->hFont);
            DrawTextW(hdc, (LPCWSTR)pThis->TEST.c_str(), pThis->TEST.length(), &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

            //Restore the font and end painting
            SelectObject(hdc, hFont);
            EndPaint(hwnd, &ps);
        }
        break;
    case WM_SHOWWINDOW:
        {
            if(wParam)
            {
                printf("[CONTENT][PROMOTION] Show\n");
            }
        }
        break;
    }

    return DefSubclassProc(hwnd, message, wParam, lParam);
}