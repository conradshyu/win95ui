// mfcenvw.cpp : implementation of the CMfcenumView class
//

#include "stdafx.h"
#include "mfcenum.h"
#include "mfcendoc.h"
#include "mfcenvw.h"
#include "resource.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMfcenumView

IMPLEMENT_DYNCREATE(CMfcenumView, CView)

BEGIN_MESSAGE_MAP(CMfcenumView, CView)
	//{{AFX_MSG_MAP(CMfcenumView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(IDM_LARGEICON, OnLargeicon)
	ON_COMMAND(IDM_SMALLICON, OnSmallicon)
	ON_COMMAND(IDM_LIST, OnList)
	ON_COMMAND(IDM_FILL, OnFill)
	ON_WM_DESTROY()
	ON_COMMAND(ID_APP_EXIT, OnAppExit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMfcenumView construction/destruction

CMfcenumView::CMfcenumView()
{
	// TODO: add construction code here

}

CMfcenumView::~CMfcenumView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CMfcenumView drawing

void CMfcenumView::OnDraw(CDC* pDC)
{
	CMfcenumDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CMfcenumView diagnostics

#ifdef _DEBUG
void CMfcenumView::AssertValid() const
{
	CView::AssertValid();
}

void CMfcenumView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMfcenumDoc* CMfcenumView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMfcenumDoc)));
	return (CMfcenumDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMfcenumView message handlers

/****************************************************************************
*
*    FUNCTION: OnCreate()
*
*    PURPOSE:  Creates the list view and tree view windows
*
****************************************************************************/
int CMfcenumView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
    m_bOutaHere = FALSE;

	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
    // Create the tree view 
	m_TreeCtl.Create(
		WS_VISIBLE | WS_CHILD | WS_BORDER | TVS_HASLINES | TVS_HASBUTTONS | 
			TVS_LINESATROOT | WS_EX_CLIENTEDGE, // styles
		CRect(0,0,0,0),	// bounding rectangle,
		this, //parent
		ID_TREEVIEW); //id

    // Get the handle to the system image list, for our icons
    HIMAGELIST  hImageList;
    SHFILEINFO    sfi;

    hImageList = (HIMAGELIST)SHGetFileInfo((LPCSTR)"C:\\", 
                                           0,
                                           &sfi, 
                                           sizeof(SHFILEINFO), 
                                           SHGFI_SYSICONINDEX | SHGFI_SMALLICON);

    // Attach ImageList to TreeView
    if (hImageList)
        ::SendMessage(m_TreeCtl.m_hWnd, TVM_SETIMAGELIST, (WPARAM) TVSIL_NORMAL,
            (LPARAM)hImageList);
	

	// Create the CListCtrl window
	m_ListCtl.Create(
		WS_VISIBLE | WS_CHILD | WS_BORDER | LVS_LIST | LVS_EDITLABELS | 
		    LVS_AUTOARRANGE | LVS_SHAREIMAGELISTS | WS_EX_CLIENTEDGE, // styles
		CRect(0,0,0,0),	// bounding rectangle,
		this, //parent
		ID_LISTVIEW); //id
	
	OnFill();
    return 0;
}

/****************************************************************************
*
*    FUNCTION: OnSize()
*
*    PURPOSE:  Resizes the listview and tree view windows
*
****************************************************************************/
void CMfcenumView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);

    m_TreeCtl.MoveWindow(0, 0, cx /2, cy);
    m_ListCtl.MoveWindow(cx/2, 0, cx, cy);

}

/****************************************************************************
*
*    FUNCTION: OnLargeicon()
*
*    PURPOSE:  Processes the View.LargeIcon command
*
****************************************************************************/
void CMfcenumView::OnLargeicon() 
{
	DWORD dwStyle;

	dwStyle = GetWindowLong(m_ListCtl.m_hWnd, GWL_STYLE);
					
	if ((dwStyle & LVS_TYPEMASK) != LVS_ICON)
		SetWindowLong(m_ListCtl.m_hWnd, GWL_STYLE,
			(dwStyle & ~LVS_TYPEMASK) | LVS_ICON);
	
}

/****************************************************************************
*
*    FUNCTION: OnSmallicon()
*
*    PURPOSE:  Processes the View.SmallIcon command
*
****************************************************************************/
void CMfcenumView::OnSmallicon() 
{
	DWORD dwStyle;

	dwStyle = GetWindowLong(m_ListCtl.m_hWnd, GWL_STYLE);
					
	if ((dwStyle & LVS_TYPEMASK) != LVS_SMALLICON)
		SetWindowLong(m_ListCtl.m_hWnd, GWL_STYLE,
			(dwStyle & ~LVS_TYPEMASK) | LVS_SMALLICON);
	
}

/****************************************************************************
*
*    FUNCTION: OnList()
*
*    PURPOSE:  Processes the View.List command
*
****************************************************************************/
void CMfcenumView::OnList() 
{
	DWORD dwStyle;

	dwStyle = GetWindowLong(m_ListCtl.m_hWnd, GWL_STYLE);
					
	if ((dwStyle & LVS_TYPEMASK) != LVS_LIST)
		SetWindowLong(m_ListCtl.m_hWnd, GWL_STYLE,
			(dwStyle & ~LVS_TYPEMASK) | LVS_LIST);
	
}

