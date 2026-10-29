
/****************************************************************************
*
*
*    PROGRAM: cmndlg.c
*
*    PURPOSE: Sample demonstrating common dialogs in Windows Chicago
*
*    FUNCTIONS:
*
*        WinMain() - calls initialization function, processes message loop
*        InitApplication() - initializes window data and registers window
*        InitInstance() - saves instance handle and creates main window
*        MainWndProc() - processes messages
*        About() - processes messages for "About" dialog box
*        OpenNewFile() - opens a new file
*        SaveToFile() - saves the current text buffer to the current filename
*        SaveAs() - saves the current text buffer to a new file name
*        EnterNew() - to enter new text into the text buffer
*        FileOpenHookProc() - Hook procedure for GetOpenFileName() common dialog
*        FileSaveHookProc() - Hook procedure for GetSaveFileName() common dialog
*        ChooseFontHookProc() - Hook procedure for ChooseFont() common dialog
*        FindTextHookProc() - Hook procedure for FindText() common dialog
*        ReplaceTextHookProc() - Hook procedure for the ReplaceText() common dialog
*        PrintDlgHookProc() - Hook procedure for the PrintDlg() common dialog
*        PrintSetupHookProc() - Hook procedure for the PrintDlg() setup common dialog
*        SearchFile() - Searches for the specified text in the file buffer
*        ChooseNewFont() - chooses a new font for display
*        ChooseNewColor() - chooses a new color for display
*        PrintFile() - prints the current text in the file buffer
*        CallFindText() - calls the FindText() common dialog function
*        CallReplaceText() - calls the ReplaceText() common dialog function
*        ProcessCDError() - uses CommonDialogExtendedError() to output useful error messages
*
*    COMMENTS:
*
*
*        The common dialog APIs demonstrated in the sample include:
*
*            ChooseColor()
*            ChooseFont()
*            FindText()
*            GetOpenFileName()
*            GetSaveFileName()
*            PrintDlg()
*            ReplaceText()
*
*
*        Each dialog box is demonstrated being used in three different ways:
*        standard, using a modified template and using a hook function.
*
*
****************************************************************************/

#include <windows.h>    // includes basic windows functionality
#include <commdlg.h>    // includes common dialog functionality
#include <dlgs.h>       // includes common dialog template defines
#include <stdio.h>      // includes standard file i/o functionality
#include <string.h>     // includes string functions
#include <cderr.h>      // includes the common dialog error codes
#include <commctrl.h>
#include "resource.h"
#include "cmndlg32.h"     // includes my common dialog functions

HANDLE       hInst;
OPENFILENAME OpenFileName;
char         szDirName[MAX_PATH]   = "";
char         szFile[MAX_PATH]      = "\0";
char         szFileTitle[MAX_PATH];

// Filter specification for the OPENFILENAME struct
// This is portable for i386 and MIPS
// Leaving out the \0 terminator will cause improper DWORD alignment
// and cause a failure under MIPS
char szFilter[] = "Text Files (*.TXT)\0*.TXT\0All Files (*.*)\0*.*\0";
                                            
char         FileBuf[FILE_LEN];
DWORD        dwFileSize;
UINT         FindReplaceMsg;
char         szFindString[MAX_PATH]   = "";
char         szReplaceString[MAX_PATH]  = "";
FINDREPLACE  frText;
LPFINDREPLACE lpFR;
char *       lpBufPtr = FileBuf;
CHOOSEFONT   chf;
CHOOSECOLOR  chsclr;
COLORREF     crColor;
LOGFONT      lf;
WORD         wMode = IDM_STANDARD;
HWND         hDlgFR = NULL;
PRINTDLG     pd;
PAGESETUPDLG psDlg;
BOOL		 bNewShell;
HWND 		 hWndStatus;		// handle for status bar window

/****************************************************************************
*
*    FUNCTION: WinMain(HANDLE, HANDLE, LPSTR, int)
*
*    PURPOSE: calls initialization function, processes message loop
*
*    COMMENTS:
*
*
****************************************************************************/

int APIENTRY WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow
    )
{

	DWORD dwVersion;
    MSG msg;                         /* message                      */

	dwVersion = GetVersion();
	if (dwVersion < 0x80000000)
		bNewShell = FALSE;
	else
		bNewShell = TRUE;

    if (!InitApplication(hInstance)) /* Initialize shared things */
            return (FALSE);              /* Exits if unable to initialize     */

    hInst = hInstance;
    lpBufPtr = &FileBuf[0];

	InitCommonControls();

    /* Perform initializations that apply to a specific instance */

    if (!InitInstance(hInstance, nCmdShow))
        return (FALSE);

    // register window message for FindText() and ReplaceText() hook procs
    FindReplaceMsg = RegisterWindowMessage( (LPTSTR) FINDMSGSTRING );

    /* Acquire and dispatch messages until a WM_QUIT message is received. */

    while (GetMessage(&msg,NULL,0,0))
        if ( !hDlgFR || !IsWindow(hDlgFR) || !IsDialogMessage( hDlgFR, &msg ) )
        {
            TranslateMessage(&msg);    /* Translates virtual key codes */
            DispatchMessage(&msg);     /* Dispatches message to window */
        }
    return (msg.wParam);           /* Returns the value from PostQuitMessage */
}


/****************************************************************************
*
*    FUNCTION: InitApplication(HANDLE)
*
*    PURPOSE: Initializes window data and registers window class
*
*    COMMENTS:
*
*        In this function, we initialize a window class by filling out a data
*        structure of type WNDCLASS and calling the Windows RegisterClass()
*        function.
*
****************************************************************************/

BOOL InitApplication(HANDLE hInstance)       /* current instance             */
{
    WNDCLASS  wc;

    /* Fill in window class structure with parameters that describe the       */
    /* main window.                                                           */

    wc.style = 0;                       /* Class style(s).                    */
    wc.lpfnWndProc = (WNDPROC)MainWndProc;
    wc.cbClsExtra = 0;                  /* No per-class extra data.           */
    wc.cbWndExtra = 0;                  /* No per-window extra data.          */
    wc.hInstance = hInstance;           /* Application that owns the class.   */
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = GetStockObject(WHITE_BRUSH); 
    wc.lpszMenuName =  "CmnDlgMenu";   /* Name of menu resource in .RC file. */
    wc.lpszClassName = "CmnDlgWClass"; /* Name used in call to CreateWindow. */

    /* Register the window class and return success/failure code. */

    return (RegisterClass(&wc));

}


/****************************************************************************
*
*    FUNCTION:  InitInstance(HANDLE, int)
*
*    PURPOSE:  Saves instance handle and creates main window
*
*    COMMENTS:
*
*        In this function, we save the instance handle in a static variable and
*        create and display the main program window.
*
****************************************************************************/

BOOL InitInstance(
    HANDLE          hInstance,          /* Current instance identifier.       */
    int             nCmdShow)           /* Param for first ShowWindow() call. */
{
    HWND            hWnd;               /* Main window handle.                */

    /* Save the instance handle in static variable, which will be used in  */
    /* many subsequence calls from this application to Windows.            */

    hInst = hInstance;

    /* Create a main window for this application instance.  */

    hWnd = CreateWindow(
        "CmnDlgWClass",
        "Common Dialogs Sample",
        WS_OVERLAPPEDWINDOW,            /* Window style.                      */
        CW_USEDEFAULT,                  /* Default horizontal position.       */
        CW_USEDEFAULT,                  /* Default vertical position.         */
        CW_USEDEFAULT,                  /* Default width.                     */
        CW_USEDEFAULT,                  /* Default height.                    */
        NULL,                           /* Overlapped windows have no parent. */
        NULL,                           /* Use the window class menu.         */
        hInstance,                      /* This instance owns this window.    */
        NULL                            /* Pointer not needed.                */
    );

    /* If window could not be created, return "failure" */

    if (!hWnd)
        return (FALSE);

    /* Make the window visible; update its client area; and return "success" */

    ShowWindow(hWnd, nCmdShow);  /* Show the window                        */
    UpdateWindow(hWnd);          /* Sends WM_PAINT message                 */
    return (TRUE);               /* Returns the value from PostQuitMessage */

}

