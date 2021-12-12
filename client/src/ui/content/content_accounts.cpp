#include "ui/objects.h"
#include "ui/content/content_accounts.h"

content_accounts::content_accounts(HWND hwndParent, int lpParam, int x, int y, int width, int height)
: content(hwndParent, lpParam, x, y, width, height)
{
    SetWindowSubclass(hwnd, ContentProc, lpParam, (DWORD_PTR)this);

    hFont = CreateFont(17, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, 
        OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, 
        DEFAULT_PITCH | FF_MODERN, TEXT("Arial"));


    //Pop up account settings
    FormAccounts = new popup_accounts(hwndParent);
    FormAccounts->hwndContent = hwnd;
    CreateThread(NULL, 0, FormAccounts->CreateThread, (void*)FormAccounts, 0, &dwThreadID_PopUp_Accounts);
    
    //RECT of hwnd for design
    RECT rectWindow;
    GetWindowRect(hwnd, &rectWindow);

    int nWidth = rectWindow.right - rectWindow.left;
    int nHeight = rectWindow.bottom - rectWindow.top;

    //For search bar
    int nSearchBarWidth = nWidth / 2;
    nSearchBarHeight = 25;
    int nSearchBarX = (nWidth / 2) - (nSearchBarWidth / 2) + (30 / 2) - 10;
    nSearchBarY = 50;

    SearchBar = new content_item_search(hwnd, FormObjects::CONTENT_ACCOUNTS_SEARCH, nSearchBarX, nSearchBarY, nSearchBarWidth, nSearchBarHeight);
    SearchBar->PlaceHolder = "Search";

    //For ListView
    int nItemListWidth = nWidth - 120;
    int nItemListX = 50;
    nItemListY = 120;
    ItemList = new content_item_list(hwnd, FormObjects::CONTENT_ACCOUNTS_LIST, nItemListX, nItemListY, nItemListWidth, nHeight - nSearchBarHeight - nSearchBarY - 175);
    ItemList->nMinXColumn = 20;

    //For buttons
    nButtonWidth = 150;
    nButtonheight = 32;
    nSpaceBetweenButtons = 15;

    btnResetUserPass = new form_button(hwnd, FormObjects::CONTENT_ACCOUNTS_BTN_RESETPASSWORD, nWidth - 70 - (nButtonWidth * 1), nHeight - 100, nButtonWidth, nButtonheight);
    btnResetUserPass->SetFont(hFont);
    btnResetUserPass->ButtonText = "Reset Password";
    btnResetUserPass->ButtonColorRGB = RedColorRGB;
    btnResetUserPass->ButtonColorRGB_Hover = RGB(224, 25, 25);

    int nEditUserWidth = 100;
    btnEditUser = new form_button(hwnd, FormObjects::CONTENT_ACCOUNTS_BTN_EDIT, nWidth - 70 - (nButtonWidth * 1) - nEditUserWidth - nSpaceBetweenButtons, nHeight - 100, nEditUserWidth, nButtonheight);
    btnEditUser->SetFont(hFont);
    btnEditUser->ButtonText = "Edit";
    btnEditUser->ButtonColorRGB = RGB(43, 185, 255);
    btnEditUser->ButtonColorRGB_Hover = RGB(0, 154, 229);

    btnCreateUser = new form_button(hwnd, FormObjects::CONTENT_ACCOUNTS_BTN_CREATE, nWidth - 70 - (nButtonWidth * 1) - (nEditUserWidth * 2) - (nSpaceBetweenButtons * 2), nHeight - 100, nEditUserWidth, nButtonheight);
    btnCreateUser->SetFont(hFont);
    btnCreateUser->ButtonText = "Create";
    btnCreateUser->ButtonColorRGB = RGB(43, 185, 255);
    btnCreateUser->ButtonColorRGB_Hover = RGB(0, 154, 229);
}

