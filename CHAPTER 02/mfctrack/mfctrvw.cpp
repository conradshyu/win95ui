// mfctrvw.cpp : implementation of the CMfctrackView class
//

#include "stdafx.h"
#include "mfctrack.h"

#include "mfctrdoc.h"
#include "mfctrvw.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMfctrackView

IMPLEMENT_DYNCREATE(CMfctrackView, CView)

BEGIN_MESSAGE_MAP(CMfctrackView, CView)
	//{{AFX_MSG_MAP(CMfctrackView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_HSCROLL()
	ON_COMMAND(IDM_RANGE, OnRange)
	ON_COMMAND(IDM_FREQUENCY, OnFrequency)
	ON_COMMAND(IDM_LINESIZE, OnLinesize)
	ON_COMMAND(IDM_PAGESIZE, OnPagesize)
	ON_WM_VSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMfctrackView construction/destruction

CMfctrackView::CMfctrackView()
{
	// TODO: add construction code here

}

CMfctrackView::~CMfctrackView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CMfctrackView drawing

void CMfctrackView::OnDraw(CDC* pDC)
{
	CMfctrackDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
}

/////////////////////////////////////////////////////////////////////////////
// CMfctrackView diagnostics

#ifdef _DEBUG
void CMfctrackView::AssertValid() const
{
	CView::AssertValid();
}

void CMfctrackView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMfctrackDoc* CMfctrackView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMfctrackDoc)));
	return (CMfctrackDoc*)m_pDocument;
}
#endif //_DEBUG

CSliderCtrl * CMfctrackView::GetSlider(int iSlider)
{
	switch (iSlider)
	{
			case 1: return &m_Slider1;
				break;

			case 2: return &m_Slider2;
				break;

			case 3: return &m_Slider3;
				break;
		}
		return ((CSliderCtrl *)NULL);
}

/////////////////////////////////////////////////////////////////////////////
// CMfctrackView message handlers

int CMfctrackView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// Create the sliders.
	m_Slider1.Create( WS_CHILD | WS_VISIBLE | TBS_AUTOTICKS,
				CRect(10,50,200,70),
				this,        
				ID_SLIDER1);

	m_Slider2.Create(WS_CHILD | WS_VISIBLE | TBS_AUTOTICKS | TBS_TOP | TBS_ENABLESELRANGE,
				CRect(10,100,200,130),
				this,         
				ID_SLIDER2);         

	m_Slider3.Create(WS_CHILD | WS_VISIBLE | TBS_VERT | TBS_LEFT | TBS_AUTOTICKS,
				CRect(10,150,30,350),
				this,         
				ID_SLIDER3);

	// Set the default range.
	m_Slider1.SetRange(1,10, TRUE);
	m_Slider2.SetRange(1,25, TRUE);
	m_Slider3.SetRange(1,30, TRUE);

	// Set the selection .
	m_Slider2.SetSelection(10, 20);
	
	return 0;
}

void CMfctrackView::OnDestroy() 
{
	CView::OnDestroy();
	
	// TODO: Add your message handler code here

	
}


// This function checks to see if a trackbar notification is being sent
// and, if so, updates the status bar with the notification message.
void CMfctrackView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
    TrackScrolling(nSBCode);

	CView::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CMfctrackView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
    TrackScrolling(nSBCode);
	
	CView::OnVScroll(nSBCode, nPos, pScrollBar);
}

VOID CMfctrackView::TrackScrolling(UINT nSBCode) 
{
 	BOOL bMsg = TRUE;
	char  *pMsg = NULL;

	switch(nSBCode)
	{
		case TB_BOTTOM:
			pMsg = "TB_BOTTOM";
			break;

		case TB_ENDTRACK:
			pMsg = "TB_ENDTRACK";
			break;

		case TB_LINEDOWN:
			pMsg = "TB_LINEDOWN";
			break;

		case TB_LINEUP:
			pMsg = "TB_LINEUP";
			break;

		case TB_PAGEDOWN:
			pMsg = "TB_PAGEDOWN";
			break;

		case TB_PAGEUP:
			pMsg = "TB_PAGEUP";
			break;

		case TB_THUMBPOSITION:
			pMsg = "TB_THUMBPOSITION";
			break;

		case TB_THUMBTRACK:
			pMsg = "TB_THUMBTRACK";
			break;

		default:
			bMsg = FALSE;
			break;

	}
	if (bMsg == TRUE)
	{
		CStatusBar *pStatus  = (CStatusBar *)GetParentFrame()->
			GetDescendantWindow(ID_VIEW_STATUS_BAR);

        char szBuf[256];

  		sprintf(szBuf,"Trackbar message: %s",pMsg);

		pStatus->SetPaneText(0, szBuf);
		pStatus->UpdateWindow();
	}
    
}
/////////////////////////////////////////////////////////////////////////////
// CRange dialog


