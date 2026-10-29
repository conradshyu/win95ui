// mfctrdoc.cpp : implementation of the CMfctreeDoc class
//

#include "stdafx.h"
#include "mfctree.h"

#include "mfctrdoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMfctreeDoc

IMPLEMENT_DYNCREATE(CMfctreeDoc, CDocument)

BEGIN_MESSAGE_MAP(CMfctreeDoc, CDocument)
	//{{AFX_MSG_MAP(CMfctreeDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMfctreeDoc construction/destruction

CMfctreeDoc::CMfctreeDoc()
{
	// TODO: add one-time construction code here

}

CMfctreeDoc::~CMfctreeDoc()
{
}

BOOL CMfctreeDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMfctreeDoc serialization

void CMfctreeDoc::Serialize(CArchive& ar)
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
// CMfctreeDoc diagnostics

#ifdef _DEBUG
void CMfctreeDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMfctreeDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMfctreeDoc commands
