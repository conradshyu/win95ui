// mfcexvw.cpp : implementation of the CMfcexpView class
//

#include "stdafx.h"
#include "mfcexp.h"

#include "mfcexdoc.h"
#include "chicoapp.h"
#include "mfcexvw.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


static char BASED_CODE szFilter[] = "Text Files (*.txt) | *.txt; *.txt | All Files (*.*) | *.* ||";

// tool bar buttons
TBBUTTON tbButtons[] = {
    { 0, IDM_NEW, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0},
    { 1, IDM_OPEN, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0},
    { 2, IDM_SAVE, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0},
	{ 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, 0},
    { 3, IDM_ADDHOUSE, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0},
    { 4, IDM_REMHOUSE, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0},
    { 5, IDM_ADDCITY, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0},
	{ 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, 0},
    { 6, IDM_LARGEICON, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0},
    { 7, IDM_SMALLICON, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0},
    { 8, IDM_LISTVIEW, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0},
    { 9, IDM_REPORTVIEW, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0},
};


/////////////////////////////////////////////////////////////////////////////
// CMfcexpView

IMPLEMENT_DYNCREATE(CMfcexpView, CView)

BEGIN_MESSAGE_MAP(CMfcexpView, CView)
	//{{AFX_MSG_MAP(CMfcexpView)
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_COMMAND(IDM_LISTVIEW, OnListview)
	ON_COMMAND(IDM_REPORTVIEW, OnReportview)
	ON_COMMAND(IDM_LARGEICON, OnLargeicon)
	ON_COMMAND(IDM_SMALLICON, OnSmallicon)
	ON_COMMAND(IDM_ADDCITY, OnAddcity)
	ON_COMMAND(IDM_ADDHOUSE, OnAddhouse)
	ON_COMMAND(IDM_PROPERTIES, OnProperties)
	ON_COMMAND(IDM_REMHOUSE, OnRemhouse)
	ON_COMMAND(IDM_NEW, OnNew)
	ON_COMMAND(IDM_OPEN, OnOpen)
	ON_COMMAND(IDM_SAVE, OnSave)
	ON_COMMAND(IDM_SAVEAS, OnSaveas)
	//}}AFX_MSG_MAP

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAddCity dialog


CAddCity::CAddCity(CWnd* pParent /*=NULL*/)
	: CDialog(CAddCity::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAddCity)
	m_City = _T("");
	//}}AFX_DATA_INIT
}


void CAddCity::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAddCity)
	DDX_Text(pDX, IDE_CITY, m_City);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAddCity, CDialog)
	//{{AFX_MSG_MAP(CAddCity)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CAddHouse dialog


CAddHouse::CAddHouse(CWnd* pParent /*=NULL*/)
	: CDialog(CAddHouse::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAddHouse)
	m_Address = _T("");
	m_Price = 0;
	m_Bathrooms = 0;
	m_Bedrooms = 0;
	m_City = _T("");
	//}}AFX_DATA_INIT
}


void CAddHouse::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAddHouse)
	DDX_Text(pDX, IDE_ADDRESS, m_Address);
	DDX_Text(pDX, IDE_PRICE, m_Price);
	DDX_Text(pDX, IDE_BATHROOMS, m_Bathrooms);
	DDX_Text(pDX, IDE_BEDROOMS, m_Bedrooms);
	DDX_CBString(pDX, IDC_CITY, m_City);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAddHouse, CDialog)
	//{{AFX_MSG_MAP(CAddHouse)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CRemHouse dialog


CRemHouse::CRemHouse(CWnd* pParent /*=NULL*/)
	: CDialog(CRemHouse::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRemHouse)
	m_List = _T("");
	//}}AFX_DATA_INIT
}


void CRemHouse::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRemHouse)
	DDX_LBString(pDX, ID_LISTBOX, m_List);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRemHouse, CDialog)
	//{{AFX_MSG_MAP(CRemHouse)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CProperties

IMPLEMENT_DYNAMIC(CProperties, CPropertySheet)

CProperties::CProperties(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
}

CProperties::CProperties(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
}

CProperties::~CProperties()
{
}


BEGIN_MESSAGE_MAP(CProperties, CPropertySheet)
	//{{AFX_MSG_MAP(CProperties)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMfcexpView construction/destruction

CMfcexpView::CMfcexpView()
{
	// TODO: add construction code here

}

CMfcexpView::~CMfcexpView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CMfcexpView drawing

void CMfcexpView::OnDraw(CDC* pDC)
{
	CMfcexpDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CMfcexpView diagnostics

#ifdef _DEBUG
void CMfcexpView::AssertValid() const
{
	CView::AssertValid();
}

void CMfcexpView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMfcexpDoc* CMfcexpView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMfcexpDoc)));
	return (CMfcexpDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMfcexpView message handlers

void CMfcexpView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
    // Resize the toolbar.
    m_Toolbar.AutoSize();

	// Resize the status bar.
    // Make it fit along the bottom of the client area.
    m_StatusBar.MoveWindow(0, cx - 10, cy, cy - 10);
    
    // Set the rectangle for each part of the status bar.
    // Make each 1/2 of the width of the client area.
    int aWidths[2];

    aWidths[0] = cx / 2;
    aWidths[1] = -1;
    m_StatusBar.SetParts(2, aWidths);

	m_TreeCtl.MoveWindow(0, 25, cx / 4, cy - 45);

	m_ListCtl.MoveWindow(cx / 4, 25, cx, cy - 45);
}

int CMfcexpView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
    m_NumCities = 0;
    m_NumHouses = 0;
    m_iSelected = -1;
	memset(m_lpstrFile, '\0', MAX_TITLE);

    if (CreateAppWindows() == FALSE)
      return FALSE;
	
	return 0;
}

void CMfcexpView::OnDestroy() 
{
	CView::OnDestroy();
	
	// TODO: Add your message handler code here
	
}

/****************************************************************************
*
*    FUNCTION: CreateAppWindows()
*
*    PURPOSE:  Creates all of the child windows to be used in mfcexp
*
****************************************************************************/

