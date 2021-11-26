#pragma once

#include <Windows.h>
#include <commctrl.h>
#include <string>

using namespace std;

class form_staticlabel
{
    private:
        HFONT hFont;
        static LRESULT CALLBACK StaticProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData);

    public:
        HWND hwndstatic;
        string StaticText;
        COLORREF TextColorRGB = RGB(0, 0 ,0);

        form_staticlabel(HWND hwndParent, int lpParam, int x, int y, int width, int height);

        void SetFont(HFONT hFont);
        void SetColor(int Color[3]);
        void Show(bool bShow = true);
};