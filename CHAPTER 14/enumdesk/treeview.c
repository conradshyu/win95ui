// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (C) 1993-1995  Microsoft Corporation.  All Rights Reserved.
//
//  MODULE:   treeview.c
//
//  PURPOSE:  Fills a TreeView control with a listing of the INI
//            files. The root items are the INI files, then children
//            off the roots are the sections, and the children off
//            the sections are the entries:
//
//            ROOT WIN.INI
//                   |
//                   --[Fonts]
//                     |
//                     --AlbertusBold
//            ROOT SYSTEM.INI
//    
//
//  FUNCTIONS:
//
//    CreateTreeView   - Create a TreeViewControl.
//    FillTreeView     - Entry point function to fill TreeView Control
//    
//  COMMENTS:
//
//    The FillTreView function is called. It adds the INI file
//    names to the treeview. It calls FillIniKeys for each INI file. 
//    The FillIniKeys function adds the sections for the passed in
//    INI filename. The FillIniKeys calls FillKeyItems for each section.
//    The FillKeyItems function adds the entries for the passed in
//    section.

#include <windows.h>            // required for all Windows applications
#include <windowsx.h>
#include <commctrl.h>           // TreeView declarations live here
#include <shlobj.h>
#include "globals.h"            // prototypes specific to this application


// Function Prototypes

extern LPITEMIDLIST ConcatPidls(LPCITEMIDLIST pidl1, LPCITEMIDLIST pidl2);
extern LPITEMIDLIST GetFullyQualPidl(LPSHELLFOLDER lpsf, LPITEMIDLIST lpi);
extern LPITEMIDLIST CopyITEMID(LPMALLOC lpMalloc, LPITEMIDLIST lpi);
extern BOOL GetName(LPSHELLFOLDER lpsf,
                    LPITEMIDLIST  lpi,
		       	    DWORD         dwFlags,
                    LPSTR         lpFriendlyName);

//
//  FUNCTION: CreateTreeView(HWND hwndParent, int iID, DWORD dwStyle)
//
//  PURPOSE: Create a TreeView control
//
//  PARAMETERS:
// 
//    hwndParent - Parent of the TreeView.
//    iID        - ID of the TreeView.
//    dwStyle    - Style bits of the TreeView.
//
//  RETURN VALUE:
//    On Success: Handle to the TreeView
//    On Failure: NULL
//
//  COMMENTS:
//
//    The call to InitCommonControls is required once per application
//    lifetime. It is OK to move this to init.c, but for the
//    cut-and-pastibility of this sample, the call is placed here.
//

HWND CreateTreeView(HWND hwndParent, int iID, DWORD dwStyle)
{
    RECT rc;      // Client rect of parent
    HWND hwnd;    // Handle to TreeView
    SHFILEINFO    sfi;
    HIMAGELIST    hImageList;         // Handle to systemn ImageList.

    // This registers the TreeView class.

    InitCommonControls();

    // Get the client area of the parent.

    GetClientRect(hwndParent, &rc);

    // Create the TreeView control.

    hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,         // Ex style
                          WC_TREEVIEW,              // Class
                          "",                       // Dummy Text
                          dwStyle,                  // Style
                          0, 0,                     // Use all of
                          rc.right/2, rc.bottom,    // client area.
                          hwndParent,               // Parent
                          (HMENU)iID,               // ID
                          hInst,                    // Instance
                          NULL);                    // No extra

    // Grab a handle to the system image list, for our icons

    hImageList = (HIMAGELIST)SHGetFileInfo((LPCSTR)"C:\\", 
                                           0,
                                           &sfi, 
                                           sizeof(SHFILEINFO), 
                                           SHGFI_SYSICONINDEX | SHGFI_SMALLICON);

    // Attach ImageList to TreeView

    if (hImageList && hwnd)
        TreeView_SetImageList(hwnd, hImageList, 0);

    // Return the window handle

    return hwnd;
}


//
//  FUNCTION: GetIcon(LPITEMIDLIST lpi, UINT uFlags)
//
//  PURPOSE: Gets the index for the current icon.  Index is index into system
//           image list.
//
//  PARAMETERS:
// 
//    lpi    - Fully qualified item id list for current item.
//    uFlags - Flags for SHGetFileInfo()
//
//  RETURN VALUE:
//    Icon index for current item.
//
//  COMMENTS:
//
//

