// mfctrvw.h : interface of the CMfctreeView class
//
/////////////////////////////////////////////////////////////////////////////

class CMfctreeView : public CView
{
protected: // create from serialization only
	CMfctreeView();
	DECLARE_DYNCREATE(CMfctreeView);
	CTreeCtrl m_TreeCtl;		// tree view control
	CImageList m_ImageList;		// image list associated with tree
	BOOL m_fDragging;			// whether you are dragging an item
	HTREEITEM m_hDragItem;		// current item being dragged
	int m_idxForSale;			// index to For Sale icon
	int m_idxRedmond;			// index to Redmond icon
	int m_idxBellevue;			// index to Bellevue icon
	int m_idxSeattle;			// index to Seattle icon

// Attributes
public:
	CMfctreeDoc* GetDocument();

// Operations
public:

   	BOOL AddTreeViewItems();
	HTREEITEM AddOneItem(HTREEITEM, LPSTR, HTREEITEM, int);
	VOID FillInStruct(HTREEITEM, int, int, int);
	VOID BeginDrag(NM_TREEVIEW *);
	VOID DropItem(HTREEITEM);

// Overrides
	// ClassWizard generated virtual function overrides.
	//{{AFX_VIRTUAL(CMfctreeView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this 
									// view
	protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMfctreeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMfctreeView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in mfctrvw.cpp
inline CMfctreeDoc* CMfctreeView::GetDocument()
   { return (CMfctreeDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
//
// constants                            
#define ID_TREEVIEW     1000
#define MAX_LEN         32
#define NUM_BITMAPS     4
#define BITMAP_WIDTH    16
#define BITMAP_HEIGHT   16
#define NUM_HOUSES      9
#define MAX_ADDRESS     32

// structures
typedef struct tagHOUSEINFO
{
    char szAddress[MAX_ADDRESS];
    int iImage;
    HTREEITEM hParent;
    HTREEITEM hItem;
} HOUSEINFO;