/****************************************************************************
*
*    FUNCTION: OnFill()
*
*    PURPOSE:  Processes the File.Fill/RefreshTree command
*
****************************************************************************/
void CMfcenumView::OnFill() 
{

    LPSHELLFOLDER lpsf=NULL;
    LPITEMIDLIST  lpi=NULL;
    HRESULT hr;
    TV_SORTCB      tvscb;
   
    // Get a pointer to the desktop folder.
    hr=SHGetDesktopFolder(&lpsf);

    if (SUCCEEDED(hr))
    {
       // Initialize the tree view control to be empty.
       m_TreeCtl.DeleteAllItems();

       // Fill in the tree view control from the root.
       FillTreeView(lpsf, NULL,	TVI_ROOT);

       // Release the folder pointer.
       lpsf->Release();
    }

    tvscb.hParent     = TVI_ROOT;
    tvscb.lParam      = 0;
    tvscb.lpfnCompare = TreeViewCompareProc;

    // Sort the items in the tree view control.
    m_TreeCtl.SortChildrenCB(&tvscb, FALSE);
    
}

/****************************************************************************
*
*  FUNCTION: FillTreeView( LPSHELLFOLDER lpsf,
*                          LPITEMIDLIST  lpifq,
*                          HTREEITEM     hParent)
*
*  PURPOSE: Fills a branch of the TreeView control.  Given the
*           shell folder, enumerate the subitems of this folder,
*           and add the appropriate items to the tree.
*
*  PARAMETERS:
*    lpsf         - Pointer to shell folder that we want to enumerate items 
*    lpifq        - Fully qualified item id list to the item that we are enumerating
*                   items for.  In other words, this is the PIDL to the item
*                   identified by the lpsf parameter.
*    hParent      - Parent node
*
*  COMMENTS:
*    This function enumerates the items in the folder identifed by lpsf.
*    Note that since we are filling the left hand pane, we will only add
*    items that are folders and/or have sub-folders.  We *could* put all
*    items in here if we wanted, but that's not the intent.
*
****************************************************************************/
void CMfcenumView::FillTreeView (
   LPSHELLFOLDER lpsf, LPITEMIDLIST lpifq, HTREEITEM hParent)
{
    TV_ITEM         tvi;            // tree view item
    TV_INSERTSTRUCT tvins;          // tree view insert structure
    HTREEITEM       hPrev = NULL;   // previous item added
    LPSHELLFOLDER   lpsf2=NULL;
    LPENUMIDLIST    lpe=NULL;
    LPITEMIDLIST    lpi=NULL, lpiTemp=NULL, lpifqThisItem;
    LPTVITEMDATA    lptvid=NULL;
    LPMALLOC        lpMalloc=NULL;
    ULONG           ulFetched;
    UINT            uCount=0;
    HRESULT         hr;						   
    char            szBuff[256];
    HWND            hwnd=::GetParent(m_TreeCtl.m_hWnd);

    // Allocate a shell memory object. 
    hr=::SHGetMalloc(&lpMalloc);
    if (FAILED(hr))
       return;

    if (SUCCEEDED(hr))
    {
        // Get the IEnumIDList object for the given folder.
        hr=lpsf->EnumObjects(hwnd, SHCONTF_FOLDERS | SHCONTF_NONFOLDERS, &lpe);

        if (SUCCEEDED(hr))
        {
            // Enumerate throught the list of folder and nonfolder objects.
            while (S_OK==lpe->Next(1, &lpi, &ulFetched))
            {
                // Create a fully qualified path to the current item.
                // The SH* functions take a fully qualified path PIDL,
                // while the interface member functions take a 
                // relative path PIDL.
                ULONG ulAttrs = SFGAO_HASSUBFOLDER | SFGAO_FOLDER;

                // Determine what type of object you have.
                lpsf->GetAttributesOf (
                   1, (const struct _ITEMIDLIST **)&lpi, &ulAttrs);

                if (ulAttrs & (SFGAO_HASSUBFOLDER | SFGAO_FOLDER))
                {
                   // You need this next if statement to
                   // avoid adding objects that are not real 
                   // folders to the tree. Some objects can
                   // have subfolders, but aren't real folders.                   
                   if (ulAttrs & SFGAO_FOLDER)
                   {
                      tvi.mask= TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM;

                      if (ulAttrs & SFGAO_HASSUBFOLDER)
                      {
                         // This item has subfolders, so put a plus sign in
                         // the tree view control. The first time the user clicks
                         // the item, you should populate the sub-folders.
                         tvi.cChildren=1;
                         tvi.mask |= TVIF_CHILDREN;
                      }
                        
                      // Get some memory for the ITEMDATA structure.
                      lptvid = (LPTVITEMDATA)lpMalloc->Alloc(sizeof(TVITEMDATA));
                      if (!lptvid)
                         goto Done;  // Error - could not allocate memory.
   
                      // Now get the friendly name to 
                      // put in the tree view control.
                      if (!GetName(lpsf, lpi, SHGDN_NORMAL, szBuff))
                         goto Done; // Error - could not get friendly name

                      tvi.pszText    = szBuff;
                      tvi.cchTextMax = MAX_PATH;
    
                      lpifqThisItem=ConcatPidls(lpifq, lpi);
      
                      // Now make a copy of the ITEMIDLIST
                      lptvid->lpi=CopyITEMID(lpMalloc, lpi);
   
                      GetNormalAndSelectedIcons(lpifqThisItem, &tvi);
   
                      lptvid->lpsfParent=lpsf;    // store the parent folder's SF
                      lpsf->AddRef();

                      lptvid->lpifq=ConcatPidls(lpifq, lpi);
   
                      tvi.lParam = (LPARAM)lptvid;
   
                      // Populate the tree view insert structure.
                      // The item is the one filled above.
                      // Insert it after the last item inserted at this level.
                      // Indicate this is a root entry.
                      tvins.item         = tvi;
                      tvins.hInsertAfter = TVI_FIRST;
                      tvins.hParent      = hParent;
   
                      // Add the item to the tree.
                      hPrev = m_TreeCtl.InsertItem(&tvins);
                   }
                   // Free the task allocator for this item.
                   lpMalloc->Free(lpifqThisItem);  
                   lpifqThisItem=0;
                }

                lpMalloc->Free(lpi);  // free PIDL the shell gave you
                lpi=0;
            }
        }

    }
    else
       return;

Done:
    if (lpe)  
        lpe->Release();

    // The following two if statements will be TRUE only if you got here
    // on an error condition from the goto statement.  Otherwise, free 
    // this memory at the end of the while loop above.
    if (lpi && lpMalloc)           
        lpMalloc->Free(lpi);
    if (lpifqThisItem && lpMalloc) 
        lpMalloc->Free(lpifqThisItem);  

    if (lpMalloc) 
        lpMalloc->Release();
}

