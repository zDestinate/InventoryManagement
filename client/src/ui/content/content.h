#pragma once

#include <Windows.h>
#include <commctrl.h>
#include <string>

using namespace std;

class content
{
    private:
        static LRESULT CALLBACK ContentProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData);
        COLORREF RedColorRGB = RGB(255, 51, 51);
        COLORREF GreenColorRGB = RGB(58, 219, 0);

    public:
        HWND hwnd;
        COLORREF BackgroundColorRGB = RGB(255, 255, 255);

        content(HWND hwndParent, int lpParam, int x, int y, int width, int height);
        void DrawBorder(HDC hdc, RECT rc, COLORREF BorderColorRGB, int BorderSize = 1);
};