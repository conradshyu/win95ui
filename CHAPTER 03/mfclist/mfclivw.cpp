// mfclivw.cpp : implementation of the CMfclistView class
//

#include "stdafx.h"
#include "mfclist.h"

#include "mfclidoc.h"
#include "mfclivw.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

HOUSEINFO rgHouseInfo[] = 
{
	{"100 Berry Lane", "Redmond", 175000, 3, 2 },
	{"523 Apple Road", "Redmond", 125000, 4, 2},
	{"1212 Peach Street", "Redmond",200000, 4, 3},
	{"22 Daffodil Lane", "Bellevue", 2500000, 4, 4},
	{"33542 Orchid Road", "Bellevue", 180000, 3, 2},
	{"64134 Lily Street", "Bellevue", 250000, 4, 3},
	{"33 Nicholas Lane", "Seattle", 350000, 3, 2},
	{"555 Tracy Road", "Seattle", 140000, 3, 2},
	{"446 Jean Street", "Seattle", 225000, 4, 3}
};

char *szColumns[] = {"Address" , "City", "Price", "Bedrooms","Bathrooms"};

/////////////////////////////////////////////////////////////////////////////
// CMfclistView

IMPLEMENT_DYNCREATE(CMfclistView, CView)

BEGIN_MESSAGE_MAP(CMfclistView, CView)
	//{{AFX_MSG_MAP(CMfclistView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(IDM_DETAILS, OnDetails)
	ON_COMMAND(IDM_LARGEICON, OnLargeicon)
	ON_COMMAND(IDM_LISTVIEW, OnListview)
	ON_COMMAND(IDM_SMALLICON, OnSmallicon)
	ON_COMMAND(IDM_EXIT, OnExit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMfclistView construction/destruction

CMfclistView::CMfclistView()
{
	// TODO: add construction code here

}

CMfclistView::~CMfclistView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CMfclistView drawing

void CMfclistView::OnDraw(CDC* pDC)
{
	CMfclistDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CMfclistView diagnostics

#ifdef _DEBUG
void CMfclistView::AssertValid() const
{
	CView::AssertValid();
}

void CMfclistView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMfclistDoc* CMfclistView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMfclistDoc)));
	return (CMfclistDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMfclistView message handlers

int CMfclistView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	int index;
	int iSubItem;
	HICON hIcon;
	LV_COLUMN lvC;      		// list view column structure
	static char szText[256];    // place to store some text
	LV_ITEM lvI;        		// list view item structure
	

	if (CView::OnCreate(lpCreateStruct) == -1)			  
		return -1;
	
	// Create the CListCtrl window.
	m_ListCtl.Create(
		WS_VISIBLE | WS_CHILD | WS_BORDER | LVS_REPORT | LVS_EDITLABELS, // styles
		CRect(0,0,0,0),	// bounding rectangle
		this, 			// parent
		ID_LISTVIEW);	// ID
	
	// create the large icon image list.
	m_ImageLarge.Create(LARGE_BITMAP_WIDTH,
		LARGE_BITMAP_HEIGHT,
		FALSE,			// list does not include masks
		NUM_BITMAPS,
		0 );			// list won't grow

	// Create the small icon image list.
	m_ImageSmall.Create(SMALL_BITMAP_WIDTH,
		SMALL_BITMAP_HEIGHT,
		FALSE,			// list does not include masks
		NUM_BITMAPS,
		0 );			// list won't grow

	// Load the icons and add them to the image lists.
	for (index = IDI_BELLEVUE; index <= IDI_SEATTLE ; index++)
	{
		hIcon = ::LoadIcon (AfxGetResourceHandle(), MAKEINTRESOURCE(index));
		// You have 3 of each type of icon here, so add 3 at a time.
		for (iSubItem = 0; iSubItem < 3; iSubItem++)
		{
			if ((m_ImageSmall.Add(hIcon) == -1) ||
				(m_ImageLarge.Add(hIcon) == -1))
				return NULL;
		}
	}
	
	// Be sure that all the small icons were added.
	if (m_ImageSmall.GetImageCount() < 3)
		return NULL;

	// Be sure that all of large icons were added.
	if (m_ImageLarge.GetImageCount() < 3)
		return NULL;

	// Associate the image lists with the list view control.
	m_ListCtl.SetImageList(&m_ImageSmall, LVSIL_SMALL);
	m_ListCtl.SetImageList(&m_ImageLarge, LVSIL_NORMAL);

	// Now initialize the columns you will need.
	// Initialize the LV_COLUMN structure.
	// The mask specifies that the fmt, width, pszText, and subitem members
	// of the structure are valid.
	lvC.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	lvC.fmt = LVCFMT_LEFT;  // left-align column
	lvC.cx = 75;            // width of column in pixels

	// Add the columns.
	for (index = 0; index < NUM_COLUMNS; index++)
	{
		lvC.iSubItem = index;
		lvC.pszText = szColumns[index];
		
		if (m_ListCtl.InsertColumn(index, &lvC) == -1)
			return NULL;
	}

	// Finally, add the actual items to the control.
	// Fill out the LV_ITEM structure for each item to add to the list.
	// The mask specifies that the pszText, iImage, lParam and state
	// members of the LV_ITEM structure are valid.
	lvI.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM | LVIF_STATE;
	lvI.state = 0;      
	lvI.stateMask = 0;  

	for (index = 0; index < NUM_ITEMS; index++)
	{
		lvI.iItem = index;
		lvI.iSubItem = 0;
		// The parent window is responsible for storing the text. 
		// The list view control will send an LVN_GETDISPINFO 
		// when it needs the text to display.
		lvI.pszText = LPSTR_TEXTCALLBACK; 
		lvI.cchTextMax = MAX_ITEMLEN;
		lvI.iImage = index;
		lvI.lParam = (LPARAM)&rgHouseInfo[index];

		if (m_ListCtl.InsertItem(&lvI) == -1)
			return NULL;

		for (iSubItem = 1; iSubItem < NUM_COLUMNS; iSubItem++)
		{
			m_ListCtl.SetItemText( index,
				iSubItem,
				LPSTR_TEXTCALLBACK);
		}

	}
	return 0;
}