/****************************************************************************
*
*    FUNCTION: GetIcon(LPITEMIDLIST lpi, UINT uFlags)
*
*    PURPOSE:  Gets the index for the current icon.  Index is index into system
*              image list.
*
*  PARAMETERS:
*    lpi    - Fully qualified item id list for current item.
*    uFlags - Flags for SHGetFileInfo()
*
*  RETURN VALUE:
*    Icon index for current item.
****************************************************************************/
int CMfcenumView::GetIcon(LPITEMIDLIST lpi, UINT uFlags)
{
   SHFILEINFO    sfi;

   SHGetFileInfo((LPCSTR)lpi, 0, &sfi, sizeof(SHFILEINFO), uFlags);

   return sfi.iIcon;
}

/****************************************************************************
*
*    FUNCTION: GetNormalAndSelectedIcons(LPITEMIDLIST lpifq, LPTV_ITEM lptvitem)
*
*    PURPOSE:  Gets the index for the normal and selected icons for the current item.
*
*    PARAMETERS:
*    lpifq    - Fully qualified item id list for current item.
*    lptvitem - Pointer to treeview item we are about to add to the tree.
*
****************************************************************************/
void CMfcenumView::GetNormalAndSelectedIcons (
   LPITEMIDLIST lpifq, LPTV_ITEM lptvitem)
{
   // Don't check the return value here. 
   // If IGetIcon() fails, you're in big trouble.
   lptvitem->iImage = GetIcon (lpifq, 
      SHGFI_PIDL | SHGFI_SYSICONINDEX | SHGFI_SMALLICON);
   
   lptvitem->iSelectedImage = GetIcon (lpifq, 
      SHGFI_PIDL | SHGFI_SYSICONINDEX | SHGFI_SMALLICON | SHGFI_OPENICON);
   
   return;
}

/****************************************************************************
*
*    FUNCTION: WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
*
*    PURPOSE:  Handles the WM_NOTIFY and WM_CONTEXTMENU messages.
*
****************************************************************************/
LRESULT CMfcenumView::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	if (message == WM_NOTIFY)
        NotifyHandler(message, wParam, lParam);
	return CView::WindowProc(message, wParam, lParam);
}

