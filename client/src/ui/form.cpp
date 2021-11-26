#include <iostream>
#include <codecvt>
#include "global.h"
#include "ui/objects.h"
#include "ui/form.h"

using namespace std;

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

    hInstLoginWin = wcex.hInstance;

    hwndLogin = CreateWindowEx(WS_EX_TOPMOST, "IMForm", "Inventory Management", WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT, 500, 500, NULL, NULL, hInstLoginWin, this);
    CenterWindow(hwndLogin);
    ShowWindow(hwndLogin, SW_RESTORE);
    UpdateWindow(hwndLogin);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

LRESULT Form::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
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

            int ntxtboxWidth = 250;
            int ntxtboxHeight = 25;

            int nCenterLoc = (nMainWidth / 2) - (ntxtboxWidth / 2);

            HFONT hFontTitle = CreateFont(30, 0, 0, 0, FW_THIN, FALSE, FALSE, FALSE, DEFAULT_CHARSET, 
                OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, 
                DEFAULT_PITCH | FF_MODERN , TEXT("Arial"));

            HFONT hFont = CreateFont(18, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, 
                OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, 
                DEFAULT_PITCH | FF_MODERN, TEXT("Arial"));

            HFONT hFontButton = CreateFont(17, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, 
                OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, 
                DEFAULT_PITCH | FF_MODERN, TEXT("Arial"));

            HFONT hFontVersion = CreateFont(15, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, 
                OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, 
                DEFAULT_PITCH | FF_MODERN, TEXT("Arial"));

            lblTitle = new form_staticlabel(hwnd, FormObjects::LBL_TITLE, -10, 80, nMainWidth, 30); 
            lblTitle->SetFont(hFontTitle);
            lblTitle->StaticText = L"COMPANYNAME";

            txtboxUsername = new form_underlinetxtbox(hwnd, FormObjects::TXT_USERNAME, nCenterLoc - 10, 170, ntxtboxWidth, ntxtboxHeight);
            txtboxUsername->SetFont(hFont);
            txtboxUsername->PlaceHolder = "USERNAME";

            txtboxPassword = new form_underlinetxtbox(hwnd, FormObjects::TXT_PASSWORD, nCenterLoc - 10, 240, ntxtboxWidth, ntxtboxHeight, true);
            txtboxPassword->SetFont(hFont);
            txtboxPassword->PlaceHolder = "PASSWORD";

            btnLogin = new form_button(hwnd, FormObjects::BTN_LOGIN, nCenterLoc - 10, 320, (ntxtboxWidth / 2) - 10, 32);
            btnLogin->SetFont(hFontButton);
            btnLogin->ButtonText = "Login";
            btnLogin->ButtonColorRGB = RGB(43, 185, 255);
            btnLogin->ButtonColorRGB_Hover = RGB(0, 154, 229);

            btnExit = new form_button(hwnd, FormObjects::BTN_EXIT, (nCenterLoc) + (ntxtboxWidth / 2), 320, (ntxtboxWidth / 2) - 10, 32);
            btnExit->SetFont(hFontButton);
            btnExit->ButtonText = "Exit";
            btnExit->ButtonColorRGB = RGB(43, 185, 255);
            btnExit->ButtonColorRGB_Hover = RGB(0, 154, 229);

            lblVersion = new form_staticlabel(hwnd, FormObjects::LBL_VERSION, nMainWidth - 120, nMainHeight - 65, 100, 20);
            lblVersion->SetFont(hFontVersion);
            wstring wstrProgramVersion = wstring_convert<codecvt_utf8<wchar_t>>().from_bytes(ProgramVersion);
            lblVersion->StaticText = wstrProgramVersion;
            lblVersion->TextColorRGB = RGB(115, 115, 115);
        }
        break;
    case WM_COMMAND:
        {
            switch(LOWORD(wParam))
            {
                case FormObjects::BTN_LOGIN:
                    {
                        printf("Login button clicked!\n");
                        ShowWindow(hwnd, SW_HIDE);
                        SendMessage(txtboxUsername->hwndTxtbox, WM_SETTEXT, 0, (LPARAM)"");
                        SendMessage(txtboxPassword->hwndTxtbox, WM_SETTEXT, 0, (LPARAM)"");

                        if(formMain == nullptr)
                        {
                            formMain = new form_main(hwnd);
                            formMain->CreateFormMain();
                        }
                        else
                        {
                            ShowWindow(formMain->hwndMain, SW_SHOW);
                        }
                    }
                    break;
                case FormObjects::BTN_EXIT:
                    {
                        printf("Exit button clicked!\n");
                        SendMessage(hwnd, WM_CLOSE, 0, NULL);
                    }
                    break;
            }
        }
        break;
    case WM_CLOSE:
        {
            DestroyWindow(hwnd);
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