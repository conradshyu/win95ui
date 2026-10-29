// mfcanvw.cpp : implementation of the CMfcanimView class
//

#include "stdafx.h"
#include "mfcanim.h"

#include "mfcandoc.h"
#include "mfcanvw.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMfcanimView

IMPLEMENT_DYNCREATE(CMfcanimView, CView)

BEGIN_MESSAGE_MAP(CMfcanimView, CView)
	//{{AFX_MSG_MAP(CMfcanimView)
	ON_COMMAND(IDM_DEMO, OnDemo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMfcanimView construction/destruction

CMfcanimView::CMfcanimView()
{
	// TODO: add construction code here

}

CMfcanimView::~CMfcanimView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CMfcanimView drawing

void CMfcanimView::OnDraw(CDC* pDC)
{
	CMfcanimDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CMfcanimView diagnostics

#ifdef _DEBUG
void CMfcanimView::AssertValid() const
{
	CView::AssertValid();
}

void CMfcanimView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMfcanimDoc* CMfcanimView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMfcanimDoc)));
	return (CMfcanimDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMfcanimView message handlers

void CMfcanimView::OnDemo() 
{
	CDemo demoDlg;
	
	// Run the Animation Demo dialog box.
	demoDlg.DoModal();
}
/////////////////////////////////////////////////////////////////////////////
// CDemo dialog


CDemo::CDemo(CWnd* pParent /*=NULL*/)
	: CDialog(CDemo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDemo)
		// NOTE: the ClassWizard will add member initialization here.
	//}}AFX_DATA_INIT
    m_bStart = FALSE;	// BOOL--whether or not animation has started
    m_iSeek = 1;		// used for single-stepping throught the frames
}


void CDemo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDemo)
	DDX_Control(pDX, IDC_GENERIC1, m_AnimateCtrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDemo, CDialog)
	//{{AFX_MSG_MAP(CDemo)
	ON_BN_CLICKED(IDB_SEEK, OnSeek)
	ON_BN_CLICKED(IDB_START, OnStart)
	ON_BN_CLICKED(IDB_STOP, OnStop)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDemo message handlers

void CDemo::OnSeek() 
{
    // If the animation is running...
    if (m_bStart)
    {
        // seek to the specified frame.
        m_AnimateCtrl.Seek(m_iSeek);
        if (m_iSeek < NUM_FRAMES)
            m_iSeek++;
    }	
	
}

void CDemo::OnStart() 
{
    // If the animation hasn't started yet...
    if (!m_bStart)
    {
        m_bStart = TRUE;	
		// Open the animation file.
        m_AnimateCtrl.Open(IDR_AVICLIP);
		// Play it from beginning to end with infinite replay.
        m_AnimateCtrl.Play(0, (UINT)-1, (UINT)-1);
    }
}

void CDemo::OnStop() 
{
    if (m_bStart)
    {
        // If the animation has started...
        m_bStart = FALSE;
		// Stop it.
        m_AnimateCtrl.Stop();
    }	
}
