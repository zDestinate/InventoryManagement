#include <iostream>
#include "ui/objects.h"
#include "ui/popup/popup_accounts.h"

using namespace std;

bool popup_accounts::CenterWindow(HWND hwndWindow)
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

popup_accounts::popup_accounts(HWND hwndContent)
{
    this->hwndContent = hwndContent;

    hFont = CreateFont(18, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, 
        OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, 
        DEFAULT_PITCH | FF_MODERN, TEXT("Arial"));

    hFontButton = CreateFont(17, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, 
        OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, 
        DEFAULT_PITCH | FF_MODERN, TEXT("Arial"));

    bShowPassword = true;
    bShowPersonalInfo = true;
}

DWORD WINAPI popup_accounts::CreateThread(void* Param)
{
    popup_accounts* pThis = (popup_accounts*)Param;
    return pThis->ThreadStart();
}

DWORD popup_accounts::ThreadStart(void)
{
    CreateFormMain();

    return 0;
}

int popup_accounts::CreateFormMain()
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
    wcex.lpszClassName = "IMFormPopupAccounts";
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

    if (!RegisterClassEx(&wcex))
    {
        MessageBox(NULL, "Unable to load popup accounts\n0x1000", "ERROR", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);
        return 1;
    }

    hInstMainWin = wcex.hInstance;

    hwnd = CreateWindowEx(WS_EX_TOPMOST, "IMFormPopupAccounts", "Inventory Management - Accounts", WS_POPUPWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 460, 500, NULL, NULL, hInstMainWin, this);
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

LRESULT popup_accounts::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    popup_accounts* pThis;
    if (message == WM_NCCREATE)
    {
        LPCREATESTRUCT lpcs = reinterpret_cast<LPCREATESTRUCT>(lParam);
        pThis = static_cast<popup_accounts*>(lpcs->lpCreateParams);
        SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pThis));
    }
    else
    {
        pThis = reinterpret_cast<popup_accounts*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
    }

    if(pThis)
    {
        return pThis->RealWndProc(hwnd, message, wParam, lParam);
    }

    return DefWindowProc(hwnd, message, wParam, lParam);
}

