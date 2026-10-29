// propext.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "propext.h"
#include "resource.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPropextApp

BEGIN_MESSAGE_MAP(CPropextApp, CWinApp)
	//{{AFX_MSG_MAP(CPropextApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPropextApp construction

CPropextApp::CPropextApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CPropextApp object

CPropextApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CPropextApp initialization

BOOL CPropextApp::InitInstance()
{
	// Register all OLE server (factories) as running.  This enables the
	//  OLE libraries to create objects from other applications.
	COleObjectFactory::RegisterAll();

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// Special entry points required for inproc servers

#if (_MFC_VER >= 0x300)
STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
	return AfxDllGetClassObject(rclsid, riid, ppv);
}

STDAPI DllCanUnloadNow(void)
{
	return AfxDllCanUnloadNow();
}
#endif

// by exporting DllRegisterServer, you can use regsvr.exe
STDAPI DllRegisterServer(void)
{
	COleObjectFactory::UpdateRegistryAll();
	return S_OK;
}
/////////////////////////////////////////////////////////////////////////////
// CPropExt

IMPLEMENT_DYNCREATE(CPropExt, CCmdTarget)

CPropExt::CPropExt()
{
	EnableAutomation();
	
	// To keep the application running as long as an OLE automation 
	//	object is active, the constructor calls AfxOleLockApp.
	
	AfxOleLockApp();
}

CPropExt::~CPropExt()
{
	// To terminate the application when all objects created with
	// 	with OLE automation, the destructor calls AfxOleUnlockApp.
	
	AfxOleUnlockApp();
}

void CPropExt::OnFinalRelease()
{
	// When the last reference for an automation object is released
	//	OnFinalRelease is called.  This implementation deletes the 
	//	object.  Add additional cleanup required for your object before
	//	deleting it from memory.

	delete this;
}


BEGIN_MESSAGE_MAP(CPropExt, CCmdTarget)
	//{{AFX_MSG_MAP(CPropExt)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CPropExt, CCmdTarget)
	//{{AFX_DISPATCH_MAP(CPropExt)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

IMPLEMENT_OLECREATE(CPropExt, "NancyPropSheet", 0x771a9da0, 0x731a, 0x11ce, 0x99, 0x3c, 0x0, 0xaa, 0x0, 0x4a, 0xdb, 0x6c)

BEGIN_INTERFACE_MAP(CPropExt, CCmdTarget)
    INTERFACE_PART(CPropExt, IID_IShellPropSheetExt, PropExt)
    INTERFACE_PART(CPropExt, IID_IShellExtInit, ShellInit)
END_INTERFACE_MAP()


// IUnknown for IShellPropSheet
STDMETHODIMP CPropExt::XPropExt::QueryInterface(REFIID riid, void** ppv)
{
    METHOD_PROLOGUE(CPropExt, PropExt);
    TRACE("CPropExt::XPropExt::QueryInterface\n");
    return pThis->ExternalQueryInterface(&riid, ppv);
}

STDMETHODIMP_(ULONG) CPropExt::XPropExt::AddRef(void)
{
    METHOD_PROLOGUE(CPropExt, PropExt);
    return pThis->ExternalAddRef();
}

STDMETHODIMP_(ULONG) CPropExt::XPropExt::Release(void)
{
    METHOD_PROLOGUE(CPropExt, PropExt);
    return pThis->ExternalRelease();
}


STDMETHODIMP CPropExt::XPropExt::AddPages(LPFNADDPROPSHEETPAGE lpfnAddPage, LPARAM lParam)
{
    METHOD_PROLOGUE(CPropExt, PropExt);
    TRACE("CPropExt::XPropExt::AddPages\n");

    PROPSHEETPAGE psp;

    psp.dwSize      = sizeof(psp);   // no extra data
    psp.dwFlags     = PSP_USEREFPARENT;
    psp.hInstance   = AfxGetResourceHandle();
    psp.pszTemplate = MAKEINTRESOURCE(IDD_TESTPAGE);
    psp.pfnDlgProc  = (DLGPROC)pThis->PropExtDlgProc;
    psp.pcRefParent = (UINT *)&(pThis->m_cRefThisDll);

    pThis->m_hPage = ::CreatePropertySheetPage(&psp);
    if (pThis->m_hPage)
    {
        if (!lpfnAddPage(pThis->m_hPage, lParam))
            ::DestroyPropertySheetPage(pThis->m_hPage);
    }
    return NOERROR;
}

