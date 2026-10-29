// mfcexdoc.cpp : implementation of the CMfcexpDoc class
//

#include "stdafx.h"
#include "mfcexp.h"

#include "mfcexdoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMfcexpDoc

IMPLEMENT_DYNCREATE(CMfcexpDoc, CDocument)

BEGIN_MESSAGE_MAP(CMfcexpDoc, CDocument)
	//{{AFX_MSG_MAP(CMfcexpDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMfcexpDoc construction/destruction

CMfcexpDoc::CMfcexpDoc()
{
	// TODO: add one-time construction code here

}

CMfcexpDoc::~CMfcexpDoc()
{
}

BOOL CMfcexpDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMfcexpDoc serialization

void CMfcexpDoc::Serialize(CArchive& ar)
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
// CMfcexpDoc diagnostics

#ifdef _DEBUG
void CMfcexpDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMfcexpDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMfcexpDoc commands