BOOL CMfcexpView::CreateAppWindows()
{
    static char szBuf[MAX_PATH];
	HICON hIcon;                // handle to an icon
	int index;                  // index used in for loops
	LV_COLUMN lvC;              // list view column structure
	char szText[MAX_ITEMLEN];   // place to store some text

    // Ensure that the common control DLL is loaded.
	InitCommonControls();

	// Create the status bar.
	m_StatusBar.Create( WS_CHILD | WS_BORDER | WS_VISIBLE | SBS_SIZEGRIP, 
        CRect(0,0,0,0),
        this,
        ID_STATUSBAR);

    // Set the status bar to have two parts.
    int aWidths[2] = {0,0};
    m_StatusBar.SetParts(2, aWidths);
    // Set the text for the status bar.
    ChangeSBText(-1);

	// Create the toolbar.
    m_Toolbar.Create(
		WS_CHILD | WS_BORDER | WS_VISIBLE | TBSTYLE_TOOLTIPS,   // styles
        CRect(0,0,0,0),
        this,
        ID_TOOLBAR);

    // Add the bitmaps.
    m_Toolbar.AddBitmap(NUM_BITMAPS, IDB_TOOLBAR);

    // Add the buttons.
    m_Toolbar.AddButtons(NUM_BUTTONS, (LPTBBUTTON)&tbButtons);

	// Create the CListCtrl window.
	m_ListCtl.Create(
		WS_VISIBLE | WS_CHILD | WS_BORDER | LVS_REPORT | LVS_EDITLABELS,
		CRect(0,0,0,0),	// bounding rectangle
		this, //parent
		ID_LISTVIEW); // ID
	
	// Create the large icon image list.
	m_ImageLarge.Create(LARGE_BITMAP_WIDTH,
		LARGE_BITMAP_HEIGHT,
		FALSE,	// list does not include masks
		NUM_BITMAPS,
		10 );	// list won't grow

	// Create the small icon image list	.
	m_ImageSmall.Create(SMALL_BITMAP_WIDTH,
		SMALL_BITMAP_HEIGHT,
		FALSE,	// list does not include masks
		NUM_BITMAPS,
		10 );	// list won't grow

 	// Load the house icon.
    hIcon = ::LoadIcon ( AfxGetResourceHandle(), MAKEINTRESOURCE(IDI_SEATTLE));
	m_idxSeattle = m_ImageSmall.Add(hIcon);
	m_ImageLarge.Add(hIcon);
	hIcon = ::LoadIcon (AfxGetResourceHandle(), MAKEINTRESOURCE(IDI_BELLEVUE));
	m_idxBellevue = m_ImageSmall.Add(hIcon);
	m_ImageLarge.Add(hIcon);
	hIcon = ::LoadIcon (AfxGetResourceHandle(), MAKEINTRESOURCE(IDI_REDMOND));
	m_idxRedmond = m_ImageSmall.Add(hIcon);
	m_ImageLarge.Add(hIcon);

	// Associate the image lists with the list view control.
	m_ListCtl.SetImageList(&m_ImageSmall, LVSIL_SMALL);
	m_ListCtl.SetImageList(&m_ImageLarge, LVSIL_NORMAL);

	// Now initialize the columns you will need.
	// Initialize the LV_COLUMN structure.
	// The mask specifies that the fmt, cx, pszText, and iSubitem
	// members of the structure are valid.
	lvC.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	lvC.fmt = LVCFMT_LEFT;  // left-align the column
	lvC.cx = 75;            // width of column in pixels
	lvC.pszText = szText;

	// Add the columns.
	for (index = 0; index < NUM_COLUMNS; index++)
	{
		lvC.iSubItem = index;
		::LoadString( AfxGetResourceHandle(), 
					IDS_ADDRESS + index,
					szText,
					sizeof(szText));
		
		if (m_ListCtl.InsertColumn(index, &lvC) == -1)
			return NULL;
	}

    // Create the tree view control.
	m_TreeCtl.Create(
		WS_VISIBLE | WS_CHILD | WS_BORDER | TVS_HASLINES | TVS_HASBUTTONS | 
			TVS_LINESATROOT, // styles
		CRect(0,0,0,0),	// bounding rectangle
		this, // parent
		ID_TREEVIEW); // ID

	// Load the bitmaps and add them to the image list.
	hIcon = ::LoadIcon (AfxGetResourceHandle(), MAKEINTRESOURCE(IDI_FORSALE));
	m_idxForSale = m_ImageSmall.Add(hIcon);
	hIcon = ::LoadIcon (AfxGetResourceHandle(), MAKEINTRESOURCE(IDI_SELECTED));
	m_idxSeaSel = m_ImageSmall.Add(hIcon);
	hIcon = ::LoadIcon (AfxGetResourceHandle(), MAKEINTRESOURCE(IDI_SELBELL));
	m_idxBellSel = m_ImageSmall.Add(hIcon);
	hIcon = ::LoadIcon (AfxGetResourceHandle(), MAKEINTRESOURCE(IDI_REDSEL));							 
	m_idxRedSel = m_ImageSmall.Add(hIcon);
	
	// Associate the image list with the tree view control.
	m_TreeCtl.SetImageList(TVSIL_NORMAL, &m_ImageSmall);

	TV_InitTreeView();
    return TRUE;

}

/****************************************************************************
* 
*    FUNCTION: TV_InitTreeView()
*
*    PURPOSE:  Initializes the tree view window 
*
****************************************************************************/
void CMfcexpView::TV_InitTreeView()
{
    char szText[MAX_CITY];

    // Add the root item "Houses for Sale"
	int idxForSale;

	idxForSale = ::LoadString(AfxGetResourceHandle(), IDS_FORSALE, szText, MAX_LEN);
    m_hTPrev = (HTREEITEM)TVI_ROOT;
    m_hParent = (HTREEITEM)NULL;
	m_hTRoot = TV_AddOneItem(szText, -1, m_idxForSale, m_idxForSale );

    // reset the previous and image
    m_hParent = m_hTRoot;
    m_hTPrev = (HTREEITEM)TVI_FIRST;
}

