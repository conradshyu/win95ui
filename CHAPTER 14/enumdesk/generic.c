// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (C) 1993, 1994  Microsoft Corporation.  All Rights Reserved.
//
//  MODULE:   generic.c
//
//  PURPOSE:   Implement the windows procedure for the main application
//    windows.  Also implement the generic message and command dispatchers.
//
//  FUNCTIONS:
//    WndProc      - Processes messages for the main window.
//    MsgCommand   - Handle the WM_COMMAND messages for the main window.
//    MsgDestroy   - Handles the WM_DESTROY message by calling 
//                   PostQuitMessage().
//    CmdExit      - Handles the file exit command by calling destory 
//                   window on the main window.
//
//  COMMENTS:
//

#include <windows.h>            // required for all Windows applications
#include <windowsx.h>
#include "globals.h"            // prototypes specific to this application
#include <commctrl.h>
#include "shlobj.h"
 
LRESULT MsgLButtonDown(HWND hwnd, UINT uMessage, WPARAM wparam, LPARAM lparam);
LRESULT MsgMouseMove(HWND hwnd, UINT uMessage, WPARAM wparam, LPARAM lparam);
LRESULT MsgTimer(HWND hwnd, UINT uMessage, WPARAM wparam, LPARAM lparam);
LRESULT MsgNotify(HWND hwnd, UINT uMessage, WPARAM wparam, LPARAM lparam);

HWND WINAPI GetShellWindow(void);

// Main window message table definition.
MSD rgmsd[] =
{
    {WM_COMMAND, MsgCommand},
    {WM_CREATE,  MsgCreate},
	{WM_LBUTTONDOWN, MsgLButtonDown},
	{WM_MOUSEMOVE, MsgMouseMove},
	{WM_TIMER, MsgTimer},
    {WM_DESTROY, MsgDestroy},
    {WM_NOTIFY, MsgNotify}
};

MSDI msdiMain =
{
    sizeof(rgmsd) / sizeof(MSD),
    rgmsd,
    edwpWindow
};


#define IDD_ENUMDESKTOP 101

// Main window command table definition.
CMD rgcmd[] =
{
    {IDM_EXIT,  CmdExit},
    {IDD_ENUMDESKTOP,  CmdEnumDesktop},
    {IDM_ABOUT, CmdAbout}
};

CMDI cmdiMain =
{
    sizeof(rgcmd) / sizeof(CMD),
    rgcmd,
    edwpWindow
};

#define NUM_TIPS 6
#define MAX_ROWS 3
#define MAX_COLS 2
#define CX_COLUMN 100
#define CY_ROW    100

HWND ghScroll, g_hwndTran, ghLB;
int  giScrollMin;
int  giScrollMax;
HHOOK ghHook;
char *szTips[NUM_TIPS] =   // tip text
{
    "Cut", "Copy", "Paste", "Undo", "Open", "Save"
};
HWND g_hwndTT;    // handle of the tooltip
FARPROC lpOldProcEdit;
FARPROC lpOldProcButton;
HWND ghButton;
LPITEMIDLIST glpiHack;

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  PARAMETERS:
//    hwnd     - window handle
//    uMessage - message number
//    wparam   - additional information (dependant on message number)
//    lparam   - additional information (dependant on message number)
//
//  RETURN VALUE:
//    The return value depends on the message number.  If the message
//    is implemented in the message dispatch table, the return value is
//    the value returned by the message handling function.  Otherwise,
//    the return value is the value returned by the default window procedure.
//
//  COMMENTS:
//    Call the DispMessage() function with the main window's message dispatch
//    information (msdiMain) and the message specific information.
//

LRESULT CALLBACK WndProc(HWND   hwnd, 
                         UINT   uMessage, 
                         WPARAM wparam, 
                         LPARAM lparam)
{
    return DispMessage(&msdiMain, hwnd, uMessage, wparam, lparam);
}


//
//  FUNCTION: MsgCommand(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Handle the WM_COMMAND messages for the main window.
//
//  PARAMETERS:
//    hwnd     - window handle
//    uMessage - WM_COMMAND (Unused)
//    GET_WM_COMMAND_ID(wparam, lparam)   - Command identifier
//    GET_WM_COMMAND_HWND(wparam, lparam) - Control handle
//
//  RETURN VALUE:
//    The return value depends on the message number.  If the message
//    is implemented in the message dispatch table, the return value is
//    the value returned by the message handling function.  Otherwise,
//    the return value is the value returned by the default window procedure.
//
//  COMMENTS:
//    Call the DispCommand() function with the main window's command dispatch
//    information (cmdiMain) and the command specific information.
//

