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
    this->FocusContentFormObj = FormObjects::CONTENT_DASHBOARD;
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

            Menu_Bar = new form_menubar(hwnd, FormObjects::MENU_SIDEBAR, 0, MenuTopHeight, ItemMaxWidth, nMainHeight - MenuTopHeight, ItemMinWidth, ItemMaxWidth, FocusContentFormObj);
            Menu_Bar->BackgroundColorRGB = RGB(0, 0, 0);

            Menu_Top = new form_menutop(hwnd, FormObjects::MENU_TOP, 0, 0, nMainWidth, MenuTopHeight);
            Menu_Top->BackgroundColorRGB = RGB(0, 0, 0);
            Menu_Top->TitleText = L"COMPANYNAME";
            Menu_Top->nTitleIndent = 60;
            Menu_Top->nTitleWidth = 250;
            Menu_Top->SetNameText(L"John Doe");
            Menu_Top->SetIDText(L"9123058");

            ContentDashboard = new content_dashboard(hwnd, FormObjects::CONTENT_DASHBOARD, ItemMinWidth, MenuTopHeight, nMainWidth - ItemMinWidth, nMainHeight - MenuTopHeight - 40);
            
            //Item
            ContentItem = new content_item(hwnd, FormObjects::CONTENT_ITEM, ItemMinWidth, MenuTopHeight, nMainWidth - ItemMinWidth, nMainHeight - MenuTopHeight - 40);
            ContentItem->SetDatahandler(DataHandler);
            ContentItem->ItemList->CreateColumn(0, "ID", 50);
            ContentItem->ItemList->CreateColumn(1, "Description", 180);
            ContentItem->ItemList->CreateColumn(2, "Quantity", 100);
            ContentItem->ItemList->CreateColumn(3, "Price", 100);
            ContentItem->ItemList->CreateColumn(4, "UPC", 130);
            ContentItem->DataHandler->demoFillItems();
            ContentItem->ShowItemList();

            
            ContentPointOfSale = new content_pointofsale(hwnd, FormObjects::CONTENT_POINTOFSALE, ItemMinWidth, MenuTopHeight, nMainWidth - ItemMinWidth, nMainHeight - MenuTopHeight - 40);
            ContentPromotion = new content_promotion(hwnd, FormObjects::CONTENT_PROMOTION, ItemMinWidth, MenuTopHeight, nMainWidth - ItemMinWidth, nMainHeight - MenuTopHeight - 40);
            
            //Account
            ContentAccounts = new content_accounts(hwnd, FormObjects::CONTENT_ACCOUNTS, ItemMinWidth, MenuTopHeight, nMainWidth - ItemMinWidth, nMainHeight - MenuTopHeight - 40);
            ContentAccounts->SetDatahandler(DataHandler);
            ContentAccounts->ItemList->CreateColumn(0, "ID", 50);
            ContentAccounts->ItemList->CreateColumn(1, "Username", 100);
            ContentAccounts->ItemList->CreateColumn(2, "Fullname", 100);
            ContentAccounts->ItemList->CreateColumn(3, "Email", 130);
            ContentAccounts->ItemList->CreateColumn(4, "Phone", 100);
            ContentAccounts->ItemList->CreateColumn(5, "Permission", 100);
            ContentAccounts->ShowUserList();

            ContentSettings = new content_settings(hwnd, FormObjects::CONTENT_SETTINGS, ItemMinWidth, MenuTopHeight, nMainWidth - ItemMinWidth, nMainHeight - MenuTopHeight - 40);

            SetFocusContent(FormObjects::CONTENT_DASHBOARD);
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

            int MaxWidth = ItemMaxWidth;
            bool bItemExtended = false;

            if(Menu_Bar->hwndmenubar != nullptr)
            {
                if(nMainWidth >= 1200)
                {
                    Menu_Bar->bItemExtended = true;
                    bItemExtended = true;
                    MaxWidth = 300;
                }
                else if(nMainWidth >= 950)
                {
                    Menu_Bar->bItemExtended = true;
                    bItemExtended = true;
                }
                else
                {
                    Menu_Bar->bItemExtended = false;
                    bItemExtended = false;
                }

                Menu_Bar->ItemMaxWidth = MaxWidth;
                SetWindowPos(Menu_Bar->hwndmenubar, NULL, 0, 0, MaxWidth, nMainHeight - MenuTopHeight, SWP_NOMOVE | SWP_NOZORDER);
                //UpdateWindow(Menu_Bar->hwndmenubar);
            }

            if(Menu_Top->hwndmenutop != nullptr)
            {
                SetWindowPos(Menu_Top->hwndmenutop, NULL, 0, 0, nMainWidth, MenuTopHeight, SWP_NOMOVE | SWP_NOZORDER);
                //UpdateWindow(Menu_Top->hwndmenutop);
            }

            UpdateContent(FocusContent, bItemExtended, nMainWidth, nMainHeight, MaxWidth);
        }
        break;
    case WM_COMMAND:
        {
            /*
            if(IsDebuggerPresent())
            {
                MessageBox(NULL, "Security risk detected!\nProgram will now exit due to security reason", "WARNING", MB_OK | MB_ICONWARNING | MB_SYSTEMMODAL);
                exit(1000);
            }
            */
            
            SetFocusContent(LOWORD(wParam));
            printf("[MAIN] Item 0x%0X clicked\n", LOWORD(wParam));

            switch(LOWORD(wParam))
            {
                
            }
        }
        break;
    case WM_CLOSE:
        {
            //DestroyWindow(hwnd);
            ShowWindow(hwnd, SW_HIDE);

            if(DataHandler != nullptr)
            {
                DataHandler->logOut();
            }

            CenterWindow(hwndLogin);
            ShowWindow(hwndLogin, SW_RESTORE);
        }
        break;
    case WM_SHOWWINDOW:
        {
            if(wParam)
            {
                SetFocusContent(FormObjects::CONTENT_DASHBOARD);
                printf("[MAIN] Main Form show\n");
            }
            else
            {
                printf("[MAIN] Main Form hidden\n");
            }
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

void form_main::UpdateContent(content* Content, bool bItemExtended, int nMainWidth, int nMainHeight, int MaxWidth)
{
    if(Content->hwnd != nullptr)
    {
        if(bItemExtended)
        {
            SetWindowPos(Content->hwnd, NULL, MaxWidth, MenuTopHeight, nMainWidth - MaxWidth, nMainHeight - MenuTopHeight - 40, SWP_NOZORDER);
        }
        else
        {
            SetWindowPos(Content->hwnd, NULL, ItemMinWidth, MenuTopHeight, nMainWidth - ItemMinWidth, nMainHeight - MenuTopHeight - 40, SWP_NOZORDER);
        }
    }
}

void form_main::SetFocusContent(int FormObj)
{
    ShowWindow(ContentDashboard->hwnd, SW_HIDE);
    ShowWindow(ContentItem->hwnd, SW_HIDE);
    ShowWindow(ContentPointOfSale->hwnd, SW_HIDE);
    ShowWindow(ContentPromotion->hwnd, SW_HIDE);
    ShowWindow(ContentAccounts->hwnd, SW_HIDE);
    ShowWindow(ContentSettings->hwnd, SW_HIDE);

    switch(FormObj)
    {
        case FormObjects::MENU_DASHBOARD:
            {
                FocusContent = ContentDashboard;
                ShowWindow(ContentDashboard->hwnd, SW_SHOW);
            }
            break;
        case FormObjects::MENU_ITEM:
            {
                FocusContent = ContentItem;
                ShowWindow(ContentItem->hwnd, SW_SHOW);
            }
            break;
        case FormObjects::MENU_POINTOFSALE:
            {
                FocusContent = ContentPointOfSale;
                ShowWindow(ContentPointOfSale->hwnd, SW_SHOW);
            }
            break;
        case FormObjects::MENU_PROMOTION:
            {
                FocusContent = ContentPromotion;
                ShowWindow(ContentPromotion->hwnd, SW_SHOW);
            }
            break;
        case FormObjects::MENU_ACCOUNTS:
            {
                FocusContent = ContentAccounts;
                ShowWindow(ContentAccounts->hwnd, SW_SHOW);
            }
            break;
        case FormObjects::MENU_SETTINGS:
            {
                FocusContent = ContentSettings;
                ShowWindow(ContentSettings->hwnd, SW_SHOW);
            }
            break;
        default:
            {
                FocusContent = ContentDashboard;
                ShowWindow(ContentDashboard->hwnd, SW_SHOW);
            }
            break;
    }

    Menu_Bar->SetCurrentContent(FocusContent);

    //Update the Content window
    RECT rectWindow;
    GetWindowRect(hwndMain, &rectWindow);

    int nMainWidth = rectWindow.right - rectWindow.left;
    int nMainHeight = rectWindow.bottom - rectWindow.top;

    int MaxWidth = ItemMaxWidth;
    bool bItemExtended = false;
    if(nMainWidth >= 1200)
    {
        bItemExtended = true;
        MaxWidth = 300;
    }
    else if(nMainWidth >= 950)
    {
        bItemExtended = true;
    }
    UpdateContent(FocusContent, bItemExtended, nMainWidth, nMainHeight, MaxWidth);
}

void form_main::SetDataHandler(mainClass* tempDataHandler)
{
    DataHandler = tempDataHandler;
}