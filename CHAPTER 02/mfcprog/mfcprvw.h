// mfcprvw.h : interface of the CMfcprogView class
//
/////////////////////////////////////////////////////////////////////////////

class CMfcprogView : public CView
{
protected: // create from serialization only
	CMfcprogView();
	DECLARE_DYNCREATE(CMfcprogView);
	int m_Current;
	int m_Max;
	int m_Min;
	CProgressCtrl m_Progress;

// Attributes
public:
	CMfcprogDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMfcprogView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMfcprogView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMfcprogView)
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnStart();
	afx_msg void OnStop();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnRange();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in mfcprvw.cpp
inline CMfcprogDoc* CMfcprogView::GetDocument()
   { return (CMfcprogDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
// CONSTANTS
#define ID_PROGRESS	100
#define ID_TIMER	200
/////////////////////////////////////////////////////////////////////////////
// CRange dialog

class CRange : public CDialog
{
// Construction
public:
	CRange(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRange)
	enum { IDD = IDD_Range };
	int		m_Max;
	int		m_Min;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRange)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRange)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
