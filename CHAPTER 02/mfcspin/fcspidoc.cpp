// fcspidoc.cpp : implementation of the CFcspinDoc class
//

#include "stdafx.h"
#include "mfcspin.h"

#include "fcspidoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFcspinDoc

IMPLEMENT_DYNCREATE(CFcspinDoc, CDocument)

BEGIN_MESSAGE_MAP(CFcspinDoc, CDocument)
	//{{AFX_MSG_MAP(CFcspinDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFcspinDoc construction/destruction

CFcspinDoc::CFcspinDoc()
{
	// TODO: add one-time construction code here

}

CFcspinDoc::~CFcspinDoc()
{
}

BOOL CFcspinDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CFcspinDoc serialization

void CFcspinDoc::Serialize(CArchive& ar)
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
// CFcspinDoc diagnostics

#ifdef _DEBUG
void CFcspinDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFcspinDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFcspinDoc commands
