// mfcstvw.h : interface of the CMfcstatusView class
//
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////

#define ID_STATUSBAR    500
/////////////////////////////////////////////////////////////////////////////
// CStatus window

class CStatus : public CStatusBarCtrl
{
// Construction
public:
	CStatus();

// Attributes
public:

// Operations
public:

// Overrides
    void DrawItem(LPDRAWITEMSTRUCT);
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStatus)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CStatus();

	// Generated message map functions
protected:
	//{{AFX_MSG(CStatus)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////


class CMfcstatusView : public CView
{
protected: // create from serialization only
	CMfcstatusView();
	DECLARE_DYNCREATE(CMfcstatusView);
    CStatus m_Status;

// Attributes
public:
	CMfcstatusDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	// {{AFX_VIRTUAL(CMfcstatusView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw
	                                // this view
	protected:
	// }}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMfcstatusView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	// {{AFX_MSG(CMfcstatusView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSimple();
	afx_msg void OnMultiple();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	// }}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in mfcstvw.cpp
inline CMfcstatusDoc* CMfcstatusView::GetDocument()
   { return (CMfcstatusDoc*)m_pDocument; }
#endif

