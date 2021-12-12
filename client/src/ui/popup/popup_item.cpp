#include <iostream>
#include "ui/objects.h"
#include "ui/popup/popup_item.h"

using namespace std;

bool popup_item::CenterWindow(HWND hwndWindow)
{
    RECT rectWindow;

    GetWindowRect(hwndWindow, &rectWindow);

    int nWidth = rectWindow.right - rectWindow.left;
    int nHeight = rectWindow.bottom - rectWindow.top;

    int nScreenWidth = GetSystemMetrics(SM_CXSCREEN);
    int nScreenHeight = GetSystemMetrics(SM_CYSCREEN);

    int nX = (nScreenWidth / 2) - (nWidth / 2);
    int nY = (nScreenHeight / 2) - (nHeight / 2);

    MoveWindow(hwndWindow, nX, nY, nWidth, nHeight, FALSE);
    return true;
}

popup_item::popup_item(HWND hwndMain)
{
    this->hwndMain = hwndMain;

    hFont = CreateFont(18, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, 
        OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, 
        DEFAULT_PITCH | FF_MODERN, TEXT("Arial"));

    hFontButton = CreateFont(17, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, 
        OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, 
        DEFAULT_PITCH | FF_MODERN, TEXT("Arial"));

}

DWORD WINAPI popup_item::CreateThread(void* Param)
{
    popup_item* pThis = (popup_item*)Param;
    return pThis->ThreadStart();
}

DWORD popup_item::ThreadStart(void)
{
    CreateFormMain();

    return 0;
}

int popup_item::CreateFormMain()
{
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = this->WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = NULL;
    wcex.hIcon = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = CreateSolidBrush(RGB(255, 255, 255));
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = "IMFormPopupItem";
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

    if (!RegisterClassEx(&wcex))
    {
        MessageBox(NULL, "Unable to load popup item\n0x1000", "ERROR", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);
        return 1;
    }

    hInstMainWin = wcex.hInstance;

    hwnd = CreateWindowEx(NULL, "IMFormPopupItem", "Inventory Management - Item", WS_POPUPWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 460, 385, NULL, NULL, hInstMainWin, this);
    CenterWindow(hwnd);
    ShowWindow(hwnd, SW_HIDE);
    UpdateWindow(hwnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

LRESULT popup_item::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    popup_item* pThis;
    if (message == WM_NCCREATE)
    {
        LPCREATESTRUCT lpcs = reinterpret_cast<LPCREATESTRUCT>(lParam);
        pThis = static_cast<popup_item*>(lpcs->lpCreateParams);
        SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pThis));
    }
    else
    {
        pThis = reinterpret_cast<popup_item*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
    }

    if(pThis)
    {
        return pThis->RealWndProc(hwnd, message, wParam, lParam);
    }

    return DefWindowProc(hwnd, message, wParam, lParam);
}

