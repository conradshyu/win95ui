// mfcstvw.cpp : implementation of the CMfcstatusView class
//

#include "stdafx.h"
#include "mfcstatus.h"

#include "mfcstdoc.h"
#include "mfcstvw.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMfcstatusView

IMPLEMENT_DYNCREATE(CMfcstatusView, CView)

BEGIN_MESSAGE_MAP(CMfcstatusView, CView)
	//{{AFX_MSG_MAP(CMfcstatusView)
	ON_WM_CREATE()
	ON_COMMAND(IDM_SIMPLE, OnSimple)
	ON_COMMAND(IDM_MULTIPLE, OnMultiple)
	ON_WM_SIZE()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMfcstatusView construction/destruction

CMfcstatusView::CMfcstatusView()
{

}

CMfcstatusView::~CMfcstatusView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CMfcstatusView drawing

void CMfcstatusView::OnDraw(CDC* pDC)
{
	CMfcstatusDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CMfcstatusView diagnostics

#ifdef _DEBUG
void CMfcstatusView::AssertValid() const
{
	CView::AssertValid();
}

void CMfcstatusView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMfcstatusDoc* CMfcstatusView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMfcstatusDoc)));
	return (CMfcstatusDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMfcstatusView message handlers

int CMfcstatusView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
    // Create the status bar.
    m_Status.Create( WS_CHILD | WS_BORDER | WS_VISIBLE | SBARS_SIZEGRIP,
    	CRect (0,0,0,0), 
		this,
        ID_STATUSBAR);

    int aWidths[4] = {0,0,0,0};

    // Set the status bar to have four parts.
    m_Status.SetParts(4, aWidths);
	// Set the text in the first part to normal.
    m_Status.SetText( (LPCTSTR)"Mouse position:", 0, 0);
	// Set the text in the second part to pop out.
    m_Status.SetText( (LPCTSTR)"This text pops out.", 1, SBT_POPOUT);
	// Set the text in the third part to have no borders.
    m_Status.SetText( (LPCTSTR)"This text has no borders.", 2,
       SBT_NOBORDERS);
	// Set the fourth part to be owner-drawn.
    m_Status.SetText( (LPCTSTR)"", 3, SBT_OWNERDRAW );
	return 0;
}

void CMfcstatusView::OnSimple() 
{
   	CMenu *pMenu  = (CMenu *)GetParentFrame()->GetMenu();

    // set the status bar to a simple one.
    m_Status.SetSimple ();
    m_Status.SetText((LPCSTR)"We are now in simple mode.",255, 0);
    // Check the Simple menu option
    pMenu->CheckMenuItem(IDM_SIMPLE, MF_CHECKED | MF_BYCOMMAND);
    // Uncheck the Multiple menu option
    pMenu->CheckMenuItem(IDM_MULTIPLE, MF_UNCHECKED | MF_BYCOMMAND);
	
}

void CMfcstatusView::OnMultiple() 
{
	CMenu *pMenu  = (CMenu *)GetParentFrame()->GetMenu();

    // set the status bar to a multiple parts.
    m_Status.SetSimple(FALSE);
    // UnCheck the Simple menu option
    pMenu->CheckMenuItem(IDM_SIMPLE, MF_UNCHECKED | MF_BYCOMMAND);
    // check the Multiple menu option
    pMenu->CheckMenuItem(IDM_MULTIPLE, MF_CHECKED | MF_BYCOMMAND);
	
}

void CMfcstatusView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
    // resize the status bar so that it fits along the bottom of the client
    m_Status.MoveWindow(0, cx - 10, cy, cy - 10);
    
    // Set the rectangles for the multiple parts of the status bar.
    // Make each 1/4 of the width of the client window.
    int aWidths[4];

    aWidths[0] = cx / 4;
    aWidths[1] = cx / 2;
    aWidths[2] = cx - aWidths[0];
    aWidths[3] = -1;
    m_Status.SetParts(4, aWidths);
	
}

void CMfcstatusView::OnMouseMove(UINT nFlags, CPoint point) 
{
	static char szBuf[64];


	wsprintf(szBuf, "Mouse position: %d, %d.", point.x, point.y);
	m_Status.SetText(szBuf, 0, 0);
	
	CView::OnMouseMove(nFlags, point);
}

/////////////////////////////////////////////////////////////////////////////
// CStatus

CStatus::CStatus()
{
}

CStatus::~CStatus()
{
}


BEGIN_MESSAGE_MAP(CStatus, CStatusBarCtrl)
	//{{AFX_MSG_MAP(CStatus)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CStatus message handlers

void CStatus::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
    static HBITMAP m_Bmp;

        if (m_Bmp ==NULL)
            // Load the bitmap for the owner-drawn part of the status bar.
            m_Bmp = ::LoadBitmap(AfxGetResourceHandle(), MAKEINTRESOURCE(ID_BITMAP));
		// Create a compatible DC for the bit block transfer.
		HDC hdcMem = ::CreateCompatibleDC(lpDrawItemStruct->hDC);
 		// Select the bitmap into the DC.
 		HBITMAP hbmOld = (HBITMAP)::SelectObject(hdcMem, (HBITMAP)m_Bmp);
		
		BITMAP bm;
		// Get the information about the bitmap's size.
		::GetObject((HBITMAP)m_Bmp, sizeof(bm), &bm);
    	// Use BitBlt to transfer the bitmap.
        ::BitBlt( lpDrawItemStruct->hDC, 
              	lpDrawItemStruct->rcItem.left, 
              	lpDrawItemStruct->rcItem.top, 
              	bm.bmWidth, 
              	bm.bmHeight, 
                hdcMem, 0, 0,
                SRCCOPY);
		// Reselect the original bitmap.
		::SelectObject(hdcMem, hbmOld);
        // Delete the compatible DC.
        ::DeleteDC(hdcMem);

}

