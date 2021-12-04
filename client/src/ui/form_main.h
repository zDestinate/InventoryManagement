#pragma once

#include <Windows.h>
#include "ui/form_menubar.h"
#include "ui/form_menutop.h"
#include "ui/content/content.h"
#include "ui/content/content_dashboard.h"
#include "ui/content/content_item.h"
#include "ui/content/content_pointofsale.h"
#include "ui/content/content_promotion.h"
#include "ui/content/content_accounts.h"
#include "ui/content/content_settings.h"

class form_main
{
    private:
        HINSTANCE hInstMainWin;
        HWND hwndLogin;

        int MenuTopHeight = 80;
        form_menutop* Menu_Top = nullptr;

        int ItemMinWidth = 55;
        int ItemMaxWidth = 220;
        form_menubar* Menu_Bar = nullptr;

        int FocusContentFormObj;
        content* FocusContent = nullptr;
        content_dashboard* ContentDashboard = nullptr;
        content_item* ContentItem = nullptr;
        content_pointofsale* ContentPointOfSale = nullptr;
        content_promotion* ContentPromotion = nullptr;
        content_accounts* ContentAccounts = nullptr;
        content_settings* ContentSettings = nullptr;


        bool CenterWindow(HWND hwndWindow);
        void UpdateContent(content* Content, bool bItemExtended, int nMainWidth, int nMainHeight, int MaxWidth);

        static LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
        LRESULT CALLBACK RealWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

    public:
        HWND hwndMain;

        form_main(HWND hwndLogin);
        int CreateFormMain();

        void SetFocusContent(int FormObj);
        
};