/****************************************************************************
*
*    FUNCTION: ChangeSBText(int)
*
*    PURPOSE:  Changes the text in the status bar to reflect the
*              currently selected item.
*
****************************************************************************/
void CMfcexpView::ChangeSBText(int iNumSelected)
{
    static char szBuf1[MAX_LEN];
    static char szBuf2[MAX_LEN];
    static char szSelected[MAX_LEN];
    char szText[MAX_ITEMLEN];
    int NumHouses;

    if (szBuf1[0] == '\0')
	::LoadString (AfxGetResourceHandle(), IDS_SELECTED, szBuf1, sizeof(szBuf1));

    if (szBuf2[0] == '\0')
	::LoadString (AfxGetResourceHandle(), IDS_NUMHOUSES, szBuf2, sizeof(szBuf2));

    if (iNumSelected == -1)
    {
		lstrcpy( szSelected, "None");
		NumHouses = 0;
    }
    else
    {
		lstrcpy( szSelected, m_rgCities[iNumSelected].szCity);
		NumHouses = m_rgCities[iNumSelected].NumHouses;
    }

    sprintf(szText, "%s %s", szBuf1, szSelected);
    m_StatusBar.SetText( (LPCTSTR)szText, 0, 0);

    sprintf(szText, "%s %d", szBuf2, NumHouses);
    m_StatusBar.SetText( (LPCTSTR)szText, 1, 0);
}

 
/****************************************************************************
*
*    FUNCTION: InitTreeAndList(VOID)
*
*    PURPOSE:  Initializes the tree and list view windows.
*
****************************************************************************/
void CMfcexpView::InitTreeAndList( void )
{
    m_NumCities = 0;
    m_NumHouses = 0;
	m_iSelHouse = -1;
    m_TreeCtl.DeleteAllItems();
	m_ListCtl.DeleteAllItems();
    TV_InitTreeView();
	memset(m_lpstrFile, '\0', MAX_TITLE);

}

/***************************************************************************
* 
*    FUNCTION: TV_AddOneItem(HTREEITEM, LPSTR)
*
*    PURPOSE: Inserts a tree view item in the specified place. 
*
****************************************************************************/
HTREEITEM CMfcexpView::TV_AddOneItem( CString szText, int index, int idxImage,
	int idxSelected)
{
	HTREEITEM hItem;
	TV_ITEM tvI;
	TV_INSERTSTRUCT tvIns;

	tvI.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM;
	tvI.pszText = (LPSTR)(LPCTSTR)szText;
	tvI.cchTextMax = szText.GetLength();
	tvI.iImage = idxImage;
    tvI.iSelectedImage = idxSelected;
    tvI.lParam = index;             // save the index of the item

	tvIns.item = tvI;
    tvIns.hInsertAfter = m_hTPrev;
	tvIns.hParent = m_hParent;
	
	hItem = m_TreeCtl.InsertItem(&tvIns);

    if (hItem == NULL)
        AfxMessageBox("TVM_INSERTITEM failed");

	return (hItem);

}
/****************************************************************************
*
*    FUNCTION: ParseFile()
*
*    PURPOSE:  Parses the current file buffer.
*
*    COMMENTS:
*
*        This function will parse the current file buffer and initialize
*        the global city and house information structures.
*
*        The file is an editable ASCII file and set up as follows:
*           - Number of cities
*           - A string representing each city for # of cities specified above
*           - Number of houses
*           - House information for each house. One line per house.
*             The fields are separated by commas and are in the following
*             order:
*                   Address
*                   City
*                   Price
*                   Bedrooms
*                   Bathrooms
*
*    RETURN VALUES:
*        TRUE - The file was parsed successfully.
*        FALSE - The parsing failed.
*
****************************************************************************/
BOOL CMfcexpView::ParseFile ( void )
{
    int count, result, index;
    char szAddress[MAX_ADDRESS], szCity[MAX_CITY], szTemp[MAX_PATH], 
    	szBeds[TEMP_LEN], szBaths[TEMP_LEN], szAgent[MAX_LEN], szPhone[MAX_LEN];
    char * lpSave;

    // initialize the tree view and list view windows
    InitTreeAndList();

    lpSave = m_lpBufPtr;

    // read in the first line to get the number of cities
    sscanf( m_lpBufPtr, "%s\n", szTemp);
    m_NumCities = atoi(szTemp);

    // move the buffer pointer
    while (*m_lpBufPtr != 0x0A)
		m_lpBufPtr++;
    m_lpBufPtr++;

    if (m_NumCities == 0 || m_NumCities > MAX_CITIES)
    {
		AfxMessageBox("Number of cities must be between 1 and 16");
		::GlobalFree(m_lpBufPtr);
		return FALSE;
    }
     
    // read a city for each line
    for (count= 0; count < m_NumCities; count++)
    {
		sscanf( m_lpBufPtr, "%s\n", szCity);

		// move the buffer pointer
		while (*m_lpBufPtr != 0x0A)
	    	m_lpBufPtr++;
		m_lpBufPtr++;

		// copy over the city
		lstrcpy((LPTSTR)m_rgCities[count].szCity.GetBuffer(MAX_CITY), szCity);
		m_rgCities[count].szCity.ReleaseBuffer();

		// Add the city to the tree view
		if (lstrcmp(szCity,"Redmond") == 0)
			m_hTPrev = TV_AddOneItem( m_rgCities[count].szCity, count, 
				m_idxRedmond, m_idxRedSel);
		else if (lstrcmp(szCity,"Bellevue") == 0)
			m_hTPrev = TV_AddOneItem( m_rgCities[count].szCity, count, 
				m_idxBellevue, m_idxBellSel);
		else 		
			m_hTPrev = TV_AddOneItem( m_rgCities[count].szCity, count, 
				m_idxSeattle, m_idxSeaSel);

		// zero out number of houses in the city
		m_rgCities[count].NumHouses=0;
    }
	
    // get the number of houses
    sscanf( m_lpBufPtr, "%s\n", szTemp);
    m_NumHouses = atoi(szTemp);

    // move the buffer pointer
    while (*m_lpBufPtr != 0x0A)
		m_lpBufPtr++;
    m_lpBufPtr++;

    if (m_NumHouses == 0 || m_NumHouses > MAX_HOUSES)
    {
		AfxMessageBox("Number of houses must be between 1 and 256");
		::GlobalFree(m_lpBufPtr);
		return FALSE;
    }


    // read a house information for each line
    for (count= 0; count < m_NumHouses; count++)
    {
		result = sscanf(m_lpBufPtr, "%[^','],%[^','],%[^','],%[^','],%[^','],%[^','],%s", 
	    	szAddress, 
	    	szCity, 
	    	szTemp, szBeds, szBaths, 
	    	szAgent, 
	    	szPhone ); 

		m_rgHouses[count].iPrice = atoi(szTemp);
		m_rgHouses[count].iBeds = atoi(szBeds);
		m_rgHouses[count].iBaths = atoi(szBaths);

		lstrcpy((LPTSTR)m_rgHouses[count].szAddress.GetBuffer(MAX_ADDRESS), szAddress);
		lstrcpy((LPTSTR)m_rgHouses[count].szCity.GetBuffer(MAX_CITY), szCity);
		lstrcpy((LPTSTR)m_rgHouses[count].szAgent.GetBuffer(MAX_LEN), szAgent);
		lstrcpy((LPTSTR)m_rgHouses[count].szNumber.GetBuffer(MAX_LEN), szPhone);

		m_rgHouses[count].szAddress.ReleaseBuffer();
		m_rgHouses[count].szCity.ReleaseBuffer();
		m_rgHouses[count].szAgent.ReleaseBuffer();
		m_rgHouses[count].szNumber.ReleaseBuffer();

		if (lstrcmp(szCity,"Redmond") == 0)
			m_rgHouses[count].iImage = m_idxRedmond; 
		else if (lstrcmp(szCity,"Bellevue") == 0)
			m_rgHouses[count].iImage = m_idxBellevue; 
		else 		
			m_rgHouses[count].iImage = m_idxSeattle; 

		// move the buffer pointer
		while (*m_lpBufPtr != 0x0A)
	    	m_lpBufPtr++;
		m_lpBufPtr++;

		// increment the house count for the city
		for (index=0;index < m_NumCities; index++)
		{
	    	if (m_rgHouses[count].szCity == m_rgCities[index].szCity)
	    	{
				m_rgCities[index].NumHouses++;
				break;
	    	}
		}
    }
    // free up the buffer
    ::GlobalFree(m_lpBufPtr);

    return TRUE;
}

