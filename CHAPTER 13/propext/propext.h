// propext.h : main header file for the PROPEXT DLL
//
#include <ole2.h>
#include <shlobj.h>
#include <prsht.h>
#include <winuser.h>
#include "propid.h"

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

/////////////////////////////////////////////////////////////////////////////
// CPropextApp
// See propext.cpp for the implementation of this class
//

class CPropextApp : public CWinApp
{
public:
	CPropextApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPropextApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CPropextApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
// CPropExt command target

class CPropExt : public CCmdTarget
{
	DECLARE_DYNCREATE(CPropExt)
protected:
	CPropExt();           // protected constructor used by dynamic creation

// Attributes
public:
    UINT m_cRefThisDll;     // Reference count for this DLL
    HPROPSHEETPAGE m_hPage; // Handle to the property sheet page
    char m_szFileName[MAX_PATH];

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPropExt)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CPropExt();

	// Generated message map functions
	//{{AFX_MSG(CPropExt)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CPropExt)

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CPropExt)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

    // Declare the interface map for this object
    DECLARE_INTERFACE_MAP()

    // IShellPropSheetExt interface
    BEGIN_INTERFACE_PART(PropExt, IShellPropSheetExt)
        STDMETHOD(AddPages)(LPFNADDPROPSHEETPAGE lpfnAddPage, LPARAM lParam);
        STDMETHOD(ReplacePage)(UINT uPageID, LPFNADDPROPSHEETPAGE lpfnReplaceWith, LPARAM lParam);
    END_INTERFACE_PART(PropExt)

    // IShellExtInit interface
    BEGIN_INTERFACE_PART(ShellInit, IShellExtInit)
        STDMETHOD(Initialize)(LPCITEMIDLIST pidlFolder,LPDATAOBJECT lpdobj, HKEY hkeyProgID);
    END_INTERFACE_PART(ShellInit)

    static BOOL APIENTRY PropExtDlgProc( HWND hDlg, UINT message, UINT wParam, LONG lParam);

};

/////////////////////////////////////////////////////////////////////////////
#define CF_HDROP            15
