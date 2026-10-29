// menu commands

// menu constants
#define IDM_ABOUT          200
#define IDM_EXIT           300

// icons & bitmaps
#define RICHED_ICON        300
#define IDB_TOOLBAR        400

// toolbar constants
#define ID_TOOLBAR         1000
#define ID_RICHED          1001

// other constants
#define NUM_POINTS          16

// Structure holding font information
typedef struct tagArFonts{
  int        nFonts;
  int        cySpace;
  HDC        hdc;
  LOGFONT    *lf;
  TEXTMETRIC *tm;
  int        *Type;
} ARFONTS, *PARFONTS;



// Function prototypes

// procs
LONG APIENTRY MainWndProc(HWND, UINT, UINT, LONG);
BOOL APIENTRY About(HWND, UINT, UINT, LONG);
LRESULT CALLBACK ComboWndProcFont( HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK ComboWndProcSize( HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam);

// font enumeration callbacks
int APIENTRY MyEnumFaces(LPLOGFONT, LPTEXTMETRIC, DWORD, LPVOID);
int APIENTRY MyEnumCopy (LPLOGFONT, LPTEXTMETRIC, DWORD, LPVOID);
int APIENTRY MyEnumCount(LPLOGFONT, LPTEXTMETRIC, DWORD, LPINT);

//functions
BOOL InitApplication(HANDLE);
BOOL InitInstance(HANDLE, int);
HWND InitToolbar(HWND);
void BoldCmd( HWND );
void ItalicCmd( HWND );
void UnderLineCmd( HWND );
PARFONTS BuildFontList(HDC, LPINT);
VOID FillCombos(void);
VOID FillPtSizes( HWND hWnd, int PtSize);
int SelectFont(LPTSTR lpFaceName, int PtSize);
VOID ChangeFaceName(HWND, LPTSTR);
VOID ChangePointSize(HWND hWndRichEdit, int PointSize);
VOID AlignCmd( HWND hWnd, HWND hWndRichEdit, int iAlign);
BOOL ToggleButton(HWND hWnd, int nID, BOOL bToggle);
DWORD CALLBACK EditStreamCallback(DWORD dwCookie,
    LPBYTE pbBuff, LONG cb, LONG FAR *pcb);
DWORD CALLBACK SaveCallback(DWORD dwCookie,
    LPBYTE pbBuff, LONG cb, LONG FAR *pcb);
BOOL OpenTheFile( HWND, int, char *);
BOOL SaveTheFile( HWND, int);
void PrintTheContents( HWND hWndRichEdit );



