/****************************************************************************
*
*
*    PROGRAM: RICHED.c
*
*    PURPOSE: Sample demonstrating the rich edit control
*
****************************************************************************/

#include <windows.h>    // includes basic windows functionality
#include <commctrl.h>   // includes the common control header
#include <richedit.h>   // includes the rich edit control header
#include <string.h>
#include "riched.h"
#include "resource.h"

HINSTANCE hInst;

// toolbar buttons
TBBUTTON tbButtons[] = {
	{ 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, 0},
	{ 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, 0},
	{ 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, 0},
	{ 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, 0},
	{ 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, 0},
	{ 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, 0},
	{ 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, 0},
	{ 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, 0},
	{ 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, 0},
	{ 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, 0},
	{ 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, 0},
	{ 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, 0},
	{ 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, 0},
	{ 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, 0},
	{ 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, 0},
	{ 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, 0},
	{ 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, 0},
	{ 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, 0},
	{ 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, 0},
	{ 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, 0},
	{ 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, 0},
	{ 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, 0},
	{ 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, 0},
	{ 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, 0},
	{ 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, 0},
	{ 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, 0},
	{ 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, 0},
	{ 0, IDM_BOLD, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0},
	{ 1, IDM_ITALIC, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0},
    { 2, IDM_UNDERLINE, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0},
	{ 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, 0},
    { 3, IDM_ALIGNLEFT, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0},
    { 4, IDM_ALIGNCENTER, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0},
    { 5, IDM_ALIGNRIGHT, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0},
};

// array of supported point sizes
int aPoints[NUM_POINTS] = {8, 9, 10, 11, 12, 14, 16, 18, 20, 22, 24, 26, 28, 36, 48, 72 };

// Window procedures for combo box subclassing
WNDPROC lpfnDefComboFont;
WNDPROC lpfnDefComboSize;

// Handle to the LIB for the RTFEDIT control
HANDLE hRTFLib;

// Handles to toolbar control windows
HWND hWndComboFont, hWndComboSize, hWndToolbar;

// used for font callbacks
HDC      hdcGlobal;
PARFONTS parFontsGlobal;
int      iFace,jFont;
int      nFaces;
char     lpCurrentFont[LF_FACESIZE]; // LF_FACESIZE is system-defined
int      PointSize;


/****************************************************************************
*
*    FUNCTION: WinMain(HANDLE, HANDLE, LPSTR, int)
*
*    PURPOSE: calls initialization function, processes message loop
*
****************************************************************************/

int APIENTRY WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow
	)
{

	MSG msg;                       

	// Ensure that common control DLL is loaded
	InitCommonControls();

    // Load the rich edit DLL
    hRTFLib = LoadLibrary("RICHED32.DLL");
 
	if (!InitApplication(hInstance))
		return (FALSE);     

	/* Perform initializations that apply to a specific instance */
	if (!InitInstance(hInstance, nCmdShow))
		return (FALSE);

	/* Acquire and dispatch messages until a WM_QUIT message is received. */
	while (GetMessage(&msg,
		NULL,              
		0,                 
		0))                
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg); 
	}
	return (msg.wParam);  
						 
}

/****************************************************************************
*
*    FUNCTION: InitApplication(HANDLE)
*
*    PURPOSE: Initializes window data and registers window class
*
****************************************************************************/

BOOL InitApplication(HANDLE hInstance)       /* current instance             */
{
	WNDCLASS  wcRichEd;
	
	/* Fill out window class structure with parameters that describe the       */
	/* main window.                                                           */
	wcRichEd.style = 0;                     
	wcRichEd.lpfnWndProc = (WNDPROC)MainWndProc; 
	wcRichEd.cbClsExtra = 0;              
	wcRichEd.cbWndExtra = 0;              
	wcRichEd.hInstance = hInstance;       
	wcRichEd.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(RICHED_ICON));
	wcRichEd.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcRichEd.hbrBackground = GetStockObject(WHITE_BRUSH); 
	wcRichEd.lpszMenuName =  "RichEdMenu";  
	wcRichEd.lpszClassName = "RichEdWClass";

	return (RegisterClass(&wcRichEd));

}

/****************************************************************************
*
*    FUNCTION:  InitInstance(HANDLE, int)
*
*    PURPOSE:  Saves instance handle and creates main window
*
****************************************************************************/
BOOL InitInstance(
	HANDLE          hInstance,
	int             nCmdShow) 
{
	HWND            hWnd;

	hInst = hInstance;

	hWnd = CreateWindow(
		"RichEdWClass",           
		"RichEd Sample", 
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 
        CW_USEDEFAULT, CW_USEDEFAULT,
		NULL,               
		NULL,               
		hInstance,          
		NULL);

	/* If window could not be created, return "failure" */
	if (!hWnd)
		return (FALSE);

	/* Make the window visible; update its client area; and return "success" */
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd); 
	return (TRUE);      

}

