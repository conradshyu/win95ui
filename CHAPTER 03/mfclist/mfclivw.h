// mfclivw.h : interface of the CMfclistView class
//
/////////////////////////////////////////////////////////////////////////////

class CMfclistView : public CView
{
protected: // create from serialization only
	CMfclistView();
	DECLARE_DYNCREATE(CMfclistView);
	CListCtrl m_ListCtl;
	CImageList m_ImageLarge;
	CImageList m_ImageSmall;

// Attributes
public:
	CMfclistDoc* GetDocument();

// Operations
public:
 	static int CALLBACK ListViewCompareProc(LPARAM, LPARAM, LPARAM);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMfclistView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMfclistView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	LRESULT NotifyHandler(UINT message, WPARAM wParam, LPARAM lParam);
// Generated message map functions
protected:
	//{{AFX_MSG(CMfclistView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDetails();
	afx_msg void OnLargeicon();
	afx_msg void OnListview();
	afx_msg void OnSmallicon();
	afx_msg void OnExit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in mfclivw.cpp
inline CMfclistDoc* CMfclistView::GetDocument()
   { return (CMfclistDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
// CONSTANTS

#define ID_LISTVIEW	1000
#define NUM_BITMAPS	3
#define LARGE_BITMAP_WIDTH	32
#define LARGE_BITMAP_HEIGHT	32
#define SMALL_BITMAP_WIDTH	16
#define SMALL_BITMAP_HEIGHT	16
#define NUM_ITEMS       9
#define NUM_COLUMNS     5
#define MAX_ITEMLEN     64
#define MAX_ADDRESS     64
#define MAX_CITY        16
#define MAX_PRICE       12

// structures
typedef struct tagHOUSEINFO
{
    char szAddress[MAX_ADDRESS];
    char szCity[MAX_CITY];
    int iPrice;
    int iBeds;
    int iBaths;
} HOUSEINFO;


