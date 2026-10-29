// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (C) 1993-1995  Microsoft Corporation.  All Rights Reserved.
//
//  MODULE:   listview.c
//
//  PURPOSE:   Implement the windows procedure for the main application
//    windows.  Also implement the generic message and command dispatchers.
//
//  FUNCTIONS:
//    WndProc      - Processes messages for the main window.
//    MsgCreate    - Handle the WM_CREATE message 
//    MsgCommand   - Handle the WM_COMMAND messages for the main window.
//    MsgDestroy   - Handles the WM_DESTROY message by calling 
//                   PostQuitMessage().
//    CmdLargeIcons- Switch main view to large icons
//    CmdSmallIcons- Switch main view to small icons
//    CmdList      - Switch main view to list view
//    CmdDetails   - Switch main view to details view
//    CmdDragList  - Displays the "DragList" dialog box
//    CmdExit      - Handles the file exit command by calling destory 
//                   window on the main window.
//
//  COMMENTS:
//

#include <windows.h>            // required for all Windows applications
#include <windowsx.h>
#include <commctrl.h>
#include <shlobj.h>
#include "globals.h"            // prototypes specific to this application
#include "listview.h"           // prototypes and defines specific to the
                                // listview control

//Function Prototypes

BOOL PopulateListView(HWND hwndLV, 
                      LPTVITEMDATA lptvid,
                      LPSHELLFOLDER lpsf);

extern BOOL GetName(LPSHELLFOLDER lpsf,
                    LPITEMIDLIST  lpi,
			        DWORD         dwFlags,
                    LPSTR         lpFriendlyName);

extern int GetIcon(LPITEMIDLIST lpi, UINT uFlags);

extern LPITEMIDLIST ConcatPidls(LPCITEMIDLIST pidl1, LPCITEMIDLIST pidl2);

extern LPITEMIDLIST CopyITEMID(LPMALLOC lpMalloc, LPITEMIDLIST lpi);

// Module specific globals

HWND hwndLV;
extern HIMAGELIST hImageList;

//
//  FUNCTION: InitListViewImageLists(HWND hwndLV)
//
//
//  PURPOSE: Associate the system image list with our listview.
//
//  PARAMETERS:
//
//    HWND - Handle to the listview control
//
//  RETURN VALUE:
//
//    TRUE on success, FALSE on failure
//
//  COMMENTS:
//

BOOL WINAPI InitListViewImageLists(HWND hwndLV)
{
    HIMAGELIST himlSmall;
    HIMAGELIST himlLarge;
    SHFILEINFO sfi;
    BOOL       bSuccess=TRUE;

    himlSmall = (HIMAGELIST)SHGetFileInfo((LPCSTR)"C:\\", 
                                           0,
                                           &sfi, 
                                           sizeof(SHFILEINFO), 
                                           SHGFI_SYSICONINDEX | SHGFI_SMALLICON);

    himlLarge = (HIMAGELIST)SHGetFileInfo((LPCSTR)"C:\\", 
                                           0,
                                           &sfi, 
                                           sizeof(SHFILEINFO), 
                                           SHGFI_SYSICONINDEX | SHGFI_LARGEICON);

    if (himlSmall && himlLarge)
    {
       ListView_SetImageList(hwndLV, himlSmall, LVSIL_SMALL);
       ListView_SetImageList(hwndLV, himlLarge, LVSIL_NORMAL);
    }
    else
       bSuccess = FALSE;

    return bSuccess;
}


//
//  FUNCTION: InitListViewItems(HWND hwndLV,
//                              LPTVITEMDATA lptvid,
//                              LPSHELLFOLDER lpsf,
//                              LPITEMIDLIST lpi)
//
//
//  PURPOSE: Add the items to the listview control
//
//  PARAMETERS:
//
//    HWND - Handle to the listview control
//    LPTVITEMDATA - Pointer to TreeView item data
//    LPSHELLFOLDER - Pointer to parent shell folder
//
//  RETURN VALUE:
//
//    TRUE  - if items were successfully added
//    FALSE - if items were not successfully added
//
//  COMMENTS:
//