/****************************************************************************
*
*    FUNCTION:  ComboWndProcFont(HWND, UINT, WPARAM, LPARAM)
*
*    PURPOSE: This function relays the mouse messages from the combo box
*    showing font facenames for tool tips.
*
****************************************************************************/
LRESULT CALLBACK ComboWndProcFont( HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
  switch (uMessage)
  {
    case WM_MOUSEMOVE:
    case WM_LBUTTONDOWN:
    case WM_LBUTTONUP:
    {
        MSG msg;
        HWND hWndTT;
        msg.lParam = lParam;
        msg.wParam = wParam;
        msg.message = uMessage;
        msg.hwnd = hWnd;
        hWndTT = (HWND)SendMessage(hWndToolbar, TB_GETTOOLTIPS, 0,0);
        SendMessage(hWndTT, TTM_RELAYEVENT, 0, (LPARAM)(LPMSG)&msg);
        break;
    }
  }
  return (CallWindowProc(lpfnDefComboFont, hWnd, uMessage, wParam, lParam));
}

/****************************************************************************
*
*    FUNCTION:  ComboWndProcSize(HWND, UINT, WPARAM, LPARAM)
*
*    PURPOSE: This function relays the mouse messages from the combo box
*    showing font point size for tool tips.
*
****************************************************************************/
LRESULT CALLBACK ComboWndProcSize( HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
  switch (uMessage)
  {
    case WM_MOUSEMOVE:
    case WM_LBUTTONDOWN:
    case WM_LBUTTONUP:
    {
        MSG msg;
        HWND hWndTT;
        msg.lParam = lParam;
        msg.wParam = wParam;
        msg.message = uMessage;
        msg.hwnd = hWnd;
        hWndTT = (HWND)SendMessage(hWndToolbar, TB_GETTOOLTIPS, 0,0);
        SendMessage(hWndTT, TTM_RELAYEVENT, 0, (LPARAM)(LPMSG)&msg);
        break;
    }
  }
  return (CallWindowProc(lpfnDefComboSize, hWnd, uMessage, wParam, lParam));
}