/****************************************************************************
*
*    FUNCTION: MainWndProc(HWND, unsigned, WORD, LONG)
*
*    PURPOSE:  Processes messages
*
*    COMMENTS:
*
*        This function processes all messags sent to the window.  When the
*        user choses one of the options from one of the menus, the command
*        is processed here and passed onto the function for that command.
*        This function also processes the special "FindReplace" message that
*        this application registers for hook processing of the FindText()
*        and ReplaceText() common dialog functions.
*
****************************************************************************/

LONG APIENTRY MainWndProc(
        HWND hWnd,                // window handle                   
        UINT message,             // type of message                 
        UINT wParam,              // additional information          
        LONG lParam)              // additional information          
{
    HDC hDC;
    PAINTSTRUCT ps;
    INT nDrawX;
    INT nDrawY;
    HFONT hFont;
    HANDLE Handle;
    static BOOL NewFont;
    RECT rcl;

    switch (message) {


        case WM_CREATE:
            //initialize the output on the screen
            lstrcpy( FileBuf, "Hello World!");
            lpBufPtr = FileBuf;
            dwFileSize = lstrlen(FileBuf);
            crColor = 0;
            NewFont = FALSE;
			hWndStatus = CreateWindowEx( 
				0L,                                 // extended style
				STATUSCLASSNAME,                    // create a status bar
				"",                                 // Window name
				WS_CHILD | WS_BORDER | WS_VISIBLE | SBS_SIZEGRIP,  // window styles
				-100, -100, 10, 10,                 // x, y, Width, Height
				hWnd,                               // parent window
				(HMENU)10,                          // ID
				hInst,                              // instance
				NULL );                             // window data

			if (hWndStatus == NULL)
				MessageBox (NULL, "Status Bar not created!", NULL, MB_OK );

			if (bNewShell)
			{
                EnableMenuItem( GetMenu( hWnd ), IDM_PAGESETUP,
                            MF_BYCOMMAND | MF_ENABLED );
                DrawMenuBar( hWnd );
			}
            break;


        case WM_SIZE:
            // resize the status bar so that it fits along the bottom of the client
            MoveWindow(hWndStatus, 0, HIWORD(lParam) - 10, LOWORD(lParam),
                HIWORD(lParam), TRUE);
            break;

        case WM_PAINT:
            /* Set up a display context to begin painting */
            hDC = BeginPaint (hWnd, &ps);

            GetClientRect(hWnd, &rcl);
            FillRect( hDC, &rcl, GetStockObject(WHITE_BRUSH));

            /* Initialize drawing position to 1/4 inch from the top  */
            /* and from the left of the top, left corner of the      */
            /* client area of the main windows.                      */
            nDrawX = GetDeviceCaps(hDC, LOGPIXELSX) / 4;   /* 1/4 inch */
            nDrawY = GetDeviceCaps(hDC, LOGPIXELSY) / 4;   /* 1/4 inch */

            if ( NewFont == TRUE )
            {
                hFont = CreateFontIndirect( &lf );
                Handle = SelectObject( hDC, hFont );
            }

            SetTextColor( hDC, crColor );
            TextOut (hDC, nDrawX, nDrawY, FileBuf, dwFileSize);


            // end painting and release hDC
            EndPaint( hWnd, &ps );
            break;


        case WM_COMMAND:           /* message: command from application menu */

            switch( LOWORD( wParam ))
            {
                case IDM_OPENFILE:
                    if ( OpenNewFile( hWnd ) == TRUE )
                    {
                        // enable the Save As and Print menu items
                        EnableMenuItem( GetMenu( hWnd ), IDM_SAVEFILE,
                            MF_BYCOMMAND | MF_ENABLED );
                        EnableMenuItem( GetMenu( hWnd ), IDM_PRINT,
                            MF_BYCOMMAND | MF_ENABLED );
                        DrawMenuBar( hWnd);
                        // reset the title in the title bar to reflect the
                        // new open file
                        SetWindowText( hWnd, OpenFileName.lpstrFile );
                        // reset the current color and current font to the
                        // default
                        crColor = 0;
                        NewFont = FALSE;
                        InvalidateRect( hWnd, NULL, TRUE );
                    }
                    break;

                case IDM_SAVEFILE:
                    OpenFileName.Flags = 0L;
                    SaveToFile( hWnd );
                    break;

                case IDM_SAVEFILEAS:
                    if ( SaveAs( hWnd ) == TRUE )
                    {
                        EnableMenuItem( GetMenu( hWnd ), IDM_SAVEFILE,
                            MF_BYCOMMAND | MF_ENABLED );
                        SetWindowText( hWnd, OpenFileName.lpstrFile );
                        DrawMenuBar( hWnd );
                    }
                    break;

                case IDM_EXIT:
                    PostQuitMessage(0);
                    break;

                case IDM_PRINT:
                    PrintFile( hWnd );
                    break;

				case IDM_PAGESETUP:
					PageSetup(hWnd);
					break;

                case IDM_CHOOSECOLOR:
                    if (ChooseNewColor( hWnd ))
                        InvalidateRect( hWnd, NULL, TRUE );
                    break;

                case IDM_CHOOSEFONT:
                    if (NewFont = ChooseNewFont( hWnd ))
                        InvalidateRect( hWnd, NULL, TRUE );

                    break;

                case IDM_FINDTEXT:
                    CallFindText( hWnd );
                    break;

                case IDM_REPLACETEXT:
                    CallReplaceText( hWnd );
                    break;

                case IDM_STANDARD:
                    // uncheck previous selection
                    CheckMenuItem( GetMenu( hWnd ), wMode, MF_UNCHECKED | MF_BYCOMMAND);
                    //reset mode
                    wMode = LOWORD(wParam);
                    //check new selection
                    CheckMenuItem( GetMenu( hWnd ), wMode, MF_CHECKED | MF_BYCOMMAND);
                    DrawMenuBar( hWnd);
                    break;

                case IDM_HOOK:
                case IDM_CUSTOM:
                     // uncheck previous selection
                    CheckMenuItem( GetMenu( hWnd ), wMode, MF_UNCHECKED | MF_BYCOMMAND);
                    //reset mode
                    wMode = LOWORD(wParam);
                    //check new selection
                    CheckMenuItem( GetMenu( hWnd ), wMode, MF_CHECKED | MF_BYCOMMAND);
                    DrawMenuBar( hWnd);
                    break;

                case IDM_ENTERNEW:

                    if (DialogBox(hInst,
                        "EnterNewBox",
                        hWnd,    
                        (DLGPROC)EnterNew) == TRUE)

                        InvalidateRect( hWnd, NULL, TRUE );

                    break;

                case IDM_ABOUT:
                    DialogBox(hInst,
                        "AboutBox",
                        hWnd,           
                        (DLGPROC)About);
                    break;

                default:
                    return (DefWindowProc(hWnd, message, wParam, lParam));

            }
            break;

        case WM_DESTROY:                  /* message: window being destroyed */
            PostQuitMessage(0);
            break;


        default:
            // Handle the special find-replace message (FindReplaceMsg) that
            // was registered at initialization time.
            if ( message == FindReplaceMsg )
            {
                if ( lpFR = (LPFINDREPLACE) lParam )
                    {
                    if (lpFR->Flags & FR_DIALOGTERM )  // terminating dialog
                        return 0;
                    SearchFile( lpFR );
                    InvalidateRect( hWnd, NULL, TRUE );
                    }
                return 0;
            }

            return (DefWindowProc(hWnd, message, wParam, lParam));
    }
    return (0);
}


/****************************************************************************
*
*    FUNCTION: EnterNew(HWND, UINT, UINT, LONG)
*
*    PURPOSE:  Processes messages for "EnterNew" dialog box
*
*    COMMENTS:
*
*        This function allows the user to enter new text in the current
*        window.  This text is stored in the global current buffer.
*
****************************************************************************/

BOOL APIENTRY EnterNew(
        HWND hDlg,                /* window handle of the dialog box */
        UINT message,             /* type of message                 */
        UINT wParam,            /* message-specific information    */
        LONG lParam)
{
    char Buf[FILE_LEN-1];

    switch (message)
    {
        case WM_INITDIALOG:                /* message: initialize dialog box */
            return (TRUE);

        case WM_COMMAND:                      /* message: received a command */
            if (LOWORD(wParam) == IDOK)
            {
                GetDlgItemText( hDlg, IDEDIT, Buf, FILE_LEN-1);
                dwFileSize = lstrlen(Buf);
                lstrcpyn( FileBuf, Buf, FILE_LEN-1);
                lpBufPtr = FileBuf;
                EndDialog( hDlg, TRUE );
                return (TRUE);
            }
            else if (LOWORD(wParam) == IDCANCEL)
            {   /* System menu close command? */
                EndDialog(hDlg, FALSE);       /* Exits the dialog box        */
                return (TRUE);
            }
            break;
    }
    return (FALSE);                           /* Didn't process a message    */
}


