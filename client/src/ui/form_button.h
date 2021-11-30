#pragma once

#include <Windows.h>
#include <commctrl.h>
#include <string>

using namespace std;

class form_button
{
    private:
        bool bHover = false;
        HFONT hFont;
        static LRESULT CALLBACK ButtonProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData);

    public:
        HWND hwndbutton;
        string ButtonText;
        COLORREF ButtonColorRGB = RGB(0, 0, 0);
        COLORREF ButtonColorRGB_Hover = RGB(0, 0, 0);
        COLORREF TextColorRGB = RGB(255, 255, 255);
        COLORREF TextColorRGB_Hover = RGB(255, 255, 255);

        form_button(HWND hwndParent, int lpParam, int x, int y, int width, int height);

        void SetFont(HFONT hFont);
};