/****************************************************************************
*
*    FUNCTION: UpdateListView(  int )
*
*    PURPOSE:  Updates the list view to show only the houses for sale
*              in the currently selected city.
*
****************************************************************************/
void CMfcexpView::UpdateListView(  int iSelected )
{
    int count, index;

    m_ListCtl.DeleteAllItems();
	
	if (m_iSelected == -1)
		return;

    for (index = 0, count = 0; count < m_NumHouses; count++)
    {
	if (m_rgHouses[count].szCity == m_rgCities[iSelected].szCity) 
	{
	    // Add the house to the list view
	    if (!LV_AddItem(index, &m_rgHouses[count]))
			AfxMessageBox("LV_AddItem failed!", NULL, MB_OK);
	    index++;
	}
    }
}
/****************************************************************************
*
*    FUNCTION: OnNew()
*
*    PURPOSE:  Processes the New menu command by initalizing the windows.
*
****************************************************************************/
void CMfcexpView::OnNew() 
{
 	// initialize the tree view and list view windows
    InitTreeAndList();
}

/****************************************************************************
*
*    FUNCTION: OnOpen()
*
*    PURPOSE:  Processes the File.Open command
*
****************************************************************************/
void CMfcexpView::OnOpen()
{

	CFileDialog Dlg(TRUE, "*.txt", m_lpstrFile, 
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		szFilter);

	if (Dlg.DoModal() == IDOK)
    {
    	HANDLE hFile;
    	DWORD dwBytesRead;
    	DWORD dwFileSize;

		if ((hFile = CreateFile((LPCTSTR)Dlg.m_ofn.lpstrFile,
			GENERIC_READ,
			FILE_SHARE_READ,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			(HANDLE)NULL)) == (HANDLE)(-1))
		{
		    AfxMessageBox( "File open failed." );
	    	return;
		}

		// Get the size of the file.
		dwFileSize = GetFileSize(hFile, NULL);
		if (dwFileSize == 0xFFFFFFFF)
		{
	    	AfxMessageBox( "GetFileSize failed!");
	    	return;
		}

		// Allocate a buffer to read the file into.
		m_lpBufPtr = (char *) malloc (dwFileSize);
		if (m_lpBufPtr == NULL)
		{
	    	AfxMessageBox ("malloc failed!");
	    	CloseHandle (hFile);
	    	return;
		}

		// Read the file's contents into the buffer.
		ReadFile(hFile,(LPVOID)m_lpBufPtr, dwFileSize, &dwBytesRead, NULL);

		if (dwBytesRead == 0)
		{
	    	AfxMessageBox( "Zero bytes read." );
	    	return;
		}

		// Close the file.
		CloseHandle(hFile);

		// Parse the file buffer.
		if( ParseFile());
		{
			lstrcpy(m_lpstrFile, Dlg.m_ofn.lpstrFileTitle);
    		// Reset the title in the title bar.
			GetParentFrame() -> SetWindowText(m_lpstrFile);
			// Redraw the title bar.
			GetParentFrame() -> Invalidate(TRUE);
		}
	}
}

/****************************************************************************
*
*    FUNCTION: OnSave()
*
*    PURPOSE:  Processes the File.Save command
*
****************************************************************************/
void CMfcexpView::OnSave() 
{
    SaveToFile();
}

