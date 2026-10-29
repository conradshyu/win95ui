// mfctodoc.cpp : implementation of the CMfctoolDoc class
//

#include "stdafx.h"
#include "mfctool.h"

#include "mfctodoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMfctoolDoc

IMPLEMENT_DYNCREATE(CMfctoolDoc, CDocument)

BEGIN_MESSAGE_MAP(CMfctoolDoc, CDocument)
	//{{AFX_MSG_MAP(CMfctoolDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMfctoolDoc construction/destruction

CMfctoolDoc::CMfctoolDoc()
{
	// TODO: add one-time construction code here

}

CMfctoolDoc::~CMfctoolDoc()
{
}

BOOL CMfctoolDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMfctoolDoc serialization

void CMfctoolDoc::Serialize(CArchive& ar)
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
// CMfctoolDoc diagnostics

#ifdef _DEBUG
void CMfctoolDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMfctoolDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMfctoolDoc commands
