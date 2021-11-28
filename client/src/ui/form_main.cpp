#include <iostream>
#include "global.h"
#include "ui/objects.h"
#include "ui/form_main.h"

using namespace std;

bool form_main::CenterWindow(HWND hwndWindow)
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

form_main::form_main(HWND hwndLogin)
{
    this->hwndLogin = hwndLogin;
}

int form_main::CreateFormMain()
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
    wcex.lpszClassName = "IMFormMain";
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

    if (!RegisterClassEx(&wcex))
    {
        MessageBox(NULL, "Unable to load\n0x1002", "ERROR", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);
        return 1;
    }

    hInstMainWin = wcex.hInstance;

    hwndMain = CreateWindowEx(0, "IMFormMain", "Inventory Management", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 750, 750, NULL, NULL, hInstMainWin, this);
    CenterWindow(hwndMain);
    ShowWindow(hwndMain, SW_RESTORE);
    UpdateWindow(hwndMain);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

LRESULT form_main::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    form_main* pThis;
    if (message == WM_NCCREATE)
    {
        LPCREATESTRUCT lpcs = reinterpret_cast<LPCREATESTRUCT>(lParam);
        pThis = static_cast<form_main*>(lpcs->lpCreateParams);
        SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pThis));
    }
    else
    {
        pThis = reinterpret_cast<form_main*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
    }

    if(pThis)
    {
        return pThis->RealWndProc(hwnd, message, wParam, lParam);
    }

    return DefWindowProc(hwnd, message, wParam, lParam);
}

LRESULT form_main::RealWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        {
            RECT rectWindow;

            GetWindowRect(hwnd, &rectWindow);

            int nMainWidth = rectWindow.right - rectWindow.left;
            int nMainHeight = rectWindow.bottom - rectWindow.top;

            HFONT hFontButton = CreateFont(17, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, 
                OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, 
                DEFAULT_PITCH | FF_MODERN, TEXT("Arial"));

            int ItemMinWidth = 55;
            int ItemMaxWidth = 220;

            Menu_Bar = new form_menubar(hwnd, FormObjects::MENU_SIDEBAR, 0, 0, ItemMaxWidth, nMainHeight, ItemMinWidth, ItemMaxWidth);
            Menu_Bar->BackgroundColorRGB = RGB(0, 0, 0);
        }
        break;
    case WM_GETMINMAXINFO:
        {
            LPMINMAXINFO lpMMI = (LPMINMAXINFO)lParam;
            lpMMI->ptMinTrackSize.x = 750;
            lpMMI->ptMinTrackSize.y = 750;
        }
        break;
    case WM_SIZE:
        {
            RECT rectWindow;

            GetWindowRect(hwnd, &rectWindow);

            int nMainWidth = rectWindow.right - rectWindow.left;
            int nMainHeight = rectWindow.bottom - rectWindow.top;

            int MaxWidth = 220;

            if(Menu_Bar->hwndmenubar != nullptr)
            {
                if(nMainWidth >= 1200)
                {
                    Menu_Bar->bItemExtended = true;
                    MaxWidth = 300;
                }
                else if(nMainWidth >= 950)
                {
                    Menu_Bar->bItemExtended = true;
                }
                else
                {
                    Menu_Bar->bItemExtended = false;
                }

                Menu_Bar->ItemMaxWidth = MaxWidth;
                SetWindowPos(Menu_Bar->hwndmenubar, NULL, 0, 0, MaxWidth, nMainHeight, SWP_NOMOVE);
            }
        }
        break;
    case WM_COMMAND:
        {
            switch(LOWORD(wParam))
            {

            }
        }
        break;
    case WM_CLOSE:
        {
            //DestroyWindow(hwnd);
            ShowWindow(hwnd, SW_HIDE);
            CenterWindow(hwndLogin);
            ShowWindow(hwndLogin, SW_RESTORE);
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