// shortdoc.cpp : implementation of the CShortcutDoc class
//

#include "stdafx.h"
#include "shortcut.h"

#include "shortdoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CShortcutDoc

IMPLEMENT_DYNCREATE(CShortcutDoc, CDocument)

BEGIN_MESSAGE_MAP(CShortcutDoc, CDocument)
	//{{AFX_MSG_MAP(CShortcutDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShortcutDoc construction/destruction

CShortcutDoc::CShortcutDoc()
{
	// TODO: add one-time construction code here

}

CShortcutDoc::~CShortcutDoc()
{
}

BOOL CShortcutDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CShortcutDoc serialization

void CShortcutDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CShortcutDoc diagnostics

#ifdef _DEBUG
void CShortcutDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CShortcutDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CShortcutDoc commands
