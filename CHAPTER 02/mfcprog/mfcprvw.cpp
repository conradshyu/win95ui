// mfcprvw.cpp : implementation of the CMfcprogView class
//

#include "stdafx.h"
#include "mfcprog.h"

#include "mfcprdoc.h"
#include "mfcprvw.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMfcprogView

IMPLEMENT_DYNCREATE(CMfcprogView, CView)

BEGIN_MESSAGE_MAP(CMfcprogView, CView)
	//{{AFX_MSG_MAP(CMfcprogView)
	ON_WM_TIMER()
	ON_COMMAND(IDM_START, OnStart)
	ON_COMMAND(IDM_STOP, OnStop)
	ON_WM_CREATE()
	ON_COMMAND(IDM_RANGE, OnRange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMfcprogView construction/destruction

CMfcprogView::CMfcprogView()
{
	// TODO: add construction code here

}

CMfcprogView::~CMfcprogView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CMfcprogView drawing

void CMfcprogView::OnDraw(CDC* pDC)
{
	CMfcprogDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CString hello = "Choose Start from the Options menu to start the progress bar.";

	pDC->TextOut(20, 10, hello);      
}

/////////////////////////////////////////////////////////////////////////////
// CMfcprogView diagnostics

#ifdef _DEBUG
void CMfcprogView::AssertValid() const
{
	CView::AssertValid();
}

void CMfcprogView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMfcprogDoc* CMfcprogView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMfcprogDoc)));
	return (CMfcprogDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMfcprogView message handlers

void CMfcprogView::OnTimer(UINT nIDEvent) 
{
	if (m_Current < m_Max)
	{
		m_Progress.StepIt();
		m_Current++;
	}
	else
	{
		KillTimer(ID_TIMER);
		m_Current = 0;
	}
	
	CView::OnTimer(nIDEvent);
}

void CMfcprogView::OnStart() 
{
	m_Current = m_Min;
	SetTimer(ID_TIMER, 500, NULL);
		
}

void CMfcprogView::OnStop() 
{
	m_Progress.SetPos(0);
	KillTimer(ID_TIMER);
	
}

int CMfcprogView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_Progress.Create( WS_CHILD | WS_VISIBLE,
		CRect(10,100,500,120),
		this,
		ID_PROGRESS );
	m_Min=0;
	m_Max=20;
	m_Progress.SetRange(m_Min, m_Max);
	m_Progress.SetStep(1);
		
	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CRange dialog


CRange::CRange(CWnd* pParent /*=NULL*/)
	: CDialog(CRange::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRange)
	m_Max = 0;
	m_Min = 0;
	//}}AFX_DATA_INIT
}


void CRange::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRange)
	DDX_Text(pDX, IDC_MAX, m_Max);
	DDV_MinMaxInt(pDX, m_Max, 0, 100);
	DDX_Text(pDX, IDC_MIN, m_Min);
	DDV_MinMaxInt(pDX, m_Min, 0, 100);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRange, CDialog)
	//{{AFX_MSG_MAP(CRange)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CRange message handlers
void CMfcprogView::OnRange() 
{
	CRange rangeDlg;
	
	if (rangeDlg.DoModal() == IDOK)
	 	m_Progress.SetRange(rangeDlg.m_Min, rangeDlg.m_Max);
}
