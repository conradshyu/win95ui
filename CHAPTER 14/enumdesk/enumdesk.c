// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (C) 1993-1995  Microsoft Corporation.  All Rights Reserved.
//
//  MODULE:   enumdesk.c
//
//  PURPOSE:  Implement the windows procedure for the main application
//    windows.  Also implement the generic message and command dispatchers.
//
//  FUNCTIONS:
//    WndProc         - Processes messages for the main window.
//    MsgCommand      - Handle the WM_COMMAND messages for the main window.
//    MsgDestroy      - Handles the WM_DESTROY message by calling 
//                      PostQuitMessage().
//    CmdExit         - Handles the file exit command by calling destory 
//                      window on the main window.
//
//  COMMENTS:
//

#include <windows.h>                // required for all Windows applications.
#include <windowsx.h>
#include <commctrl.h>               // TreeView declarations live here.
#include <shlobj.h>
#include "globals.h"                // prototypes specific to this application.
#include "resource.h"
#include "treeview.h"
#include "listview.h"

HWND   hwndTreeView;                // hwnd of TreeView Control.
BOOL   bOutaHere=FALSE;
extern HWND hwndLV;
static int cxSplitter;              // width of splitter bar
static RECT rcSplit;
static HDC hdcSplit = NULL;


extern HWND CreateTreeView(HWND hwndParent, int iID, DWORD dwStyle);
extern HWND WINAPI CreateListView(HWND hwndParent);
extern int GetIcon(LPITEMIDLIST lpi, UINT uFlags);

extern void FillTreeView(HWND hwndTreeView, 
                         LPSHELLFOLDER lpsf,
                         LPITEMIDLIST  lpiFullQualified,
                         HTREEITEM hParent);

extern BOOL PopulateListView(HWND hwndLV, 
                             LPTVITEMDATA lptvid,
                             LPSHELLFOLDER lpsf);

extern BOOL GetName(LPSHELLFOLDER lpsf,
                    LPITEMIDLIST  lpi,
			        DWORD         dwFlags,
                    LPSTR         lpFriendlyName);

extern void SwitchView(HWND hwndLV, DWORD dwView);

extern LPITEMIDLIST GetFullyQualPidl(LPSHELLFOLDER lpsf, LPITEMIDLIST lpi);

extern LPDROPSOURCE CreateDropSource(void);

extern LPITEMIDLIST ConcatPidls(LPCITEMIDLIST pidl1, LPCITEMIDLIST pidl2);

extern int CALLBACK TreeViewCompareProc(LPARAM lparam1, 
                                        LPARAM lparam2,
                                        LPARAM lparamSort);

// Main window message table definition.
MSD rgmsd[] =
{
    {WM_COMMAND,     MsgCommand},
    {WM_DESTROY,     MsgDestroy},
    {WM_CREATE,      MsgCreate},
    {WM_MOUSEMOVE,   MsgMouseMove},
    {WM_LBUTTONDOWN, MsgLButtonDown},
    {WM_LBUTTONUP,   MsgLButtonUp},
    {WM_NOTIFY,      MsgNotify},  
    {WM_SIZE,        MsgSize}
};

MSDI msdiMain =
{
    sizeof(rgmsd) / sizeof(MSD),
    rgmsd,
    edwpWindow
};


// Main window command table definition.
CMD rgcmd[] =
{
    {IDM_EXIT,       CmdExit},
    {IDM_ABOUT,      CmdAbout},
    {IDM_FILL,       CmdFill},
    {IDM_LARGEICONS, CmdLargeIcons},
    {IDM_SMALLICONS, CmdSmallIcons},
    {IDM_LIST,       CmdList}
};

CMDI cmdiMain =
{
    sizeof(rgcmd) / sizeof(CMD),
    rgcmd,
    edwpWindow
};


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

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMessage, WPARAM wparam, LPARAM lparam)
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

