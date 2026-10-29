// fileview.cpp : implementation file
//

#include "stdafx.h"
#include "mfcview.h"
#include "fileview.h"
#include "resource.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileView

IMPLEMENT_DYNCREATE(CFileView, CCmdTarget)

CFileView::CFileView()
{
	EnableAutomation();
	
	// To keep the application running as long as an OLE automation 
	//	object is active, the constructor calls AfxOleLockApp.
	
	AfxOleLockApp();
}

CFileView::~CFileView()
{
	// To terminate the application when all objects created with
	// 	with OLE automation, the destructor calls AfxOleUnlockApp.
	
	AfxOleUnlockApp();
}

void CFileView::OnFinalRelease()
{
	// When the last reference for an automation object is released
	//	OnFinalRelease is called.  This implementation deletes the 
	//	object.  Add additional cleanup required for your object before
	//	deleting it from memory.
	delete this;
}


BEGIN_MESSAGE_MAP(CFileView, CCmdTarget)
	//{{AFX_MSG_MAP(CFileView)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CFileView, CCmdTarget)
	//{{AFX_DISPATCH_MAP(CFileView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

IMPLEMENT_OLECREATE(CFileView, "NancyViewer", 0xe83b63c0, 0x6ff5, 0x11ce, 0x99, 0x3c, 0x0, 0xaa, 0x0, 0x4a, 0xdb, 0x6c)

BEGIN_INTERFACE_MAP(CFileView, CCmdTarget)
    INTERFACE_PART(CFileView, IID_IFileViewer, FileViewer)
    INTERFACE_PART(CFileView, IID_IPersistFile, PersistFile)
END_INTERFACE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CFileView message handlers

// IUnknown for IFileViewer
STDMETHODIMP CFileView::XFileViewer::QueryInterface(REFIID riid, void** ppv)
{
    METHOD_PROLOGUE(CFileView, FileViewer);
    TRACE("CFileView::IFileViewer::QueryInterface\n");
    return pThis->ExternalQueryInterface(&riid, ppv);
}

STDMETHODIMP_(ULONG) CFileView::XFileViewer::AddRef(void)
{
    METHOD_PROLOGUE(CFileView, FileViewer);
    return pThis->ExternalAddRef();
}

STDMETHODIMP_(ULONG) CFileView::XFileViewer::Release(void)
{
    METHOD_PROLOGUE(CFileView, FileViewer);
    return pThis->ExternalRelease();
}

//  IFileViewer Methods

// IFileViewer::PrintTo
//
// Asks a FileViewer to print the file that came through
//  IPersistFile::Load to a specific device with or without
//  any user interaction.  This function should not return
//  until the printing is complete.
//
STDMETHODIMP CFileView::XFileViewer::PrintTo(LPSTR pszDriver, BOOL fSuppressUI)
{
    // This is a stub. Printing isn't implemented.
    TRACE("CFileView::XFileViewer::PrintTo\n");

    return E_NOTIMPL;
}

