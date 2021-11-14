#include <Windows.h>
#include "ui/form.h"

bool Form::CenterWindow(HWND hwndWindow)
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

int Form::CreateForm()
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
    wcex.lpszClassName = "IMForm";
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

    if (!RegisterClassEx(&wcex))
    {
        MessageBox(NULL, "Unable to load\n0x1002", "ERROR", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);
        return 1;
    }

    hInstMainWin = wcex.hInstance;

    hwndMain = CreateWindow("IMForm", "Inventory Management", WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT, 500, 500, NULL, NULL, hInstMainWin, this);
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

LRESULT CALLBACK Form::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    Form* pThis;
    if (message == WM_NCCREATE)
    {
        LPCREATESTRUCT lpcs = reinterpret_cast<LPCREATESTRUCT>(lParam);
        pThis = static_cast<Form*>(lpcs->lpCreateParams);
        SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pThis));
    }
    else
    {
        pThis = reinterpret_cast<Form*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
    }

    if(pThis)
    {
        return pThis->RealWndProc(hwnd, message, wParam, lParam);
    }

    return DefWindowProc(hwnd, message, wParam, lParam);
}

LRESULT Form::RealWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        {
            RECT rectWindow;

            GetWindowRect(hwnd, &rectWindow);

            int nMainWidth = rectWindow.right - rectWindow.left;
            int nMainHeight = rectWindow.bottom - rectWindow.top;

            int ntxtboxUsernameWidth = 250;
            int ntxtboxUsernameHeight = 25;

            int nCenterLoc = (nMainWidth / 2) - (ntxtboxUsernameWidth / 2);

            HFONT hFont = CreateFont(16, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, 
                OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, 
                DEFAULT_PITCH | FF_DONTCARE, TEXT("Arial"));

            txtboxUsername = CreateWindow("EDIT", "", ES_CENTER | WS_BORDER | WS_CHILD | WS_VISIBLE, nCenterLoc, 200, ntxtboxUsernameWidth, ntxtboxUsernameHeight, hwnd, NULL, NULL, NULL);
            SendMessage(txtboxUsername, WM_SETFONT, (WPARAM)hFont, TRUE);
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