/****************************************************************************
*
*    FUNCTION: OnSaveas()
*
*    PURPOSE:  Processes the File.SaveAs command
*
****************************************************************************/
void CMfcexpView::OnSaveas() 
{
	CFileDialog Dlg(FALSE, "*.txt", m_lpstrFile, 
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		szFilter);

	if (Dlg.DoModal() == IDOK)
	{	
		if (SaveToFile())
		{
    		// reset the title in the title bar
			GetParentFrame()->SetWindowText(m_lpstrFile);
			// redraw the title bar
			GetParentFrame()->Invalidate(TRUE);
		}
	}
}

/****************************************************************************
*
*    FUNCTION: SaveToFile( )
*
*    PURPOSE:  Saves the current buffer to the current file.
*
*    COMMENTS:
*
*        This function will save the current text buffer into the file
*        specified from the GetSaveFileName() common dialog function.
*
*    RETURN VALUES:
*        TRUE - The file was saved successfully.
*        FALSE - The buffer was not saved to a file.
*
****************************************************************************/
BOOL CMfcexpView::SaveToFile( )
{
   HANDLE hFile;
   DWORD dwOpen;
   DWORD dwBytesWritten;
   char buf[MAX_PATH];
   DWORD dwFileSize;

   dwFileSize = GetDataBufferAndSize();
   if (dwFileSize == 0)
   {
	AfxMessageBox("GetDataBufferAndSize failed!");
	return FALSE;
   }

   dwOpen = CREATE_ALWAYS;

   // open the file
   if ((hFile = CreateFile((LPCTSTR)m_lpstrFile,
			GENERIC_WRITE,
			FILE_SHARE_WRITE,
			NULL,
			dwOpen,
			FILE_ATTRIBUTE_NORMAL,
			(HANDLE)NULL)) == (HANDLE)-1)

   {                      
      sprintf( buf, "Could not create file %s", m_lpstrFile );
      AfxMessageBox( buf );
      return FALSE;
   }
    
   // write it's contents into a file
   if (WriteFile( hFile, (LPCVOID)m_lpBufPtr, dwFileSize, 
		     &dwBytesWritten, NULL) == FALSE)
   {
      AfxMessageBox("Error writing file.");
      return FALSE;
   }

   // close the file
   CloseHandle(hFile);

   // free up the file buffer
   GlobalFree(m_lpBufPtr);

   return TRUE;
}


/****************************************************************************
*
*    FUNCTION: GetDataBufferAndSize()
*
*    PURPOSE:  Saves the current listing info to a buffer.
*
*    COMMENTS:
*
*        The file is an editable ASCII file and set up as follows:
*           - Number of cities
*           - A string representing each city for # of cities specified above
*           - Number of houses
*           - House information for each house. One line per house.
*             The fields are separated by commas and are in the following
*             order:
*                   Address
*                   City
*                   Price
*                   Bedrooms
*                   Bathrooms
*
*    RETURN VALUES:
*        TRUE - The file was parsed successfully.
*        FALSE - The parsing failed.
*
****************************************************************************/
DWORD CMfcexpView::GetDataBufferAndSize (void)
{
    char szTemp[MAX_PATH];
    int count;
    DWORD dwFileSize;

    // calculate the approximate buffer size needed to save the file
    dwFileSize = (m_NumCities * MAX_CITY) + (m_NumHouses * MAX_ADDRESS) +
	(m_NumHouses * MAX_CITY) + (m_NumHouses * (MAX_PRICE + 2) +
	 (m_NumHouses * MAX_CITY) + (m_NumHouses * MAX_CITY));

    m_lpBufPtr = (char *)GlobalAlloc( GMEM_FIXED, dwFileSize );
    if (m_lpBufPtr == NULL)
    {
		AfxMessageBox("GlobalAlloc failed!");
	return 0;
    }

    // copy over the number of cities
    sprintf(m_lpBufPtr, "%d\n", m_NumCities);

    // copy a city for each line
    for (count= 0; count < m_NumCities; count++)
    {
	sprintf(szTemp, "%s\n", (LPCTSTR)m_rgCities[count].szCity);
	lstrcat(m_lpBufPtr, szTemp);
    }

    sprintf(szTemp, "%d\n", m_NumHouses);
    lstrcat(m_lpBufPtr, szTemp);

    // copy house information for each line
    for (count= 0; count < m_NumHouses; count++)
    {
	 sprintf(szTemp, "%s,%s,%d,%d,%d,%s,%s\n", (LPCTSTR)m_rgHouses[count].szAddress,
	    (LPCTSTR)m_rgHouses[count].szCity,m_rgHouses[count].iPrice,
	    m_rgHouses[count].iBeds,m_rgHouses[count].iBaths,
	    (LPCTSTR)m_rgHouses[count].szAgent,(LPCTSTR)m_rgHouses[count].szNumber);
	lstrcat(m_lpBufPtr, szTemp);
    }

    dwFileSize = lstrlen(m_lpBufPtr);

    return (dwFileSize);
}
/****************************************************************************
*
*    FUNCTION: AddOneCity(CString)
*
*    PURPOSE:  Adds a city and updates the structures
*
****************************************************************************/
void CMfcexpView::AddOneCity( CString szCity)
{
    // copy the city name
    m_rgCities[m_NumCities].szCity = szCity;

    // initialize the number of houses to zero
    m_rgCities[m_NumCities].NumHouses = 0;

    // Add the city to the tree view listing
    m_rgCities[m_NumCities].hItem = TV_AddOneItem(szCity, m_NumCities, m_idxSeattle, m_idxSeaSel);

    // update the global count of cities
    m_NumCities++;

}

