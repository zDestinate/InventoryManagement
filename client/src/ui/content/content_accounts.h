#pragma once

#include <string>
#include "datahandler/mainHeader.h"
#include "ui/content/content.h"
#include "ui/content/item/search.h"
#include "ui/content/item/itemlist.h"
#include "ui/popup/popup_accounts.h"
#include "ui/form_button.h"

using namespace std;

class content_accounts : public content
{
    private:
        static LRESULT CALLBACK ContentProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData);
        HFONT hFont;

        popup_accounts* FormAccounts = nullptr;
        DWORD dwThreadID_PopUp_Accounts;

        content_item_search* SearchBar = nullptr;
        int nSearchBarHeight;
        int nSearchBarY;

        int nItemListY;

        form_button* btnCreateUser, *btnEditUser, *btnResetUserPass;
        int nButtonWidth;
        int nButtonheight;
        int nSpaceBetweenButtons;

        vector<User> SearchUserList, CurrentUserList;

    public:
        content_accounts(HWND hwndParent, int lpParam, int x, int y, int width, int height);
        COLORREF TextColorRGB = RGB(0, 0, 0);

        mainClass* DataHandler = nullptr;
        content_item_list* ItemList = nullptr;

        void ShowUserList();
        void ShowUserListVector(vector<User> UserList);
};