STDMETHODIMP CPropExt::XPropExt::ReplacePage(UINT uPageID, LPFNADDPROPSHEETPAGE lpfnReplaceWith, LPARAM lParam)
{
    return E_NOTIMPL;
}


BOOL APIENTRY CPropExt::PropExtDlgProc( HWND hDlg, UINT message, UINT wParam,	LONG lParam)
{

	switch (message)
	{
		case WM_NOTIFY:
    		switch (((NMHDR FAR *) lParam)->code) 
    		{

				case PSN_APPLY:
 	           		SetWindowLong(hDlg,	DWL_MSGRESULT, TRUE);
					break;

				case PSN_KILLACTIVE:
	           		SetWindowLong(hDlg,	DWL_MSGRESULT, FALSE);
					return 1;
					break;

				case PSN_RESET:
	           		SetWindowLong(hDlg,	DWL_MSGRESULT, FALSE);
					break;
    	}
	}
	return FALSE;   
}

// IUnknown for IShellExtInit
STDMETHODIMP CPropExt::XShellInit::QueryInterface(REFIID riid, void** ppv)
{
    METHOD_PROLOGUE(CPropExt, ShellInit);
    TRACE("CPropExt::XShellInit::QueryInterface\n");
    return pThis->ExternalQueryInterface(&riid, ppv);
}

STDMETHODIMP_(ULONG) CPropExt::XShellInit::AddRef(void)
{
    METHOD_PROLOGUE(CPropExt, ShellInit);
    return pThis->ExternalAddRef();
}

STDMETHODIMP_(ULONG) CPropExt::XShellInit::Release(void)
{
    METHOD_PROLOGUE(CPropExt, ShellInit);
    return pThis->ExternalRelease();
}

STDMETHODIMP CPropExt::XShellInit::Initialize(LPCITEMIDLIST pidlFolder, IDataObject *pdobj, HKEY hkeyProgID)
{
    METHOD_PROLOGUE(CPropExt, ShellInit);
    TRACE("CPropExt::XShellInit::Intialize\n");

    HRESULT hres = E_FAIL;
    FORMATETC fmte = 
    {
       CF_HDROP, 		   // use CF_HDROP format
       NULL, 			   // no specific device required
       DVASPECT_CONTENT,   // embedded object
       -1, 				   // must be -1 for DVASPECT_CONTENT
       TYMED_HGLOBAL	   // how to transfer data
    };
    STGMEDIUM medium;

    // No data object
    if (pdobj == NULL)
    {
	    TRACE("CPropExt::XShellInit::Initialize() no data object");
	    return E_FAIL;
    }

    // Use the given IDataObject to get a list of filenames (CF_HDROP).
    hres = pdobj->GetData(&fmte, &medium);

    if (FAILED(hres))
    {
	    TRACE("CPropExt::XShellInit::Initialize() can't get data");
	    return E_FAIL;
    }

    // HDROP can contain more than one file. If the user selects
    // multiple files and brings up a context menu, your handler
    // will be called. Not all files will be your type! Only the
    // first one will be that type. 
    if (DragQueryFile((HDROP)medium.hGlobal, (UINT)(-1), NULL, 0) == 1)
    {
    	DragQueryFile((HDROP)medium.hGlobal, 0, pThis->m_szFileName, sizeof(pThis->m_szFileName));
	    hres = S_OK;
    }
    else
    	hres = E_FAIL;
 
    // Release the data.
    ReleaseStgMedium(&medium);

    return hres;
}

/////////////////////////////////////////////////////////////////////////////
// CPropExt message handlers
/////////////////////////////////////////////////////////////////////////////
