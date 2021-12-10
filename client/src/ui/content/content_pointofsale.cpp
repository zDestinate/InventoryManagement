#include "ui/objects.h"
#include "ui/content/content_pointofsale.h"

content_pointofsale::content_pointofsale(HWND hwndParent, int lpParam, int x, int y, int width, int height)
: content(hwndParent, lpParam, x, y, width, height)
{
    SetWindowSubclass(hwnd, ContentProc, lpParam, (DWORD_PTR)this);

    hFont = CreateFont(17, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, 
        OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, 
        DEFAULT_PITCH | FF_MODERN, TEXT("Arial"));

    //RECT of hwnd for design
    RECT rectWindow;
    GetWindowRect(hwnd, &rectWindow);

    int nWidth = rectWindow.right - rectWindow.left;
    int nHeight = rectWindow.bottom - rectWindow.top;

    //SearchBar
    SearchBar = new content_item_search(hwnd, FormObjects::CONTENT_POINTOFSALE_SEARCH, 100, 50, 300, 25);
    SearchBar->bSolidIcon = true;
    SearchBar->wstrIcon = L"\uf463";
    SearchBar->PlaceHolder = "UPC";

    int nItemListWidth = nWidth - 120;
    int nItemListX = 50;
    nItemListY = 120;
    ItemList = new content_item_list(hwnd, FormObjects::CONTENT_POINTOFSALE_LIST, nItemListX, nItemListY, nItemListWidth, nHeight - 25 - 50 - 175, true);
    ItemList->nMinXColumn = 20;
    ItemList->lvcMask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM | LVCF_MINWIDTH;
    ItemList->lvcFmt = LVCFMT_LEFT | LVCFMT_FIXED_WIDTH;
    ItemList->CreateColumn(0, "Description", 150);
    ItemList->Insert(0, 0, "asdfasdf");
    ItemList->Insert(0, 1, "bbbbbb");
    ItemList->lvcFmt = LVCFMT_RIGHT | LVCFMT_FIXED_WIDTH;
    ItemList->CreateColumn(1, "Quantity", 150);
    ItemList->Insert(1, 0, "ads");
    ItemList->Insert(1, 1, "wwwwwwwww");
    ItemList->CreateColumn(2, "Price", 150);
    ItemList->Insert(2, 0, "1823");
    ItemList->Insert(2, 1, "123");

    ItemList->SetColumnWidth(0, (nItemListWidth / 2) - 20);
    ItemList->SetColumnWidth(1, nItemListWidth / 4);
    ItemList->SetColumnWidth(2, nItemListWidth / 4);

}

LRESULT CALLBACK content_pointofsale::ContentProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
    //Using the dwRefData we passed from and create this pointer
    content_pointofsale* pThis = (content_pointofsale*) dwRefData;

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

            int nItemListWidth = nWidth - 120;
            int nItemListX = 50;
            SetWindowPos(pThis->ItemList->hwnd, NULL, nItemListX, pThis->nItemListY, nItemListWidth,  nHeight - 25 - 50 - 175, SWP_NOZORDER);
        
            //Rescale column
            pThis->ItemList->SetColumnWidth(0, (nItemListWidth / 2) - 20);
            pThis->ItemList->SetColumnWidth(1, nItemListWidth / 4);
            pThis->ItemList->SetColumnWidth(2, nItemListWidth / 4);
        }
        break;
    case WM_SHOWWINDOW:
        {
            if(wParam)
            {
                printf("[CONTENT][POINTOFSALE] Show\n");
            }
        }
        break;
    }

    return DefSubclassProc(hwnd, message, wParam, lParam);
}