//
//  FUNCTION: MsgCreate(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Creates TreeView Control, and posts "Fill" message.
//
//  PARAMETERS:
//
//    hwnd      - Window handle  (Unused)
//    uMessage  - Message number (Unused)
//    wparam    - not used
//    lparam    - not used
//
//  RETURN VALUE:
//
//    Always returns 0 - Message handled
//
//  COMMENTS:
//
//

LRESULT MsgCreate(HWND hwnd, UINT uMessage, WPARAM wparam, LPARAM lparam)
{
    // Create the TreeView control, with lines and buttons, even at
    // the root level.

    // Save this value for later
    cxSplitter = GetSystemMetrics(SM_CXEDGE);
    if (!cxSplitter)
        cxSplitter = 2;

    hwndTreeView = CreateTreeView(hwnd, 
                                  IDD_TREEVIEW, 
                                  TVS_HASLINES | TVS_HASBUTTONS | 
                                  TVS_LINESATROOT | TVS_HASLINES |
                                  TVS_SHOWSELALWAYS |
                                  WS_VISIBLE | WS_CHILD | WS_BORDER);

    hwndLV = CreateListView(hwnd);

    // Post a message to fill the control, or nix app if
    // the creation failed.

    if (!hwndTreeView || !hwndLV)
        PostMessage(hwnd, WM_COMMAND, IDM_EXIT, 0L );
    else
        PostMessage(hwnd, WM_COMMAND, IDM_FILL, 0L );

    return 0;
}

//
//  FUNCTION: MsgLButtonDown(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Initiates splitter bar stuff
//
//  PARAMETERS:
//
//    hwnd      - Window handle  (Unused)
//    uMessage  - Message number (Unused)
//    wparam    - Not used.
//    lparam    - Not used.
//
//  RETURN VALUE:
//
//    Always returns 0 - Message handled
//
//  COMMENTS:
//
//

LRESULT MsgLButtonDown(HWND hwnd, UINT uMessage, WPARAM wparam, LPARAM lparam)
{
    #define xPos ((int)(short)LOWORD(lparam))

    SetCapture(hwnd);

    GetClientRect(hwnd, &rcSplit);

    // Calculate initial position
    rcSplit.left = min(max(50, xPos - cxSplitter/2), rcSplit.right - 50) + 1;

    // Get a DC (also used as a flag indicating we have capture)
    if (hdcSplit)
        ReleaseDC(hwnd, hdcSplit);
    hdcSplit = GetDC(hwnd);

    // Draw splitter bar in initial position
    PatBlt(hdcSplit, rcSplit.left, 0, cxSplitter, rcSplit.bottom, DSTINVERT);

    return 0;
}


//
//  FUNCTION: MsgMouseMove(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Moves splitter bar
//
//  PARAMETERS:
//
//    hwnd      - Window handle  (Unused)
//    uMessage  - Message number (Unused)
//    wparam    - Not used.
//    lparam    - Not used.
//
//  RETURN VALUE:
//
//    Always returns 0 - Message handled
//
//  COMMENTS:
//
//

LRESULT MsgMouseMove(HWND hwnd, UINT uMessage, WPARAM wparam, LPARAM lparam)
{
    #define xPos ((int)(short)LOWORD(lparam))

    if (hdcSplit)
    {
        // Erase previous bar
        PatBlt(hdcSplit, rcSplit.left, 0, cxSplitter, rcSplit.bottom, DSTINVERT);

        // Calculate new position
        rcSplit.left = min(max(50, xPos - cxSplitter/2), rcSplit.right - 50) + 1;

        // Draw bar in new position
        PatBlt(hdcSplit, rcSplit.left, 0, cxSplitter, rcSplit.bottom, DSTINVERT);
    }
    return 0;
}


