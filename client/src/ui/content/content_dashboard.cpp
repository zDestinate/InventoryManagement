#include "ui/content/content_dashboard.h"


content_dashboard::content_dashboard(HWND hwndParent, int lpParam, int x, int y, int width, int height)
: content(hwndParent, lpParam, x, y, width, height)
{
    SetWindowSubclass(hwnd, ContentProc, lpParam, (DWORD_PTR)this);

    TodaySale = L"N/A";
    YesterdaySale = L"N/A";
    ThisWeekSale = L"N/A";

    hFont = CreateFont(17, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, 
        OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, 
        DEFAULT_PITCH | FF_MODERN, TEXT("Arial"));
}

LRESULT CALLBACK content_dashboard::ContentProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
    //Using the dwRefData we passed from and create this pointer
    content_dashboard* pThis = (content_dashboard*) dwRefData;

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


            //Today sale
            RECT rcTodaySale;
            GetClientRect(hwnd, &rcTodaySale);
            rcTodaySale.left += 40;
            rcTodaySale.top += 50;
            rcTodaySale.bottom = rcTodaySale.top + 100;
            rcTodaySale.right = (rcTodaySale.right / 3) - 5;

            RECT rcTodaySaleTitle;
            rcTodaySaleTitle = rcTodaySale;
            rcTodaySaleTitle.top += 28;

            SetTextColor(hdc, pThis->TextColorRGB);
            SelectObject(hdc, pThis->hFont);
            DrawTextW(hdc, L"TODAY SALE", ((wstring)(L"TODAY SALE")).length(), &rcTodaySaleTitle, DT_CENTER | DT_VCENTER);

            rcTodaySaleTitle.top += 24;
            DrawTextW(hdc, (LPCWSTR)pThis->TodaySale.c_str(), pThis->TodaySale.length(), &rcTodaySaleTitle, DT_CENTER | DT_VCENTER);
            pThis->DrawBorder(hdc, rcTodaySale, pThis->TextColorRGB, 1);


            //Yesterday sale
            RECT rcYesterdaySale;
            GetClientRect(hwnd, &rcYesterdaySale);
            rcYesterdaySale.left = rcTodaySale.right + 20;
            rcYesterdaySale.top += 50;
            rcYesterdaySale.bottom = rcYesterdaySale.top + 100;
            rcYesterdaySale.right = (rcYesterdaySale.right / 3) * 2 - 30;

            RECT rcYesterdaySaleTitle;
            rcYesterdaySaleTitle = rcYesterdaySale;
            rcYesterdaySaleTitle.top += 28;

            DrawTextW(hdc, L"YESTERDAY SALE", ((wstring)(L"YESTERDAY SALE")).length(), &rcYesterdaySaleTitle, DT_CENTER | DT_VCENTER);

            rcYesterdaySaleTitle.top += 24;
            DrawTextW(hdc, (LPCWSTR)pThis->YesterdaySale.c_str(), pThis->YesterdaySale.length(), &rcYesterdaySaleTitle, DT_CENTER | DT_VCENTER);
            pThis->DrawBorder(hdc, rcYesterdaySale, pThis->TextColorRGB, 1);


            //This week sale
            RECT rcThisWeekSale;
            GetClientRect(hwnd, &rcThisWeekSale);
            rcThisWeekSale.left = rcYesterdaySale.right + 20;
            rcThisWeekSale.top += 50;
            rcThisWeekSale.bottom = rcThisWeekSale.top + 100;
            rcThisWeekSale.right -= 55;

            RECT rcThisWeekSaleTitle;
            rcThisWeekSaleTitle = rcThisWeekSale;
            rcThisWeekSaleTitle.top += 28;

            DrawTextW(hdc, L"THIS WEEK SALE", ((wstring)(L"THIS WEEK SALE")).length(), &rcThisWeekSaleTitle, DT_CENTER | DT_VCENTER);

            rcThisWeekSaleTitle.top += 24;
            DrawTextW(hdc, (LPCWSTR)pThis->ThisWeekSale.c_str(), pThis->ThisWeekSale.length(), &rcThisWeekSaleTitle, DT_CENTER | DT_VCENTER);
            pThis->DrawBorder(hdc, rcThisWeekSale, pThis->TextColorRGB, 1);


            //Restore the font and end painting
            SelectObject(hdc, hFont);
            EndPaint(hwnd, &ps);
        }
        break;
    case WM_SHOWWINDOW:
        {
            if(wParam)
            {
                printf("[CONTENT][DASHBOARD] Show\n");
            }
        }
        break;
    }

    return DefSubclassProc(hwnd, message, wParam, lParam);
}