LRESULT MsgCommand(HWND hwnd, UINT uMessage, WPARAM wparam, LPARAM lparam)
{
    return DispCommand(&cmdiMain, hwnd, wparam, lparam);
}


LRESULT CALLBACK ButtonSubClassProc(HWND   hwnd, 
                                    UINT   uMessage, 
                                    WPARAM wparam, 
                                    LPARAM lparam)
{
    MSG msg;

    msg.message=uMessage;
    msg.hwnd=hwnd;
    msg.wParam=wparam;
    msg.lParam=lparam;

    switch (uMessage)
    {
        case WM_MOUSEMOVE:

  //          SendMessage(g_hwndTT, TTM_RELAYEVENT, 0, (LPARAM)(LPMSG)&msg);
            break;

        default:
            break;
    }

    return CallWindowProc(lpOldProcButton, 
                          hwnd, 
                          uMessage, 
                          wparam, 
                          lparam) ;

}

LRESULT MsgCreate(HWND hwnd, UINT uMessage, WPARAM wparam, LPARAM lparam)
{
   // HICON hIcon=LoadIconEx(hInst, "foo", 0, 0,  LR_DEFAULTCOLOR);

     ghLB=CreateWindow("listbox",            // See RegisterClass() call
                 "",          // Text for window title bar
                 WS_CHILD | LBS_NOTIFY | WS_VISIBLE | WS_BORDER, // Window style
                 145, 10,              // Position
                 250, 400,              // Size
                 hwnd,                // Parent
                 (HMENU)5,            // ID
                 (HINSTANCE)hInst,    // This instance owns this window
                 NULL                 // Don't need data in WM_CREATE
    );


    ghButton=CreateWindow("button",            // See RegisterClass() call
                 "EnumDesktop",        // Text for window title bar
                 WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE, // Window style
                 10, 10,              // Position
                 100, 20,              // Size
                 hwnd,                // Parent
                 (HMENU)IDD_ENUMDESKTOP,  // ID
                 (HINSTANCE)hInst,    // This instance owns this window
                 NULL                 // Don't need data in WM_CREATE
    );

    lpOldProcButton = (WNDPROC)GetWindowLong(ghButton, GWL_WNDPROC) ;

    SetWindowLong(ghButton, 
                  GWL_WNDPROC, 
                  (LONG)(WNDPROC)ButtonSubClassProc) ;

    return(0);
}

LRESULT MsgTimer(HWND hwnd, UINT uMessage, WPARAM wparam, LPARAM lparam)
{
//    MessageBeep(0);
    giScrollMax+=10;
    SetScrollRange(ghScroll, SB_CTL, giScrollMin, giScrollMax, TRUE);
    return(0);
}

//
//  FUNCTION: MsgDestroy(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Calls PostQuitMessage().
//
//  PARAMETERS:
//
//    hwnd      - Window handle  (Unused)
//    uMessage  - Message number (Unused)
//    wparam    - Extra data     (Unused)
//    lparam    - Extra data     (Unused)
//
//  RETURN VALUE:
//
//    Always returns 0 - Message handled
//
//  COMMENTS:
//
//

LRESULT MsgDestroy(HWND hwnd, UINT uMessage, WPARAM wparam, LPARAM lparam)
{
    PostQuitMessage(0);

    if (ghHook)
       UnhookWindowsHookEx(ghHook);

    return 0;
}

LRESULT MsgMouseMove(HWND hwnd, UINT uMessage, WPARAM wparam, LPARAM lparam)
{
   MSG msg;

   msg.message=uMessage;
   msg.hwnd=hwnd;
   msg.wParam=wparam;
   msg.lParam=lparam;

// SendMessage(g_hwndTT, TTM_RELAYEVENT, 0, (LPARAM)(LPMSG)&msg);

   return 0;
}

