// resolves.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ResolveShortCut dialog

class ResolveShortCut : public CDialog
{
// Construction
public:
	ResolveShortCut(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(ResolveShortCut)
	enum { IDD = IDD_RESOLVE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ResolveShortCut)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnOK();
	virtual HRESULT ResolveIt(HWND hwnd, LPCSTR pszShortcutFile);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ResolveShortCut)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
