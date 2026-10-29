// mfctrvw.cpp : implementation of the CMfctreeView class
//

#include "stdafx.h"
#include "mfctree.h"

#include "mfctrdoc.h"
#include "mfctrvw.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

HOUSEINFO rgHouseInfo[] = 
{
	{"100 Berry Lane", 0, NULL, NULL },
	{"523 Apple Road", 0, NULL, NULL},
	{"1212 Peach Street", 0, NULL, NULL},
	{"22 Daffodil Lane", 0, NULL, NULL},
	{"33542 Orchid Road", 0, NULL, NULL},
	{"64134 Lily Street", 0, NULL, NULL},
	{"33 Nicholas Lane", 0, NULL, NULL},
	{"555 Tracy Road", 0, NULL, NULL},
	{"446 Jean Street", 0, NULL, NULL}
};

/////////////////////////////////////////////////////////////////////////////
// CMfctreeView

IMPLEMENT_DYNCREATE(CMfctreeView, CView)

BEGIN_MESSAGE_MAP(CMfctreeView, CView)
	//{{AFX_MSG_MAP(CMfctreeView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMfctreeView construction/destruction

CMfctreeView::CMfctreeView()
{
	// TODO: add construction code here

}

CMfctreeView::~CMfctreeView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CMfctreeView drawing

void CMfctreeView::OnDraw(CDC* pDC)
{
	CMfctreeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CMfctreeView diagnostics

#ifdef _DEBUG
void CMfctreeView::AssertValid() const
{
	CView::AssertValid();
}

void CMfctreeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMfctreeDoc* CMfctreeView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMfctreeDoc)));
	return (CMfctreeDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMfctreeView message handlers

int CMfctreeView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	HICON hIcon;

   	if (CView::OnCreate(lpCreateStruct) == -1)			  
		return -1;

	// create the tree view control
	m_TreeCtl.Create(
		WS_VISIBLE | WS_CHILD | WS_BORDER | TVS_HASLINES | TVS_HASBUTTONS | 
			TVS_LINESATROOT, // styles
		CRect(0,0,0,0),	// bounding rectangle,
		this, //parent
		ID_TREEVIEW); //id

	// Create the image list we will need
	m_ImageList.Create(BITMAP_WIDTH,
		BITMAP_HEIGHT,
		FALSE,	// list does not include masks
		NUM_BITMAPS,
		0 );	// list won't grow

	// load the bitmaps and add them to the image lists
	hIcon = ::LoadIcon (AfxGetResourceHandle(), MAKEINTRESOURCE(IDI_FORSALE));
	m_idxForSale = m_ImageList.Add(hIcon);
	hIcon = ::LoadIcon (AfxGetResourceHandle(), MAKEINTRESOURCE(IDI_REDMOND));
	m_idxRedmond = m_ImageList.Add(hIcon);
	hIcon = ::LoadIcon (AfxGetResourceHandle(), MAKEINTRESOURCE(IDI_BELLEVUE));
	m_idxBellevue = m_ImageList.Add(hIcon);
	hIcon = ::LoadIcon (AfxGetResourceHandle(), MAKEINTRESOURCE(IDI_SEATTLE));
	m_idxSeattle = m_ImageList.Add(hIcon);

	// Make sure that all of the bitmaps were added
	if (m_ImageList.GetImageCount() < NUM_BITMAPS)
		return FALSE;

	// Associate the image list with the tree
	m_TreeCtl.SetImageList(TVSIL_NORMAL, &m_ImageList);

	// Add the items to the tree view
	AddTreeViewItems();

	return 0;
}

BOOL CMfctreeView::AddTreeViewItems()
{
	static HTREEITEM hPrev;
	int index;
	HTREEITEM hTRoot, hTRed, hTBel, hTSea;

	// First, add the root item "Houses for Sale"
	hTRoot = AddOneItem((HTREEITEM)NULL, "For Sale", (HTREEITEM)TVI_ROOT, m_idxForSale);

	// Now add the Cities
	hTRed = AddOneItem(hTRoot, "Redmond", (HTREEITEM)TVI_FIRST, m_idxRedmond);
	hTBel = AddOneItem(hTRoot, "Bellevue", hTRed, m_idxBellevue);
	hTSea = AddOneItem(hTRoot, "Seattle", hTBel, m_idxSeattle);

	// Fill in the structure for each house
	FillInStruct(hTRed, m_idxRedmond, 0, 3);
	FillInStruct(hTBel, m_idxBellevue, 3, 6);
	FillInStruct(hTSea, m_idxSeattle, 6, 9);

	hPrev = hTSea;
	for (index = 0; index < NUM_HOUSES; index++)
	{
		hPrev = AddOneItem(rgHouseInfo[index].hParent, 
						rgHouseInfo[index].szAddress,
						hPrev,
						rgHouseInfo[index].iImage);
		rgHouseInfo[index].hItem = hPrev;
	}
	return TRUE;
}