//
//  FUNCTION: MsgLButtonUp(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Finishes splitter bar moving and resized child windows.
//
//  PARAMETERS:
//
//    hwnd      - Window handle  (Unused)
//    uMessage  - Message number (Unused)
//    wparam    - Not used.
//    lparam    - Not used.
//
//  RETURN VALUE:
//
//    Always returns 0 - Message handled
//
//  COMMENTS:
//
//

LRESULT MsgLButtonUp(HWND hwnd, UINT uMessage, WPARAM wparam, LPARAM lparam)
{
    #define xPos ((int)(short)LOWORD(lparam))

    if (hdcSplit)
    {
        // Erase previous bar
        PatBlt(hdcSplit, rcSplit.left, 0, cxSplitter, rcSplit.bottom, DSTINVERT);

        // Calculate new position
        rcSplit.left = min(max(50, xPos - cxSplitter/2), rcSplit.right - 50) + 1;

        // Clean up
        ReleaseCapture();
        ReleaseDC(hwnd, hdcSplit);
        hdcSplit = NULL;

        rcSplit.left -= cxSplitter/2;

        if (hwndTreeView)
            SetWindowPos(hwndTreeView,
                         NULL,
                         0, 0,
                         rcSplit.left,
                         rcSplit.bottom,
                         SWP_NOZORDER);

        rcSplit.left += cxSplitter;

        if (hwndLV)
            SetWindowPos(hwndLV,
                         NULL,
                         rcSplit.left, 0,
                         rcSplit.right - rcSplit.left,
                         rcSplit.bottom,
                         SWP_NOZORDER);
    }
    return 0;
}


//
//  FUNCTION: MsgDestroy(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Calls PostQuitMessage(), cleans up image list.
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
    bOutaHere = TRUE;
    PostQuitMessage(0);
    return 0;
}


//
//  FUNCTION: DoTheMenuThing(HWND hwnd, 
//                           LPSHELLFOLDER lpsfParent,
//                           LPITEMIDLIST  lpi,
//                           LPPOINT lppt)
//
//  PURPOSE: Displays a popup context menu, given a parent shell folder,
//           relative item id and screen location.
//
//  PARAMETERS:
//
//    hwnd       - Parent window handle
//    lpsfParent - Pointer to parent shell folder.
//    lpi        - Pointer to item id that is relative to lpsfParent
//    lppt       - Screen location of where to popup the menu.
//
//  RETURN VALUE:
//
//    Returns TRUE on success, FALSE on failure
//
//  COMMENTS:
//
//

BOOL DoTheMenuThing(HWND hwnd, 
                    LPSHELLFOLDER lpsfParent,
                    LPITEMIDLIST  lpi,
                    LPPOINT lppt)
{
    LPCONTEXTMENU lpcm;
    HRESULT       hr;
    char          szTemp[64];
    CMINVOKECOMMANDINFO cmi;
    DWORD               dwAttribs=0;
    int                 idCmd;
    HMENU               hMenu;
    BOOL                bSuccess=TRUE;

    hr=lpsfParent->lpVtbl->GetUIObjectOf(lpsfParent, hwnd,
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
                                            CMF_EXPLORE);
          if (SUCCEEDED(hr))
          {
             idCmd=TrackPopupMenu(hMenu, 
                                  TPM_LEFTALIGN | TPM_RETURNCMD | TPM_RIGHTBUTTON, 
                                  lppt->x, 
                                  lppt->y,
                                  0,
                                  hwnd,
                                  NULL);

             if (idCmd)
             {
                cmi.cbSize = sizeof(CMINVOKECOMMANDINFO);
                cmi.fMask  = 0;
                cmi.hwnd   = hwnd;
                cmi.lpVerb = MAKEINTRESOURCE(idCmd-1);
                cmi.lpParameters = NULL;
      	        cmi.lpDirectory  = NULL;
                cmi.nShow        = SW_SHOWNORMAL;
                cmi.dwHotKey     = 0;
                cmi.hIcon        = NULL;
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
          else
             bSuccess = FALSE;

          DestroyMenu(hMenu);
       }
       else
          bSuccess = FALSE;

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

       bSuccess = FALSE;
    }

    return bSuccess;
}



