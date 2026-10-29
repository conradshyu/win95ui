// fcspivw.cpp : implementation of the CFcspinView class
//

#include "stdafx.h"
#include "mfcspin.h"

#include "fcspidoc.h"
#include "fcspivw.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFcspinView

IMPLEMENT_DYNCREATE(CFcspinView, CView)

BEGIN_MESSAGE_MAP(CFcspinView, CView)
	//{{AFX_MSG_MAP(CFcspinView)
	ON_COMMAND(IDM_SPIN, OnSpin)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFcspinView construction/destruction

CFcspinView::CFcspinView()
{
	// TODO: add construction code here
	m_NumLines = 1;

}

CFcspinView::~CFcspinView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CFcspinView drawing

void CFcspinView::OnDraw(CDC* pDC)
{
	CFcspinDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	int idx;
	static char *szWelcome = "Welcome";

	for (idx = 1; idx <= m_NumLines; idx++)
		pDC->TextOut(20, 5 + (idx * 16), szWelcome, strlen(szWelcome));      
}

/////////////////////////////////////////////////////////////////////////////
// CFcspinView diagnostics

#ifdef _DEBUG
void CFcspinView::AssertValid() const
{
	CView::AssertValid();
}

void CFcspinView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CFcspinDoc* CFcspinView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFcspinDoc)));
	return (CFcspinDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFcspinView message handlers
/////////////////////////////////////////////////////////////////////////////
// CSpin dialog


CSpin::CSpin(CWnd* pParent /*=NULL*/)
	: CDialog(CSpin::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSpin)
	m_Lines = 0;
	//}}AFX_DATA_INIT
}


void CSpin::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSpin)
	DDX_Control(pDX, IDC_SPIN, m_Spin);
	DDX_Text(pDX, IDC_LINES, m_Lines);
	DDV_MinMaxInt(pDX, m_Lines, 1, 20);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSpin, CDialog)
	//{{AFX_MSG_MAP(CSpin)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CSpin message handlers

BOOL CSpin::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// Set the buddy control.
	m_Spin.SetBuddy(GetDlgItem(IDC_LINES));

	// Set the range.
	m_Spin.SetRange(1,20);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX property pages should return FALSE
}

void CFcspinView::OnSpin() 
{
	CSpin spinDlg;
	
	if (spinDlg.DoModal() == IDOK)
	{
		m_NumLines = spinDlg.m_Lines;
		GetDocument()->UpdateAllViews(NULL);
	}
}