void CMfclistView::OnSize(UINT nType, int cx, int cy) 
{
	m_ListCtl.MoveWindow(0, 0, cx, cy);
	
}

void CMfclistView::OnDetails() 
{
	DWORD dwStyle;

	dwStyle = GetWindowLong(m_ListCtl.m_hWnd, GWL_STYLE);
					
	if ((dwStyle & LVS_TYPEMASK) != LVS_REPORT)
		SetWindowLong(m_ListCtl.m_hWnd, GWL_STYLE,
			(dwStyle & ~LVS_TYPEMASK) | LVS_REPORT);
}

void CMfclistView::OnLargeicon() 
{
	DWORD dwStyle;

	dwStyle = GetWindowLong(m_ListCtl.m_hWnd, GWL_STYLE);
					
	if ((dwStyle & LVS_TYPEMASK) != LVS_ICON)
		SetWindowLong(m_ListCtl.m_hWnd, GWL_STYLE,
			(dwStyle & ~LVS_TYPEMASK) | LVS_ICON);	
}

void CMfclistView::OnListview() 
{
	DWORD dwStyle;

	dwStyle = GetWindowLong(m_ListCtl.m_hWnd, GWL_STYLE);
					
	if ((dwStyle & LVS_TYPEMASK) != LVS_LIST)
		SetWindowLong(m_ListCtl.m_hWnd, GWL_STYLE,
			(dwStyle & ~LVS_TYPEMASK) | LVS_LIST);
		
	
}

