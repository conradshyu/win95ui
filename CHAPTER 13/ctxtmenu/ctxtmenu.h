// ctxtmenu.h : main header file for the CTXTMENU DLL
//
#include <ole2.h>
#include <shlobj.h>
#include <winuser.h>
#include "ctxtid.h"

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

/////////////////////////////////////////////////////////////////////////////
// CCtxtmenuApp
// See ctxtmenu.cpp for the implementation of this class
//

class CCtxtmenuApp : public CWinApp
{
public:
	CCtxtmenuApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCtxtmenuApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CCtxtmenuApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
// CTxtMenu command target

class CTxtMenu : public CCmdTarget
{
	DECLARE_DYNCREATE(CTxtMenu)
protected:
	CTxtMenu();           // protected constructor used by dynamic creation

// Attributes
public:
    char m_szFileName[MAX_PATH];
    UINT m_cRefThisDll;     // Reference count for this DLL

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTxtMenu)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CTxtMenu();

	// Generated message map functions
	//{{AFX_MSG(CTxtMenu)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CTxtMenu)

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CTxtMenu)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

    // Declare the interface map for this object
    DECLARE_INTERFACE_MAP()

    // IFileViewer interface
    BEGIN_INTERFACE_PART(MenuExt, IContextMenu)
        STDMETHOD(QueryContextMenu)( HMENU hmenu,UINT indexMenu,UINT idCmdFirst,
            UINT idCmdLast,UINT uFlags);
        STDMETHOD(InvokeCommand)(LPCMINVOKECOMMANDINFO lpici);
        STDMETHOD(GetCommandString)(UINT idCmd,UINT uType,UINT* pwReserved,LPSTR pszName,
            UINT cchMax);
    END_INTERFACE_PART(MenuExt)

    // IShellExtInit interface
    BEGIN_INTERFACE_PART(ShellInit, IShellExtInit)
        STDMETHOD(Initialize)(LPCITEMIDLIST pidlFolder,LPDATAOBJECT lpdobj, HKEY hkeyProgID);
    END_INTERFACE_PART(ShellInit)


};

/////////////////////////////////////////////////////////////////////////////
#define ID_NEWCMD       1
#define CF_HDROP        15