/****************************************************************************
*
*    FUNCTION: MainWndProc(HWND, unsigned, WORD, LONG)
*
*    PURPOSE:  Processes messages for main window
*
****************************************************************************/
LONG APIENTRY MainWndProc(
	HWND hWnd,                /* window handle                   */
	UINT message,             /* type of message                 */
	UINT wParam,              /* additional information          */
	LONG lParam)              /* additional information          */
{
	static HWND hWndRichEdit;        // Handle to rich edit control  
	static CHAR szBuf[128];
	LPTOOLTIPTEXT lpToolTipText;
    static BOOL bBold, bItalic, bUnderLine;
    HDC hDC;
    static EDITSTREAM lpStream;
	static int iSelect;

	switch (message) 
	{
 		case WM_CREATE:
        {
            // Create the toolbar
            hWndToolbar = InitToolbar(hWnd);

            // Create the rich edit control.            
            hWndRichEdit = CreateWindowEx(
                  WS_EX_CLIENTEDGE,    // make rich edit control appear "sunken"
                  "RICHEDIT",          // class name of rich edit control
                  "",                  // text of rich edit control
                  WS_CHILD | WS_VISIBLE | ES_MULTILINE | ES_SAVESEL |
                    WS_HSCROLL | WS_VSCROLL,    // window style
                  0, 0,                // initially create 0 size,
                  0, 0,                // main window's WM_SIZE handler will resize
                  hWnd,                // use main parent
                  (HMENU)ID_RICHED,    // ID 
                  hInst,               // this app instance owns this window
                  NULL  );

            // Enumerate the fonts for the rich edit control
            hDC = GetDC(hWndRichEdit);
            parFontsGlobal = BuildFontList (hDC, &nFaces);

            // Fill out the typeface and point size combo boxes.
            FillCombos();

            // Set the current font.
            ChangeFaceName(hWndRichEdit, parFontsGlobal[0].lf->lfFaceName);
            ChangePointSize(hWndRichEdit, 12);

            // Select the current typeface and point size.
            iSelect = SelectFont(parFontsGlobal[0].lf->lfFaceName, 12);

            // Show the effects of the current font.
            bItalic = bUnderLine = FALSE;
            bBold = ToggleButton(hWnd, IDM_BOLD, FALSE);

            // Release the DC.
            ReleaseDC(hWndRichEdit, hDC);

            // Set the focus for the rich edit control.
            SetFocus(hWndRichEdit);

            // Register to allow drag and drop.
            DragAcceptFiles(hWndRichEdit, TRUE);

            // Tell the rich edit control you want to allow drag and drop.
            SendMessage(hWndRichEdit, EM_SETEVENTMASK, 0, (LPARAM)ENM_DROPFILES);
        }
        break;

		case WM_NOTIFY:
            // Is the notification a tool tip notification?
            if ( ((LPNMHDR) lParam)->code ==TTN_NEEDTEXT)
            {    
                // Display tool tip text.
			    lpToolTipText = (LPTOOLTIPTEXT)lParam;
    			LoadString (hInst, 
	    				lpToolTipText->hdr.idFrom,    // string ID == cmd ID
		    			szBuf,
			    		sizeof(szBuf));
				    	lpToolTipText->lpszText = szBuf;
            }
            // Is the notification a drop notification?
            else if ( ((LPNMHDR) lParam)->code == EN_DROPFILES)
            {   
                WORD cFiles;
                char lpszFile[80];
                HANDLE hDrop;

                // Get the handle to the drop object.
                hDrop =  ((ENDROPFILES *) lParam)->hDrop;
                // Determine how many objects have been dropped.
                cFiles = DragQueryFile(hDrop, 0xFFFF, (LPSTR) NULL, 0);
                // If more than one object has been dropped, don't bother.
                if (cFiles > 1)
                    return 0;
                // Get the name of the file dropped.
                DragQueryFile(hDrop, 0, lpszFile, sizeof(lpszFile));

                // Open the file (text or RTF).
                if (strstr(lpszFile, "TXT"))
                    OpenTheFile(hWndRichEdit, SF_TEXT, lpszFile);
                else if (strstr(lpszFile, "RTF"))
                    OpenTheFile(hWndRichEdit, SF_RTF, lpszFile);

                DragFinish(hDrop); 
                return 1;                 
            }
			return 0L;
			break;

        case WM_SIZE:
        {
            RECT rcl;

            // Tell the toolbar to resize itself to fill the top of the window.
            SendMessage(hWndToolbar, TB_AUTOSIZE, 0L, 0L);
            // Get the size of the toolbar
            GetWindowRect(hWndToolbar, &rcl);
            // Size the rich edit control to fit in the client below the toolbar
            MoveWindow(hWndRichEdit, 0, rcl.bottom - rcl.top, LOWORD(lParam), HIWORD(lParam), TRUE );
        }
        break;

		case WM_COMMAND:

			switch( LOWORD( wParam ))
			{
                case IDM_OPENTXT:
                    if (!OpenTheFile( hWndRichEdit, SF_TEXT, "TEXTDOC.TXT"))
                         MessageBox(hWnd, "File open failed!", NULL, MB_OK);
                    break;

                case IDM_OPENRTF:
                    if (!OpenTheFile( hWndRichEdit, SF_RTF, "RTFDOC.RTF"))
                         MessageBox(hWnd, "File open failed!", NULL, MB_OK);
                    break;

                case IDM_SAVETXT:
                case IDM_SAVERTF:
                    if (!SaveTheFile( hWndRichEdit,LOWORD(wParam)))
                         MessageBox(hWnd, "File open failed!", NULL, MB_OK);
                    break;

                case IDM_PRINT:
                    PrintTheContents(hWndRichEdit);
                    break;

                case IDM_COMBOFONT:
                    if (HIWORD(wParam)==CBN_SELCHANGE)
                    {
                        int iSelect;
                        // Get the currently selected face name
                        iSelect = SendMessage(hWndComboFont, CB_GETCURSEL, 0, 0);
                        ChangeFaceName(hWndRichEdit, parFontsGlobal[iSelect].lf->lfFaceName);
                   }
                    break;

                case IDM_COMBOSIZE:
                    if (HIWORD(wParam)==CBN_SELCHANGE)
                    {
                        // Get the index to the currently selcted point size
                        PointSize = SendMessage(hWndComboSize, CB_GETCURSEL, 0, 0);

                        ChangePointSize(hWndRichEdit, aPoints[PointSize]);
                    }
                    break;

                case IDM_BOLD:
                    BoldCmd(hWndRichEdit);
                    bBold = ToggleButton(hWnd, IDM_BOLD, bBold);
                    break;

                case IDM_ITALIC:
                    ItalicCmd(hWndRichEdit);
                    bItalic = ToggleButton(hWnd, IDM_ITALIC, bItalic);
                    break;

                case IDM_UNDERLINE:
                    UnderLineCmd( hWndRichEdit);
                    bUnderLine = ToggleButton(hWnd, IDM_UNDERLINE, bUnderLine);
					break;

                case IDM_ALIGNLEFT:
                case IDM_ALIGNRIGHT:
                case IDM_ALIGNCENTER:
                    AlignCmd(hWnd, hWndRichEdit, LOWORD( wParam ));
                    break;

				case IDM_EXIT:
					PostQuitMessage(0);
					break;

				case IDM_ABOUT:
					DialogBox(hInst, "AboutBox", hWnd, (DLGPROC)About);
					break;

				default:
					return (DefWindowProc(hWnd, message, wParam, lParam));

			}
			break;

	  
		case WM_DESTROY:                  /* message: window being destroyed */
            if (hWndRichEdit) 
                DestroyWindow(hWndRichEdit);

            if (hWndToolbar)
                DestroyWindow(hWndToolbar);

            if (hWndComboFont)
                DestroyWindow(hWndComboFont);

            if (hWndComboSize)
                DestroyWindow(hWndComboSize);

            if (hRTFLib) 
            {
                FreeLibrary(hRTFLib);
                hRTFLib = NULL;
            }
			PostQuitMessage(0);
			break;

		default:
			return (DefWindowProc(hWnd, message, wParam, lParam));
	}
	return (0);
}