BOOL WINAPI InitListViewItems(HWND hwndLV,
                              LPTVITEMDATA lptvid,
                              LPSHELLFOLDER lpsf)
{
    LV_ITEM      lvi;
    int          iCtr;
    HRESULT      hr;
    LPMALLOC     lpMalloc;                                             
    LPITEMIDLIST lpifqThisItem;
    LPITEMIDLIST lpi=0;
    LPENUMIDLIST lpe=0;
    LPLVITEMDATA lplvid;
    ULONG        ulFetched, ulAttrs;
    HWND         hwnd=GetParent(hwndLV);
    UINT         uFlags;

    lvi.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM;

    hr=SHGetMalloc(&lpMalloc);
    if (FAILED(hr))
       return FALSE;

    // Hourglass on!

    SetCapture(GetParent(hwndLV));
    SetCursor(LoadCursor(NULL, IDC_WAIT));

    if (SUCCEEDED(hr))
    {
        hr=lpsf->lpVtbl->EnumObjects(lpsf,
                                     hwnd, 
                                     SHCONTF_FOLDERS | SHCONTF_NONFOLDERS,
                                     &lpe);

        if (SUCCEEDED(hr))
        {
            iCtr = 0;

            while (S_OK==lpe->lpVtbl->Next(lpe,
                                           1,
                                           &lpi,
                                           &ulFetched))
            {
                //OK, let's get some memory for our ITEMDATA struct

                lplvid = (LPLVITEMDATA)lpMalloc->lpVtbl->Alloc(lpMalloc, sizeof(LVITEMDATA));
                if (!lplvid)
                   goto Done;

//Don't do this here, since we are now using the LPSTR_TEXTCALLBACK method...
// 
//                //Now get the friendly name that we'll put in the treeview...
//
//                GetName(lpsf, lpi, SHGDN_NORMAL, szBuff);

                //Note that since we are interested in the display attributes as well as
                //the other attributes, we need to set ulAttrs to SFGAO_DISPLAYATTRMASK
                //before calling GetAttributesOf();

                ulAttrs=SFGAO_DISPLAYATTRMASK;

                lpsf->lpVtbl->GetAttributesOf(lpsf, 1, &lpi, &ulAttrs);
                lplvid->ulAttribs=ulAttrs;

                lpifqThisItem=ConcatPidls(lptvid->lpifq, lpi);
 
                lvi.iItem       = iCtr++;
                lvi.iSubItem    = 0;
//                lvi.pszText     = szBuff;
                lvi.pszText     = LPSTR_TEXTCALLBACK;
                lvi.cchTextMax  = MAX_PATH;
                uFlags          = SHGFI_PIDL | SHGFI_SYSICONINDEX | SHGFI_SMALLICON;

//Don't do this here, since we are now using the I_IMAGECALLBACK method...
//
//                lvi.iImage      = GetIcon(lpifqThisItem, uFlags);
                lvi.iImage      = I_IMAGECALLBACK;
 
                lplvid->lpsfParent=lpsf;
                lpsf->lpVtbl->AddRef(lpsf);

                //Now, make a copy of the ITEMIDLIST
                lplvid->lpi=CopyITEMID(lpMalloc, lpi);

                lvi.lParam = (LPARAM)lplvid;
   
                // Add the item to the listview
   
                if (ListView_InsertItem(hwndLV, &lvi) == -1)
                   return FALSE;

                lpMalloc->lpVtbl->Free(lpMalloc, lpifqThisItem);  
                lpifqThisItem=0;
                lpMalloc->lpVtbl->Free(lpMalloc, lpi);  //Finally, free the pidl that the shell gave us...
                lpi=0;
            }
        }

    }

Done:

    // Hourglass off!

    ReleaseCapture();
    SetCursor(LoadCursor(NULL, IDC_ARROW));

    if (lpe)  lpe->lpVtbl->Release(lpe);

    //The following 2 if statements will only be TRUE if we got here on an
    //error condition from the "goto" statement.  Otherwise, we free this memory
    //at the end of the while loop above.
    if (lpi && lpMalloc)           lpMalloc->lpVtbl->Free(lpMalloc, lpi);
    if (lpifqThisItem && lpMalloc) lpMalloc->lpVtbl->Free(lpMalloc, lpifqThisItem);  

    if (lpMalloc) lpMalloc->lpVtbl->Release(lpMalloc);
 
    return TRUE;
}


