// fcspivw.h : interface of the CFcspinView class
//
/////////////////////////////////////////////////////////////////////////////

class CFcspinView : public CView
{
protected: // create from serialization only
	CFcspinView();
	DECLARE_DYNCREATE(CFcspinView);
	int m_NumLines;
	

// Attributes
public:
	CFcspinDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFcspinView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFcspinView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CFcspinView)
	afx_msg void OnSpin();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in fcspivw.cpp
inline CFcspinDoc* CFcspinView::GetDocument()
   { return (CFcspinDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// CSpin dialog

class CSpin : public CDialog
{
// Construction
public:
	CSpin(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSpin)
	enum { IDD = IDD_SPIN };
	CSpinButtonCtrl	m_Spin;
	int		m_Lines;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSpin)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSpin)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
