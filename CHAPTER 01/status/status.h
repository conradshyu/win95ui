// menu commands
// Options menu
#define IDM_SIMPLE          100
#define IDM_MULTIPLE        101
#define IDM_EXIT            102
// Help menu
#define IDM_ABOUT           200
// other constants
#define STATUS_ICON         300
#define ID_BITMAP           400
#define ID_STATUSBAR        500
// Function prototypes
// procs
LONG APIENTRY MainWndProc(HWND, UINT, UINT, LONG);
BOOL APIENTRY About(HWND, UINT, UINT, LONG);

//functions
BOOL InitApplication(HANDLE);
BOOL InitInstance(HANDLE, int);

//string constants
CHAR *hello = "Click the Options menu to set the status bar to simple mode or multiple-part mode.";