/****************************************************************************
*
*    FUNCTION: InitToolbar(HWND)
*
*    PURPOSE:  Creates the toolbar, combo boxes, and sets up ToolTips
*
****************************************************************************/
HWND InitToolbar(HWND hWndParent)
{
    TOOLINFO lpToolInfo;
    HWND hWndToolbar, hWndTT;
    HFONT hFont;

	// Create the toolbar control
	hWndToolbar = CreateToolbarEx( 
		hWndParent,             // parent
		WS_CHILD | WS_BORDER | WS_VISIBLE | TBSTYLE_TOOLTIPS,   // style
		IDB_TOOLBAR,            // toolbar ID
		6,                      // number of bitmaps
		hInst,                  // mod instance
		IDB_TOOLBAR,            // resource ID for bitmap
		(LPCTBBUTTON)&tbButtons,// address of buttons
		34,                     // number of buttons
		16,16,                  // width & height of buttons
		16,16,                  // width & height of bitmaps
		sizeof(TBBUTTON));      // structure size

	if (hWndToolbar == NULL )
	{
		MessageBox (NULL, "Toolbar not created!", NULL, MB_OK );
		return NULL;
	}

    // Create the combo box for the typeface.
    hWndComboFont = CreateWindowEx ( 0L,   // no extended styles
        "COMBOBOX",                        // class name
        "",                                // default text
        WS_CHILD | WS_BORDER | WS_VISIBLE |
          CBS_HASSTRINGS | CBS_DROPDOWN,   // window styles
        0, 3, 150, 250,                    // size and position
        hWndToolbar,                       // parent window
        (HMENU)IDM_COMBOFONT,              // ID
        hInst,                             // current instance
        NULL );                            // no class data
            
    // Set the window procedure for the combo box.
    lpfnDefComboFont = (WNDPROC)GetWindowLong(hWndComboFont, GWL_WNDPROC);
    SetWindowLong(hWndComboFont, GWL_WNDPROC, (LONG)ComboWndProcFont);

    // Create the combo box for the point size.
    hWndComboSize = CreateWindowEx ( 0L,   // no extended styles
        "COMBOBOX",                        // class name
        "",                                // default text
        WS_CHILD | WS_BORDER | WS_VISIBLE |
            CBS_HASSTRINGS | CBS_DROPDOWN, // window styles
        160, 3, 50, 250,                   // size and position
        hWndToolbar,                       // parent window
        (HMENU)IDM_COMBOSIZE,              // ID
        hInst,                             // current instance
        NULL );                            // no class data
            
    // Set the window procedure for the combo box.
    lpfnDefComboSize = (WNDPROC)GetWindowLong(hWndComboSize, GWL_WNDPROC);
    SetWindowLong(hWndComboSize, GWL_WNDPROC, (LONG)ComboWndProcSize);

    // Get the handle to the ToolTip window.
    hWndTT = (HWND)SendMessage(hWndToolbar, TB_GETTOOLTIPS, 0, 0);

    if (hWndTT)
    {
        // Fill out the TOOLINFO structure.
        lpToolInfo.cbSize = sizeof(lpToolInfo);
        lpToolInfo.uFlags = TTF_IDISHWND | TTF_CENTERTIP;
        lpToolInfo.lpszText = (LPSTR)IDM_COMBOFONT;
        lpToolInfo.hwnd = hWndParent;
        lpToolInfo.uId = (UINT)hWndComboFont;
        lpToolInfo.hinst = hInst;
        // Set up ToolTips for the typeface combo box.
        SendMessage(hWndTT, TTM_ADDTOOL, 0, (LPARAM)(LPTOOLINFO)&lpToolInfo);

        lpToolInfo.lpszText = (LPSTR)IDM_COMBOSIZE;
        lpToolInfo.uId = (UINT)hWndComboSize;
        // Set up ToolTips for the point size combo box.
        SendMessage(hWndTT, TTM_ADDTOOL, 0, (LPARAM)(LPTOOLINFO)&lpToolInfo);
    }
    else
        MessageBox(NULL, "Could not get ToolTip window handle.",NULL, MB_OK);
    
    // Set the fonts for the combo boxes on the toolbar.
    hFont = (HFONT)SendMessage(hWndToolbar, WM_GETFONT, 0, 0);
    SendMessage(hWndComboFont, WM_SETFONT, (WPARAM)hFont, 0);
    SendMessage(hWndComboSize, WM_SETFONT, (WPARAM)hFont, 0);

    return hWndToolbar;
}

/****************************************************************************
*
*    FUNCTION: ChangeFaceName(HWND, LPTSTR)
*
*    PURPOSE:  Changes the facename of the font
*
****************************************************************************/
VOID ChangeFaceName(HWND hWndRichEdit, LPTSTR lpFaceName)
{
    CHARFORMAT cf;

    // Fill out the CHARFORMAT structure to get the character effects.
    cf.cbSize = sizeof(cf);
    cf.dwMask = CFM_ITALIC | CFM_BOLD | CFM_UNDERLINE;
    SendMessage(hWndRichEdit, EM_GETCHARFORMAT, TRUE, (LPARAM)&cf);

    // Include the mask to ask the rich edit control for the current typeface.
    cf.dwMask |= CFM_FACE;

    // Set the new typeface, preserving the previous effects.
    strcpy(cf.szFaceName, lpFaceName);
    SendMessage(hWndRichEdit, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&cf);

}
/****************************************************************************
*
*    FUNCTION: ChangePointSize(HWND, int)
*
*    PURPOSE:  Changes the height of the font
*
****************************************************************************/
VOID ChangePointSize(HWND hWndRichEdit, int PointSize)
{
    CHARFORMAT cf; 

    // Fill out the CHARFORMAT structure to set the point size.
    cf.cbSize = sizeof(cf);
    cf.dwMask = CFM_SIZE;

    // Multiply by 20 to convert to twips.
    cf.yHeight = PointSize * 20;

    // Set the point size.
    SendMessage(hWndRichEdit, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&cf);

	// Reset the dirty bit.
	SendMessage (hWndRichEdit, EM_SETMODIFY, (WPARAM)TRUE, 0L);
}

