#include <iostream>
#include <codecvt>
#include "ui/content/item/itemlist.h"

#pragma comment(lib, "comctl32.lib")

content_item_list::content_item_list(HWND hwndParent, int lpParam, int x, int y, int width, int height)
{
    hwnd = CreateWindow(WC_LISTVIEW, "", WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP | LVS_REPORT, x, y, width, height, hwndParent, (HMENU)lpParam, NULL, NULL);
    SetWindowSubclass(hwnd, ListViewProc, lpParam, (DWORD_PTR)this);

    hFont = CreateFont(17, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, 
        OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, 
        DEFAULT_PITCH | FF_MODERN, TEXT("Arial"));

    SetFont(hFont);
    SetListTextColor(RGB(0, 0, 0));
    SendMessage(hwnd, LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT);
}

LRESULT CALLBACK content_item_list::ListViewProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
    //Using the dwRefData we passed from and create this pointer
    content_item_list* pThis = (content_item_list*) dwRefData;

    switch (message)
    {
    case WM_PAINT:
        {
            /*
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

            SetTextColor(hdc, RGB(0, 0, 0));

            //Grab current font
            HFONT hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);

            SelectObject(hdc, hFont);
            EndPaint(hwnd, &ps);
            */
        }
        break;
    case WM_KEYUP:
        {
            switch(wParam)
            {
                case VK_DELETE:
                {
                    for(int itemId = -1; (itemId = SendMessage(hwnd, LVM_GETNEXTITEM, -1, LVNI_SELECTED)) != -1;)
                    {
                        char szItemName[1024];
                        LVITEM item;
                        item.cchTextMax = 1024;
                        item.mask = LVIF_TEXT;
                        item.iItem = itemId;
                        item.pszText = szItemName;
                        ListView_GetItem(hwnd, &item);

                        ListView_DeleteItem(hwnd, itemId);
                    }
                }
            }
        }
        break;
    }

    return DefSubclassProc(hwnd, message, wParam, lParam);
}

void content_item_list::SetFont(HFONT hFont)
{
    if(IsWindow(hwnd))
    {
        SendMessage(hwnd, WM_SETFONT, (WPARAM)hFont, TRUE);
    }
}

int content_item_list::SetListTextColor(COLORREF TextColor)
{
    return ListView_SetTextColor(hwnd, TextColor);
}

int content_item_list::CreateColumn(int nCol, char *szText, int nWidth)
{
    LVCOLUMN lvc;

    lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
    lvc.fmt = LVCFMT_LEFT;
    lvc.cx = nWidth;
    lvc.pszText = szText;
    lvc.iSubItem = nCol;
    return ListView_InsertColumn(hwnd, nCol, &lvc);
}

int content_item_list::Insert(int nCol, int nRow, char *szText)
{
    LVITEM item;

    item.mask = LVIF_TEXT | LVIF_STATE;
    item.iSubItem = nCol;
    item.iItem = nRow;
    item.pszText = szText;
    item.stateMask = 0;
    item.state = 0;

    int nCode;
    if(nCol == 0)
    {
        nCode = ListView_InsertItem(hwnd, &item);
    }
    else
    {
        nCode = ListView_SetItem(hwnd, &item);
    }

    return nCode;
}