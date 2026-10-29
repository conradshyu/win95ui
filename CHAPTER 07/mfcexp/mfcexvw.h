// mfcexvw.h : interface of the CMfcexpView class
//
/////////////////////////////////////////////////////////////////////////////
#include "chicoapp.h"

// Constants
#define MAX_LEN         32
#define NUM_COLUMNS     5
#define MAX_ITEMLEN     64
#define MAX_ADDRESS     64
#define MAX_CITY        16
#define MAX_PRICE       12
#define BITMAP_WIDTH    16
#define BITMAP_HEIGHT   16
#define MAX_HOUSES      256
#define MAX_CITIES      16
#define MAX_TITLE		256

#define NUM_BUTTONS			12
#define NUM_BITMAPS			10
#define LARGE_BITMAP_WIDTH		32
#define LARGE_BITMAP_HEIGHT 	32
#define SMALL_BITMAP_WIDTH		16
#define SMALL_BITMAP_HEIGHT		16
#define NUM_WINDOWS			4
#define STATUS_BAR_HEIGHT	20
#define TOOLBAR_HEIGHT		20
#define TEMP_LEN			10	 
#define NUM_ICONS		  3

// Window IDs
#define ID_STATUSBAR    1000
#define ID_TOOLBAR      1001
#define ID_LISTVIEW     1002
#define ID_TREEVIEW     1003

typedef struct tagCITYINFO
{
    CString szCity; 		// city name
    int NumHouses;          // number of houses listed in this city
    HTREEITEM hItem;        // handle to tree view item
} CITYINFO;

typedef struct tagHOUSEINFO
{
    CString szAddress;
    CString szCity;
    int iPrice;
    int iBeds;
    int iBaths;
    int iImage;
    CString szAgent;
    CString szNumber;
} HOUSEINFO;

class CMfcexpView : public CView
{
protected: // create from serialization only
	CMfcexpView();
	DECLARE_DYNCREATE(CMfcexpView);

	// Common controls
	CToolBarCtrl m_Toolbar;		  // toolbar
	CStatusBarCtrl m_StatusBar;   // status bar
    CListCtrl m_ListCtl;		  // list view control
	CImageList m_ImageLarge;	  // large (32-by-32) image list
	CImageList m_ImageSmall;	  // small (16-by-16) image list
	CTreeCtrl m_TreeCtl;		  // tree view control

	// Indexes to icons in the tree view image list
	int m_idxForSale;
	int m_idxSeattle;		 
	int m_idxSeaSel;
	int m_idxRedmond;
	int m_idxRedSel;
	int m_idxBellevue;
	int m_idxBellSel;

	// Handles to the root, parent, and previous tree view items
	HTREEITEM m_hTPrev;
	HTREEITEM m_hParent;
	HTREEITEM m_hTRoot;

	// House listing information
    int m_NumCities;        // number of cities
    int m_NumHouses;        // number of houses
    int m_iSelected;        // index to selected city 
	int m_iSelHouse;		// index to selected house
	HOUSEINFO m_rgHouses[MAX_HOUSES];
	CITYINFO  m_rgCities[MAX_CITIES];

	// Pointer to buffer for listing data
	char *m_lpBufPtr;	  
	
	// Current file opened
	char  m_lpstrFile[MAX_TITLE]; 

// Attributes
public:
	CMfcexpDoc* GetDocument();

// Operations
public:
 	static int CALLBACK ListViewCompareProc(LPARAM, LPARAM, LPARAM);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMfcexpView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMfcexpView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	void InitTreeAndList(void);
	BOOL CreateAppWindows(void);
	void AddOneCity(CString);
	void AddOneHouse( CString, CString, int, int, int);
	void RemoveOneHouse(int);
	void ChangeSBText(int);
	void UpdateListView(int);
    void ListViewPopUpMenu ( CPoint pt);

	// file i/0 functions
	BOOL SaveToFile(void);
	BOOL ParseFile (void);
	DWORD GetDataBufferAndSize (void);
	void ProcessCDError(DWORD);

	void TV_InitTreeView(void);
	HTREEITEM TV_AddOneItem( CString szText, int index, int idxImage, int idxSelected);
	BOOL LV_AddItem(int index, HOUSEINFO *pHouse );

	LRESULT NotifyHandler(UINT message, WPARAM wParam, LPARAM lParam);
    LRESULT TV_NotifyHandler( UINT uMsg, WPARAM wParam, LPARAM lParam);

// Generated message map functions
protected:
	//{{AFX_MSG(CMfcexpView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnListview();
	afx_msg void OnReportview();
	afx_msg void OnLargeicon();
	afx_msg void OnSmallicon();
	afx_msg void OnAddcity();
	afx_msg void OnAddhouse();
	afx_msg void OnProperties();
	afx_msg void OnRemhouse();
	afx_msg void OnNew();
	afx_msg void OnOpen();
	afx_msg void OnSave();
	afx_msg void OnSaveas();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in mfcexvw.cpp
inline CMfcexpDoc* CMfcexpView::GetDocument()
   { return (CMfcexpDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////////
// CAddCity dialog

class CAddCity : public CDialog
{
// Construction
public:
	CAddCity(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAddCity)
	enum { IDD = IDD_ADDCITY };
	CString	m_City;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAddCity)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAddCity)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
// CAddHouse dialog

class CAddHouse : public CDialog
{
// Construction
public:
	CAddHouse(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAddHouse)
	enum { IDD = IDD_ADDHOUSE };
	CString	m_Address;
	int		m_Price;
	int		m_Bathrooms;
	int		m_Bedrooms;
	CString	m_City;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAddHouse)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAddHouse)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
// CRemHouse dialog

class CRemHouse : public CDialog
{
// Construction
public:
	CRemHouse(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRemHouse)
	enum { IDD = IDD_REMHOUSE };
	CString	m_List;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRemHouse)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRemHouse)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
// CProperties

class CProperties : public CPropertySheet
{
	DECLARE_DYNAMIC(CProperties)

// Construction
public:
	CProperties(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CProperties(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProperties)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CProperties();

	// Generated message map functions
protected:
	//{{AFX_MSG(CProperties)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// CAgent dialog

class CAgent : public CPropertyPage
{
	DECLARE_DYNCREATE(CAgent)

// Construction
public:
	CAgent();
	~CAgent();

// Dialog Data
	//{{AFX_DATA(CAgent)
	enum { IDD = IDD_AGENT };
	CString	m_AgentName;
	CString	m_PhoneNumber;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CAgent)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CAgent)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
/////////////////////////////////////////////////////////////////////////////
// CHouse dialog

class CHouse : public CPropertyPage
{
	DECLARE_DYNCREATE(CHouse)

// Construction
public:
	CHouse();
	~CHouse();

// Dialog Data
	//{{AFX_DATA(CHouse)
	enum { IDD = IDD_HOUSEPROP };
	CString	m_Address;
	CString	m_City;
	int		m_Price;
	int		m_Bathrooms;
	int		m_Bedrooms;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CHouse)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CHouse)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