/****************************************************************************
*
*    FUNCTION: ToggleButton(HWND, int, BOOL)
*
*    PURPOSE:  Toggles the command's button and menu item.
*
****************************************************************************/
BOOL ToggleButton(HWND hWnd, int nID, BOOL bToggle)
{
    if (bToggle)
    {   // Uncheck the menu item and unpress the toolbar button.
        CheckMenuItem(GetMenu(hWnd), nID, MF_BYCOMMAND | MF_UNCHECKED);
        SendMessage( hWndToolbar, TB_CHECKBUTTON, nID, MAKELONG(FALSE, 0));
        return FALSE;
    }
    else
    {   // Check the menu item and press the toolbar button.
        CheckMenuItem(GetMenu(hWnd), nID, MF_BYCOMMAND | MF_CHECKED);
        SendMessage( hWndToolbar, TB_CHECKBUTTON, nID, MAKELONG(TRUE, 0));
        return TRUE;
    }
}
/****************************************************************************
*
*    FUNCTION: BoldCmd(HWND, HWND, BOOL)
*
*    PURPOSE:  Processes the BOLD command
*
****************************************************************************/
void BoldCmd(HWND hWndRichEdit)
{
    CHARFORMAT cf; 

    // Fill out the CHARFORMAT structure to set character effects.
    cf.cbSize = sizeof(cf);
    cf.dwMask = CFM_BOLD;

    // Get the bold status.
    SendMessage(hWndRichEdit, EM_GETCHARFORMAT, TRUE, (LPARAM)&cf);

    // Toggle the bold effect
    cf.dwEffects ^= CFE_BOLD;

    // Set the new bold status.
    SendMessage(hWndRichEdit, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&cf);
}

/****************************************************************************
*
*    FUNCTION: ItalicCmd(HWND)
*
*    PURPOSE:  Processes the Italic command
*
****************************************************************************/
void ItalicCmd( HWND hWndRichEdit )
{
    CHARFORMAT cf; 

    // Fill out the CHARFORMAT structure to get character effects
    cf.cbSize = sizeof(cf);
    cf.dwMask = CFM_ITALIC;

    // Get the italic status.
    SendMessage(hWndRichEdit, EM_GETCHARFORMAT, TRUE, (LPARAM)&cf);

    // Toggle the Italic effect
    cf.dwEffects  ^= CFE_ITALIC;

    // Set the new italic status.
    SendMessage(hWndRichEdit, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&cf);

	// Reset the dirty bit.
	SendMessage (hWndRichEdit, EM_SETMODIFY, (WPARAM)TRUE, 0L);
}

/****************************************************************************
*
*    FUNCTION: UnderLineCmd(HWND)
*
*    PURPOSE:  Processes the Underline command
*
****************************************************************************/
void UnderLineCmd( HWND hWndRichEdit )
{
    CHARFORMAT cf; 

    // Fill out the CHARFORMAT structure with the mask and size 
    cf.cbSize = sizeof(cf);
    cf.dwMask = CFM_UNDERLINE;

    // Get the underline status
    SendMessage(hWndRichEdit, EM_GETCHARFORMAT, TRUE, (LPARAM)&cf);

    // Toggle the effect
    cf.dwEffects  ^= CFE_UNDERLINE;

    // Set the new underline status
    SendMessage(hWndRichEdit, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&cf);

	// Reset the dirty bit.
	SendMessage (hWndRichEdit, EM_SETMODIFY, (WPARAM)TRUE, 0L);
}

