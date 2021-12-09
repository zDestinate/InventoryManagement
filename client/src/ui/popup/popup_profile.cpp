#include <iostream>
#include "ui/objects.h"
#include "ui/popup/popup_profile.h"

using namespace std;

bool popup_profile::CenterWindow(HWND hwndWindow)
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

popup_profile::popup_profile(HWND hwndMain)
{
    this->hwndMain = hwndMain;

    hFont = CreateFont(18, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, 
        OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, 
        DEFAULT_PITCH | FF_MODERN, TEXT("Arial"));

    hFontButton = CreateFont(17, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, 
        OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, 
        DEFAULT_PITCH | FF_MODERN, TEXT("Arial"));
}

DWORD WINAPI popup_profile::CreateThread(void* Param)
{
    popup_profile* pThis = (popup_profile*)Param;
    return pThis->ThreadStart();
}

DWORD popup_profile::ThreadStart(void)
{
    CreateFormMain();

    return 0;
}

int popup_profile::CreateFormMain()
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
    wcex.lpszClassName = "IMFormPopupProfile";
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

    if (!RegisterClassEx(&wcex))
    {
        MessageBox(NULL, "Unable to load popup profile\n0x1000", "ERROR", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);
        return 1;
    }

    hInstMainWin = wcex.hInstance;

    hwnd = CreateWindowEx(NULL, "IMFormPopupProfile", "Inventory Management - Profile", WS_POPUPWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 460, 320, NULL, NULL, hInstMainWin, this);
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

LRESULT popup_profile::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    popup_profile* pThis;
    if (message == WM_NCCREATE)
    {
        LPCREATESTRUCT lpcs = reinterpret_cast<LPCREATESTRUCT>(lParam);
        pThis = static_cast<popup_profile*>(lpcs->lpCreateParams);
        SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pThis));
    }
    else
    {
        pThis = reinterpret_cast<popup_profile*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
    }

    if(pThis)
    {
        return pThis->RealWndProc(hwnd, message, wParam, lParam);
    }

    return DefWindowProc(hwnd, message, wParam, lParam);
}

LRESULT popup_profile::RealWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
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
            
            txtCurrentPassword = new form_underlinetxtbox(hwnd, FormObjects::POPUP_PROFILE_TXT_CURRENTPASSWORD, nCenterX, nY * nFieldCount, txtboxWidth, txtboxHeight, true);
            txtCurrentPassword->SetFont(hFont);
            txtCurrentPassword->PlaceHolder = "CURRENT PASSWORD";

            nFieldCount++;
            txtNewPassword = new form_underlinetxtbox(hwnd, FormObjects::POPUP_PROFILE_TXT_NEWPASSWORD, nCenterX, nY * nFieldCount, txtboxWidth, txtboxHeight, true);
            txtNewPassword->SetFont(hFont);
            txtNewPassword->PlaceHolder = "NEW PASSWORD";

            nFieldCount++;
            txtConfirmPassword = new form_underlinetxtbox(hwnd, FormObjects::POPUP_PROFILE_TXT_CONFIRMPASSWORD, nCenterX, nY * nFieldCount, txtboxWidth, txtboxHeight, true);
            txtConfirmPassword->SetFont(hFont);
            txtConfirmPassword->PlaceHolder = "RETYPE NEW PASSWORD";
            
            nFieldCount++;
            nButtonWidth = txtboxWidth / 2 - 20;
            nButtonHeight = 33;
            btnChange = new form_button(hwnd, FormObjects::POPUP_PROFILE_BTN_CHANGE, nCenterX, nY * nFieldCount, nButtonWidth, nButtonHeight);
            btnChange->SetFont(hFontButton);
            btnChange->ButtonText = "Confirm";
            btnChange->ButtonColorRGB = RGB(43, 185, 255);
            btnChange->ButtonColorRGB_Hover = RGB(0, 154, 229);

            btnCancel = new form_button(hwnd, FormObjects::POPUP_PROFILE_BTN_CANCEL, nCenterX + nButtonWidth + 40, nY * nFieldCount, nButtonWidth, nButtonHeight);
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
                case FormObjects::POPUP_PROFILE_BTN_CANCEL:
                    {
                        EnableWindow(hwndMain, true);
                        ShowWindow(hwnd, SW_HIDE);
                        SendMessage(txtCurrentPassword->hwndTxtbox, WM_SETTEXT, 0, (LPARAM)"");
                        SendMessage(txtNewPassword->hwndTxtbox, WM_SETTEXT, 0, (LPARAM)"");
                        SendMessage(txtConfirmPassword->hwndTxtbox, WM_SETTEXT, 0, (LPARAM)"");
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
            SendMessage(txtCurrentPassword->hwndTxtbox, WM_SETTEXT, 0, (LPARAM)"");
            SendMessage(txtNewPassword->hwndTxtbox, WM_SETTEXT, 0, (LPARAM)"");
            SendMessage(txtConfirmPassword->hwndTxtbox, WM_SETTEXT, 0, (LPARAM)"");
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

void popup_profile::SetFont(HFONT hFont)
{
    if(IsWindow(hwnd))
    {
        SendMessage(hwnd, WM_SETFONT, (WPARAM)hFont, TRUE);
    }
}