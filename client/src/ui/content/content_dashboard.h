#pragma once

#include <string>
#include "ui/content/content.h"

using namespace std;

class content_dashboard : public content
{
    private:
        static LRESULT CALLBACK ContentProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData);
        HFONT hFont;

    public: 
        content_dashboard(HWND hwndParent, int lpParam, int x, int y, int width, int height);
        wstring TodaySale, YesterdaySale, ThisWeekSale;
        COLORREF TextColorRGB = RGB(0, 0, 0);
};