// IFileViewer::ShowInitialize
//
//  Initializes everything necessary to display the FileViewer.
STDMETHODIMP CFileView::XFileViewer::ShowInitialize(LPFILEVIEWERSITE lpfsi)
{
    METHOD_PROLOGUE(CFileView, FileViewer);
    TRACE("CFileView::XFileViewer::ShowInitialize\n");

    HRESULT hr;

    // Be sure that you have the file viewer.
    if (pThis->m_lpfsi != lpfsi)
    {
        pThis->m_lpfsi = lpfsi;
        pThis->m_lpfsi->AddRef();
    }

    // Default error code
    hr=E_OUTOFMEMORY;

    // Create the windows
    pThis->m_Wnd = new CMyFrame;

    pThis->m_Wnd->Create();
         
    // Load a file.
    HGLOBAL     hMem=NULL;
    char     szwFile[512];

    if (pThis->m_pszPath == NULL)
        return E_UNEXPECTED;

    // This FileViewer is registered for a TXT extension that
    // is either in a compound file (a single stream called "Text")
    // or in a flat text file.  This sample is meant to show
    // how to open and work with both types of files.

    // Make a Unicode copy of the filename.
    mbstowcs((USHORT *)szwFile, pThis->m_pszPath, sizeof(szwFile));

    // CAREFUL: StgIsStorageFile returns S_FALSE if the file doesn't
    // contain an IStorage object.  Don't use SUCCEEDED to test the
    // return value!
    if (StgIsStorageFile(szwFile) == NOERROR)
    {
        LPSTORAGE   pIStorage=NULL;
        LPSTREAM    pIStream=NULL;
        STATSTG     stat;

        // It is a compound file; open it and the text stream.
        hr=StgOpenStorage(szwFile, NULL, pThis->m_grfMode, NULL, 0,
            &pIStorage);

        if (FAILED(hr))
            return hr;

        mbstowcs((USHORT *)szwFile, "Text", sizeof(szwFile));

        hr=pIStorage->OpenStream(szwFile, 0, STGM_DIRECT | STGM_READ
            | STGM_SHARE_EXCLUSIVE, 0, &pIStream);

        if (SUCCEEDED(hr))
        {
            // Determine the amount of text and allocate memory.
            hr=pIStream->Stat(&stat, STATFLAG_NONAME);

            if (SUCCEEDED(hr))
            {
                hMem= (HGLOBAL) malloc (stat.cbSize.LowPart+1);

                if (hMem != NULL)
                    // Now load the text into the controls.
                    hr=pIStream->Read((LPVOID)hMem, stat.cbSize.LowPart, NULL);
                else
                    hr=E_OUTOFMEMORY;
            }

            pIStream->Release();
        }
        pIStorage->Release();
    }
    else
    {
        HANDLE hFile;
        DWORD dwFileSize, dwBytesRead;
        char *lpBufPtr;

   		// Open the text file.
		if ((hFile = CreateFile(pThis->m_pszPath,
			GENERIC_READ,
			FILE_SHARE_READ,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			(HANDLE)NULL)) == (HANDLE)(-1))
		{
	    	AfxMessageBox( "Failed to open file");
            return STG_E_FILENOTFOUND;
		}

		// Get the size of the file.
		dwFileSize = GetFileSize(hFile, NULL);
		if (dwFileSize == 0xFFFFFFFF)
             return STG_E_READFAULT;

		// Allocate a buffer into which the file will be read.
		lpBufPtr = (char *) malloc (dwFileSize);
		if (lpBufPtr == NULL)
		{
	    	CloseHandle( hFile );
            return STG_E_READFAULT;
		}

		// Read the file contents into a buffer..
		ReadFile(hFile,(LPVOID)lpBufPtr, dwFileSize, &dwBytesRead, NULL);

        // Update the multiline edit control with the file contents.
        pThis->m_Wnd->UpdateEdit( lpBufPtr );

		// Close the file.
		CloseHandle(hFile);
    }

    //Tell IFileViewer::Show it's OK to call it.
    pThis->m_fShowInit=TRUE;

    return NOERROR;
}

// CFileView::Show
//
//  Displays the FileViewer's window
STDMETHODIMP CFileView::XFileViewer::Show(LPFVSHOWINFO pvsi)
{
    METHOD_PROLOGUE(CFileView, FileViewer);
    TRACE("CFileView::XFileViewer::Show\n");

    if (!pThis->m_fShowInit)
        return E_UNEXPECTED;

    pThis->m_pvsi = pvsi;

    // If you could not view the file, go back to the message loop.
    if ((pThis->m_pvsi->dwFlags & FVSIF_NEWFAILED) == 0)
    {
        if (pThis->m_pvsi->dwFlags & FVSIF_RECT)
            pThis->m_Wnd->MoveWindow(pThis->m_pvsi->rect.left, 
                pThis->m_pvsi->rect.top, pThis->m_pvsi->rect.right, 
                pThis->m_pvsi->rect.bottom);
        pThis->m_Wnd->ShowWindow(pThis->m_pvsi->iShow);

        if (pThis->m_pvsi->iShow != SW_HIDE)
        {
            pThis->m_Wnd->SetForegroundWindow();
            pThis->m_Wnd->UpdateWindow();
        }

        // If an old window exists, destroy it now.
        if (pThis->m_pvsi->dwFlags & FVSIF_PINNED)
        {
            pThis->m_lpfsi->SetPinnedWindow(NULL);
            pThis->m_lpfsi->SetPinnedWindow(pThis->m_Wnd->m_hWnd);
        }

        if (pThis->m_pvsi->punkRel != NULL)
        {
            pThis->m_pvsi->punkRel->Release();
            pThis->m_pvsi->punkRel = NULL;
        }
    }
    return NOERROR;
}

// IUnknown for IPersistFile
STDMETHODIMP CFileView::XPersistFile::QueryInterface(REFIID riid, void** ppv)
{
    METHOD_PROLOGUE(CFileView, PersistFile);
    TRACE("CFileView::IPersistFile::QueryInterface\n");
    return pThis->ExternalQueryInterface(&riid, ppv);
}