/****************************************************************************
*
*    FUNCTION: About(HWND, UINT, UINT, LONG)
*
*    PURPOSE:  Processes messages for "About" dialog box
*
*    COMMENTS:
*
*       No initialization is needed for this particular dialog box, but TRUE
*       must be returned to Windows.
*
*       Wait for user to click on "Ok" button, then close the dialog box.
*
****************************************************************************/

BOOL APIENTRY About(
        HWND hDlg,                /* window handle of the dialog box */
        UINT message,             /* type of message                 */
        UINT wParam,            /* message-specific information    */
        LONG lParam)
{
    switch (message)
    {
        case WM_INITDIALOG:                /* message: initialize dialog box */
            return (TRUE);

        case WM_COMMAND:                      /* message: received a command */
            if (LOWORD(wParam) == IDOK          /* "OK" box selected?        */
                || LOWORD(wParam) == IDCANCEL) {        /* System menu close command? */
                EndDialog(hDlg, TRUE);        /* Exits the dialog box        */
                return (TRUE);
            }
            break;
    }
    return (FALSE);                           /* Didn't process a message    */
}

/****************************************************************************
*
*    FUNCTION: FileOpenNotify( HWND hDlg, LPOFNOTIFY pofn)
*
*    PURPOSE: This function processes the WM_NOTIFY message that is sent
*		to the hook dialog procedure for the File Open common dialog.
*
*    COMMENTS:
*
*
****************************************************************************/
BOOL NEAR PASCAL FileOpenNotify(HWND hDlg, LPOFNOTIFY pofn)
{
	static char lpszNotification[FILE_LEN];
	HANDLE hFile;
    char szTempText[MAX_PATH];
    char szString[MAX_PATH];
    DWORD dwBytesWritten;

	switch (pofn->hdr.code)
	{
		// The current selection has changed. 
		case CDN_SELCHANGE:
		{
			char szFile[MAX_PATH];

			// Get the file specification from the common dialog box.
			CommDlg_OpenSave_GetSpec(GetParent(hDlg),
				szFile, sizeof(szFile));
			wsprintf(lpszNotification, "File Open Notification: %s. File: %s",
				"CDN_SELCHANGE", szFile);
		}
		break;

		// The current folder has changed.
		case CDN_FOLDERCHANGE:
		{
			char szFile[MAX_PATH];

			if (CommDlg_OpenSave_GetFolderPath(GetParent(hDlg),
				szFile, sizeof(szFile)) <= sizeof(szFile))
			{
				wsprintf(lpszNotification, "File Open Notification: %s. File: %s",
					"CDN_FOLDERCHANGE", szFile);
			}
		}
		break;

		// The Help button has been clicked.
		case CDN_HELP:
			wsprintf(lpszNotification, "File Open Notification: %s.",
				"CDN_HELP");
			break;

		// The OK button has been clicked.
		// To prevent the common dialog boc from closing, the result should
		// be nonzero via a call to SetWindowLong (hDlg, DWL_MSGRESULT,
		// lResult).
		case CDN_FILEOK:
			SetWindowLong(hDlg, DWL_MSGRESULT, 1L);
			wsprintf(lpszNotification, "File Open Notification: %s. File: %s",
				"CDN_FILEOK", pofn->lpOFN->lpstrFile);
             GetDlgItemText( hDlg, edt1, szTempText, sizeof( szTempText ) - 1);
             sprintf( szString, "Are you sure you want to open %s?", szTempText);
              if ( MessageBox( hDlg, szString, "Information", MB_YESNO ) == IDNO )
			  {
			           SetWindowLong(hDlg, DWL_MSGRESULT, -1);
                        break;
			  }

              // Check to see whether the Create File box is checked.
              if ( (BOOL)(SendMessage( GetDlgItem(hDlg, chx2),
                    BM_GETCHECK, 0, 0L )) == TRUE )
              {
                    // If so, create the file.
                    if ((hFile = CreateFile( szTempText,
                        GENERIC_READ | GENERIC_WRITE,
                        FILE_SHARE_READ | FILE_SHARE_WRITE,
                        NULL,
                        CREATE_ALWAYS,
                        FILE_ATTRIBUTE_NORMAL,
                        (HANDLE)NULL)) == (HANDLE)(-1))
                    {
                        MessageBox( hDlg, 
                            "Directory could not be created.",
                            NULL,
                            MB_OK );
						SetWindowLong(hDlg, DWL_MSGRESULT, -1);
                        break;
                    }

                    if (WriteFile( hFile, (LPTSTR)FileBuf, dwFileSize, 
                     &dwBytesWritten, NULL) == FALSE)
                        MessageBox( hDlg, "Error writing file.", NULL, MB_OK );
                                                   
                   if (hFile)
                   		CloseHandle(hFile);   // close the file
            }
			break;

		// Received a sharing violation
		case CDN_SHAREVIOLATION:
			wsprintf(lpszNotification, "File Open Notification: %s.",
				"CDN_SHAREVIOLATION");
			break;

		// Received when initialization has finished via the WM_INITDIALOG
		// message; all controls moved at this point
		case CDN_INITDONE:
			wsprintf(lpszNotification, "File Open Notification: %s.",
				"CDN_INITDONE");
			break;

		// Received when the file type changes in the Files of Type box
		case CDN_TYPECHANGE:
			wsprintf(lpszNotification, "File Open Notification: %s.",
				"CDN_TYPECHANGE");
			break;
	}

	// Write the notification to the status window.
	SendMessage(hWndStatus, SB_SETTEXT, 0, (LPARAM)lpszNotification);

	return TRUE;
}

/****************************************************************************
*
*    FUNCTION: FileOpenHookProc(HWND, UINT, UINT, LONG)
*
*    PURPOSE:  Processes messages for GetFileNameOpen() common dialog box
*
*    COMMENTS:
*
*        This function will prompt the user if they are sure they want
*        to open the file if the OFN_ENABLEHOOK flag is set.
*
*        If the current option mode is CUSTOM, the user is allowed to check
*        a box in the dialog prompting them whether or not they would like
*        the file created.  If they check this box, the file is created and
*        the string 'Empty' is written to it.
*
*    RETURN VALUES:
*        TRUE - User chose 'Yes' from the "Are you sure message box".
*        FALSE - User chose 'No'; return to the dialog box.
*
****************************************************************************/

BOOL APIENTRY FileOpenHookProc (HWND hDlg, UINT message, UINT wParam,
   LONG lParam)
{

    if  (message == WM_NOTIFY)
			return FileOpenNotify(hDlg, (LPOFNOTIFY)lParam);

    return FALSE;
}