int GetIcon(LPITEMIDLIST lpi, UINT uFlags)
{
   SHFILEINFO    sfi;

   SHGetFileInfo((LPCSTR)lpi, 
                 0,
                 &sfi, 
                 sizeof(SHFILEINFO), 
                 uFlags);

   return sfi.iIcon;
}


//
//  FUNCTION: GetNormalAndSelectedIcons(LPITEMIDLIST lpifq, LPTV_ITEM lptvitem)
//
//  PURPOSE: Gets the index for the normal and selected icons for the current item.
//
//  PARAMETERS:
// 
//    lpifq    - Fully qualified item id list for current item.
//    lptvitem - Pointer to treeview item we are about to add to the tree.
//
//  RETURN VALUE:
//    void
//
//  COMMENTS:
//
//

void GetNormalAndSelectedIcons(LPITEMIDLIST lpifq,
                               LPTV_ITEM lptvitem)
{
   //Note that we don't check the return value here because if GetIcon()
   //fails, then we're in big trouble...

   lptvitem->iImage = GetIcon(lpifq, SHGFI_PIDL | 
                              SHGFI_SYSICONINDEX | 
                              SHGFI_SMALLICON);
   
   lptvitem->iSelectedImage = GetIcon(lpifq, SHGFI_PIDL | 
                                      SHGFI_SYSICONINDEX | 
                                      SHGFI_SMALLICON |
                                      SHGFI_OPENICON);
   
   return;
}


//
//  FUNCTION: FillTreeView(HWND          hwndTreeView, 
//                         LPSHELLFOLDER lpsf,
//                         LPITEMIDLIST  lpifq,
//                         HTREEITEM     hParent)
//
//
//  PURPOSE: Fills a branch of the TreeView control.  Given the
//           shell folder, enumerate the subitems of this folder,
//           and add the appropriate items to the tree.
//
//  PARAMETERS:
//    hwndTreeView - Handle fo TreeView Control
//    lpsf         - Pointer to shell folder that we want to enumerate items 
//    lpifq        - Fully qualified item id list to the item that we are enumerating
//                   items for.  In other words, this is the PIDL to the item
//                   identified by the lpsf parameter.
//    hParent      - Parent node
//
//  RETURN VALUE:
//    none
//
//  COMMENTS:
//
//    This function enumerates the items in the folder identifed by lpsf.
//    Note that since we are filling the left hand pane, we will only add
//    items that are folders and/or have sub-folders.  We *could* put all
//    items in here if we wanted, but that's not the intent.

