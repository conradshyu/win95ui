// CONSTANTS
#define APPBAR_CALLBACK     WM_USER + 100 
#define TRAY_CALLBACK       WM_USER + 101  
#define DEF_APPBAR_WIDTH    70
#define DEF_APPBAR_HEIGHT   30
#define BUTTON_WIDTH        60
#define BUTTON_HEIGHT       25

#define IDM_RIGHT           2000
#define IDM_LEFT            2001
#define IDM_TOP             2002
#define IDM_BOTTOM          2003

#define ID_APPBAR           100
#define ID_BTN1             101
#define ID_BTN2             102
#define ID_BTN3             103
#define ID_BTN4             104
#define ID_EDITCHILD        105

#define ID_SHELLFUN_ICON                143
#define ID_SHELLNOFUN_ICON              144
#define IDM_DEMO                        32771
#define IDM_FILEINFO                    32772
#define IDM_TRAY                        32773
#define IDM_ADD                         32775
#define IDM_REMOVE                      32776
#define IDM_TASKBAR                     32777
#define IDM_STATECHANGE                 32784
#define IDM_REMOVEICON                  32785
#define IDM_ADDICON                     32786
#define IDM_EXIT                        32787
#define IDM_ABOUT                       32788


// Globals
HINSTANCE g_hInst;
APPBARDATA g_appBar;    // The appbar structure
BOOL g_fRegistered;     // Whether the app bar is registered
BOOL g_State1;
HWND g_hWndAppBar;
HWND g_hwndBtn1, g_hwndBtn2, g_hwndBtn3, g_hwndBtn4;
char g_szState1[10], g_szState2[10];
HICON g_hIconState;


// Function prototypes
// procs
LONG APIENTRY MainWndProc(HWND, UINT, UINT, LONG);
BOOL APIENTRY About(HWND, UINT, UINT, LONG);
LRESULT CALLBACK  AppBarWndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);


//functions
BOOL InitApplication(HANDLE);
BOOL InitInstance(HANDLE, int);

void PASCAL AppBarPosChanged(UINT uEdge, APPBARDATA *abd);
void AppBarCallback(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
void TrayMessage( HWND hWnd, UINT message);
void TrayCallback( WPARAM wParam, LPARAM lParam);
void OnFileInfo(HWND hWnd, HWND hwndEdit);
void AppBarClicked(UINT msg,APPBARDATA * pabd);


//string constants
CHAR *hello = "Click on the Options menu to set the status bar to simple or multiple parts.";


