#include <Windows.h>
#include "ui/form.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

bool CenterWindow(HWND hwndWindow)
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
    wcex.lpfnWndProc = WndProc;
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

    HWND hwndMain = CreateWindow("IMForm", "Inventory Management", WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT, 500, 500, NULL, NULL, NULL, NULL);
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


LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_PAINT:
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