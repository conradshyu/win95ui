/****************************************************************************
*
*
*    PROGRAM: shellfun.c
*
*    PURPOSE: Samples that demonstrate the shell library functions
*
****************************************************************************/

#include <windows.h>    // includes basic windows functionality
#include <string.h>
#include <stdio.h>
#include "shellfun.h"
#include "resource.h"

/****************************************************************************
*
*    FUNCTION: WinMain(HANDLE, HANDLE, LPSTR, int)
*
*    PURPOSE: calls initialization function, processes message loop
*
****************************************************************************/
int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,
int nCmdShow)
{

	MSG msg;                       

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
BOOL InitApplication(HANDLE hInstance)       
{
	WNDCLASS  wcShellfun, wcAppBar;
	
	// Fill in window class structure with parameters that describe the
	// main window.                                                      

	wcShellfun.style = 0;                     
	wcShellfun.lpfnWndProc = (WNDPROC)MainWndProc; 
	wcShellfun.cbClsExtra = 0;              
	wcShellfun.cbWndExtra = 0;              
	wcShellfun.hInstance = hInstance;       
	wcShellfun.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(SHELLFUN_ICON));
	wcShellfun.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcShellfun.hbrBackground = GetStockObject(WHITE_BRUSH); 
	wcShellfun.lpszMenuName =  "ShellfunMenu";  
	wcShellfun.lpszClassName = "ShellfunWClass";

	RegisterClass(&wcShellfun);

    // Register the app bar window class
    wcAppBar.style = 0;                     
	wcAppBar.lpfnWndProc = (WNDPROC)AppBarWndProc; 
	wcAppBar.cbClsExtra = 0;              
	wcAppBar.cbWndExtra = 0;              
	wcAppBar.hInstance = hInstance;       
	wcAppBar.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(SHELLFUN_ICON));
	wcAppBar.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcAppBar.hbrBackground = GetSysColorBrush(COLOR_BTNFACE); 
	wcAppBar.lpszMenuName =  NULL;  
	wcAppBar.lpszClassName = "AppBarClass";

	return(RegisterClass(&wcAppBar));

}

/****************************************************************************
*
*    FUNCTION:  InitInstance(HANDLE, int)
*
*    PURPOSE:  Saves instance handle and creates main window
*
****************************************************************************/
BOOL InitInstance(HANDLE  hInstance, int nCmdShow) 
{
    HWND hWnd;

	g_hInst = hInstance;

	hWnd = CreateWindow(
		"ShellfunWClass",           
		"Shellfun Sample", 
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL,               
		NULL,               
		hInstance,          
		NULL);

	/* If window could not be created, return "failure" */
	if (!hWnd)
		return (FALSE);

    // Create the access bar
    g_hWndAppBar = CreateWindowEx(WS_EX_TOOLWINDOW , 
        "AppBarClass", "AppBar",
        WS_POPUP|WS_THICKFRAME | WS_CLIPCHILDREN,
        0,0,DEF_APPBAR_WIDTH, DEF_APPBAR_HEIGHT,
        NULL, NULL, hInstance, NULL);

    // Now create the button children.
	g_hwndBtn1 = CreateWindow( 
		"BUTTON",                           // create button
		"&Right",                           // window title
		BS_PUSHBUTTON | BS_CENTER | WS_VISIBLE | WS_CHILD,
		0,0,0,0,
		g_hWndAppBar,                       // parent window
        (HMENU)IDM_RIGHT,                   // ID
		hInstance,                          // instance
	    NULL );                             

    g_hwndBtn2 = CreateWindow( 
		"BUTTON",                           // create button
		"&Left",                            // window title
		BS_PUSHBUTTON | BS_CENTER | WS_VISIBLE | WS_CHILD,
		0,0,0,0,
		g_hWndAppBar,                       // parent window
        (HMENU)IDM_LEFT,                    // ID
		hInstance,                          // instance
		NULL );
				                             
    g_hwndBtn3 = CreateWindow( 
		"BUTTON",                           // create button
		"&Top",                             // window title
		BS_PUSHBUTTON | BS_CENTER | WS_VISIBLE |WS_CHILD, 
		0,0,0,0,
		g_hWndAppBar,                       // parent window
        (HMENU)IDM_TOP,                     // ID
		hInstance,                          // instance
		NULL ); 
				                            
    g_hwndBtn4 = CreateWindow( 
		"BUTTON",                           // create button
		"&Bottom",                          // window title
		BS_PUSHBUTTON | BS_CENTER | WS_VISIBLE | WS_CHILD,
		0,0,0,0,
		g_hWndAppBar,                         // parent window
        (HMENU)IDM_BOTTOM,                  // ID
		hInstance,                          // instance
		NULL );                             

    // Load Tray icons and tips
    lstrcpyn(g_szState1, "State 1", sizeof(g_szState1));
    lstrcpyn(g_szState2, "State 2", sizeof(g_szState2));
    g_hIconState = LoadIcon(NULL, MAKEINTRESOURCE(IDI_WINLOGO));
    g_State1 = FALSE;

	// Make the window visible; update its client area; and return "success" 
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd); 
	return (TRUE);      
}