VOID CMfctreeView::FillInStruct(HTREEITEM hParent, int iImage, int index, int iMax)
{
	for (;index < iMax; index++)
	{
		rgHouseInfo[index].iImage = iImage;
		rgHouseInfo[index].hParent = hParent;
	}
}

/***************************************************************************
* 
*    FUNCTION: AddOneItem(HTREEITEM, LPSTR, HTREEITEM, int)
*
*    PURPOSE: Inserts a tree view item in the specified place. 
*
****************************************************************************/

HTREEITEM CMfctreeView::AddOneItem( HTREEITEM hParent, LPSTR szText, HTREEITEM hInsAfter, 
	int iImage)
{
	HTREEITEM hItem;
	TV_ITEM tvI;
	TV_INSERTSTRUCT tvIns;

	tvI.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM;
	tvI.pszText = szText;
	tvI.cchTextMax = lstrlen(szText);
	tvI.iImage = iImage;
	tvI.iSelectedImage = iImage;

	tvIns.item = tvI;
	tvIns.hInsertAfter = hInsAfter;
	tvIns.hParent = hParent;
	
	hItem = m_TreeCtl.InsertItem(&tvIns);

	return (hItem);

}

void CMfctreeView::OnSize(UINT nType, int cx, int cy) 
{
	m_TreeCtl.MoveWindow(0, 0, cx, cy);	
}

void CMfctreeView::OnDestroy() 
{

	CView::OnDestroy();
	
}

// Handle the WM_NOTIFY::TVN_BEGINDRAG notification.
LRESULT CMfctreeView::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	TV_ITEM tvI;
	if (message == WM_NOTIFY)
	{
		if ( ((LPNMHDR)lParam)->code == TVN_BEGINDRAG )
		{
			BeginDrag((NM_TREEVIEW *)lParam);
			tvI = ((NM_TREEVIEW *)lParam)->itemNew;

			// Get a handle to the drag object.
			m_hDragItem = tvI.hItem;
		}
	}
	return CView::WindowProc(message, wParam, lParam);
}


void CMfctreeView::OnMouseMove(UINT nFlags, CPoint point) 
{
	HTREEITEM hTarget;
	UINT flags;

	if (m_fDragging)
	{
		// Drag the item to the current mouse position.
		m_ImageList.DragMove(point);

		flags = TVHT_ONITEM;
		// if the cursor is on an item, highlight it as the drop target.
		if ((hTarget = m_TreeCtl.HitTest(point, &flags)) != NULL)
			m_TreeCtl.SelectDropTarget(hTarget);
	}
		
	CView::OnMouseMove(nFlags, point);
}

void CMfctreeView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// If dragging, stop it.
	if (m_fDragging)
	{
		// Process the item drop.
		DropItem(m_hDragItem);
				
		m_ImageList.EndDrag();

		// Release the mouse.
		ReleaseCapture();

		// Show the normal cursor.
		ShowCursor(TRUE);

		// Reset boolean.
		m_fDragging = FALSE;
	}
	
	CView::OnLButtonUp(nFlags, point);
}


/****************************************************************************
* 
*    FUNCTION: BeginDrag(NM_TREEVIEW *)
*
*    PURPOSE: This function proceeses the beginning of a drag operation. 
*
****************************************************************************/
VOID CMfctreeView::BeginDrag(NM_TREEVIEW *lItem)
{
	CImageList * CImage;

	// Create an image to use for dragging.
	CImage = m_TreeCtl.CreateDragImage(lItem->itemNew.hItem);

	// Start dragging the image.
	CImage->BeginDrag(0, lItem->ptDrag);

	// Hide the cursor
	ShowCursor(FALSE);
	SetCapture();
	m_fDragging = TRUE;
}

/****************************************************************************
* 
*    FUNCTION: DropItem(HTREEITEM)
*
*    PURPOSE: This function proceeses the drop consequences. 
*
****************************************************************************/
VOID CMfctreeView::DropItem(HTREEITEM hDragItem)
{
	HTREEITEM hParent, hNewItem, hTarget;
	TV_ITEM tvTarget;
	int index;

	// Get the handle to the drop target.
	hTarget = m_TreeCtl.GetDropHilightItem();
					
	// Get the parent of the drop target.
	hParent = m_TreeCtl.GetParentItem(hTarget);

	// Get the image information.
	tvTarget.hItem = hTarget;
	tvTarget.mask = TVIF_IMAGE;
	m_TreeCtl.GetItem(&tvTarget);

	for (index = 0; index < NUM_HOUSES; index++)
	{
		if (rgHouseInfo[index].hItem == hDragItem)
			break;
	}

	if (index == NUM_HOUSES)
		index--;

	// Insert the new item back in.
	hNewItem = AddOneItem( hParent, rgHouseInfo[index].szAddress, hTarget, 
						tvTarget.iImage);

	// Delete the "dragged" item.
	m_TreeCtl.DeleteItem(hDragItem);

	// Reset the drop target to NULL.
	m_TreeCtl.SelectDropTarget((HTREEITEM)NULL);
}

