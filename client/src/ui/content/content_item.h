#pragma once

#include <string>
#include "datahandler/mainHeader.h"
#include "ui/content/content.h"
#include "ui/content/item/search.h"
#include "ui/content/item/itemlist.h"
#include "ui/popup/popup_item.h"
#include "ui/form_button.h"

using namespace std;

class content_item : public content
{
    private:
        static LRESULT CALLBACK ContentProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData);
        HFONT hFont;

        popup_item* FormItem = nullptr;
        DWORD dwThreadID_PopUp_Item;

        content_item_search* SearchBar = nullptr;
        int nSearchBarHeight;
        int nSearchBarY;

        int nItemListY;

        form_button* btnCreateItem, *btnEditItem;
        int nButtonWidth;
        int nButtonheight;
        int nSpaceBetweenButtons;

        vector<itemObj> SearchItemList, CurrentItemList;

    public: 
        content_item(HWND hwndParent, int lpParam, int x, int y, int width, int height);
        COLORREF TextColorRGB = RGB(0, 0, 0);

        mainClass* DataHandler = nullptr;
        content_item_list* ItemList = nullptr;

        void SetDatahandler(mainClass* DataHandler);
        void ShowItemList();
        void ShowItemListVector(vector<itemObj> vItemList);
};