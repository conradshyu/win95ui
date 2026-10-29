// resolves.cpp : implementation file
//
#include "stdafx.h"


#define NOTOOLTIPS    // HACK to get around namespace collision
#define _OLEAUTO_H_

extern "C" {
#include <shlobj.h>
#include <objbase.h>
}

#include "shortcut.h"
#include "resolves.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ResolveShortCut dialog


ResolveShortCut::ResolveShortCut(CWnd* pParent /*=NULL*/)
	: CDialog(ResolveShortCut::IDD, pParent)
{
	//{{AFX_DATA_INIT(ResolveShortCut)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void ResolveShortCut::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ResolveShortCut)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(ResolveShortCut, CDialog)
	//{{AFX_MSG_MAP(ResolveShortCut)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// ResolveShortCut message handlers


void ResolveShortCut::OnOK() 
{
	char szFile[MAX_PATH];

	// Get the selected item in the list box.
	DlgDirSelect( szFile, IDC_LIST1);

	// Find out whether it is a LNK file.
	if (strstr(szFile, ".lnk") != NULL)
		// Make the call to ResolveShortcut::ResolveIt here.
		ResolveIt(m_hWnd, szFile );

	CDialog::OnOK();
}

// find the destination of a shortcut
//
// in:
//   hwnd      to post resolve shortcut UI
//   pszShortcutFile     fully qualified path to shortcut file
//
// returns:
//   standard hres codes
//
//
// assumes:
//   CoInitialize() has been called...
HRESULT ResolveShortCut::ResolveIt(HWND hwnd, LPCSTR pszShortcutFile)
{
    HRESULT hres;
    IShellLink *psl;
	char szGotPath[MAX_PATH];
	char szDescription[MAX_PATH];
	WIN32_FIND_DATA wfd;

    // Get a pointer to the IShellLink interface.
    hres = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER,
                            IID_IShellLink, (void **)&psl);
    if (SUCCEEDED(hres))
    {
        IPersistFile *ppf;

        // Get a pointer to the IPersistFile interface.
        hres = psl->QueryInterface(IID_IPersistFile, (void **)&ppf);
        if (SUCCEEDED(hres))
        {
             WORD wsz[MAX_PATH];   // buffer for Unicode string

             // Ensure that the string consists of Unicode characters.
             MultiByteToWideChar(CP_ACP, 0, pszShortcutFile, -1, wsz,
                                 MAX_PATH);
			 
			 // Load the shortcut.
             hres = ppf->Load(wsz, STGM_READ);
             if (SUCCEEDED(hres))
             {
                // Resolve the shortcut.
                hres = psl->Resolve(hwnd, SLR_ANY_MATCH);

                if (SUCCEEDED(hres))
				{
					strcpy(szGotPath, pszShortcutFile);
                   	// Get the parth to the shortcut target.
                   	hres = psl->GetPath(szGotPath, MAX_PATH,
                   	   (WIN32_FIND_DATA *)&wfd, SLGP_SHORTPATH );
				   	if (!SUCCEEDED(hres))
						AfxMessageBox("GetPath failed!");
					else
						AfxMessageBox(szGotPath);
	               	
	               	// Get the description of the target.
	               	hres = psl->GetDescription(szDescription, MAX_PATH);
					if (!SUCCEEDED(hres))
						AfxMessageBox("GetDescription failed!");
					else
						AfxMessageBox(szDescription);
				}
             }
          // Release the pointer to IPersistFile.
          ppf->Release();
      }
      // Release the pointer to IShellLink.
      psl->Release();
   }
   return hres;
}

BOOL ResolveShortCut::OnInitDialog() 
{
	DWORD cchCurDir = MAX_PATH;
	char szCurDir[MAX_PATH];

	CDialog::OnInitDialog();
	
	// Initialize the list box by filling it with files from
	// the current directory
	GetCurrentDirectory(cchCurDir, szCurDir);
	DlgDirList(szCurDir, IDC_LIST1, 0, DDL_READWRITE);
	
return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
