// mfcstdoc.cpp : implementation of the CMfcstatusDoc class
//

#include "stdafx.h"
#include "mfcstatus.h"

#include "mfcstdoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMfcstatusDoc

IMPLEMENT_DYNCREATE(CMfcstatusDoc, CDocument)

BEGIN_MESSAGE_MAP(CMfcstatusDoc, CDocument)
	//{{AFX_MSG_MAP(CMfcstatusDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMfcstatusDoc construction/destruction

CMfcstatusDoc::CMfcstatusDoc()
{
	// TODO: add one-time construction code here

}

CMfcstatusDoc::~CMfcstatusDoc()
{
}

BOOL CMfcstatusDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMfcstatusDoc serialization

void CMfcstatusDoc::Serialize(CArchive& ar)
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
// CMfcstatusDoc diagnostics

#ifdef _DEBUG
void CMfcstatusDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMfcstatusDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMfcstatusDoc commands