/****************************************************************************
*
*    FUNCTION: AlignCmd(HWND, HWND, int)
*
*    PURPOSE:  Processes the alignment commands
*
****************************************************************************/
VOID AlignCmd( HWND hWnd, HWND hWndRichEdit, int iAlign)
{
    PARAFORMAT pf; 

    // Fill out the PARAFORMAT structure with the mask and size .
    pf.cbSize = sizeof(pf);
    pf.dwMask = PFM_ALIGNMENT;

    switch (iAlign)
    {
        case IDM_ALIGNLEFT:
            pf.wAlignment = PFA_LEFT;

            // uncheck right and center.
            CheckMenuItem(GetMenu(hWnd), IDM_ALIGNRIGHT, MF_BYCOMMAND | MF_UNCHECKED);
            SendMessage( hWndToolbar, TB_CHECKBUTTON, IDM_ALIGNRIGHT, MAKELONG(FALSE, 0));
            CheckMenuItem(GetMenu(hWnd), IDM_ALIGNCENTER, MF_BYCOMMAND | MF_UNCHECKED);
            SendMessage( hWndToolbar, TB_CHECKBUTTON, IDM_ALIGNCENTER, MAKELONG(FALSE, 0));

            // check align left
            CheckMenuItem(GetMenu(hWnd), IDM_ALIGNLEFT, MF_BYCOMMAND | MF_CHECKED);
            SendMessage( hWndToolbar, TB_CHECKBUTTON, IDM_ALIGNLEFT, MAKELONG(TRUE, 0));

            break;

        case IDM_ALIGNRIGHT:
            pf.wAlignment = PFA_RIGHT;

            // uncheck left and center.
            CheckMenuItem(GetMenu(hWnd), IDM_ALIGNLEFT, MF_BYCOMMAND | MF_UNCHECKED);
            SendMessage( hWndToolbar, TB_CHECKBUTTON, IDM_ALIGNLEFT, MAKELONG(FALSE, 0));
            CheckMenuItem(GetMenu(hWnd), IDM_ALIGNCENTER, MF_BYCOMMAND | MF_UNCHECKED);
            SendMessage( hWndToolbar, TB_CHECKBUTTON, IDM_ALIGNCENTER, MAKELONG(FALSE, 0));

            // check align right
            CheckMenuItem(GetMenu(hWnd), IDM_ALIGNRIGHT, MF_BYCOMMAND | MF_CHECKED);
            SendMessage( hWndToolbar, TB_CHECKBUTTON, IDM_ALIGNRIGHT, MAKELONG(TRUE, 0));

            break;

        case IDM_ALIGNCENTER:
            pf.wAlignment = PFA_CENTER;

            // uncheck right and left.
            CheckMenuItem(GetMenu(hWnd), IDM_ALIGNRIGHT, MF_BYCOMMAND | MF_UNCHECKED);
            SendMessage( hWndToolbar, TB_CHECKBUTTON, IDM_ALIGNRIGHT, MAKELONG(FALSE, 0));
            CheckMenuItem(GetMenu(hWnd), IDM_ALIGNLEFT, MF_BYCOMMAND | MF_UNCHECKED);
            SendMessage( hWndToolbar, TB_CHECKBUTTON, IDM_ALIGNLEFT, MAKELONG(FALSE, 0));

            // check align center
            CheckMenuItem(GetMenu(hWnd), IDM_ALIGNCENTER, MF_BYCOMMAND | MF_CHECKED);
            SendMessage( hWndToolbar, TB_CHECKBUTTON, IDM_ALIGNCENTER, MAKELONG(TRUE, 0));
            break;
    }

    // Set the new paragraph alignment.
    SendMessage(hWndRichEdit, EM_SETPARAFORMAT, 0, (LPARAM)&pf);

	// Reset the dirty bit.
	SendMessage (hWndRichEdit, EM_SETMODIFY, (WPARAM)TRUE, 0L);
}

/****************************************************************************
*
*    FUNCTION: BuildFontList(HDC, LPINT)
*
*    PURPOSE:  Enumerates all of the TrueType fonts for the current 
*    DC allocating and copying the font information to a parFonts 
*    structure as needed. This function is from TTFONTS in the Win32 SDK.
*
****************************************************************************/
PARFONTS BuildFontList(HDC hdcIn, LPINT retnFaces)
{
  nFaces = 0; // Initialize global face count to 0

  hdcGlobal = hdcIn;    // save HDC for the callbacks

  // Count the number of typefaces. 
  EnumFonts (hdcGlobal, NULL, (FONTENUMPROC)MyEnumCount, (LPARAM)&nFaces);

  // Allocate the pointer to the array of ARFONTS structures. 
  parFontsGlobal = (PARFONTS)LocalAlloc (LPTR, sizeof(ARFONTS) * (nFaces+1));

  // Step through all fonts again.  For each one, fill out a LOGFONT
  // structure and a TEXTMETRIC structure.
  iFace = 0;
  EnumFonts (hdcGlobal, NULL, (FONTENUMPROC)MyEnumFaces, (LPARAM)NULL);

  *retnFaces = nFaces;
  return parFontsGlobal;
}

/****************************************************************************
*
*    FUNCTION: MyEnumFaces(LPLOGFONT, LPTEXTMETRIC, DWORD, LPVOID)
*
*    PURPOSE:  Count the number of fonts for this particular face name.  
*    Allocate the LOGFONT and TEXTMETRIC arrays large enough to hold 
*    all of them.  Then enumerate the fonts once again to fill in these arrays.
*
****************************************************************************/
int APIENTRY MyEnumFaces(
       LPLOGFONT  lpLogFont,
       LPTEXTMETRIC lpTEXTMETRICs,
       DWORD  fFontType,
       LPVOID  lpData)
{
  int nFonts;

  UNREFERENCED_PARAMETER (lpTEXTMETRICs);
  UNREFERENCED_PARAMETER (fFontType);
  UNREFERENCED_PARAMETER (lpData);

  if (fFontType & TRUETYPE_FONTTYPE)
  {  
    nFonts = 0;
    EnumFonts (hdcGlobal, lpLogFont->lfFaceName, (FONTENUMPROC)MyEnumCount, (LPARAM)&nFonts);

    parFontsGlobal[iFace].lf   = (LPLOGFONT)LocalAlloc (LPTR, sizeof(LOGFONT) * nFonts);
    parFontsGlobal[iFace].tm   = (LPTEXTMETRIC)LocalAlloc (LPTR, sizeof(TEXTMETRIC) * nFonts);
    parFontsGlobal[iFace].Type = (LPINT)LocalAlloc (LPTR, sizeof(int) * nFonts);

    if ((parFontsGlobal[iFace].lf   == NULL) ||
      (parFontsGlobal[iFace].tm   == NULL) ||
      (parFontsGlobal[iFace].Type == NULL)) 
    {
        MessageBox (NULL, "alloc failed", NULL , MB_OK);
        return FALSE;
    }

    parFontsGlobal[iFace].nFonts = nFonts;

    jFont = 0;
    EnumFonts (hdcGlobal, lpLogFont->lfFaceName, (FONTENUMPROC)MyEnumCopy, (LPARAM)NULL);

    iFace++;
  }
  return TRUE;
}