/****************************************************************************
*
*    FUNCTION: OpenNewFile(HWND)
*
*    PURPOSE:  Invokes common dialog function to open a file and opens it.
*
*    COMMENTS:
*
*        This function initializes the OPENFILENAME structure and calls
*        the GetOpenFileName() common dialog function.  This function will
*        work regardless of the mode: standard, using a hook or using a
*        customized template.
*
*    RETURN VALUES:
*        TRUE - The file was opened successfully and read into the buffer.
*        FALSE - No files were opened.
*
****************************************************************************/
BOOL OpenNewFile( HWND hWnd )
{
   HANDLE hFile;
   DWORD dwBytesRead;

   lstrcpy( szFile, "");
   lstrcpy( szFileTitle, "");

   OpenFileName.lStructSize       = sizeof(OPENFILENAME);
   OpenFileName.hwndOwner         = hWnd;
   OpenFileName.hInstance         = (HANDLE) hInst;
   OpenFileName.lpstrFilter       = szFilter;
   OpenFileName.lpstrCustomFilter = (LPTSTR) NULL;
   OpenFileName.nMaxCustFilter    = 0L;
   OpenFileName.nFilterIndex      = 1L;
   OpenFileName.lpstrFile         = szFile;
   OpenFileName.nMaxFile          = sizeof(szFile);
   OpenFileName.lpstrFileTitle    = szFileTitle;
   OpenFileName.nMaxFileTitle     = sizeof(szFileTitle);
   OpenFileName.lpstrInitialDir   = NULL;
   OpenFileName.lpstrTitle        = "Open";
   OpenFileName.nFileOffset       = 0;
   OpenFileName.nFileExtension    = 0;
   OpenFileName.lpstrDefExt       = "*.txt";
   OpenFileName.lCustData         = 0;

   switch( wMode )
   {
        case IDM_STANDARD:
            OpenFileName.Flags = OFN_SHOWHELP | OFN_PATHMUSTEXIST |
                OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
            break;

        case IDM_HOOK:
            OpenFileName.Flags = OFN_SHOWHELP | OFN_PATHMUSTEXIST |	OFN_EXPLORER |
                OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_ENABLEHOOK;
            OpenFileName.lpfnHook = (LPOFNHOOKPROC)FileOpenHookProc;
            break;

        case IDM_CUSTOM:
            OpenFileName.Flags = OFN_SHOWHELP | OFN_ENABLEHOOK |
                OFN_HIDEREADONLY | OFN_ENABLETEMPLATE;
            OpenFileName.lpfnHook = (LPOFNHOOKPROC)FileOpenHookProc;
			if (bNewShell)
			{
				OpenFileName.Flags |= OFN_EXPLORER;
            	OpenFileName.lpTemplateName = (LPTSTR)MAKEINTRESOURCE(IDD_OPENSAVE);
			}
			else
            	OpenFileName.lpTemplateName = (LPTSTR)MAKEINTRESOURCE(FILEOPENORD);
            break;
   }

   if (GetOpenFileName(&OpenFileName))
   {
      // Open the file.
      if ((hFile = CreateFile((LPCTSTR)OpenFileName.lpstrFile,
                        GENERIC_READ,
                        FILE_SHARE_READ,
                        NULL,
                        OPEN_EXISTING,
                        FILE_ATTRIBUTE_NORMAL,
                        (HANDLE)NULL)) == (HANDLE)-1)
      {
         MessageBox( hWnd, "File open failed.", NULL, MB_OK );
         return FALSE;
      }

      // Read its contents into a buffer.
      ReadFile(hFile,(LPVOID)FileBuf, FILE_LEN, &dwBytesRead, NULL);
      lpBufPtr = FileBuf;

      if (dwBytesRead == 0)
      {
         MessageBox( hWnd, "Zero bytes read.", NULL, MB_OK );
         return FALSE;
      }

      // close the file
      CloseHandle(hFile);

      dwFileSize = dwBytesRead / 2;
    }
    else
    {
      // Send the error to your error handler.
      ProcessCDError(CommDlgExtendedError(), hWnd );
      return FALSE;
    }
    return TRUE;
}

/****************************************************************************
*
*    FUNCTION: SaveToFile( HWND )
*
*    PURPOSE:  Saves the current buffer to the current file.
*
*    COMMENTS:
*
*        This function will save the current text buffer into the file
*        specified from the GetSaveFileName() common dialog function.
*
*    RETURN VALUES:
*        TRUE - The file was saved successfully.
*        FALSE - The buffer was not saved to a file.
*
****************************************************************************/
BOOL SaveToFile( HWND hWnd )
{
   HANDLE hFile;
   DWORD dwOpen, dwBytesWritten;
   char buf[MAX_PATH];

   dwOpen = CREATE_ALWAYS;

   // open the file
   if ((hFile = CreateFile((LPCTSTR)OpenFileName.lpstrFile,
                        GENERIC_WRITE,
                        FILE_SHARE_WRITE,
                        NULL,
                        dwOpen,
                        FILE_ATTRIBUTE_NORMAL,
                        (HANDLE)NULL)) == (HANDLE)-1)

   {                      
      sprintf( buf, "Could not create file %s", OpenFileName.lpstrFile );
      MessageBox( hWnd, buf, NULL, MB_OK );
      return FALSE;
   }

   // write it's contents into a file
   if (WriteFile( hFile, (LPCVOID)FileBuf, dwFileSize*2, 
                     &dwBytesWritten, NULL) == FALSE)
   {
      MessageBox( hWnd, "Error writing file.", NULL, MB_OK );
      return FALSE;
   }

   // close the file
   CloseHandle(hFile);

   return TRUE;
}


/****************************************************************************
*
*    FUNCTION: FileSaveHookProc(HWND, UINT, UINT, LONG)
*
*    PURPOSE:  Processes messages for FileSave common dialog box
*
*    COMMENTS:
*
*        This hook procedure prompts the user if they want to save the
*        current file.  If they choose YES, the file is saved and the dialog
*        is dismissed.  If they choose NO, they are returned to the
*        GetSaveFileName() common dialog.
*
*        If the current mode calls for a customized template, this function
*        will test the 'Create File?' checkbox.  If the user choses no, the
*        OFN_FILEMUSTEXIST flag is set.
*
*    RETURN VALUES:
*        TRUE - User chose 'Yes' from the "Are you sure message box".
*        FALSE - User chose 'No'; return to the dialog box.
*
*
****************************************************************************/

BOOL APIENTRY FileSaveHookProc(
        HWND hDlg,                /* window handle of the dialog box */
        UINT message,             /* type of message                 */
        UINT wParam,            /* message-specific information    */
        LONG lParam)
{
    char szTempText[MAX_PATH];
    char szString[MAX_PATH];

    switch (message)
    {
        case WM_COMMAND:
            if (LOWORD(wParam) == IDOK)
            {
                GetDlgItemText( hDlg, edt1, szTempText,
                    sizeof( szTempText ) - 1);
                if ( OpenFileName.Flags & OFN_ENABLETEMPLATE )
                {
                    // check to see if the Create File box has been checked
                    if ( (BOOL)(SendMessage( GetDlgItem(hDlg, chx2),
                        BM_GETCHECK, 0, 0L )) == FALSE )
                        OpenFileName.Flags |= OFN_FILEMUSTEXIST;
                    break;

                }
                else
                {
                    sprintf( szString, "Are you sure you want to save %s?",
                        szTempText);
                    if ( MessageBox( hDlg, szString, "Information",
                        MB_YESNO ) == IDYES )
                        break;
                    return(TRUE);
                }

            }
            break;
    }
    return (FALSE);
}

/****************************************************************************
*
*    FUNCTION: SaveAs(HWND)
*
*    PURPOSE:  Invokes the common dialog function to save the current
*              buffer to a file.
*    COMMENTS:
*
*        This function initializes the OPENFILENAME structure for any
*        mode selected by the user: standard, using a hook or using a
*        customized template.  It then calls the GetSaveFileName()
*        common dialog function.
*
*    RETURN VALUES:
*        TRUE - The file was saved successfully.
*        FALSE - The buffer was not saved to a file.
*
****************************************************************************/
BOOL SaveAs( HWND hWnd )
{

   lstrcpy( szFile, "");
   lstrcpy( szFileTitle, "");

   OpenFileName.lStructSize       = sizeof(OPENFILENAME);
   OpenFileName.hwndOwner         = hWnd;
   OpenFileName.hInstance         = (HANDLE) hInst;
   OpenFileName.lpstrFilter       = szFilter;
   OpenFileName.lpstrCustomFilter = (LPTSTR) NULL;
   OpenFileName.nMaxCustFilter    = 0L;
   OpenFileName.nFilterIndex      = 1L;
   OpenFileName.lpstrFile         = szFile;
   OpenFileName.nMaxFile          = sizeof(szFile);
   OpenFileName.lpstrFileTitle    = szFileTitle;
   OpenFileName.nMaxFileTitle     = sizeof(szFileTitle);
   OpenFileName.lpstrInitialDir   = NULL;
   OpenFileName.lpstrTitle        = "Save As";
   OpenFileName.nFileOffset       = 0;
   OpenFileName.nFileExtension    = 0;
   OpenFileName.lpstrDefExt       = "txt";
   OpenFileName.lCustData         = 0;

   switch( wMode )
   {
        case IDM_STANDARD:
            OpenFileName.Flags = 0L;
            OpenFileName.lpfnHook = (LPOFNHOOKPROC)(FARPROC)NULL;
            OpenFileName.lpTemplateName = (LPTSTR)NULL;
            break;

        case IDM_HOOK:
            OpenFileName.Flags = OFN_ENABLEHOOK;
            OpenFileName.lpfnHook = (LPOFNHOOKPROC)FileSaveHookProc;
            OpenFileName.lpTemplateName = (LPTSTR)NULL;
            break;

        case IDM_CUSTOM:
            OpenFileName.Flags = OFN_ENABLEHOOK | OFN_ENABLETEMPLATE;
            OpenFileName.lpfnHook = (LPOFNHOOKPROC)FileSaveHookProc;
			if (bNewShell)
			{
				OpenFileName.Flags |= OFN_EXPLORER;
            	OpenFileName.lpTemplateName = (LPTSTR)MAKEINTRESOURCE(IDD_OPENSAVE);
			}
			else
            	OpenFileName.lpTemplateName = (LPTSTR)MAKEINTRESOURCE(FILEOPENORD);
            break;
   }

   if ( GetSaveFileName( &OpenFileName ))
        return(SaveToFile( hWnd ));
   else
   {
        ProcessCDError(CommDlgExtendedError(), hWnd );
        return FALSE;
   }

   return (FALSE);
}