LRESULT MsgLButtonDown(HWND hwnd, UINT uMessage, WPARAM wparam, LPARAM lparam)
{
    LPCONTEXTMENU lpcm;
    LPSHELLFOLDER lpsf;
    LPITEMIDLIST  lpi;
    HRESULT       hr;
    char          szTemp[64];
    CMINVOKECOMMANDINFO cmi;
    DWORD               dwAttribs=0;
    int                 idCmd, iCount, i;
    HMENU               hMenu;
    MENUITEMINFO        mii;
    DWORD               dwEaten;

    hr=SHGetDesktopFolder(&lpsf);

    if (FAILED(hr))
       return 0;

    {
        i=(int)SendMessage(ghLB, LB_GETCURSEL, 0, 0L);
        if (LB_ERR==i)
        {
            lpsf->lpVtbl->Release(lpsf);
            return 0;
        }

        lpi=(LPITEMIDLIST)SendMessage(ghLB, LB_GETITEMDATA, (WPARAM)i, 0L);

        hr=lpsf->lpVtbl->GetUIObjectOf(lpsf, hwnd,
                                       1,  //Number of objects to get attributes of
                                       &lpi,
                                       &IID_IContextMenu,
                                       0,
                                       (LPVOID *)&lpcm);
        if (SUCCEEDED(hr))  
        {
				hMenu=CreatePopupMenu();
				if (hMenu)
				{
                    hr=lpcm->lpVtbl->QueryContextMenu(lpcm, hMenu,
                                                      0,
                                                      1,
                                                      0x7fff,
                                                      CMF_DEFAULTONLY);
                    if (SUCCEEDED(hr))
                    {
                        POINT pt;

                        pt.x=LOWORD(lparam);
                        pt.y=HIWORD(lparam);

                        ClientToScreen(hwnd, (LPPOINT)&pt);

                        TrackPopupMenu(hMenu, 
                                       TPM_LEFTALIGN, 
                                       pt.x, 
                                       pt.y,
                                       0,
                                       hwnd,
                                       NULL);

                        idCmd=GetMenuDefaultItem(hMenu, MF_BYCOMMAND, 0);
/*                      mii.cbSize=sizeof(mii);
                        iCount=GetMenuItemCount(hMenu);
                        for (i=0; i<iCount; i++)
                        {
                           GetMenuString(hMenu, i, szTemp, sizeof(szTemp), MF_BYPOSITION);
                           MessageBox(hwnd, szTemp, "GAK", MB_OK);
                        }
                        GetMenuItemInfo(hMenu, 0, MF_BYPOSITION, &mii);
*/        
                        if (idCmd)
                        {
                            cmi.cbSize=sizeof(CMINVOKECOMMANDINFO);
                       	    cmi.fMask=0;
                            cmi.hwnd=hwnd;
                           	cmi.lpVerb=MAKEINTRESOURCE(idCmd-1);
                            cmi.lpParameters=NULL;
          	                cmi.lpDirectory=NULL;
                            cmi.nShow=SW_SHOWNORMAL;
                            cmi.dwHotKey=0;
                            cmi.hIcon=NULL;
                            hr=lpcm->lpVtbl->InvokeCommand(lpcm, &cmi);
                            if (SUCCEEDED(hr))  
                                ;  //Do nothing
                            else
                            {
                                MessageBox(hwnd, 
                                           "InvokeCommand failed!!", 
                                           "Shell Extension Sample", 
                                           MB_OK);
                                wsprintf(szTemp, "hr=%lx", hr);
                	            MessageBox(hwnd, 
        	                               szTemp, 
        	                               "Shell Extension Sample", 
        	                               MB_OK);
                            }
                        }
                    }
                    DestroyMenu(hMenu);
                }
                lpcm->lpVtbl->Release(lpcm);
        } 
        else
        {
            MessageBox(hwnd, 
                       "GetUIObjectOf failed!!", 
                       "Shell Extension Sample", 
                       MB_OK);
            wsprintf(szTemp, "hr=%lx", hr);
            MessageBox(hwnd, 
        	           szTemp, 
        	           "Shell Extension Sample", 
        	           MB_OK);
        }
    }

    lpsf->lpVtbl->Release(lpsf);

    return 0;
}

//
//  FUNCTION: CmdEnumDesktop(HWND, WORD, WORD, HWND)
//
//  PURPOSE: Enumerate the objects on the desktop
//
//  PARAMETERS:
//    hwnd     - The window.
//    wCommand - IDD_ENUMDESKTOP (unused)
//    wNotify  - Notification number (unused)
//    hwndCtrl - NULL (unused)
//
//  RETURN VALUE:
//    Always returns 0 - command handled.
//
//  COMMENTS:
//
//

LRESULT CmdEnumDesktop(HWND hwnd, WORD wCommand, WORD wNotify, HWND hwndCtrl)
{
   
    return 0;
}

//
//  FUNCTION: CmdExit(HWND, WORD, WORD, HWND)
//
//  PURPOSE: Exit the application.
//
//  PARAMETERS:
//    hwnd     - The window.
//    wCommand - IDM_EXIT (unused)
//    wNotify  - Notification number (unused)
//    hwndCtrl - NULL (unused)
//
//  RETURN VALUE:
//    Always returns 0 - command handled.
//
//  COMMENTS:
//
//