/****************************************************************************
*
*    FUNCTION: MyEnumCount(LPLOGFONT, LPTEXTMETRIC, DWORD, LPVOID)
*
*    PURPOSE:  Increment the variable lpData points to to increment the
*    font count.
*
****************************************************************************/
int APIENTRY MyEnumCount(
       LPLOGFONT  lpLogFont,
       LPTEXTMETRIC lpTEXTMETRICs,
       DWORD  fFontType,
       LPINT  lpData)
{
    UNREFERENCED_PARAMETER (lpLogFont);
    UNREFERENCED_PARAMETER (lpTEXTMETRICs);
    UNREFERENCED_PARAMETER (fFontType);

    if (fFontType & TRUETYPE_FONTTYPE)
        (*lpData)++;
    return TRUE;
}

/****************************************************************************
*
*    FUNCTION: MyEnumCopy (LPLOGFONT, LPTEXTMETRIC, DWORD, LPVOID)
*
*    PURPOSE: Each time that this function is called, copy the LOGFONT 
*    and TEXTMETRIC structures into the global arrays. 
*
****************************************************************************/
int APIENTRY MyEnumCopy(
       LPLOGFONT  lpLogFont,
       LPTEXTMETRIC lpTEXTMETRICs,
       DWORD  fFontType,
       LPVOID  lpData)
{
LOGFONT    *lplf;
TEXTMETRIC *lptm;
int        *pType;

  UNREFERENCED_PARAMETER (lpData);
  if (fFontType & TRUETYPE_FONTTYPE)
  {
    lplf  = parFontsGlobal[iFace].lf;
    lptm  = parFontsGlobal[iFace].tm;
    pType = parFontsGlobal[iFace].Type;

    lplf[jFont]  = *lpLogFont;
    lptm[jFont]  = *lpTEXTMETRICs;
    pType[jFont] = fFontType;

    jFont++;
  }
  return TRUE;
}

/****************************************************************************
*
*    FUNCTION: FillCombos(void)
*
*    PURPOSE:  Initializes the facename and point size combo boxes
*    on the toolbar.
*
****************************************************************************/
VOID FillCombos( void )
{
    int idx;
    char szSize[10];

    // Insert the face names into the combo box.
    for (idx=0; idx < nFaces; idx++)
        SendMessage(hWndComboFont, CB_ADDSTRING, 0, 
        (LPARAM) (LPCSTR) parFontsGlobal[idx].lf->lfFaceName );

    // Fill the point size combo box with the list of possible point sizes
    for (idx=0; idx < NUM_POINTS; idx++)
    {
	    wsprintf(szSize, "%d", aPoints[idx]);

        SendMessage(hWndComboSize, CB_ADDSTRING, 0, (LPARAM) (LPCSTR) szSize);
    }

}

/****************************************************************************
*
*    FUNCTION: SelectFont(LPSTR, int)
*
*    PURPOSE:  Select the face name and point size for the current font
*    in the combo boxes on the toolbars. This is done only at initialization.
*       
****************************************************************************/
int SelectFont(LPTSTR lpFaceName, int PtSize)
{
    char szSize[10];
    int iSelect;

    // Select the font face name
    iSelect = SendMessage( hWndComboFont, CB_SELECTSTRING, 0, (LPARAM) (LPCSTR) lpFaceName);

    // Select the current point size
 	wsprintf(szSize, "%d", PtSize);
    SendMessage(hWndComboSize, CB_SELECTSTRING, 0 , (LPARAM) (LPCSTR) szSize);

    return iSelect;
}

/****************************************************************************
*
*    FUNCTION: OpenTheFile(HWND, int, char *)
*
*    PURPOSE:  Opens the given text or rtf file.
*
****************************************************************************/
BOOL OpenTheFile( HWND hWndRichEdit, int iAttrib, char *lpszFileName )
{
    HFILE hFile;
    OFSTRUCT of;
    EDITSTREAM eStream;

    if (hFile = OpenFile(lpszFileName, &of, OF_READ))
    {
        // dwCookie is an app-defined value that holds
        // the handle to the file.
        eStream.dwCookie = hFile;
        eStream.pfnCallback = EditStreamCallback;
        eStream.dwError = 0;
        SendMessage(hWndRichEdit, EM_STREAMIN, (WPARAM)iAttrib,
                        (LPARAM)&eStream);

        // Reset the dirty bit.
     	SendMessage (hWndRichEdit, EM_SETMODIFY, (WPARAM)TRUE, 0L);

        CloseHandle((HANDLE)hFile);
        return TRUE;
    }
    return FALSE;
}

/****************************************************************************
*
*    FUNCTION: EditStreamCallback(DWORD, LPBYTE, LONG, LONG FAR *)
*
*    PURPOSE:  Callback that reads int the stream.
*
****************************************************************************/
DWORD CALLBACK EditStreamCallback(DWORD dwCookie,
    LPBYTE pbBuff, LONG cb, LONG FAR *pcb)
{
    ReadFile((HANDLE)dwCookie, pbBuff, cb, pcb, NULL);
    if (*pcb < cb )
        return 0;   // file has been fully read in
    else
        return ((DWORD)*pcb); // more to read
}