void FillTreeView(HWND          hwndTreeView, 
                  LPSHELLFOLDER lpsf,
                  LPITEMIDLIST  lpifq,
                  HTREEITEM     hParent)
{
    TV_ITEM         tvi;                          // TreeView Item.
    TV_INSERTSTRUCT tvins;                        // TreeView Insert Struct.
    HTREEITEM       hPrev = NULL;                 // Previous Item Added.
    LPSHELLFOLDER   lpsf2=0;
    LPENUMIDLIST    lpe=0;
    LPITEMIDLIST    lpi=0, lpiTemp=0, lpifqThisItem;
    LPTVITEMDATA    lptvid=0;
    LPMALLOC        lpMalloc=0;
    ULONG           ulFetched;
    UINT            uCount=0;
    HRESULT         hr;
    char            szBuff[256];
    HWND            hwnd=GetParent(hwndTreeView);

    hr=SHGetMalloc(&lpMalloc);
    if (FAILED(hr))
       return;

    // Hourglass on!

    SetCapture(GetParent(hwndTreeView));
    SetCursor(LoadCursor(NULL, IDC_WAIT));

    if (SUCCEEDED(hr))
    {
        hr=lpsf->lpVtbl->EnumObjects(lpsf,
                                     hwnd, 
                                     SHCONTF_FOLDERS | SHCONTF_NONFOLDERS,
                                     &lpe);

        if (SUCCEEDED(hr))
        {
            while (S_OK==lpe->lpVtbl->Next(lpe,
                                           1,
                                           &lpi,
                                           &ulFetched))
            {
                //Create a fully qualified path to the current item
                //The SH* shell api's take a fully qualified path pidl,
                //(see GetIcon above where I call SHGetFileInfo) whereas the
                //interface methods take a relative path pidl.

                ULONG ulAttrs = SFGAO_HASSUBFOLDER | SFGAO_FOLDER;

                lpsf->lpVtbl->GetAttributesOf(lpsf, 1, &lpi, &ulAttrs);

                if (ulAttrs & (SFGAO_HASSUBFOLDER | SFGAO_FOLDER))
                {
                   //We need this next if statement so that we don't add things like
                   //the MSN to our tree.  MSN is not a folder, but according to the
                   //shell is has subfolders....

                   if (ulAttrs & SFGAO_FOLDER)
                   {
                      tvi.mask            = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE |
                                            TVIF_PARAM;

                      if (ulAttrs & SFGAO_HASSUBFOLDER)
                      {
                         //This item has sub-folders, so let's put the + in the TreeView.
                         //The first time the user clicks on the item, we'll populate the
                         //sub-folders then.

                         tvi.cChildren=1;
                         tvi.mask |= TVIF_CHILDREN;
                      }
                        
                      //OK, let's get some memory for our ITEMDATA struct

                      lptvid = (LPTVITEMDATA)lpMalloc->lpVtbl->Alloc(lpMalloc, sizeof(TVITEMDATA));
                      if (!lptvid)
                         goto Done;
   
                      //Now get the friendly name that we'll put in the treeview...

                      if (!GetName(lpsf, lpi, SHGDN_NORMAL, szBuff))
                         goto Done;
                      tvi.pszText    = szBuff;
                      tvi.cchTextMax = MAX_PATH;
    
                      lpifqThisItem=ConcatPidls(lpifq, lpi);
      
                      //Now, make a copy of the ITEMIDLIST
      
                      lptvid->lpi=CopyITEMID(lpMalloc, lpi);
   
                      GetNormalAndSelectedIcons(lpifqThisItem, &tvi);
   
                      lptvid->lpsfParent=lpsf;    //Store the parent folders SF
                      lpsf->lpVtbl->AddRef(lpsf);

                      //So, you ask, what's the story here?  Why do we have 2
                      //functions that apparently do the same thing?  Well, 
                      //ParseDisplayName() (used in GetFullyQualPidl) does not 
                      //work well for non-file system objects such as the My 
                      //Computer and Net Hood.  So, since we know that these 
                      //guys will only show up when we are enumerating the root 
                      //of the namespace (as identified by an hParent of TVI_ROOT), 
                      //we special case this here.  You *could* use ConcatPidls() 
                      //in ALL cases, but the GetFullyQualPidl() is shown for 
                      //demonstration purposes, since it's the more intuative way.

//Commented out for now, since we need ConcatPidls for *any* non-file system object.
//This includes things like Control Panel, et al.

//                      if (hParent==TVI_ROOT)
                         lptvid->lpifq=ConcatPidls(lpifq, lpi);
//                      else
//                         lptvid->lpifq=GetFullyQualPidl(lpsf, lpi);
   
                      tvi.lParam = (LPARAM)lptvid;
   
                      // Populate the TreeVeiw Insert Struct
                      // The item is the one filled above.
                      // Insert it after the last item inserted at this level.
                      // And indicate this is a root entry.
   				   
                      tvins.item         = tvi;
                      tvins.hInsertAfter = hPrev;
                      tvins.hParent      = hParent;
   
                      // Add the item to the tree
   
                      hPrev = TreeView_InsertItem(hwndTreeView, &tvins);
                   }

                   lpMalloc->lpVtbl->Free(lpMalloc, lpifqThisItem);  
                   lpifqThisItem=0;
                }

                lpMalloc->lpVtbl->Free(lpMalloc, lpi);  //Finally, free the pidl that the shell gave us...
                lpi=0;
            }
        }

    }
    else
       return;

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
}


//
//  FUNCTION: TreeViewCompareProc(LPARAM, LPARAM, LPARAM)
//
//  PURPOSE: Callback routine for sorting treeview
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

int CALLBACK TreeViewCompareProc(LPARAM lparam1, 
                                 LPARAM lparam2,
                                 LPARAM lparamSort)
{
    LPTVITEMDATA lptvid1=(LPTVITEMDATA)lparam1;
    LPTVITEMDATA lptvid2=(LPTVITEMDATA)lparam2;
    HRESULT   hr;

    hr = lptvid1->lpsfParent->lpVtbl->CompareIDs(lptvid1->lpsfParent,
                                                 0,
                                                 lptvid1->lpi,
                                                 lptvid2->lpi);

    if (FAILED(hr))
       return 0;

    return (short)SCODE_CODE(GetScode(hr));
}
