// mfcenvw.h : interface of the CMfcenumView class
//
/////////////////////////////////////////////////////////////////////////////
#include <shlobj.h>

// Window IDs
#define ID_LISTVIEW     1000
#define ID_TREEVIEW     1001

// STRUCTURES
typedef struct tagLVID
{
   LPSHELLFOLDER lpsfParent;
   LPITEMIDLIST  lpi;
   ULONG         ulAttribs;
} LVITEMDATA, *LPLVITEMDATA;

typedef struct tagID
{
   LPSHELLFOLDER lpsfParent;
   LPITEMIDLIST  lpi;
   LPITEMIDLIST  lpifq;
} TVITEMDATA, *LPTVITEMDATA;

// CLASSES
class FAR CDropSource : public IDropSource
{
public:    
    CDropSource();

    /* IUnknown methods */
    STDMETHOD(QueryInterface)(REFIID riid, void FAR* FAR* ppvObj);
    STDMETHOD_(ULONG, AddRef)(void);
    STDMETHOD_(ULONG, Release)(void);

    /* IDropSource methods */
    STDMETHOD(QueryContinueDrag)(BOOL fEscapePressed, DWORD grfKeyState);
    STDMETHOD(GiveFeedback)(DWORD dwEffect);
 
private:
    ULONG m_refs;     
};  


class CMfcenumView : public CView
{
protected: // create from serialization only
	CMfcenumView();
	DECLARE_DYNCREATE(CMfcenumView)

	// Common controls
    CListCtrl m_ListCtl;
	CImageList m_ImageLarge;
	CImageList m_ImageSmall;
	CTreeCtrl m_TreeCtl;
    BOOL m_bOutaHere;

// Attributes
public:
	CMfcenumDoc* GetDocument();

// Operations
public:
 	static int CALLBACK ListViewCompareProc(LPARAM, LPARAM, LPARAM);
 	static int CALLBACK TreeViewCompareProc(LPARAM, LPARAM, LPARAM);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMfcenumView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMfcenumView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMfcenumView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLargeicon();
	afx_msg void OnSmallicon();
	afx_msg void OnList();
	afx_msg void OnFill();
	afx_msg void OnDestroy();
	afx_msg void OnAppExit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


    void FillTreeView(LPSHELLFOLDER lpsf, LPITEMIDLIST  lpifq, HTREEITEM hParent);
    int GetIcon(LPITEMIDLIST lpi, UINT uFlags);
    void GetNormalAndSelectedIcons(LPITEMIDLIST lpifq, LPTV_ITEM lptvitem);
    LRESULT NotifyHandler(UINT message, WPARAM wParam, LPARAM lParam); 
    BOOL DoTheMenuThing(HWND hwnd, LPSHELLFOLDER lpsfParent, LPITEMIDLIST  lpi, LPPOINT lppt);
    BOOL PopulateListView(LPTVITEMDATA lptvid, LPSHELLFOLDER lpsf);
    BOOL InitListViewItems(LPTVITEMDATA lptvid, LPSHELLFOLDER lpsf);
    BOOL InitListViewImageLists();

    // Functions that deal with PIDLs
    LPITEMIDLIST ConcatPidls(LPCITEMIDLIST pidl1, LPCITEMIDLIST pidl2);
    LPITEMIDLIST GetFullyQualPidl(LPSHELLFOLDER lpsf, LPITEMIDLIST lpi);
    LPITEMIDLIST CopyITEMID(LPMALLOC lpMalloc, LPITEMIDLIST lpi);
    BOOL GetName(LPSHELLFOLDER lpsf, LPITEMIDLIST  lpi, DWORD dwFlags, LPSTR lpFriendlyName);
    LPITEMIDLIST Create(UINT cbSize);
    UINT GetSize(LPCITEMIDLIST pidl);
    LPITEMIDLIST Next(LPCITEMIDLIST pidl);

};

#ifndef _DEBUG  // debug version in mfcenvw.cpp
inline CMfcenumDoc* CMfcenumView::GetDocument()
   { return (CMfcenumDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
