// mfctrvw.h : interface of the CMfctrackView class
//
/////////////////////////////////////////////////////////////////////////////

class CMfctrackView : public CView
{
protected: // create from serialization only
	CMfctrackView();
	DECLARE_DYNCREATE(CMfctrackView);
	CSliderCtrl m_Slider1;
	CSliderCtrl m_Slider2;
	CSliderCtrl m_Slider3;

// Attributes
public:
	CMfctrackDoc* GetDocument();

// Operations
public:
	CSliderCtrl * GetSlider(int iSlider);
// Overrides
	// ClassWizard generated virtual function overrides.
	//{{AFX_VIRTUAL(CMfctrackView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to
	                                // draw this view
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMfctrackView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
    VOID TrackScrolling(UINT nSBCode); 

// Generated message map functions
protected:
	//{{AFX_MSG(CMfctrackView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnRange();
	afx_msg void OnFrequency();
	afx_msg void OnLinesize();
	afx_msg void OnPagesize();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in mfctrvw.cpp
inline CMfctrackDoc* CMfctrackView::GetDocument()
   { return (CMfctrackDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
// constants
#define ID_SLIDER1	1
#define ID_SLIDER2  2
#define ID_SLIDER3	3
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
	int		m_Min;
	int		m_Max;
	int		m_Slider;
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
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
// CFrequency dialog

class CFrequency : public CDialog
{
// Construction
public:
	CFrequency(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFrequency)
	enum { IDD = IDD_FREQUENCY };
	int		m_Slider;
	int		m_Frequency;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFrequency)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFrequency)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
// CLineSize dialog

class CLineSize : public CDialog
{
// Construction
public:
	CLineSize(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLineSize)
	enum { IDD = IDD_LINESIZE };
	int		m_Slider;
	int		m_LineSize;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLineSize)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLineSize)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
// CPageSize dialog

class CPageSize : public CDialog
{
// Construction
public:
	CPageSize(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPageSize)
	enum { IDD = IDD_PAGESIZE };
	int		m_Slider;
	int		m_PageSize;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPageSize)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPageSize)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
