#pragma once

#include <Windows.h>
#include <commctrl.h>
#include <string>

using namespace std;

class form_underlinetxtbox
{
    private:
        bool bFocus = false;
        static LRESULT CALLBACK UnderLineTxtBoxProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData);

    public:
        HWND hwndTxtbox;
        string PlaceHolder;

        form_underlinetxtbox(HWND hwndParent, int lpParam, int x, int y, int width, int height);
        form_underlinetxtbox(HWND hwndParent, int lpParam, int x, int y, int width, int height, bool IsPassword);

        void SetFont(HFONT hFont);
        void SetPlaceHolder(string strPlaceHolder);
};