/****************************************************************************
*
*    FUNCTION: ChooseColorHookProc(HWND, UINT, UINT, LONG)
*
*    PURPOSE:  Processes messages for ChooseColor common dialog box
*
*    COMMENTS:
*
*        This hook procedure simply prompts the user whether or not they
*        want to change the color.  if they choose YES, the color of the
*        text will be changed and the dialog will be dismissed.  If they
*        choose NO, the color will not be changed and the user will be
*        returned to the dialog
*
*    RETURN VALUES:
*        TRUE - User chose 'Yes' from the "Are you sure message box".
*        FALSE - User chose 'No'; return to the dialog box.
*
****************************************************************************/

BOOL APIENTRY ChooseColorHookProc(
        HWND hDlg,                /* window handle of the dialog box */
        UINT message,             /* type of message                 */
        UINT wParam,            /* message-specific information    */
        LONG lParam)
{

    switch (message)
    {
        case WM_COMMAND:
            if (LOWORD(wParam) == IDOK)
            {
                if (MessageBox( hDlg, "Are you sure you want to change the color?",
                    "Information", MB_YESNO ) == IDYES )
                    break;
                return (TRUE);

            }
			else if (LOWORD(wParam) == IDCANCEL)
				return TRUE;
            break;
    }
    return (FALSE);
}


/****************************************************************************
*
*    FUNCTION: ChooseNewColor(HWND)
*
*    PURPOSE:  Invokes common dialog function to chose a new color.
*
*    COMMENTS:
*        This function initializes the CHOOSECOLOR structure for any
*        mode the user chooses: standard, using a hook or using a
*        customized template.  It then calls the ChooseColor()
*        common dialog function.
*
*    RETURN VALUES:
*        TRUE - A new color was chosen.
*        FALSE - No new color was chosen.
*
****************************************************************************/
BOOL ChooseNewColor( HWND hWnd )
{

    DWORD dwColor;
    DWORD dwCustClrs[16];
    BOOL fSetColor = FALSE;
    int i;


    for (i=0; i < 15; i++)
        dwCustClrs[i] = RGB( 255, 255, 255);

    dwColor = RGB( 0, 0, 0 );

    chsclr.lStructSize = sizeof(CHOOSECOLOR);
    chsclr.hwndOwner = hWnd;
    chsclr.hInstance = (HANDLE)hInst;
    chsclr.rgbResult = dwColor;
    chsclr.lpCustColors = (LPDWORD)dwCustClrs;
    chsclr.lCustData = 0L;

    switch( wMode )
    {
        case IDM_HOOK:
            chsclr.Flags = CC_ENABLEHOOK;
            chsclr.lpfnHook = (LPCCHOOKPROC)ChooseColorHookProc;
            chsclr.lpTemplateName = (LPTSTR)NULL;
            break;

        case IDM_CUSTOM:
            chsclr.Flags = CC_PREVENTFULLOPEN | CC_ENABLEHOOK | CC_ENABLETEMPLATE;
            chsclr.lpfnHook = (LPCCHOOKPROC)ChooseColorHookProc;
		    chsclr.lpTemplateName = "CHOOSECOLOR";
			break;

        case IDM_STANDARD:
			chsclr.Flags = CC_PREVENTFULLOPEN;
            chsclr.lpfnHook = (LPCCHOOKPROC)(FARPROC)NULL;
            chsclr.lpTemplateName = (LPTSTR)NULL;
            break;


   }

   if ( fSetColor = ChooseColor( &chsclr ))
   {
       crColor = chsclr.rgbResult;
       return TRUE;
   }
   else
   {
       ProcessCDError(CommDlgExtendedError(), hWnd );
       return FALSE;
   }
}


/****************************************************************************
*
*    FUNCTION: ChooseFontHookProc(HWND, UINT, UINT, LONG)
*
*    PURPOSE:  Processes messages for ChooseFont common dialog box
*
*    COMMENTS:
*
*        This hook procedure simply prompts the user whether or not they
*        want to change the font.  if they choose YES, the color of the
*        font will be changed and the dialog will be dismissed.  If they
*        choose NO, the font will not be changed and the user will be
*        returned to the dialog
*
*        If the current mode is set to use a customized template, the
*        color drop down combo box is hidden.
*
*    RETURN VALUES:
*        TRUE - Change the font.
*        FALSE - Return to the dialog box.
*
****************************************************************************/

BOOL APIENTRY ChooseFontHookProc(
        HWND hDlg,                /* window handle of the dialog box */
        UINT message,             /* type of message                 */
        UINT wParam,            /* message-specific information    */
        LONG lParam)
{

    switch (message)
    {
        case WM_INITDIALOG:
            if (chf.Flags & CF_ENABLETEMPLATE)
            {
                ShowWindow(GetDlgItem(hDlg, stc4), SW_HIDE);
                ShowWindow(GetDlgItem(hDlg, cmb4), SW_HIDE);
            }
            break;

        case WM_COMMAND:
            if (LOWORD(wParam) == IDOK)
            {
                if (MessageBox( hDlg, "Are you sure you want to change the font?",
                    "Information", MB_YESNO ) == IDYES )
                    break;
                return (TRUE);

            }
            break;
    }
    return (FALSE);
}

/****************************************************************************
*
*    FUNCTION: ChooseNewFont(HWND)
*
*    PURPOSE:  Invokes common dialog function to chose a new font.
*
*    COMMENTS:
*
*        This function initializes the CHOOSEFONT structure for any mode
*        the user chooses: standard, using a hook or using a customized
*        template.  It then calls the ChooseFont() common dialog function.
*
*    RETURN VALUES:
*        TRUE - A new font was chosen.
*        FALSE - No new font was chosen.
*
****************************************************************************/
BOOL ChooseNewFont( HWND hWnd )
{

   HDC hDC;

   hDC = GetDC( hWnd );
   chf.hDC = CreateCompatibleDC( hDC );
   ReleaseDC( hWnd, hDC );
   chf.lStructSize = sizeof(CHOOSEFONT);
   chf.hwndOwner = hWnd;
   chf.lpLogFont = &lf;
   chf.Flags = CF_SCREENFONTS | CF_EFFECTS;
   chf.rgbColors = RGB(0, 255, 255);
   chf.lCustData = 0;
   chf.hInstance = (HANDLE)hInst;
   chf.lpszStyle = (LPTSTR)NULL;
   chf.nFontType = SCREEN_FONTTYPE;
   chf.nSizeMin = 0;
   chf.nSizeMax = 0;

   switch( wMode )
   {
        case IDM_STANDARD:
            chf.lpfnHook = (LPCFHOOKPROC)(FARPROC)NULL;
            chf.lpTemplateName = (LPTSTR)NULL;
            break;

        case IDM_HOOK:
            chf.Flags |= CF_ENABLEHOOK;
            chf.lpfnHook = (LPCFHOOKPROC)ChooseFontHookProc;
            chf.lpTemplateName = (LPTSTR)NULL;
            break;

        case IDM_CUSTOM:
            chf.Flags |= CF_ENABLEHOOK | CF_ENABLETEMPLATE;
            chf.lpfnHook = (LPCFHOOKPROC)ChooseFontHookProc;
           	chf.lpTemplateName = (LPTSTR)MAKEINTRESOURCE(FORMATDLGORD31);
            break;
   }


   if( ChooseFont( &chf ) == FALSE )
   {
        DeleteDC( hDC );
        ProcessCDError(CommDlgExtendedError(), hWnd );
        return FALSE;
   }


   DeleteDC( hDC );

   return (TRUE);
}