/****************************************************************************
*
*    FUNCTION: AddOneHouse(CString)
*
*    PURPOSE:  Adds a house and updates the structures
*
****************************************************************************/
void CMfcexpView::AddOneHouse(  CString szAddress, CString szCity, int iPrice, int iBeds,
    int iBaths)
{
    int index;

    // copy the address
    m_rgHouses[m_NumHouses].szAddress = szAddress;

    // copy the city name
    m_rgHouses[m_NumHouses].szCity= szCity;

    // initialize the price, bedrooms and bathrooms
    m_rgHouses[m_NumHouses].iPrice = iPrice;
    m_rgHouses[m_NumHouses].iBeds = iBeds;
    m_rgHouses[m_NumHouses].iBaths = iBaths;

    // add the house to the list view
    LV_AddItem(m_NumHouses, &m_rgHouses[m_NumHouses]);

    // update the global count of houses
    m_NumHouses++;

    // find the city for the house in the CITY struct and update the number
    // of houses for that city
    for (index =0 ; index < m_NumCities; index++)
	if (szCity == m_rgCities[index].szCity)
	    break;

    m_rgCities[index].NumHouses++;

}

/****************************************************************************
*
*    FUNCTION: RemoveOneHouse(int)
*
*    PURPOSE:  Removes a house from the listing book
*
****************************************************************************/
void CMfcexpView::RemoveOneHouse( int index )
{
	int count, idx;		// general purpose counters

    // find the city and decrement its house counter
    m_rgCities[m_iSelected].NumHouses--;

	// find the house in the list
	for (count=0, idx=0; count < m_NumHouses; count++)
	{
		if (m_rgCities[m_iSelected].szCity == m_rgHouses[count].szCity)
		{
			if (idx == index)
			{
				// found it -- change .szCity to "deleted"
				m_rgHouses[count].szCity = CString("deleted");
				break;
			}
			else
				idx++;
		}
	}

    // remove the house from the list view
	m_ListCtl.DeleteItem(index);
}

/****************************************************************************
*
*    FUNCTION: LV_AddOneItem(int, HOUSEINFO *)
*
*    PURPOSE: Inserts a list view item
*
****************************************************************************/
BOOL CMfcexpView::LV_AddItem(int index, HOUSEINFO *pHouse )
{
	LV_ITEM lvI;        // List view item structure
	int iSubItem;       // index for inserting sub items

    // Fill in the LV_ITEM structure 
	// The mask specifies the the pszText, iImage, lParam and state
	// members of the LV_ITEM structure are valid.
	lvI.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM | LVIF_STATE;
    lvI.state = 0;      
    lvI.stateMask = 0;  
    lvI.iItem = index;
    lvI.iSubItem = 0;

    // The parent window is responsible for storing the text. The List view
    // window will send a LVN_GETDISPINFO when it needs the text to display/
    lvI.pszText = LPSTR_TEXTCALLBACK; 
    lvI.cchTextMax = MAX_ITEMLEN;
	lvI.iImage = pHouse->iImage;
    lvI.lParam = (LPARAM)pHouse;

    if (m_ListCtl.InsertItem(&lvI) == -1)
        return FALSE;

    // set the text for each of the columns for report view
    for (iSubItem = 1; iSubItem < NUM_COLUMNS; iSubItem++)
    {
        m_ListCtl.SetItemText( index,
				iSubItem,
				LPSTR_TEXTCALLBACK);
	}
    return TRUE;
}

/****************************************************************************
*
*    FUNCTION: OnListview()
*
*    PURPOSE:  Processes the View.ListView command
*
****************************************************************************/

void CMfcexpView::OnListview() 
{
	DWORD dwStyle;

	dwStyle = GetWindowLong(m_ListCtl.m_hWnd, GWL_STYLE);
					
	if ((dwStyle & LVS_TYPEMASK) != LVS_LIST)
		SetWindowLong(m_ListCtl.m_hWnd, GWL_STYLE,
			(dwStyle & ~LVS_TYPEMASK) | LVS_LIST);
}

/****************************************************************************
*
*    FUNCTION: OnReportview()
*
*    PURPOSE:  Processes the View.ReportView command
*
****************************************************************************/
void CMfcexpView::OnReportview() 
{
	DWORD dwStyle;

	dwStyle = GetWindowLong(m_ListCtl.m_hWnd, GWL_STYLE);
					
	if ((dwStyle & LVS_TYPEMASK) != LVS_REPORT)
		SetWindowLong(m_ListCtl.m_hWnd, GWL_STYLE,
			(dwStyle & ~LVS_TYPEMASK) | LVS_REPORT);
	
}

/****************************************************************************
*
*    FUNCTION: OnLargeicon()
*
*    PURPOSE:  Processes the View.LargeIcon command
*
****************************************************************************/
void CMfcexpView::OnLargeicon() 
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
void CMfcexpView::OnSmallicon() 
{
	DWORD dwStyle;

	dwStyle = GetWindowLong(m_ListCtl.m_hWnd, GWL_STYLE);
					
	if ((dwStyle & LVS_TYPEMASK) != LVS_SMALLICON)
		SetWindowLong(m_ListCtl.m_hWnd, GWL_STYLE,
			(dwStyle & ~LVS_TYPEMASK) | LVS_SMALLICON);
	
}

/****************************************************************************
*
*    FUNCTION: WindowProc(UINT, WPARAM, LPARAM)
*
*    PURPOSE:  Processes the WM_NOTIFY command for the View
*
****************************************************************************/
LRESULT CMfcexpView::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	char  szBuf[MAX_PATH];
	LPTOOLTIPTEXT lpToolTipText;

   	if (message == WM_NOTIFY)
	{	
		// first check to see if we need a tool tip
		if 	(((NMHDR *) lParam)->code == TTN_NEEDTEXT)
		{
			lpToolTipText = (LPTOOLTIPTEXT)lParam;
    		::LoadString (AfxGetResourceHandle(), 
	    				lpToolTipText->hdr.idFrom,    // string ID == cmd ID
		    			szBuf,
			    		sizeof(szBuf));
			lpToolTipText->lpszText = szBuf;
		}
 		else if (TV_NotifyHandler( message, wParam, lParam))
    	{  
		
    		// update the list view window to reflect the selected cities houses
        	UpdateListView(m_iSelected);

       		// update the status bar text
       		ChangeSBText(m_iSelected );
    	}
		NotifyHandler(message, wParam, lParam);
	}
	
	return CView::WindowProc(message, wParam, lParam);
}