LRESULT CALLBACK content_accounts::ContentProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
    //Using the dwRefData we passed from and create this pointer
    content_accounts* pThis = (content_accounts*) dwRefData;

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


            SetTextColor(hdc, pThis->TextColorRGB);
            SelectObject(hdc, pThis->hFont);

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
            SetWindowPos(pThis->btnResetUserPass->hwndbutton, NULL, nWidth - 70 - (pThis->nButtonWidth * 1), nHeight - 100, pThis->nButtonWidth, pThis->nButtonheight, SWP_NOZORDER);

            int nEditUserWidth = 100;
            SetWindowPos(pThis->btnEditUser->hwndbutton, NULL, nWidth - 70 - (pThis->nButtonWidth * 1) - nEditUserWidth - pThis->nSpaceBetweenButtons, nHeight - 100, nEditUserWidth, pThis->nButtonheight, SWP_NOZORDER);
            SetWindowPos(pThis->btnCreateUser->hwndbutton, NULL, nWidth - 70 - (pThis->nButtonWidth * 1) - (nEditUserWidth * 2) - (pThis->nSpaceBetweenButtons * 2), nHeight - 100, nEditUserWidth, pThis->nButtonheight, SWP_NOZORDER);
        }
        break;
    case WM_COMMAND:
        {
            switch(LOWORD(wParam))
            {
                case FormObjects::CONTENT_ACCOUNTS_SEARCH:
                    {
                        int nSearchBarLength = GetWindowTextLength(pThis->SearchBar->hwnd) + 1;
                        TCHAR *tszSearchBarText = new TCHAR[nSearchBarLength];
                        nSearchBarLength = GetWindowText(pThis->SearchBar->hwnd, tszSearchBarText, nSearchBarLength);
                        string strSearchbarText;
                        strSearchbarText.assign(&tszSearchBarText[0], &tszSearchBarText[nSearchBarLength]);

                        pThis->SearchUserList.clear();
                        if(!strSearchbarText.empty())
                        {
                            if(!pThis->CurrentUserList.empty())
                            {
                                for(int i = 0; i < pThis->CurrentUserList.size(); i++)
                                {
                                    if((pThis->CurrentUserList[i]).id.find(strSearchbarText) != string::npos)
                                    {
                                        pThis->SearchUserList.push_back(pThis->CurrentUserList[i]);
                                    }
                                    else if((pThis->CurrentUserList[i]).user.find(strSearchbarText) != string::npos)
                                    {
                                        pThis->SearchUserList.push_back(pThis->CurrentUserList[i]);
                                    }
                                    else if((pThis->CurrentUserList[i]).flname.find(strSearchbarText) != string::npos)
                                    {
                                        pThis->SearchUserList.push_back(pThis->CurrentUserList[i]);
                                    }
                                    else if((pThis->CurrentUserList[i]).phone.find(strSearchbarText) != string::npos)
                                    {
                                        pThis->SearchUserList.push_back(pThis->CurrentUserList[i]);
                                    }
                                    else if((pThis->CurrentUserList[i]).email.find(strSearchbarText) != string::npos)
                                    {
                                        pThis->SearchUserList.push_back(pThis->CurrentUserList[i]);
                                    }
                                    else if((pThis->CurrentUserList[i]).perm.find(strSearchbarText) != string::npos)
                                    {
                                        pThis->SearchUserList.push_back(pThis->CurrentUserList[i]);
                                    }
                                }

                                pThis->ShowUserListVector(pThis->SearchUserList);
                            }
                        }
                        else
                        {
                            pThis->ShowUserList();
                        }
                    }
                    break;
                case FormObjects::CONTENT_ACCOUNTS_BTN_CREATE:
                    {
                        pThis->FormAccounts->bShowPassword = true;
                        pThis->FormAccounts->bShowPersonalInfo = true;
                        ShowWindow(pThis->FormAccounts->hwnd, SW_SHOW);
                        EnableWindow(pThis->hwndParent, FALSE);
                    }
                    break;
                case FormObjects::CONTENT_ACCOUNTS_BTN_EDIT:
                    {
                        int itemId = SendMessage(pThis->ItemList->hwnd, LVM_GETNEXTITEM, -1, LVNI_SELECTED);

                        if(itemId != -1)
                        {
                            string strUsername = pThis->ItemList->GetItemText(1, itemId);
                            SendMessage(pThis->FormAccounts->txtUsername->hwndTxtbox, WM_SETTEXT, 0, (LPARAM)((LPCTSTR)strUsername.c_str()));

                            string strFullname = pThis->ItemList->GetItemText(2, itemId);
                            SendMessage(pThis->FormAccounts->txtFullname->hwndTxtbox, WM_SETTEXT, 0, (LPARAM)((LPCTSTR)strFullname.c_str()));

                            string strEmail = pThis->ItemList->GetItemText(3, itemId);
                            SendMessage(pThis->FormAccounts->txtEmail->hwndTxtbox, WM_SETTEXT, 0, (LPARAM)((LPCTSTR)strEmail.c_str()));

                            string strPhone = pThis->ItemList->GetItemText(4, itemId);
                            SendMessage(pThis->FormAccounts->txtPhone->hwndTxtbox, WM_SETTEXT, 0, (LPARAM)((LPCTSTR)strPhone.c_str()));

                            string strPerm = pThis->ItemList->GetItemText(5, itemId);
                            SendMessage(pThis->FormAccounts->txtPermission->hwndTxtbox, WM_SETTEXT, 0, (LPARAM)((LPCTSTR)strPerm.c_str()));

                            pThis->FormAccounts->nEditVectorID = itemId;

                            pThis->FormAccounts->bShowPassword = false;
                            pThis->FormAccounts->bShowPersonalInfo = true;
                            ShowWindow(pThis->FormAccounts->hwnd, SW_SHOW);
                            EnableWindow(pThis->hwndParent, FALSE);
                        }
                        else
                        {
                            MessageBox(NULL, "Please select an user to edit that user information", "Information", MB_OK | MB_ICONINFORMATION | MB_SYSTEMMODAL);
                        }
                    }
                    break;
                case FormObjects::CONTENT_ACCOUNTS_BTN_RESETPASSWORD:
                    {
                        pThis->FormAccounts->bShowPassword = true;
                        pThis->FormAccounts->bShowPersonalInfo = false;
                        ShowWindow(pThis->FormAccounts->hwnd, SW_SHOW);
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
                SendMessage(pThis->SearchBar->hwnd, WM_SETTEXT, 0, (LPARAM)"");
                pThis->ShowUserList();
                printf("[CONTENT][ACCOUNTS] Show\n");
            }
        }
        break;
    }

    return DefSubclassProc(hwnd, message, wParam, lParam);
}

