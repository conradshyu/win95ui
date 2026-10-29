// TREEVIEW.H

// constants                            
#define ID_TREEVIEW     1000

#define MAX_LEN         32
#define NUM_BITMAPS     4
#define BITMAP_WIDTH    16
#define BITMAP_HEIGHT   16
#define NUM_HOUSES      9
#define MAX_ADDRESS     32

// menu commands

// Options menu

#define IDM_EXIT        104

// Help menu
#define IDM_ABOUT       300

// icons & bitmaps
#define APP_ICON        400
#define REDMOND         401
#define BELLEVUE        402
#define SEATTLE         403
#define FORSALE         404

// stringtable defines
#define IDS_FORSALE     1
#define IDS_REDMOND     2
#define IDS_BELLEVUE    3
#define IDS_SEATTLE     4

// structures
typedef struct tagHOUSEINFO
{
    char szAddress[MAX_ADDRESS];
    int iImage;
    HTREEITEM hParent;
    HTREEITEM hItem;
} HOUSEINFO;

// Function prototypes

// procs
long APIENTRY MainWndProc(HWND, UINT, UINT, LONG);
BOOL APIENTRY About(HWND, UINT, UINT, LONG);

//functions
BOOL InitApplication(HANDLE);
BOOL InitInstance(HANDLE, int);
HWND CreateTreeView(HWND);
BOOL AddTreeViewItems(HWND);
HTREEITEM AddOneItem(HTREEITEM, LPSTR, HTREEITEM, int, HWND);
VOID FillInStruct(HTREEITEM, int, int, int);
VOID BeginDrag(HWND, NM_TREEVIEW *);
VOID DropItem(HTREEITEM, HWND);

