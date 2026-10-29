// reatesho.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CreateShortCut dialog

class CreateShortCut : public CDialog
{
// Construction
public:
	CreateShortCut(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CreateShortCut)
	enum { IDD = IDD_CREATE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CreateShortCut)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnOK();
	virtual HRESULT CreateIt(LPCSTR pszShortcutFile, LPSTR pszLink, LPSTR pszDesc);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CreateShortCut)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