/****************************************************************************
*
*    FUNCTION: SaveTheFile(HWND, int)
*
*    PURPOSE:  Saves the file as text or rtf.
*
****************************************************************************/
BOOL SaveTheFile( HWND hWndRichEdit, int nID )
{
    HFILE hFile;
    OFSTRUCT of;
    EDITSTREAM eStream;
    char *lpszFileName;
    int iAttrib;

    if (nID == IDM_SAVETXT)
    {
        lpszFileName = "TEXTDOC.TXT";
        iAttrib = SF_TEXT;
    }
    else
    {
        lpszFileName = "RTFDOC.RTF";
        iAttrib = SF_RTF;
    }
    if (hFile = OpenFile(lpszFileName, &of, OF_CREATE))
    {
        eStream.dwCookie = hFile;
        eStream.dwError = 0;
        eStream.pfnCallback = SaveCallback;
        SendMessage(hWndRichEdit, EM_STREAMOUT, (WPARAM)iAttrib, (LPARAM)&eStream);
        
        CloseHandle((HANDLE)hFile);
        return TRUE;
    }
    return FALSE;        
}

/****************************************************************************
*
*    FUNCTION: SaveCallback(DWORD, LPBYTE, LONG, LONG FAR *)
*
*    PURPOSE:  Writes the stream out to the file.
*
****************************************************************************/
DWORD CALLBACK SaveCallback(DWORD dwCookie,
    LPBYTE pbBuff, LONG cb, LONG FAR *pcb)
{
    WriteFile((HANDLE)dwCookie, pbBuff, cb, pcb, NULL );
    return 0;
}

/****************************************************************************
*
*    FUNCTION: PrintTheContents(HWND)
*
*    PURPOSE:  Prints the contents of the rich edit control.
*
****************************************************************************/
void PrintTheContents( HWND hWndRichEdit )
{
    FORMATRANGE fr;
    DOCINFO docInfo;
    LONG lTextOut, lTextAmt;
    PRINTDLG pd;

    // Initialize the PRINTDLG structure.
    pd.lStructSize = sizeof(PRINTDLG);
    pd.hwndOwner = hWndRichEdit;
    pd.hDevMode = (HANDLE)NULL;
    pd.hDevNames = (HANDLE)NULL;
    pd.nFromPage = 0;
    pd.nToPage = 0;
    pd.nMinPage = 0;
    pd.nMaxPage = 0;
    pd.nCopies = 0;
    pd.hInstance = (HANDLE)hInst;
    pd.Flags = PD_RETURNDC | PD_NOPAGENUMS | PD_NOSELECTION | PD_PRINTSETUP;
    pd.lpfnSetupHook = (LPSETUPHOOKPROC)(FARPROC)NULL;
    pd.lpSetupTemplateName = (LPTSTR)NULL;
    pd.lpfnPrintHook = (LPPRINTHOOKPROC)(FARPROC)NULL;
    pd.lpPrintTemplateName = (LPTSTR)NULL;

    // Get the printer DC.
    if (PrintDlg(&pd) == TRUE)
    {
        // Fill out the FORMATRANGE structure for the RTF output.
        fr.hdc = fr.hdcTarget = pd.hDC; // HDC
        fr.chrg.cpMin = 0;              // Print
        fr.chrg.cpMax = -1;             // entire contents
        fr.rc.top = fr.rcPage.top = fr.rc.left = fr.rcPage.left = 0;
        fr.rc.right = fr.rcPage.right = GetDeviceCaps(pd.hDC, HORZRES);
        fr.rc.bottom = fr.rcPage.bottom = GetDeviceCaps(pd.hDC, VERTRES );

        // Fill out the DOCINFO structure.
        docInfo.cbSize = sizeof(DOCINFO);
        docInfo.lpszDocName = "(RTF Test)";
        docInfo.lpszOutput = NULL;

        // Be sure that the printer DC is in text mode.
        SetMapMode(pd.hDC, MM_TEXT);

        StartDoc( pd.hDC, &docInfo);
        StartPage( pd.hDC );

        lTextOut = 0;
        lTextAmt = SendMessage( hWndRichEdit, WM_GETTEXTLENGTH, 0, 0);

        while (lTextOut < lTextAmt)
        {
            lTextOut = SendMessage(hWndRichEdit, EM_FORMATRANGE, TRUE, 
                (LPARAM) &fr);
        
            if (lTextOut < lTextAmt)
            {
                EndPage( pd.hDC );
                StartPage( pd.hDC );    
                fr.chrg.cpMin = lTextOut;
                fr.chrg.cpMax = -1;
            }
        }
        // Reset the formatting of the rich edit control.
        SendMessage(hWndRichEdit, EM_FORMATRANGE, TRUE, (LPARAM)NULL);

        // Finish the document.
        EndPage( pd.hDC );
        EndDoc( pd.hDC );

        // Delete the printer DC.
        DeleteDC( pd.hDC );
    }
}

/****************************************************************************
*
*    FUNCTION: About(HWND, UINT, UINT, LONG)
*
*    PURPOSE:  Processes messages for "About" dialog box
*
****************************************************************************/
BOOL APIENTRY About(
	HWND hDlg,
	UINT message,
	UINT wParam,
	LONG lParam)
{
	switch (message)
	{
		case WM_INITDIALOG:
			return (TRUE);

		case WM_COMMAND:              
			if (LOWORD(wParam) == IDOK)
			{
				EndDialog(hDlg, TRUE);
				return (TRUE);
			}
			break;
	}
	return (FALSE);   
}