LRESULT popup_accounts::RealWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
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
            
            txtUsername = new form_underlinetxtbox(hwnd, FormObjects::POPUP_ACCOUNTS_TXT_USERNAME, nCenterX, nY * nFieldCount, txtboxWidth, txtboxHeight);
            txtUsername->SetFont(hFont);
            txtUsername->PlaceHolder = "USERNAME";

            if(bShowPassword)
            {
                nFieldCount++;
                txtPassword = new form_underlinetxtbox(hwnd, FormObjects::POPUP_ACCOUNTS_TXT_PASSWORD, nCenterX, nY * nFieldCount, txtboxWidth, txtboxHeight, true);
                txtPassword->SetFont(hFont);
                txtPassword->PlaceHolder = "PASSWORD";
            }

            if(bShowPersonalInfo)
            {
                nFieldCount++;
                txtFullname = new form_underlinetxtbox(hwnd, FormObjects::POPUP_ACCOUNTS_TXT_FULLNAME, nCenterX, nY * nFieldCount, txtboxWidth, txtboxHeight);
                txtFullname->SetFont(hFont);
                txtFullname->PlaceHolder = "FULL NAME";

                nFieldCount++;
                txtEmail = new form_underlinetxtbox(hwnd, FormObjects::POPUP_ACCOUNTS_TXT_EMAIL, nCenterX, nY * nFieldCount, txtboxWidth, txtboxHeight);
                txtEmail->SetFont(hFont);
                txtEmail->PlaceHolder = "EMAIL";

                nFieldCount++;
                txtPhone = new form_underlinetxtbox(hwnd, FormObjects::POPUP_ACCOUNTS_TXT_PHONE, nCenterX, nY * nFieldCount, txtboxWidth, txtboxHeight);
                txtPhone->SetFont(hFont);
                txtPhone->PlaceHolder = "PHONE NUMBER";

                nFieldCount++;
                txtPermission = new form_underlinetxtbox(hwnd, FormObjects::POPUP_ACCOUNTS_TXT_PERMISSION, nCenterX, nY * nFieldCount, txtboxWidth, txtboxHeight);
                txtPermission->SetFont(hFont);
                txtPermission->PlaceHolder = "PERMISSION";
            }
            
            nFieldCount++;
            nButtonWidth = txtboxWidth / 2 - 20;
            nButtonHeight = 33;
            btnFirstButton = new form_button(hwnd, FormObjects::POPUP_ACCOUNTS_BTN_FIRST, nCenterX, nY * nFieldCount, nButtonWidth, nButtonHeight);
            btnFirstButton->SetFont(hFontButton);
            btnFirstButton->ButtonText = "Create";
            btnFirstButton->ButtonColorRGB = RGB(43, 185, 255);
            btnFirstButton->ButtonColorRGB_Hover = RGB(0, 154, 229);

            btnCancel = new form_button(hwnd, FormObjects::POPUP_ACCOUNTS_BTN_CANCEL, nCenterX + nButtonWidth + 40, nY * nFieldCount, nButtonWidth, nButtonHeight);
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
                case FormObjects::POPUP_ACCOUNTS_BTN_CANCEL:
                    {
                        EnableWindow(hwndContent, true);
                        ShowWindow(hwnd, SW_HIDE);
                        SendMessage(txtUsername->hwndTxtbox, WM_SETTEXT, 0, (LPARAM)"");
                        SendMessage(txtPassword->hwndTxtbox, WM_SETTEXT, 0, (LPARAM)"");
                        SendMessage(txtFullname->hwndTxtbox, WM_SETTEXT, 0, (LPARAM)"");
                        SendMessage(txtEmail->hwndTxtbox, WM_SETTEXT, 0, (LPARAM)"");
                        SendMessage(txtPhone->hwndTxtbox, WM_SETTEXT, 0, (LPARAM)"");
                        SendMessage(txtPermission->hwndTxtbox, WM_SETTEXT, 0, (LPARAM)"");
                    }
                    break;
            }
        }
        break;
    case WM_SHOWWINDOW:
        {
            int nFieldCount = 2;
            if(bShowPassword && bShowPersonalInfo)
            {
                ShowWindow(txtPassword->hwndTxtbox, SW_SHOW);
                ShowWindow(txtFullname->hwndTxtbox, SW_SHOW);
                ShowWindow(txtEmail->hwndTxtbox, SW_SHOW);
                ShowWindow(txtPhone->hwndTxtbox, SW_SHOW);
                ShowWindow(txtPermission->hwndTxtbox, SW_SHOW);

                SetWindowPos(txtPassword->hwndTxtbox, NULL, nCenterX, nY * nFieldCount, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
                nFieldCount++;
                SetWindowPos(txtFullname->hwndTxtbox, NULL, nCenterX, nY * nFieldCount, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
                nFieldCount++;
                SetWindowPos(txtEmail->hwndTxtbox, NULL, nCenterX, nY * nFieldCount, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
                nFieldCount++;
                SetWindowPos(txtPhone->hwndTxtbox, NULL, nCenterX, nY * nFieldCount, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
                nFieldCount++;
                SetWindowPos(txtPermission->hwndTxtbox, NULL, nCenterX, nY * nFieldCount, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

                SetWindowPos(hwnd, NULL, NULL, NULL, 460, 500, SWP_NOZORDER | SWP_NOMOVE);
            }
            else if(bShowPersonalInfo)
            {
                ShowWindow(txtPassword->hwndTxtbox, SW_HIDE);
                ShowWindow(txtFullname->hwndTxtbox, SW_SHOW);
                ShowWindow(txtEmail->hwndTxtbox, SW_SHOW);
                ShowWindow(txtPhone->hwndTxtbox, SW_SHOW);
                ShowWindow(txtPermission->hwndTxtbox, SW_SHOW);

                SetWindowPos(txtFullname->hwndTxtbox, NULL, nCenterX, nY * nFieldCount, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
                nFieldCount++;
                SetWindowPos(txtEmail->hwndTxtbox, NULL, nCenterX, nY * nFieldCount, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
                nFieldCount++;
                SetWindowPos(txtPhone->hwndTxtbox, NULL, nCenterX, nY * nFieldCount, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
                nFieldCount++;
                SetWindowPos(txtPermission->hwndTxtbox, NULL, nCenterX, nY * nFieldCount, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

                SetWindowPos(hwnd, NULL, NULL, NULL, 460, 440, SWP_NOZORDER | SWP_NOMOVE);
            }
            else if(bShowPassword)
            {
                ShowWindow(txtPassword->hwndTxtbox, SW_SHOW);
                ShowWindow(txtFullname->hwndTxtbox, SW_HIDE);
                ShowWindow(txtEmail->hwndTxtbox, SW_HIDE);
                ShowWindow(txtPhone->hwndTxtbox, SW_HIDE);
                ShowWindow(txtPermission->hwndTxtbox, SW_HIDE);

                SetWindowPos(txtPassword->hwndTxtbox, NULL, nCenterX, nY * nFieldCount, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

                SetWindowPos(hwnd, NULL, NULL, NULL, 460, 260, SWP_NOZORDER | SWP_NOMOVE);
            }

            nFieldCount++;
            ShowWindow(btnFirstButton->hwndbutton, SW_SHOW);
            ShowWindow(btnCancel->hwndbutton, SW_SHOW);
            SetWindowPos(btnFirstButton->hwndbutton, NULL, nCenterX , nY * nFieldCount, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
            SetWindowPos(btnCancel->hwndbutton, NULL, nCenterX + nButtonWidth + 40, nY * nFieldCount, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

            CenterWindow(hwnd);
        }
        break;
    case WM_CLOSE:
        {
            EnableWindow(hwndContent, true);
            ShowWindow(hwnd, SW_HIDE);
            SendMessage(txtUsername->hwndTxtbox, WM_SETTEXT, 0, (LPARAM)"");
            SendMessage(txtPassword->hwndTxtbox, WM_SETTEXT, 0, (LPARAM)"");
            SendMessage(txtFullname->hwndTxtbox, WM_SETTEXT, 0, (LPARAM)"");
            SendMessage(txtEmail->hwndTxtbox, WM_SETTEXT, 0, (LPARAM)"");
            SendMessage(txtPhone->hwndTxtbox, WM_SETTEXT, 0, (LPARAM)"");
            SendMessage(txtPermission->hwndTxtbox, WM_SETTEXT, 0, (LPARAM)"");
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

void popup_accounts::SetFont(HFONT hFont)
{
    if(IsWindow(hwnd))
    {
        SendMessage(hwnd, WM_SETFONT, (WPARAM)hFont, TRUE);
    }
}