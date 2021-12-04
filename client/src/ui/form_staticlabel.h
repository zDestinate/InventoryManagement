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
        wstring StaticText;
        COLORREF TextColorRGB = RGB(0, 0 ,0);
        COLORREF BackgroundColorRGB = RGB(255, 255, 255);
        bool bUseBorder = false;
        COLORREF BorderColorRGB = RGB(0, 0 ,0);
        int BorderSize = 1;

        form_staticlabel(HWND hwndParent, int lpParam, int x, int y, int width, int height);

        void SetFont(HFONT hFont);
        void Show(bool bShow = true);
};