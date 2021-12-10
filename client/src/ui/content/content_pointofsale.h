#pragma once

#include <string>
#include "ui/content/content.h"
#include "ui/content/item/search.h"
#include "ui/content/item/itemlist.h"

using namespace std;

class content_pointofsale : public content
{
    private:
        static LRESULT CALLBACK ContentProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData);
        HFONT hFont;

        content_item_search* SearchBar = nullptr;

        content_item_list* ItemList = nullptr;
        int nItemListY;

    public: 
        content_pointofsale(HWND hwndParent, int lpParam, int x, int y, int width, int height);
};