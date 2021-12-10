#pragma once

#include <Windows.h>
#include <commctrl.h>
#include <string>

using namespace std;

class content_item_search
{
    private:
        HWND hwndParent;
        bool bFocus = false;
        static LRESULT CALLBACK UnderLineTxtBoxProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData);
        HFONT hFont;

    public:
        HWND hwnd;
        string PlaceHolder;
        wstring wstrIcon;
        int nIconX;
        bool bSolidIcon;

        content_item_search(HWND hwndParent, int lpParam, int x, int y, int width, int height);

        void SetFont(HFONT hFont);
        void SetPlaceHolder(string strPlaceHolder);
};