/****************************************************************************
*
*  FUNCTION: DoTheMenuThing(HWND hwnd, 
*                           LPSHELLFOLDER lpsfParent,
*                           LPITEMIDLIST  lpi,
*                           LPPOINT lppt)
*
*  PURPOSE: Displays a popup context menu, given a parent shell folder,
*           relative item id and screen location.
*
*  PARAMETERS:
*    hwnd       - Parent window handle
*    lpsfParent - Pointer to parent shell folder.
*    lpi        - Pointer to item id that is relative to lpsfParent
*    lppt       - Screen location of where to popup the menu.
*
*  RETURN VALUE:
*    Returns TRUE on success, FALSE on failure
*
****************************************************************************/
BOOL CMfcenumView::DoTheMenuThing(HWND hwnd, LPSHELLFOLDER lpsfParent,
     LPITEMIDLIST  lpi, LPPOINT lppt)
{
    LPCONTEXTMENU lpcm;
    HRESULT       hr;
    char          szTemp[64];
    CMINVOKECOMMANDINFO cmi;
    DWORD               dwAttribs=0;
    int                 idCmd;
    HMENU               hMenu;
    BOOL                bSuccess=TRUE;

    hr=lpsfParent->GetUIObjectOf(hwnd,
        1,  // get attributes for this many objects
        (const struct _ITEMIDLIST **)&lpi,
        IID_IContextMenu,
        0,
        (LPVOID *)&lpcm);
    if (SUCCEEDED(hr))  
    {
       hMenu = CreatePopupMenu();

       if (hMenu)
       {
          // Get the context menu for the item.
          hr=lpcm->QueryContextMenu(hMenu, 0, 1, 0x7fff, CMF_EXPLORE);
          if (SUCCEEDED(hr))
          {
             idCmd=TrackPopupMenu(hMenu, 
                TPM_LEFTALIGN | TPM_RETURNCMD | TPM_RIGHTBUTTON, 
                lppt->x, lppt->y, 0, hwnd, NULL);

             if (idCmd)
             {
                // Execute the command that was selected.
                cmi.cbSize = sizeof(CMINVOKECOMMANDINFO);
                cmi.fMask  = 0;
                cmi.hwnd   = hwnd;
                cmi.lpVerb = MAKEINTRESOURCE(idCmd-1);
                cmi.lpParameters = NULL;
      	        cmi.lpDirectory  = NULL;
                cmi.nShow        = SW_SHOWNORMAL;
                cmi.dwHotKey     = 0;
                cmi.hIcon        = NULL;
                hr=lpcm->InvokeCommand(&cmi);
                if (!SUCCEEDED(hr))  
                {
                   wsprintf(szTemp, "InvokeCommand failed. hr = %lx", hr);
                   AfxMessageBox(szTemp);
                }
             }

          }
          else
             bSuccess = FALSE;

          DestroyMenu(hMenu);
       }
       else
          bSuccess = FALSE;

       lpcm->Release();
    } 
    else
    {
       wsprintf(szTemp, "GetUIObjectOf failed! hr = %lx", hr);
       AfxMessageBox(szTemp );
       bSuccess = FALSE;
    }
    return bSuccess;
}

void CMfcenumView::OnAppExit () 
{
m_bOutaHere = TRUE;     
PostQuitMessage (0);     
}

