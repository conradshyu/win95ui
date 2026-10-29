// mfcprdoc.cpp : implementation of the CMfcprogDoc class
//

#include "stdafx.h"
#include "mfcprog.h"

#include "mfcprdoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMfcprogDoc

IMPLEMENT_DYNCREATE(CMfcprogDoc, CDocument)

BEGIN_MESSAGE_MAP(CMfcprogDoc, CDocument)
	//{{AFX_MSG_MAP(CMfcprogDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMfcprogDoc construction/destruction

CMfcprogDoc::CMfcprogDoc()
{
	// TODO: add one-time construction code here

}

CMfcprogDoc::~CMfcprogDoc()
{
}

BOOL CMfcprogDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMfcprogDoc serialization

void CMfcprogDoc::Serialize(CArchive& ar)
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
// CMfcprogDoc diagnostics

#ifdef _DEBUG
void CMfcprogDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMfcprogDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMfcprogDoc commands