void content_accounts::ShowUserList()
{
    CurrentUserList.clear();

    if((DataHandler != nullptr) && (ItemList != nullptr))
    {
        ItemList->DeleteAllItems();

        if(DataHandler->returnUserData())
        {
            if(DataHandler->exeCheck())
            {
                vector<User> UserList = DataHandler->returnUserVector();

                CurrentUserList = UserList;

                for(int i = 0; i < UserList.size(); i++)
                {
                    char* szID = new char[UserList[i].id.length() + 1];
                    strcpy(szID, UserList[i].id.c_str());
                    ItemList->Insert(0, i, szID);

                    char* szUsername = new char[UserList[i].user.length() + 1];
                    strcpy(szUsername, UserList[i].user.c_str());
                    ItemList->Insert(1, i, szUsername);

                    char* szFullname = new char[UserList[i].flname.length() + 1];
                    strcpy(szFullname, UserList[i].flname.c_str());
                    ItemList->Insert(2, i, szFullname);

                    char* szEmail = new char[UserList[i].email.length() + 1];
                    strcpy(szEmail, UserList[i].email.c_str());
                    ItemList->Insert(3, i, szEmail);

                    char* szPhone = new char[UserList[i].phone.length() + 1];
                    strcpy(szPhone, UserList[i].phone.c_str());
                    ItemList->Insert(4, i, szPhone);

                    char* szPerm = new char[UserList[i].perm.length() + 1];
                    strcpy(szPerm, UserList[i].perm.c_str());
                    ItemList->Insert(5, i, szPerm);
                }
            }
        }
    }
}

void content_accounts::ShowUserListVector(vector<User> UserList)
{
    if(ItemList != nullptr)
    {
        ItemList->DeleteAllItems();

        for(int i = 0; i < UserList.size(); i++)
        {
            char* szID = new char[UserList[i].id.length() + 1];
            strcpy(szID, UserList[i].id.c_str());
            ItemList->Insert(0, i, szID);

            char* szUsername = new char[UserList[i].user.length() + 1];
            strcpy(szUsername, UserList[i].user.c_str());
            ItemList->Insert(1, i, szUsername);

            char* szFullname = new char[UserList[i].flname.length() + 1];
            strcpy(szFullname, UserList[i].flname.c_str());
            ItemList->Insert(2, i, szFullname);

             char* szEmail = new char[UserList[i].email.length() + 1];
            strcpy(szEmail, UserList[i].email.c_str());
            ItemList->Insert(3, i, szEmail);

            char* szPhone = new char[UserList[i].phone.length() + 1];
            strcpy(szPhone, UserList[i].phone.c_str());
            ItemList->Insert(4, i, szPhone);

            char* szPerm = new char[UserList[i].perm.length() + 1];
            strcpy(szPerm, UserList[i].perm.c_str());
            ItemList->Insert(5, i, szPerm);
        }
    }
}

void content_accounts::SetDatahandler(mainClass* DataHandler)
{
    this->DataHandler = DataHandler;
    FormAccounts->DataHandler = DataHandler;
}