/****************************************************************************
*
*    FUNCTION: NotifyHandler(UINT message, WPARAM wParam, LPARAM lParam)
*
*    PURPOSE:  Handles the WM_NOTIFY and WM_CONTEXTMENU messages.
*
****************************************************************************/
LRESULT CMfcenumView::NotifyHandler(UINT message, WPARAM wParam, LPARAM lParam) 
{
   POINT pt;
   NM_TREEVIEW *pnmtv   = (NM_TREEVIEW *)lParam;
   NM_LISTVIEW *pnmlv   = (NM_LISTVIEW *)lParam;
   LV_HITTESTINFO lvhti;
   LPTVITEMDATA   lptvid;  //Long pointer to TreeView item data
   LPLVITEMDATA   lplvid;  //Long pointer to ListView item data
   HRESULT        hr;
   LPMALLOC       lpMalloc;
   LPSHELLFOLDER  lpsf2=NULL;
   LV_ITEM        lvi;
   static char    szBuff[MAX_PATH];
   LV_DISPINFO    *plvdi;
   TV_SORTCB      tvscb;
   TV_HITTESTINFO tvhti;
   TV_ITEM        tvi;
   LPDATAOBJECT   lpdo;
   DWORD          dwEffect;

   switch (pnmtv->hdr.idFrom)
   {
      case ID_TREEVIEW:
		 switch (pnmtv->hdr.code)   
		 {
		    case NM_RCLICK:
		       ::GetCursorPos((LPPOINT)&pt);
		       ::ScreenToClient(m_hWnd, &pt);
		       tvhti.pt=pt;
               m_TreeCtl.HitTest(&tvhti);
               m_TreeCtl.SelectItem(tvhti.hItem);
		       if (tvhti.flags & TVHT_ONITEMLABEL)
		       {
		           ::ClientToScreen(m_hWnd, &pt);
		           tvi.mask=TVIF_PARAM;
		           tvi.hItem=tvhti.hItem;
		
                   if (!m_TreeCtl.GetItem(&tvi))
		              return 0;
		
		           lptvid=(LPTVITEMDATA)tvi.lParam;
		
                   if (lptvid)
		              DoTheMenuThing(::GetParent(m_TreeCtl.m_hWnd),
		                  lptvid->lpsfParent, lptvid->lpi, &pt);
		       }
		       break;

		    case TVN_DELETEITEM:
		       //Let's free the memory for the TreeView item data...
		       hr=SHGetMalloc(&lpMalloc);
		       if (FAILED(hr))
		          break;
		
		       lptvid=(LPTVITEMDATA)pnmtv->itemOld.lParam;
               lptvid->lpsfParent->Release();
               lpMalloc->Free(lptvid->lpi);  
               lpMalloc->Free(lptvid->lpifq);  
		       lpMalloc->Free(lptvid);  
		       lpMalloc->Release();
		       break;
		
			case TVN_SELCHANGED:
		       //Do this only if we are not exiting the application...
               if (!m_bOutaHere)
               {
                  lptvid=(LPTVITEMDATA)pnmtv->itemNew.lParam;
                  if (lptvid)
                  {
                    hr=lptvid->lpsfParent->BindToObject(lptvid->lpi,
		                0,IID_IShellFolder,(LPVOID *)&lpsf2);
		
                    if (SUCCEEDED(hr))
                    {
                        PopulateListView(lptvid,lpsf2);
                        lpsf2->Release();
                    }
                  }
               }

		       break;
		
		    case TVN_ITEMEXPANDING:
		       if ((pnmtv->itemNew.state & TVIS_EXPANDEDONCE))
		          break;
		
		       lptvid=(LPTVITEMDATA)pnmtv->itemNew.lParam;
		       if (lptvid)
               {
		            hr=lptvid->lpsfParent->BindToObject(lptvid->lpi,
		                0, IID_IShellFolder,(LPVOID *)&lpsf2);
		
		            if (SUCCEEDED(hr))
		            {
		                FillTreeView(lpsf2,
		                       lptvid->lpifq,
		                       pnmtv->itemNew.hItem);
		            }
		
                    tvscb.hParent     = pnmtv->itemNew.hItem;
                    tvscb.lParam      = 0;
                    tvscb.lpfnCompare = TreeViewCompareProc;

		            m_TreeCtl.SortChildrenCB(&tvscb, FALSE);
               }
		       break;
		  
		       default:
		           break;
		 }

		 break;

	  case ID_LISTVIEW:
	     switch (pnmlv->hdr.code)
		 {
            case NM_RCLICK:
            case NM_DBLCLK:
		       ::GetCursorPos((LPPOINT)&pt);
		       ::ScreenToClient(m_ListCtl.m_hWnd, &pt);
		       lvhti.pt=pt;
		       m_ListCtl.HitTest(&lvhti);
		       if (lvhti.flags & LVHT_ONITEM)
		       {
		           ::ClientToScreen(m_ListCtl.m_hWnd, &pt);
		           lvi.mask = LVIF_PARAM;
                   lvi.iItem = lvhti.iItem;
                   lvi.iSubItem = 0;
		
		           if (!m_ListCtl.GetItem(&lvi))
		              break;
		
		           lplvid=(LPLVITEMDATA)lvi.lParam;

                   if (pnmlv->hdr.code==NM_RCLICK)
                      DoTheMenuThing(::GetParent(m_ListCtl.m_hWnd), 
                        lplvid->lpsfParent, lplvid->lpi, &pt);
                   else if (!(lplvid->ulAttribs & SFGAO_FOLDER))
                   {
                         SHELLEXECUTEINFO sei =
                         {
                            sizeof(SHELLEXECUTEINFO),
                            SEE_MASK_INVOKEIDLIST,	// fMask
                            ::GetParent(m_ListCtl.m_hWnd),  // hwnd of parent
                            "Open",                 // lpVerb
                            NULL,	                // lpFile
                            "",
                            "",                     // lpDirectory
                            SW_SHOWNORMAL,	        // nShow
                            AfxGetInstanceHandle(), // hInstApp
                            (LPVOID)NULL,           // lpIDList...will set below
                            NULL,                   // lpClass
                            0,			            // hkeyClass
                            0,				        // dwHotKey
                            NULL			        // hIcon
                         };

                         sei.lpIDList=GetFullyQualPidl(lplvid->lpsfParent, lplvid->lpi);

                         ShellExecuteEx(&sei);
                      }
                      else
                         AfxMessageBox("Clicked on folder");
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
		
		       if (!m_ListCtl.GetItem(&lvi))
		          return 0;
			   lplvid=(LPLVITEMDATA)lvi.lParam;

               lplvid->lpsfParent->Release();
               lpMalloc->Free(lplvid->lpi);  
		       lpMalloc->Free(lplvid);  
		       lpMalloc->Release();
	           break;

            case LVN_GETDISPINFO:

               plvdi  = (LV_DISPINFO *)lParam;
               lplvid = (LPLVITEMDATA)plvdi->item.lParam;

               if ((plvdi) &&(plvdi->item.mask & LVIF_IMAGE))
               {
                  TV_ITEM tvi;
                  HTREEITEM hti;

                  hti = m_TreeCtl.GetSelectedItem();
                  tvi.mask = TVIF_PARAM;
                  tvi.hItem = hti;

                  m_TreeCtl.GetItem(&tvi);

                  lptvid=(LPTVITEMDATA)tvi.lParam;

                  if (lptvid)
                  {
                     plvdi->item.iImage = GetIcon(ConcatPidls(lptvid->lpifq, lplvid->lpi),
                        SHGFI_PIDL | SHGFI_SYSICONINDEX | SHGFI_SMALLICON);

                     if (lplvid->ulAttribs & SFGAO_LINK)
                        {
                        plvdi->item.mask |= LVIF_STATE;
                        plvdi->item.stateMask = LVIS_OVERLAYMASK;
                        plvdi->item.state = INDEXTOOVERLAYMASK(2);
                        }
                     if (plvdi->item.mask & LVIF_TEXT)
                        GetName(lplvid->lpsfParent, lplvid->lpi, SHGDN_NORMAL, plvdi->item.pszText);
				  }
                }
               break;
            case LVN_BEGINDRAG:
            case LVN_BEGINRDRAG:

		       lvi.mask = LVIF_PARAM;
               lvi.iItem = pnmlv->iItem;
               lvi.iSubItem = 0;
		
		       if (!m_ListCtl.GetItem(&lvi))
		          return 0;
			   lplvid=(LPLVITEMDATA)lvi.lParam;

               hr=lplvid->lpsfParent->GetUIObjectOf(m_hWnd,
                    1,  //Number of objects to get attributes of
                    (const struct _ITEMIDLIST **)&lplvid->lpi,
                    IID_IDataObject,
                    0,
                    (LPVOID *)&lpdo);

               if (SUCCEEDED(hr))  
               {
                  LPDROPSOURCE lpds= new CDropSource();

                  if (lpds)
                     ::DoDragDrop(lpdo,
                                lpds,
                                DROPEFFECT_COPY | DROPEFFECT_MOVE | DROPEFFECT_LINK,
                                &dwEffect);     

                  lpdo->Release();
                  lpds->Release();
               }

               break;

			default:
			   break;
		 }

		 break;

   }

   return 0;
}

/****************************************************************************
*
*    FUNCTION: PopulateListView(LPTVITEMDATA, LPSHELLFOLDER )
*
*    PURPOSE:  Populates the list view.
*
****************************************************************************/
BOOL CMfcenumView::PopulateListView(LPTVITEMDATA lptvid, LPSHELLFOLDER lpsf)
{
    m_ListCtl.DeleteAllItems();

    if (!InitListViewImageLists() ||
        !InitListViewItems(lptvid, lpsf))
        return FALSE;

    m_ListCtl.SortItems(ListViewCompareProc, 0);
    return TRUE;
}

/****************************************************************************
*
*    FUNCTION: InitListViewImageLists()
*
*    PURPOSE:  Associate the system image list with our listview.
*
****************************************************************************/
BOOL CMfcenumView::InitListViewImageLists()
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
        ::SendMessage(m_ListCtl.m_hWnd, LVM_SETIMAGELIST, (WPARAM)LVSIL_SMALL,
            (LPARAM)himlSmall);
        ::SendMessage(m_ListCtl.m_hWnd, LVM_SETIMAGELIST, (WPARAM)LVSIL_NORMAL,
            (LPARAM)himlLarge);
    }
    else
       bSuccess = FALSE;

    return bSuccess;
}

