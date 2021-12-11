#pragma once

#include <Windows.h>
#include <commctrl.h>
#include <string>

using namespace std;

class content_item_list
{
    private:
        static LRESULT CALLBACK ListViewProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData);
        HFONT hFont;

        //WM_NOTIFY
        LVITEM lvItemOriginal;
        LVITEM lvItemChanged;

    public:
        HWND hwnd;

        content_item_list(HWND hwndParent, int lpParam, int x, int y, int width, int height, bool bNoHeader = false);
        void Init();

        UINT lvcMask;
        int lvcFmt;
        int nMinXColumn;

        void SetFont(HFONT hFont);
        int SetListTextColor(COLORREF TextColor);
        int CreateColumn(int nCol, char *szText, int nWidth);
        int Insert(int nCol, int nRow, char *szText);
        bool SetColumnWidth(int nCol, int Width);
        bool DeleteColumn(int nCol);
        void DeleteColumns(int nNumberOfColumns);

};