STDMETHODIMP_(ULONG) CFileView::XPersistFile::AddRef(void)
{
    METHOD_PROLOGUE(CFileView, PersistFile);
    return pThis->ExternalAddRef();
}

STDMETHODIMP_(ULONG) CFileView::XPersistFile::Release(void)
{
    METHOD_PROLOGUE(CFileView, PersistFile);
    return pThis->ExternalRelease();
}

// IPersistFile Methods
STDMETHODIMP CFileView::XPersistFile::IsDirty(void)
{
    return S_FALSE;
}


STDMETHODIMP CFileView::XPersistFile::Load(LPCOLESTR pszFileName,
    DWORD dwMode)
{
    METHOD_PROLOGUE(CFileView, PersistFile);

    // No modifications are necessary to this code; it simply
    // copies the parameters into the CFileView::m_pszPath and
    // m_grfMode members for use in IFileViewer::ShowInitialize
    // and IFileViewer::Show later on.

    // You should never be called twice.
    if (pThis->m_pszPath)
        pThis->m_fLoadCalled = FALSE;   // handle error case

    if (pszFileName == NULL)
        return E_INVALIDARG;

    // Copy the ANSI filename and the mode to use in opening it.
    lstrcpy(pThis->m_pszPath,pszFileName);

    // Remember that this function has been called.
    pThis->m_fLoadCalled=TRUE;
    return NOERROR;
}

STDMETHODIMP CFileView::XPersistFile::Save (
   LPCOLESTR pszFileName, BOOL fRemember)
{
    return E_NOTIMPL;
}


STDMETHODIMP CFileView::XPersistFile::SaveCompleted(LPCOLESTR pszFileName)
{
    return E_NOTIMPL;
}


STDMETHODIMP CFileView::XPersistFile::GetCurFile(LPOLESTR __RPC_FAR *ppszFileName)
{
    LPOLESTR    psz;
    ULONG       cb;

    METHOD_PROLOGUE(CFileView, PersistFile);

    // No modifications are necessary to this code; it simply
    // copies the CFileView::m_pszPath string into a piece
    // of memory and stores the pointer at *ppszFile.

    // Load must be called, of course.
    if (pThis->m_fLoadCalled)
        return E_UNEXPECTED;

    if (ppszFileName == NULL)
        return E_INVALIDARG;

    cb=(lstrlen(pThis->m_pszPath)+1)*sizeof(OLECHAR);
    psz=(LPOLESTR)malloc(cb);

    if (NULL==psz)
        return E_OUTOFMEMORY;

    return NOERROR;
}

STDMETHODIMP CFileView::XPersistFile::GetClassID(LPCLSID pClsID)
{
    METHOD_PROLOGUE(CFileView, PersistFile);

    *pClsID=pThis->m_clsID;
    return NOERROR;
}

/////////////////////////////////////////////////////////////////////////////
// CMyFrame

IMPLEMENT_DYNCREATE(CMyFrame, CFrameWnd)

CMyFrame::CMyFrame()
{
}

CMyFrame::~CMyFrame()
{
}


BEGIN_MESSAGE_MAP(CMyFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMyFrame)
	ON_WM_SIZE()
	ON_COMMAND(ID_FILE_EXIT, OnFileExit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMyFrame message handlers
/////////////////////////////////////////////////////////////////////////////
void CMyFrame::OnSize(UINT nType, int cx, int cy) 
{
	CFrameWnd::OnSize(nType, cx, cy);
	
    // resize the edit window
	m_Edit.MoveWindow(0, 0, cx, cy);	
}

void CMyFrame::Create(void)
{
    // Create the frame window
    CFrameWnd::Create("AfxFrameOrView","Nancy's Viewer", 
        WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
        CRect(CW_USEDEFAULT , CW_USEDEFAULT, 250, 250),
        NULL, MAKEINTRESOURCE(IDR_VIEWERMENU), WS_EX_TOPMOST);

    // Create the edit window inside.
    // Get the size of the parent window.
    CRect wndRect;
    GetClientRect(&wndRect);

    // Create a child edit control to display the text.
    m_Edit.Create(ES_MULTILINE | ES_AUTOVSCROLL | WS_CHILD | 
        WS_VISIBLE | ES_AUTOVSCROLL, wndRect, this, ID_EDIT );

}

void CMyFrame::UpdateEdit(char *lpBufPtr)
{
    ::SendMessage(m_Edit.m_hWnd, WM_SETTEXT, 0, (LPARAM) lpBufPtr);
}

void CMyFrame::OnFileExit() 
{
    m_Edit.DestroyWindow();	
}