//
//  FUNCTION: MsgNotify(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Handles notifications from TreeView and ListView controls
//
//  PARAMETERS:
//
//    hwnd      - Window handle  (Unused)
//    uMessage  - Message number (Unused)
//    wparam    - control id
//    lparam    - points to an NMHDR (Notify Message Header) which 
//                is overloaded with a NM_TREEVIEW structure:
//     
//
//  RETURN VALUE:
//
//    Always returns 0 - Message handled
//
//  COMMENTS:
//
//
LRESULT MsgNotify(HWND hwnd, UINT uMessage, WPARAM wparam, LPARAM lparam)
{
   POINT pt;
   NM_TREEVIEW *pnmtv   = (NM_TREEVIEW *)lparam;
   NM_LISTVIEW *pnmlv   = (NM_LISTVIEW *)lparam;
   TV_HITTESTINFO tvhti;
   LV_HITTESTINFO lvhti;
   LPTVITEMDATA   lptvid;  //Long pointer to TreeView item data
   LPLVITEMDATA   lplvid;  //Long pointer to ListView item data
   LPDATAOBJECT   lpdo;
   HRESULT        hr;
   LPMALLOC       lpMalloc;
   LPSHELLFOLDER  lpsf2=0;
   TV_ITEM        tvi;
   LV_ITEM        lvi;
   DWORD          dwEffect;
   static char    szBuff[MAX_PATH];
   LV_DISPINFO    *plvdi;
   TV_SORTCB      tvscb;

   switch (pnmtv->hdr.idFrom)
   {
      case IDD_TREEVIEW:

		 switch (pnmtv->hdr.code)   
		 {
		    case NM_RCLICK:
		
		       GetCursorPos((LPPOINT)&pt);
		       ScreenToClient(hwnd, &pt);
		       tvhti.pt=pt;
		       TreeView_HitTest(hwndTreeView, &tvhti);
		       TreeView_SelectItem(hwndTreeView, tvhti.hItem);
		       if (tvhti.flags & TVHT_ONITEMLABEL)
		       {
		           ClientToScreen(hwnd, &pt);
		           tvi.mask=TVIF_PARAM;
		           tvi.hItem=tvhti.hItem;
		
		           if (!TreeView_GetItem(hwndTreeView, &tvi))
		              return 0;
		
		           lptvid=(LPTVITEMDATA)tvi.lParam;
		
		           DoTheMenuThing(hwnd, lptvid->lpsfParent, lptvid->lpi, &pt);
		       }
		       break;
		
		    case TVN_DELETEITEM:
		
		       //Let's free the memory for the TreeView item data...
		
		       hr=SHGetMalloc(&lpMalloc);
		       if (FAILED(hr))
		          break;
		
		       lptvid=(LPTVITEMDATA)pnmtv->itemOld.lParam;
               lptvid->lpsfParent->lpVtbl->Release(lptvid->lpsfParent);
               lpMalloc->lpVtbl->Free(lpMalloc, lptvid->lpi);  
               lpMalloc->lpVtbl->Free(lpMalloc, lptvid->lpifq);  
		       lpMalloc->lpVtbl->Free(lpMalloc, lptvid);  
		       lpMalloc->lpVtbl->Release(lpMalloc);
		       break;
		
			case TVN_SELCHANGED:

		       //Do this only if we are not exiting the application...

               if (!bOutaHere)
               {
                  lptvid=(LPTVITEMDATA)pnmtv->itemNew.lParam;
                  hr=lptvid->lpsfParent->lpVtbl->BindToObject(lptvid->lpsfParent,
		                                                      lptvid->lpi,
		                                                      0,
		                                                      &IID_IShellFolder,
		                                                      (LPVOID *)&lpsf2);
		
                  if (SUCCEEDED(hr))
                  {
                     PopulateListView(hwndLV,
                                      lptvid,
				                      lpsf2);

                     lpsf2->lpVtbl->Release(lpsf2);
                  }
               }

		       break;
		
		    case TVN_ITEMEXPANDING:
		
		       if ((pnmtv->itemNew.state & TVIS_EXPANDEDONCE))
		          break;
		
		       lptvid=(LPTVITEMDATA)pnmtv->itemNew.lParam;
		
		       hr=lptvid->lpsfParent->lpVtbl->BindToObject(lptvid->lpsfParent,
		                                                   lptvid->lpi,
		                                                   0,
		                                                   &IID_IShellFolder,
		                                                   (LPVOID *)&lpsf2);
		
		       if (SUCCEEDED(hr))
		       {
		          FillTreeView(hwndTreeView,
		                       lpsf2,
		                       lptvid->lpifq,
		                       pnmtv->itemNew.hItem);
		       }
		
               tvscb.hParent     = pnmtv->itemNew.hItem;
               tvscb.lpfnCompare = TreeViewCompareProc;
               tvscb.lParam      = 0;

		       TreeView_SortChildrenCB(hwndTreeView, &tvscb, 0);
		
		       break;
		  
		       default:
		           break;
		 }

		 break;

	  case IDD_LISTVIEW:

	     switch (pnmlv->hdr.code)
		 {
		    case NM_RCLICK:
            case NM_DBLCLK:
		
		       GetCursorPos((LPPOINT)&pt);
		       ScreenToClient(hwndLV, &pt);
		       lvhti.pt=pt;
		       ListView_HitTest(hwndLV, &lvhti);
		       if (lvhti.flags & LVHT_ONITEM)
		       {
		           ClientToScreen(hwndLV, &pt);
		           lvi.mask = LVIF_PARAM;
                   lvi.iItem = lvhti.iItem;
                   lvi.iSubItem = 0;
		
		           if (!ListView_GetItem(hwndLV, &lvi))
		              return 0;
		
		           lplvid=(LPLVITEMDATA)lvi.lParam;
		
                   if (pnmlv->hdr.code==NM_RCLICK)
                      DoTheMenuThing(hwnd, lplvid->lpsfParent, lplvid->lpi, &pt);
                   else
                   {
                      if (!(lplvid->ulAttribs & SFGAO_FOLDER))
                      {
                         SHELLEXECUTEINFO sei =
                         {
                            sizeof(SHELLEXECUTEINFO),
                            SEE_MASK_INVOKEIDLIST,	// fMask
                            hwnd,                  // hwnd of parent
                            "Open",                // lpVerb
                            NULL,	                // lpFile
                            "",
                            "",                     // lpDirectory
                            SW_SHOWNORMAL,	         // nShow
                            hInst,                  // hInstApp
                            (LPVOID)NULL,           // lpIDList...will set below
                            NULL,                   // lpClass
                            0,			             // hkeyClass
                            0,				         // dwHotKey
                            NULL			         // hIcon
                         };

                         sei.lpIDList=GetFullyQualPidl(lplvid->lpsfParent, lplvid->lpi);

                         ShellExecuteEx(&sei);
                      }
                      else
                      {
                         MessageBox(hwnd, "Clicked on folder", "ENUMDESK", MB_OK);
                      }
                   }
		       }
		       break;

            case LVN_DELETEITEM:


		       //Let's free the memory for the ListView item data...
		
		       hr=SHGetMalloc(&lpMalloc);
		       if (FAILED(hr))
		          break;
		
		       lvi.mask = LVIF_PARAM;
               lvi.iItem = pnmlv->iItem;
               lvi.iSubItem = 0;
		
		       if (!ListView_GetItem(hwndLV, &lvi))
		          return 0;
			   lplvid=(LPLVITEMDATA)lvi.lParam;

               lplvid->lpsfParent->lpVtbl->Release(lplvid->lpsfParent);
               lpMalloc->lpVtbl->Free(lpMalloc, lplvid->lpi);  
		       lpMalloc->lpVtbl->Free(lpMalloc, lplvid);  
		       lpMalloc->lpVtbl->Release(lpMalloc);
	           break;

            case LVN_GETDISPINFO:

               plvdi  = (LV_DISPINFO *)lparam;
               lplvid = (LPLVITEMDATA)plvdi->item.lParam;

               if (plvdi->item.mask & LVIF_IMAGE)
               {
                  TV_ITEM tvi;
                  HTREEITEM hti;

                  hti = TreeView_GetSelection(hwndTreeView);
                  tvi.mask = TVIF_PARAM;
                  tvi.hItem = hti;

                  TreeView_GetItem(hwndTreeView, &tvi);

                  lptvid=(LPTVITEMDATA)tvi.lParam;

                  plvdi->item.iImage = GetIcon(ConcatPidls(lptvid->lpifq, lplvid->lpi),
                                               SHGFI_PIDL | 
                                               SHGFI_SYSICONINDEX | 
                                               SHGFI_SMALLICON);

                  if (lplvid->ulAttribs & SFGAO_LINK)
                  {
                      plvdi->item.mask |= LVIF_STATE;
                      plvdi->item.stateMask = LVIS_OVERLAYMASK;
                      plvdi->item.state = INDEXTOOVERLAYMASK(2);
                  }

               }

               if (plvdi->item.mask & LVIF_TEXT)
                   GetName(lplvid->lpsfParent, lplvid->lpi, SHGDN_NORMAL, plvdi->item.pszText);

               break;

            case LVN_BEGINDRAG:
            case LVN_BEGINRDRAG:

		       lvi.mask = LVIF_PARAM;
               lvi.iItem = pnmlv->iItem;
               lvi.iSubItem = 0;
		
		       if (!ListView_GetItem(hwndLV, &lvi))
		          return 0;
			   lplvid=(LPLVITEMDATA)lvi.lParam;

               hr=lplvid->lpsfParent->lpVtbl->GetUIObjectOf(lplvid->lpsfParent, 
                                                            hwnd,
                                                            1,  //Number of objects to get attributes of
                                                            &lplvid->lpi,
                                                            &IID_IDataObject,
                                                            0,
                                                            (LPVOID *)&lpdo);
               if (SUCCEEDED(hr))  
               {
                  LPDROPSOURCE lpds=CreateDropSource();

                  if (lpds)
                     DoDragDrop(lpdo,
                                lpds,
                                DROPEFFECT_COPY | DROPEFFECT_MOVE | DROPEFFECT_LINK,
                                &dwEffect);     

                  lpdo->lpVtbl->Release(lpdo);
                  lpds->lpVtbl->Release(lpds);
               }

               break;

			default:
			   
			   break;
		 }

		 break;

	  default:
	   
	     break;
   }

   return 0;
}