void CMfclistView::OnSmallicon() 
{
	DWORD dwStyle;

	dwStyle = GetWindowLong(m_ListCtl.m_hWnd, GWL_STYLE);
					
	if ((dwStyle & LVS_TYPEMASK) != LVS_SMALLICON)
		SetWindowLong(m_ListCtl.m_hWnd, GWL_STYLE,
			(dwStyle & ~LVS_TYPEMASK) | LVS_SMALLICON);
}

LRESULT CMfclistView::NotifyHandler(UINT message, WPARAM wParam, LPARAM lParam) 
{
	LV_DISPINFO *pLvdi = (LV_DISPINFO *)lParam;
	NM_LISTVIEW *pNm = (NM_LISTVIEW *)lParam;
	HOUSEINFO *pHouse = (HOUSEINFO *)(pLvdi->item.lParam);
	static char szText[64];

	if (wParam != ID_LISTVIEW)
		return 0L;

	switch(pLvdi->hdr.code)
	{
		case LVN_GETDISPINFO:

			switch (pLvdi->item.iSubItem)
			{
				case 0:     // Address
					pLvdi->item.pszText = pHouse->szAddress;
					break;

				case 1:     // City
					pLvdi->item.pszText = pHouse->szCity;
					break;

				case 2:     // Price
					sprintf(szText, "$%u", pHouse->iPrice);
					pLvdi->item.pszText = szText;
					break;

				case 3:     // Number of bedrooms
					sprintf(szText, "%u", pHouse->iBeds);
					pLvdi->item.pszText = szText;
					break;

				case 4:     // Number of bathrooms
					sprintf(szText, "%u", pHouse->iBaths);
					pLvdi->item.pszText = szText;
					break;

				default:
					break;
			}
			break;
        case LVN_BEGINLABELEDIT:
            {
            CEdit *pEdit;

            // Get the handle to the edit control.
            pEdit = m_ListCtl.GetEditControl();
            // Limit the amount of text that teh user can enter.
            pEdit->LimitText(20);
            }
            break;

        case LVN_ENDLABELEDIT:
            // If label editing wasn't cancelled and the 
            // text buffer is non-NULL...
            if ((pLvdi->item.iItem != -1) && (pLvdi->item.pszText != NULL))
                // save the new label information.
	    		lstrcpy(pHouse->szAddress, pLvdi->item.pszText);
            break;

		case LVN_COLUMNCLICK:
			// The user clicked on one of the column headings - sort by
			// this column.
			m_ListCtl.SortItems( ListViewCompareProc,
								(LPARAM)(pNm->iSubItem));
			break;

		default:
			break;
	}
	return 0L;
}

// this is static

int CALLBACK CMfclistView::ListViewCompareProc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	HOUSEINFO *pHouse1 = (HOUSEINFO *)lParam1;
	HOUSEINFO *pHouse2 = (HOUSEINFO *)lParam2;
	LPSTR lpStr1, lpStr2;
	int iResult;


	if (pHouse1 && pHouse2)
	{
		switch( lParamSort)
		{
			case 0:     // sort by Address
				lpStr1 = pHouse1->szAddress;
				lpStr2 = pHouse2->szAddress;
				iResult = lstrcmpi(lpStr1, lpStr2);
				break;

			case 1:     // sort by City
				lpStr1 = pHouse1->szCity;
				lpStr2 = pHouse2->szCity;
				iResult = lstrcmpi(lpStr1, lpStr2);
				break;

			case 2:     // sort by Price
				iResult = pHouse1->iPrice - pHouse2->iPrice;
				break;

			case 3:     // sort by the number of bedrooms
				iResult = pHouse1->iBeds - pHouse2->iBeds;
				break;

			case 4:     // sort by the number of bathrooms
				iResult = pHouse1->iBaths - pHouse2->iBaths;
				break;

			default:
				iResult = 0;
				break;

		}

	}
	return(iResult);
}

LRESULT CMfclistView::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	if (message == WM_NOTIFY)
		NotifyHandler(message, wParam, lParam);
			
	return CView::WindowProc(message, wParam, lParam);
}

void CMfclistView::OnExit() 
{
	PostQuitMessage(0);	
}
