                            
// menu commands

// Options menu
#define IDM_ANIMATE     100
#define IDM_EXIT        101

// Help menu
#define IDM_ABOUT       200

// icons
#define EXE_ICON        300

#define ID_ANIMATION    1000

#define NUM_FRAMES      32

// Function prototypes

// procs
long APIENTRY MainWndProc(HWND, UINT, UINT, LONG);
BOOL APIENTRY About(HWND, UINT, UINT, LONG);
BOOL APIENTRY Demo(HWND, UINT, UINT, LONG);

//functions
BOOL InitApplication(HANDLE);
BOOL InitInstance(HANDLE, int);

