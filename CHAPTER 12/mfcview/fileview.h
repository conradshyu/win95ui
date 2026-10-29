// fileview.h : header file
//
#include <ole2.h>
#include <shlobj.h>

/////////////////////////////////////////////////////////////////////////////
// CMyFrame frame

class CMyFrame : public CFrameWnd
{
	DECLARE_DYNCREATE(CMyFrame)
public:
	CMyFrame();           
   	virtual ~CMyFrame();
    void Create(void);
    void UpdateEdit(char *);

// Attributes
public:
    CEdit m_Edit;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyFrame)
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMyFrame)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnFileExit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// CFileView command target

class CFileView : public CCmdTarget
{
	DECLARE_DYNCREATE(CFileView)
protected:
	CFileView();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileView)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CFileView();

	// Generated message map functions
	//{{AFX_MSG(CFileView)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CFileView)

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CFileView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()  

    // Declare the interface map for this object.
    DECLARE_INTERFACE_MAP()

    // IFileViewer interface
    BEGIN_INTERFACE_PART(FileViewer, IFileViewer)
        // IFileViewer stuff
        STDMETHOD(ShowInitialize) (LPFILEVIEWERSITE lpfsi);
        STDMETHOD(Show) (LPFVSHOWINFO pvsi);
        STDMETHOD(PrintTo) (LPSTR pszDriver, BOOL fSuppressUI);
    END_INTERFACE_PART(FileViewer)

    BEGIN_INTERFACE_PART(PersistFile, IPersistFile)
      //IPersistFile
	    STDMETHODIMP IsDirty();
	    STDMETHODIMP Load(LPCOLESTR pszFileName,DWORD dwMode);
	    STDMETHODIMP Save(LPCOLESTR pszFileName,BOOL fRemember);
	    STDMETHODIMP SaveCompleted(LPCOLESTR pszFileName);
	    STDMETHODIMP GetCurFile(LPOLESTR __RPC_FAR *ppszFileName);
        STDMETHODIMP GetClassID(LPCLSID pClsID);
    END_INTERFACE_PART(PersistFile)
    
public:
    // Member variables 
    LPFILEVIEWERSITE    m_lpfsi;            // file viewer site

    CLSID               m_clsID;            // CLSID of this file viewer
    char               m_pszPath[MAX_PATH]; // path from IPersistFile::Load
    DWORD               m_grfMode;          // open mode for the file
    BOOL                m_fLoadCalled;      // Load already called?
    BOOL                m_fShowInit;        // ShowInitialize called?

    CMyFrame* m_Wnd; // viewer frame window

    LPFVSHOWINFO        m_pvsi;

};

/////////////////////////////////////////////////////////////////////////////
#define ID_WINDOW   1000
#define ID_EDIT     1001
