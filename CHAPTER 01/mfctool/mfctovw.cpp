// mfctovw.cpp : implementation of the CMfctoolView class
//

#include "stdafx.h"
#include "mfctool.h"

#include "mfctodoc.h"
#include "mfctovw.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

TBBUTTON tbButtons[] = {
	{ 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, 0},
	{ 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, 0},
	{ 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, 0},
	{ 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, 0},
	{ 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, 0},
	{ 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, 0},
	{ 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, 0},
	{ 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, 0},
	{ 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, 0},
	{ 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, 0},
	{ 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, 0},
	{ 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, 0},
	{ 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, 0},
	{ 0, IDM_NEW, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0},
	{ 1, IDM_OPEN, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0},
	{ 2, IDM_SAVE, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0},
	{ 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, 0},
	{ 3, IDM_CUT, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0},
	{ 4, IDM_COPY, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0},
	{ 5, IDM_PASTE, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0},
	{ 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, 0},
	{ 6, IDM_PRINT, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0},
	{ 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, 0},
    { 7, IDM_ABOUT, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0}
};

char *szStrings[] = { "Nancy", "Dale", "Dennis", "Herman", "Ken", "Kyle", "Nigel", "Renan", "Ruediger"};

/////////////////////////////////////////////////////////////////////////////
// CMfctoolView

IMPLEMENT_DYNCREATE(CMfctoolView, CView)

BEGIN_MESSAGE_MAP(CMfctoolView, CView)
	//{{AFX_MSG_MAP(CMfctoolView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_LBUTTONDBLCLK()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMfctoolView construction/destruction

CMfctoolView::CMfctoolView()
{
	// TODO: add construction code here

}

CMfctoolView::~CMfctoolView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CMfctoolView drawing

void CMfctoolView::OnDraw(CDC* pDC)
{
	CMfctoolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CMfctoolView diagnostics

#ifdef _DEBUG
void CMfctoolView::AssertValid() const
{
	CView::AssertValid();
}

void CMfctoolView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMfctoolDoc* CMfctoolView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMfctoolDoc)));
	return (CMfctoolDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMfctoolView message handlers

int CMfctoolView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// Create the toolbar.
    m_ToolBar.Create(
		WS_CHILD | WS_BORDER | WS_VISIBLE | TBSTYLE_TOOLTIPS | CCS_ADJUSTABLE,   // style
        CRect(0,0,0,0),
        this,
        ID_TOOLBAR);

    // Add the bitmaps
    m_ToolBar.AddBitmap(8, IDB_BITMAP1);

    // Add the buttons
    m_ToolBar.AddButtons(24, (LPTBBUTTON)&tbButtons);

    // Create the combo box.
    m_Combo.Create(
        WS_CHILD | WS_BORDER | WS_VISIBLE | CBS_HASSTRINGS | CBS_DROPDOWN,
        CRect(0,0,100,250),
        (CWnd *)&m_ToolBar,
        ID_COMBO );

    int idx;
    for (idx=0; idx < 8; idx++)
        m_Combo.InsertString( -1, (LPCTSTR)szStrings[idx]);

    // Get the handle to the tooltip window.
    CToolTipCtrl *tTip = (CToolTipCtrl *)m_ToolBar.GetToolTips();

    // Set up tooltips for the combo box.
    tTip->AddTool((CWnd *)&m_ToolBar, IDS_COMBO, CRect(0,0,100,30), ID_COMBO );

    return 0;
}

void CMfctoolView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
    // Resize the toolbar
    m_ToolBar.AutoSize();	
}

void CMfctoolView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
    // Toolbar Customization
    m_ToolBar.Customize();
    	
	CView::OnLButtonDblClk(nFlags, point);
}

LRESULT CMfctoolView::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	static CHAR szBuf[128];
	LPTOOLTIPTEXT lpToolTipText;

    if (message == WM_NOTIFY)
    {
	    switch (((LPNMHDR) lParam)->code) 
        {
            case TTN_NEEDTEXT:    
                 // Display the ToolTip text.
			     lpToolTipText = (LPTOOLTIPTEXT)lParam;
    			 ::LoadString (AfxGetResourceHandle(), 
	    				lpToolTipText->hdr.idFrom,    // string ID == cmd ID
		    			szBuf,
			    		sizeof(szBuf));
				    	lpToolTipText->lpszText = szBuf;
			      break;

            case TBN_QUERYDELETE:
                 // Toolbar customization--can we delete this button?
                 return TRUE;
                 break;

            case TBN_GETBUTTONINFO:
                 // The toolbar needs information about a button.
                 return FALSE;
                 break;

            case TBN_QUERYINSERT:
                 // Can this button be inserted? Just say yo.
                 return TRUE;
                 break;

            case TBN_CUSTHELP:
                 // Need to display custom Help.
                 AfxMessageBox("This Help is custom.");
                 break;

            case TBN_TOOLBARCHANGE:
                 // The user finished dragging a bitmap to the toolbar.
                 m_ToolBar.AutoSize();
                 break;

            default:
                 return TRUE;
                 break;
        }
    }	
	return CView::WindowProc(message, wParam, lParam);
}
/////////////////////////////////////////////////////////////////////////////
// Combo

Combo::Combo()
{
}

Combo::~Combo()
{
}


BEGIN_MESSAGE_MAP(Combo, CComboBox)
	//{{AFX_MSG_MAP(Combo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Combo message handlers

LRESULT Combo::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{

    switch (message)
    {
        case WM_LBUTTONDOWN:
        case WM_LBUTTONUP:
        case WM_MOUSEMOVE:
        {
            CToolTipCtrl *tTip;
            CToolBarCtrl *tBar;

            tBar = (CToolBarCtrl *)GetParentFrame()->GetDescendantWindow(ID_TOOLBAR);
            tTip = tBar->GetToolTips();

            tTip->RelayEvent((MSG *)GetCurrentMessage());
	        break;
        }
    }
	return CComboBox::WindowProc(message, wParam, lParam);
}
