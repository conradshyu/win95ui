// reatesho.cpp : implementation file
//
#include "stdafx.h"

#define NOTOOLTIPS
#define _OLEAUTO_H_

extern "C" {
#include <shlobj.h>
#include <objbase.h>
}

#include "shortcut.h"
#include "reatesho.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CreateShortCut dialog


CreateShortCut::CreateShortCut(CWnd* pParent /*=NULL*/)
	: CDialog(CreateShortCut::IDD, pParent)
{
	//{{AFX_DATA_INIT(CreateShortCut)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void CreateShortCut::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CreateShortCut)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CreateShortCut, CDialog)
	//{{AFX_MSG_MAP(CreateShortCut)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CreateShortCut message handlers

void CreateShortCut::OnOK() 
{
	char szFileSel[MAX_PATH];
	char szFile[MAX_PATH];
	char szDesc[MAX_PATH];
	char szLink[MAX_PATH];
	DWORD cchCurDir = MAX_PATH;
	char *pDot;

	// First get the path to the link.
	// Should this shortcut be put on the desktop?
	if (IsDlgButtonChecked(IDC_CHECK1))
	{
		// Yes. Get the directory for Windows.
		GetSystemDirectory(szLink, MAX_PATH);

		// Strip off the SYSTEM directory.
		if (pDot = strstr(strupr(szLink), "SYSTEM"))
			*pDot = (char)NULL;

		// Add in the desktop.
		lstrcat(szLink, "Desktop");
	}
	else
		// Get the current directory.
		GetCurrentDirectory(cchCurDir, szLink);

	// Get the selected item in the list box
	DlgDirSelect( szFile, ID_LBOX);

	// Testing getting the file name sans extension
    pDot = strrchr(szFile, '.');


	// Get the description
	lstrcpy(szDesc, "Shortcut to ");
	lstrcat(szDesc, strupr(szFile));

	// Add the forward slash for the path
	lstrcat (szLink, "\\");

	// Add the file name.
	lstrcat (szLink, strupr(szFile));

	// Strip off the extension, if any
	if (pDot = strstr(szLink, "."))
		*pDot = (char)NULL;

	// Add in the .LNK extension
	lstrcat (szLink, ".LNK");

	// Get the path to the target
	GetCurrentDirectory(cchCurDir, szFileSel);
	lstrcat(szFileSel, "\\");
	lstrcat(szFileSel, strupr(szFile));

	// Make call to CreateShortcut() here...
	CreateIt(szFileSel, szLink, szDesc);

	// Call the default handler.
	CDialog::OnOK();
}

// create a shortcut to a file
//
// in:
//   pszShortcutFile     fully qualified path to shortcut file
//   pszTo          shortcut points to this file
//
// returns:
//   standard hres codes
//
// assumes:
//   CoInitialize() has been called...

HRESULT CreateShortCut::CreateIt(LPCSTR pszShortcutFile, LPSTR pszLink, 
	LPSTR pszDesc)
{
    HRESULT hres;
    IShellLink *psl;

	// Create an IShellLink object and get a pointer to the IShellLink
	// interface (returned from CoCreateInstance).
    hres = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER,
                            IID_IShellLink, (void **)&psl);
    if (SUCCEEDED(hres))
    {
       IPersistFile *ppf;
       
	   // Query IShellLink for the IPersistFile interface for
	   // saving the shortcut in persistent storage.
       hres = psl->QueryInterface(IID_IPersistFile, (void **)&ppf);
	   if (SUCCEEDED(hres))
	   {   
	        WORD wsz[MAX_PATH];   // buffer for Unicode string

	   		// Set the path to the shortcut target.
          	hres = psl->SetPath(pszShortcutFile);

			if (!SUCCEEDED(hres))
				AfxMessageBox("SetPath failed!");

            // Set the description of the shortcut.
          	hres = psl->SetDescription(pszDesc);

			if (!SUCCEEDED(hres))
				AfxMessageBox("SetDescription failed!");

	     	// Ensure that the string consists of ANSI characters.
	     	MultiByteToWideChar(CP_ACP, 0, pszLink, -1, wsz, MAX_PATH);

          	// Save the shortcut via the IPersistFile::Save member function.
          	hres = ppf->Save(wsz, TRUE);

			if (!SUCCEEDED(hres))
				AfxMessageBox("Save failed!");

            // Release the pointer to IPersistFile.
          	ppf->Release();
       }
       // Release the pointer to IShellLink.
       psl->Release();
    }
    return hres;
}

BOOL CreateShortCut::OnInitDialog() 
{
	DWORD cchCurDir = MAX_PATH;
	char szCurDir[MAX_PATH];

	CDialog::OnInitDialog();
	
	// Initialize the list box by filling it with files from
	// the current directory
	GetCurrentDirectory(cchCurDir, szCurDir);
	DlgDirList((LPSTR)szCurDir, ID_LBOX, 0, DDL_READWRITE);
	

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
