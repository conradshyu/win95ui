// mainfrm.cpp : implementation of the CMainFrame class
//
#include "stdafx.h"

#define _OLEAUTO_H_

extern "C" {
#include <objbase.h>
}

#include "wtypes.h"
#include "shortcut.h"
#include "reatesho.h"
#include "resolves.h"
#include "mainfrm.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_COMMAND(IDM_RESOLVE, OnResolve)
	ON_COMMAND(IDM_CREATE, OnCreate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


void CMainFrame::OnResolve() 
{
	// Invoke Resolve Shortcut dialog box here
	ResolveShortCut MyDlg;
	MyDlg.DoModal();
	
}

void CMainFrame::OnCreate() 
{
	// Invoke Create Dialog Box
	CreateShortCut MyDlg;
	MyDlg.DoModal();
	
}