/****************************************************************************
*
*    FUNCTION: InitListViewItems(LPTVITEMDATA lptvid,
*                              LPSHELLFOLDER lpsf,
*                              LPITEMIDLIST lpi)
*
*    PURPOSE:  Add items to the list view.
*
*    PARAMETERS:
*      HWND - Handle to the listview control
*      LPTVITEMDATA - Pointer to TreeView item data
*      LPSHELLFOLDER - Pointer to parent shell folder
*
****************************************************************************/
BOOL CMfcenumView::InitListViewItems(LPTVITEMDATA lptvid, LPSHELLFOLDER lpsf)
{
    LV_ITEM      lvi;
    int          iCtr;
    HRESULT      hr;
    LPMALLOC     lpMalloc;                                             
    LPITEMIDLIST lpifqThisItem;
    LPITEMIDLIST lpi=NULL;
    LPENUMIDLIST lpe=NULL;
    LPLVITEMDATA lplvid;
    ULONG        ulFetched, ulAttrs;
    HWND         hwnd=::GetParent(m_ListCtl.m_hWnd);
    UINT         uFlags;

    lvi.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM;

    hr=SHGetMalloc(&lpMalloc);
    if (FAILED(hr))
       return FALSE;

    if (SUCCEEDED(hr))
    {
        hr=lpsf->EnumObjects(hwnd,SHCONTF_FOLDERS | SHCONTF_NONFOLDERS, &lpe);

        if (SUCCEEDED(hr))
        {
            iCtr = 0;

            while (S_OK==lpe->Next(1, &lpi, &ulFetched))
            {
                // Get some memory for yhe ITEMDATA structure.
                lplvid = (LPLVITEMDATA)lpMalloc->Alloc(sizeof(LVITEMDATA));
                if (!lplvid)
                   goto Done;

                // Since you are interested in the display attributes 
                // as well as other attributes, you need to set ulAttrs to 
                // SFGAO_DISPLAYATTRMASK before calling GetAttributesOf().
                ulAttrs=SFGAO_DISPLAYATTRMASK;
                lpsf->GetAttributesOf(1, (const struct _ITEMIDLIST **)&lpi, &ulAttrs);
                lplvid->ulAttribs=ulAttrs;

                lpifqThisItem=ConcatPidls(lptvid->lpifq, lpi);
 
                lvi.iItem       = iCtr++;
                lvi.iSubItem    = 0;
                lvi.pszText     = LPSTR_TEXTCALLBACK;
                lvi.cchTextMax  = MAX_PATH;
                uFlags          = SHGFI_PIDL | SHGFI_SYSICONINDEX | SHGFI_SMALLICON;
                lvi.iImage      = I_IMAGECALLBACK;
 
                lplvid->lpsfParent=lpsf;
                lpsf->AddRef();

                // Now make a copy of the ITEMIDLIST.
                lplvid->lpi=CopyITEMID(lpMalloc, lpi);

                lvi.lParam = (LPARAM)lplvid;
   
                // Add the item to the list view control.   
                if (m_ListCtl.InsertItem(&lvi) == -1)
                   return FALSE;

                lpMalloc->Free(lpifqThisItem);  
                lpifqThisItem=0;
                lpMalloc->Free(lpi);  // free PIDL the shell gave you
                lpi=0;
            }
        }

    }

Done:

    if (lpe)  
        lpe->Release();

    // The following two if statements will be TRUE only if you got here
    // on an error condition from the goto statement.  Otherwise, free 
    // this memory at the end of the while loop above.
    if (lpi && lpMalloc)           
        lpMalloc->Free(lpi);
    if (lpifqThisItem && lpMalloc) 
        lpMalloc->Free(lpifqThisItem);  

    if (lpMalloc) 
        lpMalloc->Release();
 
    return TRUE;
}

