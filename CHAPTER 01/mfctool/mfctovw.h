/////////////////////////////////////////////////////////////////////////////
// Combo window

class Combo : public CComboBox
{
// Construction
public:
	Combo();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Combo)
	protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~Combo();

	// Generated message map functions
protected:
	//{{AFX_MSG(Combo)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// mfctovw.h : interface of the CMfctoolView class
//
/////////////////////////////////////////////////////////////////////////////

class CMfctoolView : public CView
{
protected: // create from serialization only
	CMfctoolView();
	DECLARE_DYNCREATE(CMfctoolView);
    TOOLINFO tbToolInfo;
    CToolBarCtrl m_ToolBar;
    Combo m_Combo;

// Attributes
public:
	CMfctoolDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMfctoolView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMfctoolView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMfctoolView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in mfctovw.cpp
inline CMfctoolDoc* CMfctoolView::GetDocument()
   { return (CMfctoolDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
#define ID_TOOLBAR  1000
#define ID_COMBO    1001