/****************************************************************************
*
*    FUNCTION: PrintSetupHookProc(HWND, UINT, UINT, LONG)
*
*    PURPOSE:  Processes messages for PrintDlg setup common dialog box
*
*    COMMENTS:
*
*        This function processes the hook and customized template for the
*        print setup common dialog box.  If the customized template has
*        been provided, the 'Options' pushbutton is hidden.  If the hook only mode
*        is chosen, a message box is displayed informing the user that the
*        hook has been installed.
*
*    RETURN VALUES:
*        TRUE - Continue.
*        FALSE - Return to the dialog box.
*
****************************************************************************/

BOOL APIENTRY PrintSetupHookProc(
        HWND hDlg,                /* window handle of the dialog box */
        UINT message,             /* type of message                 */
        UINT wParam,            /* message-specific information    */
        LONG lParam)
{

    switch (message)
    {
        case WM_INITDIALOG:
            if (pd.Flags & PD_ENABLESETUPTEMPLATE )
            {
                ShowWindow( GetDlgItem(hDlg, psh1), SW_HIDE );
                return(TRUE);
            }
            MessageBox( hDlg,
                    "Hook installed.",
                    "Information", MB_OK );
            return (TRUE);
    }
    return (FALSE);
}



/****************************************************************************
*
*    FUNCTION: PrintDlgHookProc(HWND, UINT, UINT, LONG)
*
*    PURPOSE:  Processes messages for PrintDlg common dialog box
*
*    COMMENTS:
*
*        This hook procedure simply prompts the user whether or not they
*        want to print.  if they choose YES, the text buf will be printed
*        and the dialog will be dismissed.  If they choose NO, the text buf
*        will not be printeded and the user will be returned to the dialog.
*
*        If the current mode is 'custom', the 'Print to file' and 'Collate
*        Copies' options are hidden.
*
*    RETURN VALUES:
*        TRUE - Continue.
*        FALSE - Return to the dialog box.
*
****************************************************************************/

BOOL APIENTRY PrintDlgHookProc(
        HWND hDlg,                /* window handle of the dialog box */
        UINT message,             /* type of message                 */
        UINT wParam,            /* message-specific information    */
        LONG lParam)
{

    switch (message)
    {
        case WM_INITDIALOG:
            if (pd.Flags & PD_ENABLEPRINTTEMPLATE )
            {
                ShowWindow( GetDlgItem(hDlg, chx1), SW_HIDE );
                ShowWindow( GetDlgItem(hDlg, chx2), SW_HIDE );
                return(TRUE);
            }
            MessageBox( hDlg,
                    "Hook installed.",
                    "Information", MB_OK );
            return (TRUE);

        case WM_COMMAND:
            if (LOWORD(wParam) == IDOK)
            {
                if (MessageBox( hDlg, "Are you sure you want to print?",
                    "Information", MB_YESNO ) == IDYES )
                    break;
                return (TRUE);

            }
            break;
    }
    return (FALSE);
}
/****************************************************************************
*
*    FUNCTION: PrintFile(HWND)
*
*    PURPOSE:  Invokes common dialog function to print.
*
*    COMMENTS:
*
*        This function initializes the PRINTDLG structure for all modes
*        possible: standard, using a hook or using a customized template.
*        When hook mode is chosen, a hook is installed for both the
*        Print dialog and the Print Setup dialog.  When custom mode is
*        chosen, the templates are enabled for both the print dialog and
*        the Print Setup dialog boxes.
*
*        If the PrintDlg() common dialog returns TRUE, the current
*        text buffer is printed out.
*
*
*    RETURN VALUES:
*        void.
*
****************************************************************************/
void PrintFile( HWND hWnd )
{
    DOCINFO di;
    int nError;

    // Initialize PRINTDLG structure.
    pd.lStructSize = sizeof(PRINTDLG);
    pd.hwndOwner = hWnd;
    pd.hDevMode = (HANDLE)NULL;
    pd.hDevNames = (HANDLE)NULL;
    pd.nFromPage = 0;
    pd.nToPage = 0;
    pd.nMinPage = 0;
    pd.nMaxPage = 0;
    pd.nCopies = 0;
    pd.hInstance = (HANDLE)hInst;
    pd.Flags = PD_RETURNDC | PD_USEDEVMODECOPIES | PD_COLLATE | PD_NOSELECTION | PD_PRINTSETUP;

    switch( wMode )
    {
        case IDM_STANDARD:
            pd.lpfnSetupHook = (LPSETUPHOOKPROC)(FARPROC)NULL;
            pd.lpSetupTemplateName = (LPTSTR)NULL;
            pd.lpfnPrintHook = (LPPRINTHOOKPROC)(FARPROC)NULL;
            pd.lpPrintTemplateName = (LPTSTR)NULL;
            break;

        case IDM_HOOK:
            pd.Flags |= PD_ENABLEPRINTHOOK | PD_ENABLESETUPHOOK;
            pd.lpfnSetupHook = (LPSETUPHOOKPROC)PrintSetupHookProc;
            pd.lpSetupTemplateName = (LPTSTR)NULL;
            pd.lpfnPrintHook = (LPPRINTHOOKPROC)PrintDlgHookProc;
            pd.lpPrintTemplateName = (LPTSTR)NULL;
            break;

        case IDM_CUSTOM:
            pd.Flags |= PD_ENABLEPRINTHOOK | PD_ENABLEPRINTTEMPLATE |
                PD_ENABLESETUPHOOK | PD_ENABLESETUPTEMPLATE;
            pd.lpfnSetupHook = (LPSETUPHOOKPROC)PrintSetupHookProc;
            pd.lpfnPrintHook = (LPPRINTHOOKPROC)PrintDlgHookProc;
           	pd.lpPrintTemplateName = (LPTSTR)MAKEINTRESOURCE(PRINTDLGORD);
           	pd.lpSetupTemplateName = (LPTSTR)MAKEINTRESOURCE(PRNSETUPDLGORD);
           break;

    }

    // Print a test page if successful.
    if (PrintDlg(&pd) == TRUE)
    {
        // Fill out the DOCINFO structure.
        di.cbSize = sizeof(DOCINFO);
        di.lpszDocName = "Printing Test";
        di.lpszOutput = (LPTSTR) NULL;
        //di.lpszDataType = (LPTSTR) NULL;
        di.fwType = 0;

        // Start the document.
        StartDoc(pd.hDC, &di);

        nError = StartPage(pd.hDC);
        if (nError <= 0) 
            MessageBox(hWnd, "Error in StartPage.", NULL, MB_OK);
        else
        {

            // Print the text.
            TextOut(pd.hDC, 5, 5, FileBuf, lstrlen(FileBuf));
        
            // Exit if the user has clicked the Cancel button in the
            // AbortPrintJob dialog box; if the button has been clicked,
            // call the AbortDoc function. Otherwise, inform the spooler
            // that the page is complete.
            nError = EndPage(pd.hDC);
            if (nError <= 0) 
            {
                MessageBox(hWnd, "Error in EndPage.", NULL, MB_OK);
                AbortDoc(pd.hDC);
            }
            else
            {
                // The document has ended.
                nError = EndDoc(pd.hDC);
                if (nError <= 0) 
                    MessageBox(hWnd, "Error in EndDoc.", NULL, MB_OK);
            }
        }
        DeleteDC(pd.hDC);
        if (pd.hDevMode)
            GlobalFree(pd.hDevMode);
        if (pd.hDevNames)
            GlobalFree(pd.hDevNames);
    }
   else
        ProcessCDError(CommDlgExtendedError(), hWnd );
}

/****************************************************************************
*
*    FUNCTION: PageSetupHook(HWND, UINT, UINT, LONG)
*
*    PURPOSE:  Processes messages for PageSetupDlg common dialog box
*
*    COMMENTS:
*
*        This hook procedure simply informs the user that the hook is in place.
*
*    RETURN VALUES:
*        TRUE - Continue.
*        FALSE - Return to the dialog box.
*
****************************************************************************/

