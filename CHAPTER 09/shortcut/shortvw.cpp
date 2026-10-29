// shortvw.cpp : implementation of the CShortcutView class
//

#include "stdafx.h"
#include "shortcut.h"

#include "shortdoc.h"
#include "shortvw.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CShortcutView

IMPLEMENT_DYNCREATE(CShortcutView, CView)

BEGIN_MESSAGE_MAP(CShortcutView, CView)
	//{{AFX_MSG_MAP(CShortcutView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShortcutView construction/destruction

CShortcutView::CShortcutView()
{
	// TODO: add construction code here

}

CShortcutView::~CShortcutView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CShortcutView drawing

void CShortcutView::OnDraw(CDC* pDC)
{
	CShortcutDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CShortcutView diagnostics

#ifdef _DEBUG
void CShortcutView::AssertValid() const
{
	CView::AssertValid();
}

void CShortcutView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CShortcutDoc* CShortcutView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CShortcutDoc)));
	return (CShortcutDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CShortcutView message handlers