//
//  FUNCTION: MsgSize(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Resizes TreeView Control
//
//  PARAMETERS:
//
//    hwnd      - Window handle  (Unused)
//    uMessage  - Message number (Unused)
//    wparam    - Not used.
//    lparam    - Not used.
//
//  RETURN VALUE:
//
//    Always returns 0 - Message handled
//
//  COMMENTS:
//
//

LRESULT MsgSize(HWND hwnd, UINT uMessage, WPARAM wparam, LPARAM lparam)
{
    #define cxClient ((int)(short)LOWORD(lparam))
    #define cyClient ((int)(short)HIWORD(lparam))
 
    RECT rc;    // Client area rect

    // Resize the TreeView control

    if (hwndTreeView)
    {                
        GetWindowRect(hwndTreeView, &rc);
        ScreenToClient(hwnd, (LPPOINT)&rc.right);
        rc.right = max(50, min(rc.right, cxClient - 50));

        SetWindowPos(hwndTreeView,
                     NULL,
                     0, 0,
                     rc.right,
                     cyClient,
                     SWP_NOZORDER);
    }

    // Resize the ListView control

    rc.right += cxSplitter;

    if (hwndLV)
        SetWindowPos(hwndLV,
                     NULL,
                     rc.right, 0,
                     cxClient - rc.right,
                     cyClient,
                     SWP_NOZORDER);

    return 0;
}

