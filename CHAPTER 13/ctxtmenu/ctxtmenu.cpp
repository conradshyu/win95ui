// ctxtmenu.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "ctxtmenu.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCtxtmenuApp

BEGIN_MESSAGE_MAP(CCtxtmenuApp, CWinApp)
	//{{AFX_MSG_MAP(CCtxtmenuApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCtxtmenuApp construction

CCtxtmenuApp::CCtxtmenuApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CCtxtmenuApp object

CCtxtmenuApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CCtxtmenuApp initialization

BOOL CCtxtmenuApp::InitInstance()
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
// CTxtMenu

IMPLEMENT_DYNCREATE(CTxtMenu, CCmdTarget)

CTxtMenu::CTxtMenu()
{
	EnableAutomation();
	
	// To keep the application running as long as an OLE automation 
	//	object is active, the constructor calls AfxOleLockApp.
	
	AfxOleLockApp();
}

CTxtMenu::~CTxtMenu()
{
	// To terminate the application when all objects created with
	// 	with OLE automation, the destructor calls AfxOleUnlockApp.
	
	AfxOleUnlockApp();
}

void CTxtMenu::OnFinalRelease()
{
	// When the last reference for an automation object is released
	//	OnFinalRelease is called.  This implementation deletes the 
	//	object.  Add additional cleanup required for your object before
	//	deleting it from memory.

	delete this;
}


BEGIN_MESSAGE_MAP(CTxtMenu, CCmdTarget)
	//{{AFX_MSG_MAP(CTxtMenu)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CTxtMenu, CCmdTarget)
	//{{AFX_DISPATCH_MAP(CTxtMenu)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

IMPLEMENT_OLECREATE(CTxtMenu, "NWContextMenu", 0x5fbcd2e0, 0x73dd, 0x11ce, 0x99, 0x3c, 0x0, 0xaa, 0x0, 0x4a, 0xdb, 0x6c)

BEGIN_INTERFACE_MAP(CTxtMenu, CCmdTarget)
    INTERFACE_PART(CTxtMenu, IID_IContextMenu, MenuExt)
    INTERFACE_PART(CTxtMenu, IID_IShellExtInit, ShellInit)
END_INTERFACE_MAP()

// IUnknown for IContextMenu
STDMETHODIMP CTxtMenu::XMenuExt::QueryInterface(REFIID riid, void** ppv)
{
    METHOD_PROLOGUE(CTxtMenu, MenuExt);
    TRACE("CTxtMenu::XMenuExt::QueryInterface\n");
    return pThis->ExternalQueryInterface(&riid, ppv);
}

STDMETHODIMP_(ULONG) CTxtMenu::XMenuExt::AddRef(void)
{
    METHOD_PROLOGUE(CTxtMenu, MenuExt);
    return pThis->ExternalAddRef();
}

STDMETHODIMP_(ULONG) CTxtMenu::XMenuExt::Release(void)
{
    METHOD_PROLOGUE(CTxtMenu, MenuExt);
    return pThis->ExternalRelease();
}

STDMETHODIMP CTxtMenu::XMenuExt::QueryContextMenu( HMENU hmenu,UINT indexMenu,
    UINT idCmdFirst, UINT idCmdLast,UINT uFlags)
{

    ::InsertMenu(hmenu, indexMenu++, MF_STRING | MF_BYPOSITION,
        idCmdFirst + ID_NEWCMD, "&Test Context Menu...");

    return ResultFromScode(MAKE_SCODE(SEVERITY_SUCCESS, FACILITY_NULL, (USHORT)2));
}

STDMETHODIMP CTxtMenu::XMenuExt::InvokeCommand(LPCMINVOKECOMMANDINFO lpici)
{
    METHOD_PROLOGUE(CTxtMenu, MenuExt);
    char szTest[MAX_PATH * 2];

    if (HIWORD(lpici->lpVerb ))
    {
        AfxMessageBox("E_FAIL");
        return E_FAIL;
    }

    if (LOWORD(lpici->lpVerb) > ID_NEWCMD)
    {
        AfxMessageBox("Invalid Arg");
        return E_INVALIDARG;
    }

    if (LOWORD(lpici->lpVerb) == ID_NEWCMD)
    {
        wsprintf(szTest, "Context menu for file: %s", pThis->m_szFileName);
        ::MessageBox(lpici->hwnd, szTest, "Context Menu Handler", MB_OK);
    }
    else
        ::MessageBox(lpici->hwnd, "ID != ID_NEWCMD", "Context Menu Handler", MB_OK);
        
    return NOERROR;
}

STDMETHODIMP CTxtMenu::XMenuExt::GetCommandString(UINT idCmd,UINT uType,
    UINT* pwReserved,LPSTR pszName,UINT cchMax)
{
    if (idCmd > ID_NEWCMD)
        return ResultFromScode(E_INVALIDARG);

    if (idCmd == ID_NEWCMD)
        lstrcpy(pszName, "Context Menu Test");

    return NOERROR;
}

// IUnknown for IShellExtInit
STDMETHODIMP CTxtMenu::XShellInit::QueryInterface(REFIID riid, void** ppv)
{
    METHOD_PROLOGUE(CTxtMenu, ShellInit);
    TRACE("CTxtMenu::XShellInit::QueryInterface\n");
    return pThis->ExternalQueryInterface(&riid, ppv);
}

STDMETHODIMP_(ULONG) CTxtMenu::XShellInit::AddRef(void)
{
    METHOD_PROLOGUE(CTxtMenu, ShellInit);
    return pThis->ExternalAddRef();
}

STDMETHODIMP_(ULONG) CTxtMenu::XShellInit::Release(void)
{
    METHOD_PROLOGUE(CTxtMenu, ShellInit);
    return pThis->ExternalRelease();
}

STDMETHODIMP CTxtMenu::XShellInit::Initialize(LPCITEMIDLIST pidlFolder, IDataObject *pdobj, HKEY hkeyProgID)
{
    METHOD_PROLOGUE(CTxtMenu, ShellInit);
    TRACE("CTxtMenu::XShellInit::Intialize\n");

    HRESULT hres = E_FAIL;
    FORMATETC fmte = {CF_HDROP, NULL, DVASPECT_CONTENT, -1, TYMED_HGLOBAL};
    STGMEDIUM medium;

    //
    //  no data object, we dont deal with that.
    //
    if (pdobj == NULL)
    {
	    TRACE("CTxtMenu::XShellInit::Initialize() no data object");
	    return E_FAIL;
    }

    //
    //  use the given IDataObject to get a list of filenames (CF_HDROP)
    //
    hres = pdobj->GetData(&fmte, &medium);

    if (FAILED(hres))
    {
	    TRACE("CTxtMenu::XShellInit::Initialize() cant get data");
	    return E_FAIL;
    }
    //
    // a HDROP can contain more than one file if the user selects
    // multiple files and brings up a context menu your handler
    // will be called.	not all files will be your type! only the
    // first one will be.  unless your handler can deal with
    // any file type, the best thing to do is to not
    // support HDROPs with more than one file.
    //
    if (DragQueryFile((HDROP)medium.hGlobal, (UINT)-1, NULL, 0) == 1)
    {
    	DragQueryFile((HDROP)medium.hGlobal, 0, pThis->m_szFileName, sizeof(pThis->m_szFileName));
	    hres = S_OK;
    }
    else
    	hres = E_FAIL;
 
    //
    //	release the data.
    //
    ReleaseStgMedium(&medium);

    return hres;
}

/////////////////////////////////////////////////////////////////////////////
// CTxtMenu message handlers
