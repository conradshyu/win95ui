// mfcanvw.h : interface of the CMfcanimView class
//
/////////////////////////////////////////////////////////////////////////////

class CMfcanimView : public CView
{
protected: // create from serialization only
	CMfcanimView();
	DECLARE_DYNCREATE(CMfcanimView)

// Attributes
public:
	CMfcanimDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMfcanimView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMfcanimView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMfcanimView)
	afx_msg void OnDemo();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in mfcanvw.cpp
inline CMfcanimDoc* CMfcanimView::GetDocument()
   { return (CMfcanimDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// CDemo dialog

class CDemo : public CDialog
{
// Construction
public:
	CDemo(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDemo)
	enum { IDD = IDD_DEMO };
	CAnimateCtrl	m_AnimateCtrl;
	//}}AFX_DATA

    BOOL m_bStart;
    int m_iSeek;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDemo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDemo)
	afx_msg void OnSeek();
	afx_msg void OnStart();
	afx_msg void OnStop();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#define NUM_FRAMES  32
