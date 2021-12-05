#include "ui/objects.h"
#include "ui/content/content_item.h"

content_item::content_item(HWND hwndParent, int lpParam, int x, int y, int width, int height)
: content(hwndParent, lpParam, x, y, width, height)
{
    SetWindowSubclass(hwnd, ContentProc, lpParam, (DWORD_PTR)this);

    hFont = CreateFont(30, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, 
        OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, 
        DEFAULT_PITCH | FF_MODERN, TEXT("Arial"));


    RECT rectWindow;
    GetWindowRect(hwnd, &rectWindow);

    int nWidth = rectWindow.right - rectWindow.left;
    int nHeight = rectWindow.bottom - rectWindow.top;

    int nSearchBarWidth = nWidth / 2;
    nSearchBarHeight = 25;
    int nSearchBarX = (nWidth / 2) - (nSearchBarWidth / 2) + (30 / 2) - 10;
    nSearchBarY = 50;

    SearchBar = new content_item_search(hwnd, FormObjects::CONTENT_ITEM_SEARCH, nSearchBarX, nSearchBarY, nSearchBarWidth, nSearchBarHeight);
    SearchBar->PlaceHolder = "Search";

    
    int nItemListWidth = nWidth / 1.5;
    int nItemListX = (nWidth / 2) - (nItemListWidth / 2) - 10;
    nItemListY = 120;
    ItemList = new content_item_list(hwnd, FormObjects::CONTENT_ITEM_LIST, nItemListX, nItemListY, nItemListWidth, nHeight / 1.5);
    ItemList->CreateColumn(0, "TESTTT", 150);
    ItemList->Insert(0, 0, "asdfasdf");
    ItemList->Insert(0, 1, "bbbbbb");
    ItemList->CreateColumn(1, "ASDASD", 150);
    ItemList->Insert(1, 0, "ads");
    ItemList->Insert(1, 1, "wwwwwwwww");
}

LRESULT CALLBACK content_item::ContentProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
    //Using the dwRefData we passed from and create this pointer
    content_item* pThis = (content_item*) dwRefData;

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
    case WM_SIZE:
        {
            RECT rc;
            GetWindowRect(hwnd, &rc);

            int nWidth = rc.right - rc.left;
            int nHeight = rc.bottom - rc.top;

            int nSearchBarWidth = nWidth / 2;
            int nSearchBarX = (nWidth / 2) - (nSearchBarWidth / 2) + (30 / 2) - 10;
            SetWindowPos(pThis->SearchBar->hwnd, NULL, nSearchBarX, pThis->nSearchBarY, nSearchBarWidth, pThis->nSearchBarHeight, SWP_NOZORDER);

            int nItemListWidth = nWidth / 1.5;
            int nItemListX = (nWidth / 2) - (nItemListWidth / 2) - 10;
            SetWindowPos(pThis->ItemList->hwnd, NULL, nItemListX, pThis->nItemListY, nItemListWidth, nHeight / 1.5, SWP_NOZORDER);
        }
        break;
    case WM_COMMAND:
        {
            switch(LOWORD(wParam))
            {
                case FormObjects::CONTENT_ITEM_SEARCH:
                    {
                        int nSearchBarLength = GetWindowTextLength(pThis->SearchBar->hwnd) + 1;
                        TCHAR *tszSearchBarText = new TCHAR[nSearchBarLength];
                        nSearchBarLength = GetWindowText(pThis->SearchBar->hwnd, tszSearchBarText, nSearchBarLength);
                        string strSearchbarText;
                        strSearchbarText.assign(&tszSearchBarText[0], &tszSearchBarText[nSearchBarLength]);
                    }
                    break;
            }
        }
        break;
    }

    return DefSubclassProc(hwnd, message, wParam, lParam);
}