//
//  FUNCTION: CmdFill
//
//  PURPOSE: Fill TreeView Control with initial items.  Basically, this is
//           the root of the name space.
//
//  PARAMETERS:
//    hwnd     - window handle
//    wCommand - IDM_FILL
//    wNotify  - Not Used.
//    hwndCtrl - Not Used.
//
//  RETURN VALUE:
//    Always 0.
//
//  COMMENTS:
//    This calls the FillTreeView function in INI.C to fill the
//    TreeView control. The message to invoke this function is posted
//    at startup in MsgCreate.

LRESULT CmdFill(HWND hwnd, WORD wCommand, WORD wNotify, HWND hwndCtrl)
{
    LPSHELLFOLDER lpsf=0;
    LPITEMIDLIST  lpi=0;
    HRESULT hr;
    
    hr=SHGetDesktopFolder(&lpsf);

    if (SUCCEEDED(hr))
    {
       TreeView_DeleteAllItems(hwndTreeView);

       FillTreeView(hwndTreeView,
                    lpsf,
                    NULL,
                    TVI_ROOT);
    }
        
    if (lpsf) lpsf->lpVtbl->Release(lpsf);
                     
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
    DestroyWindow(hwnd);
    return 0;
}

//
//  FUNCTION: CmdLargeIcons(HWND, WORD, WORD, HWND)
//
//  PURPOSE: 
//
//  PARAMETERS:
//    hwnd      - Window handle
//    wCommand  - IDM_LARGEICONS (unused)
//    wNotify   - Notification number (unused)
//    hwndCtrl  - NULL (unused)
//
//  RETURN VALUE:
//
//    Always returns 0 - Message handled
//
//  COMMENTS:
//   
//