/****************************************************************************
*
*    FUNCTION: NotifyHandler(UINT, WPARAM, LPARAM)
*
*    PURPOSE:  Processes the WM_NOTIFY command for the list view
*
****************************************************************************/
LRESULT CMfcexpView::NotifyHandler(UINT message, WPARAM wParam, LPARAM lParam) 
{
	LV_DISPINFO *pLvdi = (LV_DISPINFO *)lParam;
	NM_LISTVIEW *pNm = (NM_LISTVIEW *)lParam;
	HOUSEINFO *pHouse = (HOUSEINFO *)(pLvdi->item.lParam);
	static char szText[64];

	if (wParam != ID_LISTVIEW)
		return 0L;

	switch(pLvdi->hdr.code)
	{
			case NM_RCLICK:		// right mouse button has been clicked
			{
				POINT pt;
				int idx;
				LV_HITTESTINFO lvH;

				lvH.pt.x = pNm->ptAction.x;
            	lvH.pt.y = pNm->ptAction.y;	   
            	idx = m_ListCtl.HitTest(&lvH);
            	if ( idx != -1)
				{
					::GetCursorPos(&pt);
                	ListViewPopUpMenu(pt);
					return idx;
				}
			}
			break;


		case LVN_GETDISPINFO:

			switch (pLvdi->item.iSubItem)
			{
				case 0:     // Address
					lstrcpy(pLvdi->item.pszText, (LPCTSTR) pHouse->szAddress);
					break;

				case 1:     // City
					lstrcpy(pLvdi->item.pszText, (LPCTSTR)pHouse->szCity);
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

            // Get the handle to the edit box.
            pEdit = m_ListCtl.GetEditControl();
            // Limit the amount of text that can be entered.
            pEdit->LimitText(20);
            }
            break;

        case LVN_ENDLABELEDIT:
            // If the label editing wasn't cancelled and the text buffer is non-NULL
            if ((pLvdi->item.iItem != -1) && (pLvdi->item.pszText != NULL))
                // Save the new label information
	    		pHouse->szAddress = pLvdi->item.pszText;
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

/****************************************************************************
*
*    FUNCTION: ListViewPopUpMenu(POINT)
*
*    PURPOSE:  Pops up a menu on a right mouse button click
*
****************************************************************************/

void CMfcexpView::ListViewPopUpMenu ( CPoint pt)
{
	CMenu pMenu;

    // Get the menu for the popup from the resource file.
	pMenu.LoadMenu( "HousePopupMenu");

    // Get the first menu in it which we will use for the call to
    // TrackPopup(). This could also have been created on the fly using
    // CreatePopupMenu and then we could have used InsertMenu() or
    // AppendMenu.
	pMenu.TrackPopupMenu(	TPM_LEFTALIGN | TPM_RIGHTBUTTON,
        pt.x, pt.y, GetParentFrame());

    // Destroy the menu
    pMenu.DestroyMenu();
}


/****************************************************************************
* 
*    FUNCTION: TV_NotifyHandler(UINT,WPARAM, LPARAM)
*
*    PURPOSE: This function is the handler for the WM_NOTIFY that is 
*    sent to the parent of the tree view window.
*
****************************************************************************/
LRESULT CMfcexpView::TV_NotifyHandler( UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static NM_TREEVIEW *pNm;

    pNm = (NM_TREEVIEW *)lParam;

    if (wParam != ID_TREEVIEW)
		return 0L;

    switch(pNm->hdr.code)
	{
        case TVN_SELCHANGED:
            m_iSelected = (int)(pNm->itemNew.lParam);

            return 1;
            break;

		default:
			break;
	}
	return 0L;
}

/****************************************************************************
*
*    FUNCTION: ListviewCompareProc()
*
*    PURPOSE:  Callback that sorts the list view items
*
****************************************************************************/
int CALLBACK CMfcexpView::ListViewCompareProc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	HOUSEINFO *pHouse1 = (HOUSEINFO *)lParam1;
	HOUSEINFO *pHouse2 = (HOUSEINFO *)lParam2;
	int iResult;

	if (pHouse1 && pHouse2)
	{
		switch( lParamSort)
		{
			case 0:     // sort by Address
				iResult = pHouse1->szAddress.Compare (pHouse2->szAddress);
				break;

			case 1:     // sort by City
				iResult = pHouse1->szCity.Compare(pHouse2->szCity);
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


/****************************************************************************
*
*    FUNCTION: OnAddCity()
*
*    PURPOSE:  Processes the Options.AddCity command
*
****************************************************************************/

void CMfcexpView::OnAddcity() 
{
	CAddCity Dlg;
	
	if (Dlg.DoModal() == IDOK) 
		// add the city to the array
		AddOneCity(Dlg.m_City);
	
}

/****************************************************************************
*
*    FUNCTION: OnInitDialog()
*
*    PURPOSE:  Initializes the Add House dialog
*
****************************************************************************/
BOOL CAddHouse::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	int index; 

	CMfcexpView *pView  = (CMfcexpView *)GetParentFrame()->
			GetActiveView();

    for (index = 0; index < pView->m_NumCities; index++)
		SendDlgItemMessage(IDC_CITY, CB_INSERTSTRING, (WPARAM)-1, (LPARAM) (LPCTSTR)pView->m_rgCities[index].szCity);
	   
	GotoDlgCtrl(GetDlgItem(IDC_CITY));

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/****************************************************************************
*
*    FUNCTION: OnAddHouse()
*
*    PURPOSE:  Processes the Options.AddHouse command
*
****************************************************************************/
void CMfcexpView::OnAddhouse() 
{
	CAddHouse Dlg;

	if (Dlg.DoModal() == IDOK)
		AddOneHouse(Dlg.m_Address, Dlg.m_City, Dlg.m_Price, Dlg.m_Bedrooms, Dlg.m_Bathrooms);
	
}

/****************************************************************************
*
*    FUNCTION: OnProperties()
*
*    PURPOSE:  Processes the Options.HouseProperties command and the popup
*
****************************************************************************/
void CMfcexpView::OnProperties() 
{
	if (m_iSelected == -1)
		return;

	// Create a property sheet object.
   CPropertySheet dlgPropertySheet("House Properties",this);
   CHouse dlgHouse;
   CAgent dlgAgent;
   int index, count;
   LV_ITEM lvItem;
   char szAddSave[MAX_ADDRESS];

   dlgPropertySheet.AddPage(&dlgHouse);
   dlgPropertySheet.AddPage(&dlgAgent);

  	// Fill in the list box with the cities .
	for (index = 0; index < m_NumCities; index++)
			SendDlgItemMessage(IDC_CITY, CB_ADDSTRING, 0, (LPARAM) (LPCTSTR)m_rgCities[index].szCity);

 	// Get the index to the selected list view item
   	index = m_ListCtl.GetNextItem( -1, LVNI_SELECTED);

	// Get the house address.
	lvItem.iItem = index;
	lvItem.iSubItem = 0;
	lvItem.mask = LVIF_TEXT;
	lvItem.cchTextMax = sizeof(szAddSave);
	lvItem.pszText = szAddSave;
	m_ListCtl.GetItem(&lvItem);

	// Find the house in the list.
	for (count=0; count < m_NumHouses; count++)
	{
		if (strcmp(lvItem.pszText, m_rgHouses[count].szAddress) == 0)
			break;
	}
	m_iSelHouse = count;

	dlgHouse.m_Address = m_rgHouses[m_iSelHouse].szAddress; 
	dlgHouse.m_City = m_rgHouses[m_iSelHouse].szCity;
	dlgHouse.m_Price = 	 m_rgHouses[m_iSelHouse].iPrice;
	dlgHouse.m_Bedrooms =  m_rgHouses[m_iSelHouse].iBeds ;
	dlgHouse.m_Bathrooms = m_rgHouses[m_iSelHouse].iBaths;

	dlgAgent.m_AgentName = m_rgHouses[m_iSelHouse].szAgent;
	dlgAgent.m_PhoneNumber = m_rgHouses[m_iSelHouse].szNumber;

   if (dlgPropertySheet.DoModal() == IDOK)
   {
   		m_rgHouses[m_iSelHouse].szAddress = dlgHouse.m_Address; 
		m_rgHouses[m_iSelHouse].szCity = dlgHouse.m_City;
		m_rgHouses[m_iSelHouse].iPrice = dlgHouse.m_Price;
		m_rgHouses[m_iSelHouse].iBeds = dlgHouse.m_Bedrooms;
		m_rgHouses[m_iSelHouse].iBaths = dlgHouse.m_Bathrooms;

		m_rgHouses[m_iSelHouse].szAgent = dlgAgent.m_AgentName;
		m_rgHouses[m_iSelHouse].szNumber = dlgAgent.m_PhoneNumber;

        GetDocument() -> SetModifiedFlag();
        GetDocument() -> UpdateAllViews(NULL);
   }
}
	
/****************************************************************************
*
*    FUNCTION: OnRemHouse()
*
*    PURPOSE:  Processes the Options.RemoveHouse command
*
****************************************************************************/
void CMfcexpView::OnRemhouse() 
{
	CRemHouse Dlg;

	if (Dlg.DoModal() == IDOK)
	{
	    int index;
		index = SendDlgItemMessage(ID_LISTBOX, LB_GETCURSEL, 0, 0);

		RemoveOneHouse(index);
    	// update the list view window to reflect the selected cities houses
        UpdateListView(m_iSelected);

       	// update the status bar text
       	ChangeSBText(m_iSelected );

	}
		
}

/****************************************************************************
*
*    FUNCTION: OnInitDialog()
*
*    PURPOSE:  Initializes the Remove House dialog
*
****************************************************************************/
BOOL CRemHouse::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	int index;

	
	CMfcexpView *pView  = (CMfcexpView *)GetParentFrame()->
			GetActiveView();

	// Fill the dialog with only houses listed for the current city
   	for (index = 0; index < pView->m_NumHouses; index++)
	{
		if (pView->m_rgHouses[index].szCity == pView->m_rgCities[pView->m_iSelected].szCity) 
			SendDlgItemMessage(ID_LISTBOX, LB_INSERTSTRING, (WPARAM)-1, 
				(LPARAM) (LPCTSTR)pView->m_rgHouses[index].szAddress);
	}	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


/////////////////////////////////////////////////////////////////////////////
// CAgent property page

IMPLEMENT_DYNCREATE(CAgent, CPropertyPage)

CAgent::CAgent() : CPropertyPage(CAgent::IDD)
{
	//{{AFX_DATA_INIT(CAgent)
	m_AgentName = _T("");
	m_PhoneNumber = _T("");
	//}}AFX_DATA_INIT
}

CAgent::~CAgent()
{
}

void CAgent::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAgent)
	DDX_Text(pDX, IDE_AGENTNAME, m_AgentName);
	DDX_Text(pDX, IDE_PHONE, m_PhoneNumber);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAgent, CPropertyPage)
	//{{AFX_MSG_MAP(CAgent)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CHouse property page

IMPLEMENT_DYNCREATE(CHouse, CPropertyPage)

CHouse::CHouse() : CPropertyPage(CHouse::IDD)
{
	//{{AFX_DATA_INIT(CHouse)
	m_Address = _T("");
	m_City = _T("");
	m_Price = 0;
	m_Bathrooms = 0;
	m_Bedrooms = 0;
	//}}AFX_DATA_INIT
}

CHouse::~CHouse()
{
}

void CHouse::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHouse)
	DDX_Text(pDX, IDE_ADDRESS, m_Address);
	DDX_Text(pDX, IDE_CITY, m_City);
	DDX_Text(pDX, IDE_PRICE, m_Price);
	DDX_Text(pDX, IDE_BATHROOMS, m_Bathrooms);
	DDX_Text(pDX, IDE_BEDROOMS, m_Bedrooms);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHouse, CPropertyPage)
	//{{AFX_MSG_MAP(CHouse)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

