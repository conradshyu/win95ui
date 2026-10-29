// shortvw.h : interface of the CShortcutView class
//
/////////////////////////////////////////////////////////////////////////////

class CShortcutView : public CView
{
protected: // create from serialization only
	CShortcutView();
	DECLARE_DYNCREATE(CShortcutView)

// Attributes
public:
	CShortcutDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShortcutView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CShortcutView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CShortcutView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in shortvw.cpp
inline CShortcutDoc* CShortcutView::GetDocument()
   { return (CShortcutDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