BOOL APIENTRY PageSetupHook(
        HWND hDlg,                /* window handle of the dialog box */
        UINT message,             /* type of message                 */
        UINT wParam,            /* message-specific information    */
        LONG lParam)
{

    switch (message)
    {
        case WM_INITDIALOG:
            if (psDlg.Flags & PSD_ENABLEPAGESETUPTEMPLATE )
            {
				// Hide the Options button
                ShowWindow( GetDlgItem(hDlg, psh1), SW_HIDE );
                return(TRUE);
            }
            MessageBox( hDlg,
                    "Hook installed.",
                    "Information", MB_OK );
            return (TRUE);

        case WM_COMMAND:
            if (LOWORD(wParam) == IDOK)
            {
                if (MessageBox( hDlg, "Are you done?",
                    "Information", MB_YESNO ) == IDYES )
                    break;
                return (TRUE);

            }
            break;
    }
    return (FALSE);

}
/****************************************************************************
*
*    FUNCTION: PageSetup(HWND)
*
*    PURPOSE:  Invokes Page Setup common dialog function.
*
*    COMMENTS:
*
*        This function initializes the PAGESETUPDLG structure for all modes
*        possible: standard, using a hook or using a customized template.
*
*    RETURN VALUES:
*        void.
*
****************************************************************************/
void PageSetup( HWND hWnd )
{

    // Initialize the PAGESETUPDLG structure.
    psDlg.lStructSize = sizeof(PAGESETUPDLG);
    psDlg.hwndOwner = hWnd;
    psDlg.hDevMode = (HANDLE)NULL;
    psDlg.hDevNames = (HANDLE)NULL;
    psDlg.hInstance = (HANDLE)hInst;
    psDlg.lCustData = (LPARAM)NULL;
	psDlg.hPageSetupTemplate = (HGLOBAL)NULL;
    psDlg.Flags = PSD_DEFAULTMINMARGINS | PSD_INHUNDREDTHSOFMILLIMETERS;

    switch( wMode )
    {
        case IDM_STANDARD:
            psDlg.lpfnPageSetupHook = (LPPAGESETUPHOOK)(FARPROC)NULL;
            psDlg.lpPageSetupTemplateName = (LPTSTR)NULL;
            psDlg.lpfnPagePaintHook = (LPPAGEPAINTHOOK)(FARPROC)NULL;
            break;

        case IDM_HOOK:
            psDlg.Flags |= PSD_ENABLEPAGESETUPHOOK;
            psDlg.lpfnPageSetupHook = (LPPAGESETUPHOOK)(FARPROC)PageSetupHook;
            psDlg.lpPageSetupTemplateName = (LPTSTR)NULL;
            psDlg.lpfnPagePaintHook = (LPPAGEPAINTHOOK)(FARPROC)NULL;
            break;

        case IDM_CUSTOM:
            psDlg.Flags |= PSD_ENABLEPAGESETUPHOOK | PSD_ENABLEPAGESETUPTEMPLATE;
            psDlg.lpfnPageSetupHook = (LPPAGESETUPHOOK)(FARPROC)PageSetupHook;
            psDlg.lpPageSetupTemplateName = (LPTSTR)PRNSETUPDLGORD95;
            psDlg.lpfnPagePaintHook = (LPPAGEPAINTHOOK)(FARPROC)NULL;
           break;

    }

    // Call the Page Setup common dialog procedure.
    if (PageSetupDlg(&psDlg) == FALSE)
        ProcessCDError(CommDlgExtendedError(), hWnd );
}

/****************************************************************************
*
*    FUNCTION: ReplaceTextHookProc(HWND, UINT, UINT, LONG)
*
*    PURPOSE:  Processes messages for ReplaceText common dialog box
*
*    COMMENTS:
*
*        Puts up a message stating that the hook is active if hook
*        only active.  Otherwise, if template enabled, hides the
*        Replace All pushbutton, plus the 'Match case' and
*        'Match whole word' check box options.
*
*    RETURN VALUES:
*        TRUE - Continue.
*        FALSE - Return to the dialog box.
*
****************************************************************************/

BOOL APIENTRY ReplaceTextHookProc(
        HWND hDlg,                /* window handle of the dialog box */
        UINT message,             /* type of message                 */
        UINT wParam,            /* message-specific information    */
        LONG lParam)
{
    switch (message)
    {
        case WM_INITDIALOG:
            if (frText.Flags & FR_ENABLETEMPLATE )
                {
                    ShowWindow( GetDlgItem(hDlg, psh2), SW_HIDE );
                    ShowWindow( GetDlgItem(hDlg, chx1), SW_HIDE );
                    ShowWindow( GetDlgItem(hDlg, chx2), SW_HIDE );
                }
            MessageBox( hDlg,
                    "Hook installed.",
                    "Information", MB_OK );
            return (TRUE);


        default:
            break;
    }
    return (FALSE);
}

/****************************************************************************
*
*    FUNCTION: FindTextHookProc(HWND, UINT, UINT, LONG)
*
*    PURPOSE:  Processes messages for FindText common dialog box
*
*    COMMENTS:
*
*        Puts up a message stating that the hook is active if hook
*        only enabled.  If custom template, hides the 'Match case'
*        and 'Match whole word' options, hides the group box 'Direction'
*        with the radio buttons 'Up' and 'Down'.
*
*    RETURN VALUES:
*        TRUE - Continue.
*        FALSE - Return to the dialog box.
*
****************************************************************************/

BOOL APIENTRY FindTextHookProc(
        HWND hDlg,                /* window handle of the dialog box */
        UINT message,             /* type of message                 */
        UINT wParam,            /* message-specific information    */
        LONG lParam)
{

    switch (message)
    {
        case WM_INITDIALOG:
            if (frText.Flags & FR_ENABLETEMPLATE )
            {
                ShowWindow(GetDlgItem(hDlg, chx1), SW_HIDE);
                ShowWindow(GetDlgItem(hDlg, grp1), SW_HIDE);
                ShowWindow(GetDlgItem(hDlg, chx2), SW_HIDE);
                ShowWindow(GetDlgItem(hDlg, rad1), SW_HIDE);
                ShowWindow(GetDlgItem(hDlg, rad2), SW_HIDE);
            }
            MessageBox( hDlg,
                    "Hook installed.",
                    "Information", MB_OK );
            return (TRUE);


        default:
            break;
    }
    return (FALSE);
}


/****************************************************************************
*
*    FUNCTION: CallFindText( HWND )
*
*    PURPOSE:  Initializes and calls the FindText()
*        common dialog.
*
*    COMMENTS:
*
*        This function initialzes the FINDREPLACE structure for any mode:
*        standard, using a hook or using a customized template.  It then
*        calls the FindText() common dialog function.
*
*    RETURN VALUES:
*        void.
*
****************************************************************************/
void CallFindText( HWND hWnd )
{

    frText.lStructSize = sizeof( frText );
    frText.hwndOwner = hWnd;
    frText.hInstance = (HANDLE)hInst;
    frText.lpstrFindWhat = szFindString;
    frText.lpstrReplaceWith = (LPTSTR)NULL;
    frText.wFindWhatLen = sizeof(szFindString);
    frText.wReplaceWithLen = 0;
    frText.lCustData = 0;
    lpBufPtr = FileBuf;

    switch( wMode )
    {
        case IDM_STANDARD:
            frText.Flags =  FR_NOMATCHCASE | FR_NOUPDOWN | FR_NOWHOLEWORD;
            frText.lpfnHook = (LPFRHOOKPROC)(FARPROC)NULL;
            frText.lpTemplateName = (LPTSTR)NULL;
            break;

        case IDM_HOOK:
            frText.Flags = FR_NOMATCHCASE | FR_NOUPDOWN | FR_NOWHOLEWORD |
                FR_ENABLEHOOK;
            frText.lpfnHook = (LPFRHOOKPROC)FindTextHookProc;
            frText.lpTemplateName = (LPTSTR)NULL;
            break;

        case IDM_CUSTOM:
            frText.Flags = FR_NOMATCHCASE | FR_NOUPDOWN | FR_NOWHOLEWORD |
                 FR_ENABLEHOOK | FR_ENABLETEMPLATE;
            frText.lpfnHook = (LPFRHOOKPROC)FindTextHookProc;
           	frText.lpTemplateName = (LPTSTR)MAKEINTRESOURCE(FINDDLGORD);
            break;
    }

    if ((hDlgFR = FindText(&frText)) == NULL)
        ProcessCDError(CommDlgExtendedError(), hWnd );

}