//
//  FUNCTION: CreateListView(HWND)
//
//  PURPOSE: Create the listview control
//
//  PARAMETERS:
//
//    HWND - Handle to the parent window
//
//  RETURN VALUE:
//
//    hwndLV - Handle to listview control if successful
//    NULL   - if creation of listview control fails
//
//  COMMENTS:
//

HWND WINAPI CreateListView(HWND hwndParent)
{
    HWND hwndLV;
    RECT rc;

    // Force the common controls DLL to be loaded.

    InitCommonControls();

    // Create the control.

    GetClientRect(hwndParent, &rc);

    hwndLV = CreateWindowEx(WS_EX_CLIENTEDGE,
    	                    WC_LISTVIEW, "",
                            WS_VISIBLE | WS_CHILD | WS_BORDER | LVS_EDITLABELS |
                            LVS_LIST | LVS_AUTOARRANGE | LVS_SHAREIMAGELISTS,
                            0, 0, 
                            rc.right-rc.left, rc.bottom-rc.top,
                            hwndParent,
                            (HMENU)IDD_LISTVIEW, 
                            hInst, 
                            NULL);

    return hwndLV;
}


//
//  FUNCTION: SwitchView(HWND, DWORD)
//
//  PURPOSE: Change the visual view of the listview control
//
//  PARAMETERS:
//
//    HWND  - Handle to the listview control
//    DWORD - View style indicating new view
//
//  RETURN VALUE:
//
//    void
//
//  COMMENTS:
//

void SwitchView(HWND hwndLV, DWORD dwView)
{
    DWORD dwStyle = GetWindowLong(hwndLV, GWL_STYLE);

    if ((dwStyle & LVS_TYPEMASK) != dwView)
        SetWindowLong(hwndLV, GWL_STYLE, (dwStyle & ~LVS_TYPEMASK) | dwView);
}


//
//  FUNCTION: ListViewCompareProc(LPARAM, LPARAM, LPARAM)
//
//  PURPOSE: Callback routine for sorting list
//
//  PARAMETERS:
//
//    lparam1    - 
//    lparam2    - 
//    lparamSort - 
//                 
//
//  RETURN VALUE:
//
//    Always returns 0 - Message handled
//
//  COMMENTS:
//

int CALLBACK ListViewCompareProc(LPARAM lparam1, 
                                 LPARAM lparam2,
                                 LPARAM lparamSort)
{
    LPLVITEMDATA lplvid1=(LPLVITEMDATA)lparam1;
    LPLVITEMDATA lplvid2=(LPLVITEMDATA)lparam2;
    HRESULT   hr;

    hr = lplvid1->lpsfParent->lpVtbl->CompareIDs(lplvid1->lpsfParent,
                                                 0,
                                                 lplvid1->lpi,
                                                 lplvid2->lpi);

    if (FAILED(hr))
       return 0;

    return (short)SCODE_CODE(GetScode(hr));
}


//
//  FUNCTION: PopulateListView(HWND, HWND, LPTVITEMDATA)
//
//  PURPOSE: Fill the listview
//
//  PARAMETERS:
//
//    HWND  - Handle to the listview control
//    DWORD - View style indicating new view
//
//  RETURN VALUE:
//
//    void
//
//  COMMENTS:
//


BOOL PopulateListView(HWND hwndLV, 
                      LPTVITEMDATA lptvid,
                      LPSHELLFOLDER lpsf)
{
    ListView_DeleteAllItems(hwndLV);

    if (!InitListViewImageLists(hwndLV) ||
        !InitListViewItems(hwndLV, lptvid, lpsf))
    {
        return FALSE;
    }

    ListView_SortItems(hwndLV,
                       ListViewCompareProc,
                       0);
}


