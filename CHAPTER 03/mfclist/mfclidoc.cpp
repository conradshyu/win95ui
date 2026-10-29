// mfclidoc.cpp : implementation of the CMfclistDoc class
//

#include "stdafx.h"
#include "mfclist.h"

#include "mfclidoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMfclistDoc

IMPLEMENT_DYNCREATE(CMfclistDoc, CDocument)

BEGIN_MESSAGE_MAP(CMfclistDoc, CDocument)
	//{{AFX_MSG_MAP(CMfclistDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMfclistDoc construction/destruction

CMfclistDoc::CMfclistDoc()
{
	// TODO: add one-time construction code here

}

CMfclistDoc::~CMfclistDoc()
{
}

BOOL CMfclistDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMfclistDoc serialization

void CMfclistDoc::Serialize(CArchive& ar)
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
// CMfclistDoc diagnostics

#ifdef _DEBUG
void CMfclistDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMfclistDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMfclistDoc commands