LRESULT popup_item::RealWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        {
            RECT rectWindow;

            GetWindowRect(hwnd, &rectWindow);

            int nMainWidth = rectWindow.right - rectWindow.left;
            int nMainHeight = rectWindow.bottom - rectWindow.top;

            txtboxWidth = 300;
            txtboxHeight = 25;
            nCenterX = (nMainWidth / 2) - (txtboxWidth / 2);
            nY = 60;
            int nFieldCount = 1;
            
            txtUPC = new form_underlinetxtbox(hwnd, FormObjects::POPUP_ITEM_TXT_UPC, nCenterX, nY * nFieldCount, txtboxWidth, txtboxHeight);
            txtUPC->SetFont(hFont);
            txtUPC->PlaceHolder = "UPC";

            nFieldCount++;
            txtDescription = new form_underlinetxtbox(hwnd, FormObjects::POPUP_ITEM_TXT_DESCRIPTION, nCenterX, nY * nFieldCount, txtboxWidth, txtboxHeight, true);
            txtDescription->SetFont(hFont);
            txtDescription->PlaceHolder = "DESCRIPTION";

            nFieldCount++;
            txtQuantity = new form_underlinetxtbox(hwnd, FormObjects::POPUP_ITEM_TXT_QUANTITY, nCenterX, nY * nFieldCount, txtboxWidth, txtboxHeight);
            txtQuantity->SetFont(hFont);
            txtQuantity->PlaceHolder = "QUANTITY";

            nFieldCount++;
            txtPrice = new form_underlinetxtbox(hwnd, FormObjects::POPUP_ITEM_TXT_PRICE, nCenterX, nY * nFieldCount, txtboxWidth, txtboxHeight);
            txtPrice->SetFont(hFont);
            txtPrice->PlaceHolder = "PRICE";
            
            nFieldCount++;
            nButtonWidth = txtboxWidth / 2 - 20;
            nButtonHeight = 33;
            btnFirstButton = new form_button(hwnd, FormObjects::POPUP_ITEM_BTN_FIRST, nCenterX, nY * nFieldCount, nButtonWidth, nButtonHeight);
            btnFirstButton->SetFont(hFontButton);
            btnFirstButton->ButtonText = "Create";
            btnFirstButton->ButtonColorRGB = RGB(43, 185, 255);
            btnFirstButton->ButtonColorRGB_Hover = RGB(0, 154, 229);

            btnCancel = new form_button(hwnd, FormObjects::POPUP_ITEM_BTN_CANCEL, nCenterX + nButtonWidth + 40, nY * nFieldCount, nButtonWidth, nButtonHeight);
            btnCancel->SetFont(hFontButton);
            btnCancel->ButtonText = "Cancel";
            btnCancel->ButtonColorRGB = RGB(43, 185, 255);
            btnCancel->ButtonColorRGB_Hover = RGB(0, 154, 229);
        }
        break;
    case WM_GETMINMAXINFO:
        {
            LPMINMAXINFO lpMMI = (LPMINMAXINFO)lParam;
            lpMMI->ptMinTrackSize.x = 750;
            lpMMI->ptMinTrackSize.y = 750;
        }
        break;
    case WM_COMMAND:
        {
            switch(LOWORD(wParam))
            {
                case FormObjects::POPUP_ITEM_BTN_CANCEL:
                    {
                        EnableWindow(hwndMain, true);
                        ShowWindow(hwnd, SW_HIDE);
                        SendMessage(txtUPC->hwndTxtbox, WM_SETTEXT, 0, (LPARAM)"");
                        SendMessage(txtDescription->hwndTxtbox, WM_SETTEXT, 0, (LPARAM)"");
                        SendMessage(txtQuantity->hwndTxtbox, WM_SETTEXT, 0, (LPARAM)"");
                        SendMessage(txtPrice->hwndTxtbox, WM_SETTEXT, 0, (LPARAM)"");
                    }
                    break;
            }
        }
        break;
    case WM_SHOWWINDOW:
        {
            CenterWindow(hwnd);
        }
        break;
    case WM_CLOSE:
        {
            EnableWindow(hwndMain, true);
            ShowWindow(hwnd, SW_HIDE);
            SendMessage(txtUPC->hwndTxtbox, WM_SETTEXT, 0, (LPARAM)"");
            SendMessage(txtDescription->hwndTxtbox, WM_SETTEXT, 0, (LPARAM)"");
            SendMessage(txtQuantity->hwndTxtbox, WM_SETTEXT, 0, (LPARAM)"");
            SendMessage(txtPrice->hwndTxtbox, WM_SETTEXT, 0, (LPARAM)"");
        }
        break;
    case WM_KILLFOCUS:
        {
            FLASHWINFO fi;
            fi.cbSize = sizeof(FLASHWINFO);
            fi.hwnd = hwnd;
            fi.dwFlags = FLASHW_ALL | FLASHW_TIMERNOFG;
            fi.uCount = 0;
            fi.dwTimeout = 0;
            FlashWindowEx(&fi);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, message, wParam, lParam);
        break;
    }

    return 0;
}

void popup_item::SetFont(HFONT hFont)
{
    if(IsWindow(hwnd))
    {
        SendMessage(hwnd, WM_SETFONT, (WPARAM)hFont, TRUE);
    }
}