CRange::CRange(CWnd* pParent /*=NULL*/)
	: CDialog(CRange::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRange)
	m_Min = 0;
	m_Max = 0;
	m_Slider = 1;
	//}}AFX_DATA_INIT
}


void CRange::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRange)
	DDX_Text(pDX, IDE_MIN, m_Min);
	DDX_Text(pDX, IDE_MAX, m_Max);
	DDX_Text(pDX, IDE_SLIDER, m_Slider);
	DDV_MinMaxInt(pDX, m_Slider, 1, 2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRange, CDialog)
	//{{AFX_MSG_MAP(CRange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CRange message handlers

void CMfctrackView::OnRange() 
{
	CRange rangeDlg;
	
	if (rangeDlg.DoModal() == IDOK)
	{
		switch (rangeDlg.m_Slider)
		{
			case 1:
				m_Slider1.SetRange(rangeDlg.m_Min, rangeDlg.m_Max, TRUE);
				break;

			case 2:
				m_Slider2.SetRange(rangeDlg.m_Min, rangeDlg.m_Max, TRUE);
				break;

			case 3:
				m_Slider3.SetRange(rangeDlg.m_Min, rangeDlg.m_Max, TRUE);
				break;

			default:
				break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// CFrequency dialog


CFrequency::CFrequency(CWnd* pParent /*=NULL*/)
	: CDialog(CFrequency::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFrequency)
	m_Slider = 1;
	m_Frequency = 0;
	//}}AFX_DATA_INIT
}


void CFrequency::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFrequency)
	DDX_Text(pDX, IDE_SLIDER, m_Slider);
	DDV_MinMaxInt(pDX, m_Slider, 1, 3);
	DDX_Text(pDX, IDE_FREQUENCY, m_Frequency);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFrequency, CDialog)
	//{{AFX_MSG_MAP(CFrequency)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CFrequency message handlers
void CMfctrackView::OnFrequency() 
{
	
	CFrequency frequencyDlg;
	if (frequencyDlg.DoModal() == IDOK)
	{
		switch (frequencyDlg.m_Slider)
		{
			case 1:
				m_Slider1.SetTicFreq(frequencyDlg.m_Frequency);
				break;

			case 2:
				m_Slider2.SetTicFreq(frequencyDlg.m_Frequency);
				break;

			case 3:
				m_Slider3.SetTicFreq(frequencyDlg.m_Frequency);
				break;

			default:
				break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// CLineSize dialog


CLineSize::CLineSize(CWnd* pParent /*=NULL*/)
	: CDialog(CLineSize::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLineSize)
	m_Slider = 1;
	m_LineSize = 0;
	//}}AFX_DATA_INIT
}


void CLineSize::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLineSize)
	DDX_Text(pDX, IDE_SLIDER, m_Slider);
	DDV_MinMaxInt(pDX, m_Slider, 1, 3);
	DDX_Text(pDX, IDE_LINESIZE, m_LineSize);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLineSize, CDialog)
	//{{AFX_MSG_MAP(CLineSize)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CLineSize message handlers

void CMfctrackView::OnLinesize() 
{
	CLineSize LineSizeDlg;
	if (LineSizeDlg.DoModal()==IDOK)
	{
		switch (LineSizeDlg.m_Slider)
		{
			case 1:
				m_Slider1.SetLineSize(LineSizeDlg.m_LineSize);
				break;

			case 2:
				m_Slider2.SetLineSize(LineSizeDlg.m_LineSize);
				break;

			case 3:
				m_Slider3.SetLineSize(LineSizeDlg.m_LineSize);
				break;

			default:
				break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// CPageSize dialog


CPageSize::CPageSize(CWnd* pParent /*=NULL*/)
	: CDialog(CPageSize::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPageSize)
	m_Slider = 1;
	m_PageSize = 0;
	//}}AFX_DATA_INIT
}


void CPageSize::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageSize)
	DDX_Text(pDX, IDE_SLIDER, m_Slider);
	DDV_MinMaxInt(pDX, m_Slider, 1, 3);
	DDX_Text(pDX, IDE_PAGESIZE, m_PageSize);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageSize, CDialog)
	//{{AFX_MSG_MAP(CPageSize)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CPageSize message handlers

void CMfctrackView::OnPagesize() 
{
	CPageSize PageSizeDlg;
	if (PageSizeDlg.DoModal()==IDOK)
	{
		switch (PageSizeDlg.m_Slider)
		{
			case 1:
				m_Slider1.SetPageSize(PageSizeDlg.m_PageSize);
				break;

			case 2:
				m_Slider2.SetPageSize(PageSizeDlg.m_PageSize);
				break;

			case 3:
				m_Slider3.SetPageSize(PageSizeDlg.m_PageSize);
				break;

			default:
				break;
		}

	}
}


