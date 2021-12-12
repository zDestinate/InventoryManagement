#include "ui/objects.h"
#include "ui/content/content_item.h"

content_item::content_item(HWND hwndParent, int lpParam, int x, int y, int width, int height)
: content(hwndParent, lpParam, x, y, width, height)
{
    SetWindowSubclass(hwnd, ContentProc, lpParam, (DWORD_PTR)this);

    hFont = CreateFont(17, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, 
        OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, 
        DEFAULT_PITCH | FF_MODERN, TEXT("Arial"));

    //Pop up
    FormItem = new popup_item(hwndParent);
    FormItem->hwndContent = hwnd;
    CreateThread(NULL, 0, FormItem->CreateThread, (void*)FormItem, 0, &dwThreadID_PopUp_Item);

    
    RECT rectWindow;
    GetWindowRect(hwnd, &rectWindow);

    int nWidth = rectWindow.right - rectWindow.left;
    int nHeight = rectWindow.bottom - rectWindow.top;

    //Searchbar
    int nSearchBarWidth = nWidth / 2;
    nSearchBarHeight = 25;
    int nSearchBarX = (nWidth / 2) - (nSearchBarWidth / 2) + (30 / 2) - 10;
    nSearchBarY = 50;

    SearchBar = new content_item_search(hwnd, FormObjects::CONTENT_ITEM_SEARCH, nSearchBarX, nSearchBarY, nSearchBarWidth, nSearchBarHeight);
    SearchBar->PlaceHolder = "Search";

    //Listview
    int nItemListWidth = nWidth - 120;
    int nItemListX = 50;
    nItemListY = 120;
    ItemList = new content_item_list(hwnd, FormObjects::CONTENT_ITEM_LIST, nItemListX, nItemListY, nItemListWidth, nHeight - nSearchBarHeight - nSearchBarY - 175);
    ItemList->CreateColumn(0, "TESTTT", 150);
    ItemList->Insert(0, 0, "asdfasdf");
    ItemList->Insert(0, 1, "bbbbbb");
    ItemList->CreateColumn(1, "ASDASD", 150);
    ItemList->Insert(1, 0, "ads");
    ItemList->Insert(1, 1, "wwwwwwwww");

    //Buttons
    nButtonWidth = 120;
    nButtonheight = 32;
    nSpaceBetweenButtons = 15;

    btnEditItem = new form_button(hwnd, FormObjects::CONTENT_ITEM_BTN_EDIT, nWidth - 70 - (nButtonWidth * 1), nHeight - 100, nButtonWidth, nButtonheight);
    btnEditItem->SetFont(hFont);
    btnEditItem->ButtonText = "Edit Item";
    btnEditItem->ButtonColorRGB = RGB(43, 185, 255);
    btnEditItem->ButtonColorRGB_Hover = RGB(0, 154, 229);

    btnCreateItem = new form_button(hwnd, FormObjects::CONTENT_ITEM_BTN_CREATE, nWidth - 70 - (nButtonWidth * 2) - nSpaceBetweenButtons, nHeight - 100, nButtonWidth, nButtonheight);
    btnCreateItem->SetFont(hFont);
    btnCreateItem->ButtonText = "Create Item";
    btnCreateItem->ButtonColorRGB = RGB(43, 185, 255);
    btnCreateItem->ButtonColorRGB_Hover = RGB(0, 154, 229);
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

            int nItemListWidth = nWidth - 120;
            int nItemListX = 50;
            SetWindowPos(pThis->ItemList->hwnd, NULL, nItemListX, pThis->nItemListY, nItemListWidth,  nHeight - pThis->nSearchBarHeight - pThis->nSearchBarY - 175, SWP_NOZORDER);

            //Buttons
            SetWindowPos(pThis->btnEditItem->hwndbutton, NULL, nWidth - 70 - (pThis->nButtonWidth * 1), nHeight - 100, pThis->nButtonWidth, pThis->nButtonheight, SWP_NOZORDER);
            SetWindowPos(pThis->btnCreateItem->hwndbutton, NULL, nWidth - 70 - (pThis->nButtonWidth * 2) - pThis->nSpaceBetweenButtons, nHeight - 100, pThis->nButtonWidth, pThis->nButtonheight, SWP_NOZORDER);
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
                case FormObjects::CONTENT_ITEM_BTN_CREATE:
                    {
                        ShowWindow(pThis->FormItem->hwnd, SW_SHOW);
                        EnableWindow(pThis->hwndParent, FALSE);
                    }
                    break;
                case FormObjects::CONTENT_ITEM_BTN_EDIT:
                    {
                        ShowWindow(pThis->FormItem->hwnd, SW_SHOW);
                        EnableWindow(pThis->hwndParent, FALSE);
                    }
                    break;
            }
        }
        break;
    case WM_SHOWWINDOW:
        {
            if(wParam)
            {
                printf("[CONTENT][ITEM] Show\n");
            }
        }
        break;
    }

    return DefSubclassProc(hwnd, message, wParam, lParam);
}