/***************************************************************************
*
*    FUNCTION: MainWndProc(HWND, unsigned, WORD, LONG)
*
*    PURPOSE:  Processes messages
*
****************************************************************************/
LONG APIENTRY MainWndProc(
	HWND hWnd,                /* window handle                   */
	UINT message,             /* type of message                 */
	UINT wParam,              /* additional information          */
	LONG lParam)              /* additional information          */
{         
    static HWND hwndEdit;

	switch (message) 
	{

		case WM_CREATE:
	        // Indicate that drag and drop is ok.
	        DragAcceptFiles(hWnd, TRUE);

            hwndEdit = CreateWindow(
                "EDIT",     
				NULL,       
                WS_CHILD | WS_VISIBLE | WS_VSCROLL |
                    ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL,
                0, 0, 0, 0, 
                hWnd,       
                (HMENU) ID_EDITCHILD, 
                (HINSTANCE) GetWindowLong(hWnd, GWL_HINSTANCE),
                NULL);               
            break;

        case WM_SIZE:
            // Make the edit control the size of the window's client area. 
            MoveWindow(hwndEdit, 0, 0, LOWORD(lParam), HIWORD(lParam), TRUE);          
            break;

        case TRAY_CALLBACK:      
            TrayCallback(wParam, lParam);
            break;

		case WM_COMMAND:
			switch( LOWORD( wParam ))
			{
                case IDM_FILEINFO:  
                    OnFileInfo(hWnd, hwndEdit);
                    break;

                case IDM_ADD:
                    if (!g_fRegistered)
                    {
	                    // Fill out the structure needed to register the new access bar.
                        g_appBar.hWnd = g_hWndAppBar;
                        g_appBar.cbSize = sizeof(APPBARDATA);

                        // Identifier for notifications.
                        g_appBar.uCallbackMessage = APPBAR_CALLBACK;

                        // Register the access bar.
                        if (!SHAppBarMessage(ABM_NEW, &g_appBar)) 
                            break;

                        // Set the default size and position of the access bar.
                        AppBarPosChanged(ABE_TOP, &g_appBar);

                        ShowWindow(g_hWndAppBar, SW_SHOW);

                        // Set the registered flag to TRUE.
                        g_fRegistered = TRUE; 
                    }
                    break;

                case IDM_REMOVE:
                    if (g_fRegistered)
                    {
                        // Unregister the access bar.
                        SHAppBarMessage(ABM_REMOVE, &g_appBar);

                        ShowWindow(g_hWndAppBar, SW_HIDE);

                        g_fRegistered = FALSE;
                    }
                    break;

                case IDM_TASKBAR:
                {
                    APPBARDATA abd;
                    char buff[MAX_PATH];
       
                    memset(buff, '\0', sizeof(buff));

                    abd.cbSize = sizeof(APPBARDATA);
                    SHAppBarMessage(ABM_GETTASKBARPOS, &abd);

                    wsprintf(buff, "Left: %d, Right: %d, Top: %d, Bottom: %d",
                        abd.rc.left, abd.rc.right, abd.rc.top, abd.rc.bottom);

                    // Update the multiline edit control.
                    SendMessage(hwndEdit, WM_SETTEXT, 0, (LPARAM) buff);
                    break;
                }
                case IDM_ADDICON:
                    TrayMessage(hWnd, NIM_ADD);
                    break;

                case IDM_STATECHANGE:
                    TrayMessage(hWnd, NIM_MODIFY);
                    break;

                case IDM_REMOVEICON:
                    TrayMessage(hWnd, NIM_DELETE);
                    break;

 				case IDM_EXIT:
                    SendMessage(hWnd, WM_DESTROY, 0L, 0L);;
					break;

				case IDM_ABOUT:
					DialogBox(g_hInst, "AboutBox", hWnd, (DLGPROC)About);
					break;

				default:
					return (DefWindowProc(hWnd, message, wParam, lParam));

			}
			break;

        case WM_DROPFILES:
        {
	        //A file is being dropped
            int iFiles;
            char lpszFile[MAX_PATH];
            HDROP hDropInfo = (HANDLE) wParam;

            // Get the number of files.
            iFiles = DragQueryFile(hDropInfo,  (DWORD)(-1), (LPSTR) NULL, 0);

            if (iFiles != 1)
                MessageBox(hWnd, "One file at a time, please.", NULL, MB_OK);
            else
            {
                HANDLE hFile;
                DWORD dwFileSize, dwBytesRead;
                char *lpBufPtr;

                DragQueryFile(hDropInfo, 0, lpszFile, sizeof(lpszFile));

           		// Open the file.
		        if ((hFile = CreateFile(lpszFile,
			        GENERIC_READ,
			        FILE_SHARE_READ,
			        NULL,
			        OPEN_EXISTING,
			        FILE_ATTRIBUTE_NORMAL,
			        (HANDLE)NULL)) == (HANDLE)(-1))
		        {
	    	        MessageBox( hWnd, "File open failed.", NULL, MB_OK );
	    	        break;
		        }

		        // Get the size of the file.
		        dwFileSize = GetFileSize(hFile, NULL);
		        if (dwFileSize == 0xFFFFFFFF)
		        {
	    	        MessageBox( NULL, "GetFileSize failed!", NULL, MB_OK);
	    	        break;
		        }

		        // Allocate a buffer for to read the file into.
                lpBufPtr = (char *)malloc(dwFileSize);
		        if (lpBufPtr == NULL)
		        {
	    	        MessageBox( NULL, "malloc failed!", NULL, MB_OK);
	    	        CloseHandle( hFile );
	    	        break;
		        }

		        // Read the file contents into the buffer.
		        ReadFile(hFile,(LPVOID)lpBufPtr, dwFileSize, &dwBytesRead, NULL);

        		if (dwBytesRead == 0)
		        {
	    	        MessageBox( hWnd, "Zero bytes read.", NULL, MB_OK );
	    		    break;
		        }

                // Update the multiline edit control with the file contents.
                SendMessage(hwndEdit, WM_SETTEXT, 0, (LPARAM) lpBufPtr);

		        // Close the file.
		        CloseHandle(hFile);

                free(lpBufPtr);
            }

            // Signal that the drag and drop operation is over.
            DragFinish(hDropInfo);	

            break;
        }

		case WM_DESTROY: 
            // Destroy the app bar window
            if (g_fRegistered)
            {
                // Unregister the access bar.
                SHAppBarMessage(ABM_REMOVE, &g_appBar);

                // Destroy the window
                DestroyWindow(g_hWndAppBar);
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
*    FUNCTION: TrayCallback(WPARAM, LPARAM)
*
*    PURPOSE:  Window procedure for the appbar window.
*
****************************************************************************/
void TrayCallback( WPARAM wParam, LPARAM lParam)
{
    UINT uID;
    UINT uMouseMsg;

    uID = (UINT)wParam;
    uMouseMsg = (UINT) lParam;

    if (uMouseMsg == WM_LBUTTONDOWN)
    {
        if (uID == (UINT)IDI_WINLOGO)
            MessageBox(NULL, "Click!", "This sure is fun!", MB_OK);
    }

}

/****************************************************************************
*
*    FUNCTION: AppBarWndProc(HWND)
*
*    PURPOSE:  Window procedure for the appbar window.
*
****************************************************************************/
LRESULT CALLBACK  AppBarWndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    static HWND hwndBtn1, hwndBtn2, hwndBtn3, hwndBtn4;

   	switch (msg)
    {
        case WM_CREATE:
            g_fRegistered = FALSE;
            break;

        case WM_DESTROY:
            DestroyWindow(hwndBtn1);
            DestroyWindow(hwndBtn2);
            DestroyWindow(hwndBtn3);
            DestroyWindow(hwndBtn4);
            break;        

        case WM_WINDOWPOSCHANGED:
        case WM_ACTIVATE:
        {
            APPBARDATA abd;
            abd.cbSize = sizeof(APPBARDATA);
            abd.hWnd = hwnd;
            abd.lParam = (LONG)NULL;
            SHAppBarMessage(ABM_ACTIVATE, &abd);
            break;
        }
            
        case WM_COMMAND:
            if (HIWORD(wparam) == BN_CLICKED)
                AppBarClicked(LOWORD(wparam),(APPBARDATA *)&g_appBar); 
            break;
           
        case APPBAR_CALLBACK:
            AppBarCallback(hwnd, msg, wparam, lparam);
            return 0;

        default:
            return DefWindowProc(hwnd, msg, wparam, lparam);
	}
}

/****************************************************************************
*
*    FUNCTION: AppBarClicked(UINT, APPBARDATA *)
*
*    PURPOSE:  Handles a button click on the app bar.
*
****************************************************************************/
void AppBarClicked(UINT msg,APPBARDATA * pabd)
{
    switch (msg)
    {
        case IDM_LEFT:
	        AppBarPosChanged(ABE_LEFT, pabd);	
            break;

        case IDM_RIGHT:
	        AppBarPosChanged(ABE_RIGHT, pabd);	
            break;

        case IDM_TOP:
	        AppBarPosChanged(ABE_TOP, pabd);	
            break;

        case IDM_BOTTOM:
	        AppBarPosChanged(ABE_BOTTOM, pabd);	
            break;
    }
}

/****************************************************************************
*
*    FUNCTION: TrayMessage(HWND, UINT)
*
*    PURPOSE:  Sends messages to the tray about the tray icon we added.
*
****************************************************************************/
void TrayMessage( HWND hWnd, UINT message)
{
   	NOTIFYICONDATA tnd;

	// Change the state of the small icon in the task bar
    if (g_State1)
    {
       	lstrcpyn(tnd.szTip, g_szState2, sizeof(tnd.szTip));
        g_State1 = FALSE;
    }
    else
    {
    	lstrcpyn(tnd.szTip, g_szState1, sizeof(tnd.szTip));
        g_State1 = TRUE;
    }
    
    switch (message)
    {
        case NIM_ADD:
            tnd.uFlags = NIF_MESSAGE|NIF_ICON|NIF_TIP;
            break;

        case NIM_MODIFY:
            tnd.uFlags = NIF_TIP;
            break;

        case NIM_DELETE:
            tnd.uFlags = 0;
            g_State1 = FALSE;
            break;
    }

    tnd.uID = (UINT)IDI_WINLOGO;
    tnd.cbSize		= sizeof(NOTIFYICONDATA);
    tnd.hWnd		= hWnd;
    tnd.uCallbackMessage = TRAY_CALLBACK;
    tnd.hIcon		= g_hIconState;
    Shell_NotifyIcon(message, &tnd);
}

/****************************************************************************
*
*    FUNCTION: AppBarCallback(HWND, UINT, WPARAM, LPARAM)
*
*    PURPOSE:  Handles appbar notifications.
*
****************************************************************************/
void AppBarCallback(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    UINT uState;

    switch (wParam) 
    {
        case ABN_STATECHANGE:
            // Check to see whether the access bar is still ABS_ALWAYSONTOP.
            uState = SHAppBarMessage(ABM_GETSTATE, &g_appBar);
            
            SetWindowPos(hWnd,
               (ABS_ALWAYSONTOP & uState) ? HWND_TOPMOST : HWND_BOTTOM,
               0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
            break;

        case ABN_FULLSCREENAPP:
            // A full screen application has started, or the last
            // full-screen application has closed. Set the access bar's 
            // z-order appropriately. 
            uState = SHAppBarMessage(ABM_GETSTATE, &g_appBar);

            if (lParam) 
            {
                SetWindowPos(hWnd, 
                   (ABS_ALWAYSONTOP & uState) ? HWND_TOPMOST : HWND_BOTTOM,
                   0, 0, 0, 0, 
                   SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
            } 
            else 
            {
                if (uState & ABS_ALWAYSONTOP) 
                    SetWindowPos(hWnd, HWND_TOPMOST, 
                        0, 0, 0, 0, 
                        SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
            }
        
        case ABN_POSCHANGED:
            // The taskbar or another access bar 
            // has changed its size or position. 
            AppBarPosChanged(g_appBar.uEdge, &g_appBar);
            break;
    }
}

/****************************************************************************
*
*    FUNCTION: AppBarPosChanged(UINT, APPBARDATA *)
*
*    PURPOSE:  Resizes the app bar.
*
****************************************************************************/
void PASCAL AppBarPosChanged(UINT uEdge, APPBARDATA *abd)
{
    RECT rcl;
    
    // Get the screen coordinates.
    rcl.left = rcl.top = 0;
    rcl.right = GetSystemMetrics(SM_CXSCREEN);
    rcl.bottom = GetSystemMetrics(SM_CYSCREEN);
    
    switch (uEdge) 
    {
        case ABE_TOP:
            abd->rc.left = abd->rc.top = 0;
            abd->rc.right = rcl.right;
            abd->rc.bottom = DEF_APPBAR_HEIGHT;
            break;

        case ABE_BOTTOM:
            abd->rc.left = 0;
            abd->rc.top = rcl.bottom - DEF_APPBAR_HEIGHT;
            abd->rc.right = rcl.right;
            abd->rc.bottom = rcl.bottom;
            break;

        case ABE_LEFT:
            abd->rc.left = abd->rc.top = 0;
            abd->rc.right = DEF_APPBAR_WIDTH;
            abd->rc.bottom = rcl.bottom;
            break;

        case ABE_RIGHT:
            abd->rc.top = 0;
            abd->rc.left = rcl.right - DEF_APPBAR_WIDTH;
            abd->rc.right = rcl.right;
            abd->rc.bottom = rcl.bottom;
            break;
    }
    
    // Check to see whether this position is OK.
    SHAppBarMessage( ABM_QUERYPOS, abd);

    switch (uEdge) 
    {
        case ABE_LEFT:
            abd->rc.right = abd->rc.left + DEF_APPBAR_WIDTH;
            break;
        
        case ABE_RIGHT:
            abd->rc.left = abd->rc.right - DEF_APPBAR_WIDTH;
            break;
        
        case ABE_TOP:
            abd->rc.bottom = abd->rc.top + DEF_APPBAR_HEIGHT;
            break;
        
        case ABE_BOTTOM:
            abd->rc.top = abd->rc.bottom - DEF_APPBAR_HEIGHT;
            break;
    }

    // Set the access bar position.
    SHAppBarMessage(ABM_SETPOS, abd);

    // Move and size the access bar so that it conforms to the 
    // bounding rectangle passed to the system.
    MoveWindow(abd->hWnd, abd->rc.left, abd->rc.top, 
        abd->rc.right, abd->rc.bottom, TRUE);

    if ((uEdge == ABE_TOP) || (uEdge == ABE_BOTTOM))
    {
        MoveWindow(g_hwndBtn1, 5, 0, BUTTON_WIDTH, BUTTON_HEIGHT, TRUE);
        MoveWindow(g_hwndBtn2, BUTTON_WIDTH * 2, 0, BUTTON_WIDTH, BUTTON_HEIGHT, TRUE);
        MoveWindow(g_hwndBtn3, BUTTON_WIDTH * 4, 0, BUTTON_WIDTH, BUTTON_HEIGHT, TRUE);
        MoveWindow(g_hwndBtn4, BUTTON_WIDTH * 6, 0, BUTTON_WIDTH, BUTTON_HEIGHT, TRUE);
    }
    else
    {
        MoveWindow(g_hwndBtn1, 2, 5, BUTTON_WIDTH, BUTTON_HEIGHT, TRUE);
        MoveWindow(g_hwndBtn2, 2, BUTTON_HEIGHT * 2, BUTTON_WIDTH, BUTTON_HEIGHT, TRUE);
        MoveWindow(g_hwndBtn3, 2, BUTTON_HEIGHT * 4, BUTTON_WIDTH, BUTTON_HEIGHT, TRUE);
        MoveWindow(g_hwndBtn4, 2, BUTTON_HEIGHT * 6, BUTTON_WIDTH, BUTTON_HEIGHT, TRUE);
    }
}

/****************************************************************************
*
*    FUNCTION: OnFileInfo(HWND, HWND)
*
*    PURPOSE:  Invokes common dialog function to gather file information.
*
****************************************************************************/
void OnFileInfo(HWND hWnd, HWND hwndEdit)
{
    OPENFILENAME OpenFileName;
    char         szDirName[MAX_PATH]   = "";
    char         szFile[MAX_PATH]      = "\0";
    char         szFileTitle[MAX_PATH] = "\0";

    // The filter specification for the OPENFILENAME structure.
    char szFilter[] = {"All Files\0*.*\0"};

   OpenFileName.lStructSize       = sizeof(OPENFILENAME);
   OpenFileName.hwndOwner         = hWnd;
   OpenFileName.hInstance         = (HANDLE) g_hInst;
   OpenFileName.lpstrFilter       = szFilter;
   OpenFileName.lpstrCustomFilter = (LPTSTR) NULL;
   OpenFileName.nMaxCustFilter    = 0L;
   OpenFileName.nFilterIndex      = 1L;
   OpenFileName.lpstrFile         = szFile;
   OpenFileName.nMaxFile          = sizeof(szFile);
   OpenFileName.lpstrFileTitle    = szFileTitle;
   OpenFileName.nMaxFileTitle     = sizeof(szFileTitle);
   OpenFileName.lpstrInitialDir   = NULL;
   OpenFileName.lpstrTitle        = "Pick a file for information.";
   OpenFileName.nFileOffset       = 0;
   OpenFileName.nFileExtension    = 0;
   OpenFileName.lpstrDefExt       = "*.*";
   OpenFileName.lCustData         = 0;
   OpenFileName.Flags = OFN_PATHMUSTEXIST |
                OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;

   if (GetOpenFileName(&OpenFileName))
   {
        SHFILEINFO sfi; 
        char buff[2056];

        // The user chose to get the file information: display name,
        // type name, file attributes, icon location, and executable type.
        if (SHGetFileInfo(OpenFileName.lpstrFile, 0, &sfi, 
                       sizeof(SHFILEINFO), SHGFI_DISPLAYNAME | SHGFI_TYPENAME ))
        {
            memset(buff, '\0', sizeof(buff));

            // Display the information.
            wsprintf(buff, "Display name: %s    Type Name: %s",
                             sfi.szDisplayName, sfi.szTypeName);
                    
            // Update the multiline edit control with the file description.
            SendMessage(hwndEdit, WM_SETTEXT, 0, (LPARAM) buff);
        }
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