/****************************************************************************
*
*    FUNCTION: CallReplaceText( HWND )
*
*    PURPOSE:  Initializes and calls the ReplaceText()
*        common dialog.
*
*    COMMENTS:
*
*        This function initialzes the FINDREPLACE structure for any mode:
*        standard, using a hook or using a customized template.  It then
*        calls the ReplaceText() common dialog function.
*
*    RETURN VALUES:
*        void.
*
****************************************************************************/
void CallReplaceText( HWND hWnd )
{
    frText.lStructSize = sizeof( frText );
    frText.hwndOwner = hWnd;
    frText.hInstance = (HANDLE)hInst;
    frText.lpstrFindWhat = szFindString;
    frText.lpstrReplaceWith = szReplaceString;
    frText.wFindWhatLen = sizeof(szFindString);
    frText.wReplaceWithLen = sizeof( szReplaceString );
    frText.lCustData = 0;
    lpBufPtr = FileBuf;

    switch( wMode )
    {
        case IDM_STANDARD:
            frText.Flags = FR_NOMATCHCASE | FR_NOUPDOWN | FR_NOWHOLEWORD;
            frText.lpfnHook = (LPFRHOOKPROC)(FARPROC)NULL;
            frText.lpTemplateName = (LPTSTR)NULL;
            break;

        case IDM_HOOK:
            frText.Flags = FR_NOMATCHCASE | FR_NOUPDOWN | FR_NOWHOLEWORD |
                FR_ENABLEHOOK;
            frText.lpfnHook = (LPFRHOOKPROC)ReplaceTextHookProc;
            frText.lpTemplateName = (LPTSTR)NULL;
            break;

        case IDM_CUSTOM:
            frText.Flags = FR_NOMATCHCASE | FR_NOUPDOWN | FR_NOWHOLEWORD |
                FR_ENABLEHOOK | FR_ENABLETEMPLATE;
            frText.lpfnHook = (LPFRHOOKPROC)ReplaceTextHookProc;
           	frText.lpTemplateName = (LPTSTR)MAKEINTRESOURCE(REPLACEDLGORD);
            break;
    }

    if ( (hDlgFR = ReplaceText( &frText )) == NULL )
            ProcessCDError(CommDlgExtendedError(), hWnd );

}

/****************************************************************************
*
*    FUNCTION: SearchFile(LPFINDREPLACE)
*
*    PURPOSE:  Does the find/replace specified by the Find/ReplaceText
*        common dialog.
*
*    COMMENTS:
*
*        This function does the least necessary to implement find and
*        replace by calling existing c-runtime functions.  It is in
*        no way intended to demonstrate either correct or efficient
*        methods for doing textual search or replacement.
*
*    RETURN VALUES:
*        void.
*
****************************************************************************/
void SearchFile( LPFINDREPLACE lpFR )
{

    char Buf[FILE_LEN];
    char *pStr;
    int count, newcount;
    static BOOL bFoundLast = FALSE;

   memset(Buf, '\0', FILE_LEN);
    
   if ( lpFR->Flags & ( FR_FINDNEXT | FR_REPLACE | FR_REPLACEALL ) )
   {
      if ( bFoundLast )
      {
         if ( (lpBufPtr != FileBuf) && (lpFR->Flags & FR_FINDNEXT) )
            lpBufPtr++;
         bFoundLast = FALSE;
      }

      if (!*lpBufPtr || !(pStr = strstr( lpBufPtr, lpFR->lpstrFindWhat ) ) )
      {
         lpBufPtr = FileBuf;
         MessageBox( lpFR->hwndOwner, lpFR->lpstrFindWhat, "String not found", MB_OK );
      }
      else
      {
         if ( lpFR->Flags & FR_FINDNEXT )
         {
            lpBufPtr = pStr;
            bFoundLast = TRUE;
            MessageBox( lpFR->hwndOwner, lpFR->lpstrFindWhat, "String found!", MB_OK );
         }
         else if ( lpFR->Flags & FR_REPLACE )
         {
            // replace string specified in the replace with found string
            // copy up to found string into new buffer
            for( count=0; 
               *pStr && lpBufPtr[count] && *pStr != lpBufPtr[count]; 
               count++);
            lstrcpyn( Buf, lpBufPtr, count );
            // concatenate new string
            lstrcat( Buf, lpFR->lpstrReplaceWith );
            // copy rest of string (less the found string)
            newcount = count + lstrlen(lpFR->lpstrFindWhat);
            lstrcat( Buf, lpBufPtr+newcount);
            lstrcpy( lpBufPtr, Buf );
            lpBufPtr += count + lstrlen(lpFR->lpstrReplaceWith);
            dwFileSize = lstrlen(FileBuf);
            MessageBox( lpFR->hwndOwner, FileBuf, "Success!", MB_OK );
         }
         else if ( lpFR->Flags & FR_REPLACEALL)
		 	MessageBox(NULL, "This feature not implemented.", "Information", MB_OK);
      }
   }
}


/****************************************************************************
*
*    FUNCTION: ProcessCDError(DWORD)
*
*    PURPOSE:  Processes errors from the common dialog functions.
*
*    COMMENTS:
*
*        This function is called whenever a common dialog function
*        fails.  The CommonDialogExtendedError() value is passed to
*        the function which maps the error value to a string table.
*        The string is loaded and displayed for the user.
*
*    RETURN VALUES:
*        void.
*
****************************************************************************/
void ProcessCDError(DWORD dwErrorCode, HWND hWnd)
{
   WORD  wStringID;
   char  buf[MAX_PATH];

   switch(dwErrorCode)
      {
         case CDERR_STRUCTSIZE:      wStringID=IDS_STRUCTSIZE;      break;
         case CDERR_INITIALIZATION:  wStringID=IDS_INITIALIZATION;  break;
         case CDERR_NOTEMPLATE:      wStringID=IDS_NOTEMPLATE;      break;
         case CDERR_NOHINSTANCE:     wStringID=IDS_NOHINSTANCE;     break;
         case CDERR_LOADSTRFAILURE:  wStringID=IDS_LOADSTRFAILURE;  break;
         case CDERR_FINDRESFAILURE:  wStringID=IDS_FINDRESFAILURE;  break;
         case CDERR_LOADRESFAILURE:  wStringID=IDS_LOADRESFAILURE;  break;
         case CDERR_LOCKRESFAILURE:  wStringID=IDS_LOCKRESFAILURE;  break;
         case CDERR_MEMALLOCFAILURE: wStringID=IDS_MEMALLOCFAILURE; break;
         case CDERR_MEMLOCKFAILURE:  wStringID=IDS_MEMLOCKFAILURE;  break;
         case CDERR_NOHOOK:          wStringID=IDS_NOHOOK;          break;
         case PDERR_PARSEFAILURE:    wStringID=IDS_PARSEFAILURE;    break;
         case PDERR_RETDEFFAILURE:   wStringID=IDS_RETDEFFAILURE;   break;
         case PDERR_LOADDRVFAILURE:  wStringID=IDS_LOADDRVFAILURE;  break;
         case PDERR_GETDEVMODEFAIL:  wStringID=IDS_GETDEVMODEFAIL;  break;
         case PDERR_INITFAILURE:     wStringID=IDS_INITFAILURE;     break;
         case PDERR_NODEVICES:       wStringID=IDS_NODEVICES;       break;
         case PDERR_NODEFAULTPRN:    wStringID=IDS_NODEFAULTPRN;    break;
         case PDERR_DNDMMISMATCH:    wStringID=IDS_DNDMMISMATCH;    break;
         case PDERR_CREATEICFAILURE: wStringID=IDS_CREATEICFAILURE; break;
         case PDERR_PRINTERNOTFOUND: wStringID=IDS_PRINTERNOTFOUND; break;
         case CFERR_NOFONTS:         wStringID=IDS_NOFONTS;         break;
         case FNERR_SUBCLASSFAILURE: wStringID=IDS_SUBCLASSFAILURE; break;
         case FNERR_INVALIDFILENAME: wStringID=IDS_INVALIDFILENAME; break;
         case FNERR_BUFFERTOOSMALL:  wStringID=IDS_BUFFERTOOSMALL;  break;

         case 0:      // user might have clicked Cancel,
            return;   // or this is a very random error

         default:
            wStringID=IDS_UNKNOWNERROR;
      }

   LoadString(NULL, wStringID, buf, sizeof(buf));
   MessageBox(hWnd, buf, NULL, MB_OK);
   return;
}
