// mfcendoc.cpp : implementation of the CMfcenumDoc class
//

#include "stdafx.h"
#include "mfcenum.h"

#include "mfcendoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMfcenumDoc

IMPLEMENT_DYNCREATE(CMfcenumDoc, CDocument)

BEGIN_MESSAGE_MAP(CMfcenumDoc, CDocument)
	//{{AFX_MSG_MAP(CMfcenumDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CMfcenumDoc, CDocument)
	//{{AFX_DISPATCH_MAP(CMfcenumDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//      DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMfcenumDoc construction/destruction

CMfcenumDoc::CMfcenumDoc()
{
	// TODO: add one-time construction code here

	EnableAutomation();

	AfxOleLockApp();
}

CMfcenumDoc::~CMfcenumDoc()
{
	AfxOleUnlockApp();
}

BOOL CMfcenumDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMfcenumDoc serialization

void CMfcenumDoc::Serialize(CArchive& ar)
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
// CMfcenumDoc diagnostics

#ifdef _DEBUG
void CMfcenumDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMfcenumDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMfcenumDoc commands