LRESULT CmdLargeIcons(HWND hwnd, WORD wCommand, WORD wNotify, HWND hwndCtrl)
{
    SwitchView(GetDlgItem(hwnd, IDD_LISTVIEW), LVS_ICON);
    return 0;
}


//
//  FUNCTION: CmdSmallIcons(HWND, WORD, WORD, HWND)
//
//  PURPOSE: 
//
//  PARAMETERS:
//    hwnd      - Window handle
//    wCommand  - IDM_SMALLICONS (unused)
//    wNotify   - Notification number (unused)
//    hwndCtrl  - NULL (unused)
//
//  RETURN VALUE:
//
//    Always returns 0 - Message handled
//
//  COMMENTS:
//   
//

LRESULT CmdSmallIcons(HWND hwnd, WORD wCommand, WORD wNotify, HWND hwndCtrl)
{
    SwitchView(GetDlgItem(hwnd, IDD_LISTVIEW), LVS_SMALLICON);
    return 0;
}


//
//  FUNCTION: CmdList(HWND, WORD, WORD, HWND)
//
//  PURPOSE: 
//
//  PARAMETERS:
//    hwnd      - Window handle
//    wCommand  - IDM_LIST (unused)
//    wNotify   - Notification number (unused)
//    hwndCtrl  - NULL (unused)
//
//  RETURN VALUE:
//
//    Always returns 0 - Message handled
//
//  COMMENTS:
//   
//

LRESULT CmdList(HWND hwnd, WORD wCommand, WORD wNotify, HWND hwndCtrl)
{
    SwitchView(GetDlgItem(hwnd, IDD_LISTVIEW), LVS_LIST);
    return 0;
}