/****************************************************************************
*
*    FUNCTION: ListViewCompareProc(LPARAM, LPARAM, LPARAM)
*
*    PURPOSE:  Callback routine for sorting list 
*
****************************************************************************/
int CALLBACK CMfcenumView::ListViewCompareProc(LPARAM lparam1, 
                                 LPARAM lparam2,
                                 LPARAM lparamSort)
{
    LPLVITEMDATA lplvid1=(LPLVITEMDATA)lparam1;
    LPLVITEMDATA lplvid2=(LPLVITEMDATA)lparam2;
    HRESULT   hr;

    hr = lplvid1->lpsfParent->CompareIDs(0,lplvid1->lpi,lplvid2->lpi);

    if (FAILED(hr))
       return 0;

    return hr;
}

/****************************************************************************
*
*    FUNCTION: TreeViewCompareProc(LPARAM, LPARAM, LPARAM)
*
*    PURPOSE:  Callback routine for sorting the tree 
*
****************************************************************************/
int CALLBACK CMfcenumView::TreeViewCompareProc(LPARAM lparam1, 
    LPARAM lparam2, LPARAM lparamSort)
{
    LPTVITEMDATA lptvid1=(LPTVITEMDATA)lparam1;
    LPTVITEMDATA lptvid2=(LPTVITEMDATA)lparam2;
    HRESULT   hr;

    hr = lptvid1->lpsfParent->CompareIDs(0,lptvid1->lpi,lptvid2->lpi);

    if (FAILED(hr))
       return 0;

    return (hr);
}

// 
// FUNCTIONS THAT DEAL WITH PIDLs
//
/****************************************************************************
*
*    FUNCTION: Next(LPCITEMIDLIST pidl)
*
*    PURPOSE:  Gets the next PIDL in the list 
*
****************************************************************************/
LPITEMIDLIST CMfcenumView::Next(LPCITEMIDLIST pidl)
{
   LPSTR lpMem=(LPSTR)pidl;

   lpMem+=pidl->mkid.cb;

   return (LPITEMIDLIST)lpMem;
}

/****************************************************************************
*
*    FUNCTION: GetSize(LPCITEMIDLIST pidl)
*
*    PURPOSE:  Gets the size of the PIDL 
*
****************************************************************************/
UINT CMfcenumView::GetSize(LPCITEMIDLIST pidl)
{
    UINT cbTotal = 0;
    if (pidl)
    {
        cbTotal += sizeof(pidl->mkid.cb);       // Null terminator
        while (pidl->mkid.cb)
        {
            cbTotal += pidl->mkid.cb;
            pidl = Next(pidl);
        }
    }

    return cbTotal;
}

/****************************************************************************
*
*    FUNCTION: Create(UINT cbSize)
*
*    PURPOSE:  Allocates a PIDL 
*
****************************************************************************/
LPITEMIDLIST CMfcenumView::Create(UINT cbSize)
{
    LPMALLOC lpMalloc;
    HRESULT  hr;
    LPITEMIDLIST pidl=NULL;

    hr=SHGetMalloc(&lpMalloc);

    if (FAILED(hr))
       return 0;

    pidl=(LPITEMIDLIST)lpMalloc->Alloc(cbSize);

    if (pidl)
        memset(pidl, 0, cbSize);      // zero-init for external task   alloc

    if (lpMalloc) lpMalloc->Release();

    return pidl;
}

/****************************************************************************
*
*    FUNCTION: ConcatPidls(LPCITEMIDLIST pidl1, LPCITEMIDLIST pidl2)
*
*    PURPOSE:  Concatenates two PIDLs 
*
****************************************************************************/
LPITEMIDLIST CMfcenumView::ConcatPidls(LPCITEMIDLIST pidl1, LPCITEMIDLIST pidl2)
{
    LPITEMIDLIST pidlNew;
    UINT cb1;
    UINT cb2;

    if (pidl1)  //May be NULL
       cb1 = GetSize(pidl1) - sizeof(pidl1->mkid.cb);
    else
       cb1 = 0;

    cb2 = GetSize(pidl2);

    pidlNew = Create(cb1 + cb2);
    if (pidlNew)
    {
        if (pidl1)
           memcpy(pidlNew, pidl1, cb1);
        memcpy(((LPSTR)pidlNew) + cb1, pidl2, cb2);
    }
    return pidlNew;
}