LRESULT CmdExit(HWND hwnd, WORD wCommand, WORD wNotify, HWND hwndCtrl)
{
/*
    int row, col;   // rows and columns
    TOOLINFO ti;    // tool information
    int id = 0;     // offset to string identifiers
    RECT r;
    char szBuff[64];
    WORD wCount;

    // Ensure the common control DLL is loaded and create a tooltip
    // control.
    InitCommonControls();

    DragAcceptFiles(hwnd, TRUE);

    GetClientRect(hwnd, &r);

    g_hwndTT = CreateWindow(TOOLTIPS_CLASS,
                          (LPSTR) NULL, 
                          WS_POPUP,
                          CW_USEDEFAULT, 
                          CW_USEDEFAULT, 
                          CW_USEDEFAULT, 
                          CW_USEDEFAULT, 
                          hwnd, 
                          (HMENU)NULL, 
                          hInst, 
                          NULL);

    if (g_hwndTT == (HWND) NULL)
        return 0;

    // Divide the client area into a grid of rectangles and add each
    // rectangle to the tooltip.
    for (row = 0; row < MAX_ROWS ; row++ )
        for (col = 0; col < MAX_COLS; col++) {
            ti.cbSize = sizeof(TOOLINFO);
            ti.uFlags = 0;
            ti.hwnd = hwnd;
            ti.hinst = hInst;
//            ti.uId = (UINT)id;
            ti.uId = (UINT) id++;
//            ti.lpszText = (LPSTR) szTips[id++];
            ti.lpszText = LPSTR_TEXTCALLBACK;
            ti.rect.left = col * CX_COLUMN;
            ti.rect.top = row * CY_ROW;
            ti.rect.right = ti.rect.left + CX_COLUMN;
            ti.rect.bottom = ti.rect.top + CY_ROW;

            if (!SendMessage(g_hwndTT,
                             TTM_ADDTOOL, 
                             0,
                             (LPARAM)(LPTOOLINFO)&ti))
                return 0;
        }
*/
//    int iRetType;
//
//    iRetType=GetKeyboardType(0);
//   iRetType=GetKeyboardType(1);
//    iRetType=GetKeyboardType(2);

//    DestroyWindow(hwnd);

    BROWSEINFO bi;
    char szFolder[64];
	LPCITEMIDLIST lpidl;
	LPMALLOC pMalloc;
	HRESULT hr;

    bi.hwndOwner=hwnd;
    bi.pidlRoot=NULL;
    bi.pszDisplayName=szFolder;
    bi.lpszTitle="Hello Folder Finder!";
    bi.ulFlags=BIF_RETURNONLYFSDIRS;
    bi.lpfn=NULL;
    bi.lParam=0;
    
    lpidl=SHBrowseForFolder(&bi);
	if (lpidl)
	{
		if (SHGetPathFromIDList(lpidl, szFolder))
	        MessageBox(hwnd, szFolder, "Test", MB_OK);
		else
	        MessageBox(hwnd, "SHGetPathFromIDList failed", "Test", MB_OK);
		hr=SHGetMalloc(&pMalloc);
		if (SUCCEEDED(hr))
		{
            pMalloc->lpVtbl->Free(pMalloc, (LPVOID *)lpidl);
	        MessageBox(hwnd, "SHGetMalloc succeeded", "Test", MB_OK);
		}
		else
	        MessageBox(hwnd, "SHGetMalloc failed", "Test", MB_OK);
        pMalloc->lpVtbl->Release(pMalloc);
	}

    return 0;
}

//
//  FUNCTION: MsgNotify(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  WM_NOTIFY is sent to the parent window to get the
//            tooltip text assoc'd with that toolbar button.
//
//  PARAMETERS:
//
//    hwnd      - Window handle  (Unused)
//    uMessage  - Message number (Unused)
//    wparam    - Extra data     (Unused)
//    lparam    - TOOLTIPTEXT FAR*
//
//  RETURN VALUE:
//    Always returns 0 - Message handled
//
//
//  COMMENTS:
//    This message fills in the lpszText field of the TOOLTIPTEXT
//    structure if code == TTN_NEEDTEXT
//

LRESULT MsgNotify(HWND hwnd, UINT uMessage, WPARAM wparam, LPARAM lparam)
{
    LPTOOLTIPTEXT lpToolTipText;
    static char   szBuffer[64];

    lpToolTipText = (LPTOOLTIPTEXT)lparam;

    MessageBeep(0);

    if (lpToolTipText->hdr.code == TTN_NEEDTEXT)
    {
        lpToolTipText->lpszText = (LPSTR)szTips[lpToolTipText->hdr.idFrom];
    }

    return 0;
}