/****************************************************************************
*
*    FUNCTION: CopyITEMID(LPMALLOC lpMalloc, LPITEMIDLIST lpi)
*
*    PURPOSE:  Copies the ITEMID 
*
****************************************************************************/
LPITEMIDLIST CMfcenumView::CopyITEMID(LPMALLOC lpMalloc, LPITEMIDLIST lpi)
{
   LPITEMIDLIST lpiTemp;

   lpiTemp=(LPITEMIDLIST)lpMalloc->Alloc(lpi->mkid.cb+sizeof(lpi->mkid.cb));
   CopyMemory((PVOID)lpiTemp, (CONST VOID *)lpi, lpi->mkid.cb+sizeof(lpi->mkid.cb));

   return lpiTemp;
}

/****************************************************************************
*
*    FUNCTION: GetName(LPSHELLFOLDER lpsf,LPITEMIDLIST  lpi,DWORD dwFlags,
*             LPSTR         lpFriendlyName)
*
*    PURPOSE:  Gets the friendly name for the folder 
*
****************************************************************************/
BOOL CMfcenumView::GetName (LPSHELLFOLDER lpsf, LPITEMIDLIST lpi, 
   DWORD dwFlags, LPSTR lpFriendlyName)
{
   BOOL   bSuccess=TRUE;
   STRRET str;

   if (NOERROR==lpsf->GetDisplayNameOf(lpi,dwFlags, &str))
   {
      switch (str.uType)
      {
         case STRRET_WSTR:
            WideCharToMultiByte(
               CP_ACP,                 // code page
               0,		               // dwFlags
               str.pOleStr,            // lpWideCharStr
               -1,                     // cchWideCharStr
               lpFriendlyName,         // lpMultiByteStr
               sizeof(lpFriendlyName), // cchMultiByte
               NULL,                   // lpDefaultChar
               NULL);                  // lpUsedDefaultChar
             break;

         case STRRET_OFFSET:
             lstrcpy(lpFriendlyName, (LPSTR)lpi+str.uOffset);
             break;

         case STRRET_CSTR:             
             lstrcpy(lpFriendlyName, (LPSTR)str.cStr);
             break;

         default:
             bSuccess = FALSE;
             break;
      }
   }
   else
      bSuccess = FALSE;

   return bSuccess;
}

/****************************************************************************
*
*    FUNCTION: GetFullyQualPidl(LPSHELLFOLDER lpsf, LPITEMIDLIST lpi)
*
*    PURPOSE:  Gets the Fully qualified Pidls for the folder 
*
****************************************************************************/
LPITEMIDLIST CMfcenumView::GetFullyQualPidl(LPSHELLFOLDER lpsf, LPITEMIDLIST lpi)
{
   char szBuff[MAX_PATH];
   OLECHAR szOleChar[MAX_PATH];
   LPSHELLFOLDER lpsfDeskTop;
   LPITEMIDLIST  lpifq;
   ULONG ulEaten, ulAttribs;
   HRESULT hr;

   if (!GetName(lpsf, lpi, SHGDN_FORPARSING, szBuff))
      return NULL;

   hr=SHGetDesktopFolder(&lpsfDeskTop);

   if (FAILED(hr))
      return NULL;

   MultiByteToWideChar(CP_ACP,
					   MB_PRECOMPOSED,
					   szBuff,
					   -1,
					   (USHORT *)szOleChar,
					   sizeof(szOleChar));

   hr=lpsfDeskTop->ParseDisplayName(NULL,
									NULL,
									szOleChar,
									&ulEaten,
									&lpifq,
									&ulAttribs);

   lpsfDeskTop->Release();

   if (FAILED(hr))
      return NULL;

   return lpifq;
}

void CMfcenumView::OnDestroy() 
{
	CView::OnDestroy();
	
    m_bOutaHere = TRUE;	
}

//---------------------------------------------------------------------
//                    IUnknown Methods
//---------------------------------------------------------------------


STDMETHODIMP CDropSource::QueryInterface(REFIID iid, void FAR* FAR* ppv) 
{
    if(iid == IID_IUnknown || iid == IID_IDropSource)
    {
      *ppv = this;
      ++m_refs;
      return NOERROR;
    }
    *ppv = NULL;

    return E_NOINTERFACE;
}


STDMETHODIMP_(ULONG) CDropSource::AddRef(void)
{
    return ++m_refs;
}


STDMETHODIMP_(ULONG) CDropSource::Release(void)
{
    if(--m_refs == 0)
    {
      delete this;
      return 0;
    }
    return m_refs;
}  

//---------------------------------------------------------------------
//                    CDropSource Constructor
//---------------------------------------------------------------------        
 
CDropSource::CDropSource()
{
    m_refs = 1;  
}

//---------------------------------------------------------------------
//                    IDropSource Methods
//---------------------------------------------------------------------  

STDMETHODIMP CDropSource::QueryContinueDrag(BOOL fEscapePressed, 
                                            DWORD grfKeyState)
{  

    if (fEscapePressed)
        return DRAGDROP_S_CANCEL;
    else if (!(grfKeyState & MK_LBUTTON) && !(grfKeyState & MK_RBUTTON))
        return DRAGDROP_S_DROP;
    else
        return NOERROR;                  
}

STDMETHODIMP CDropSource::GiveFeedback(DWORD dwEffect)
{
    return DRAGDROP_S_USEDEFAULTCURSORS;
}

