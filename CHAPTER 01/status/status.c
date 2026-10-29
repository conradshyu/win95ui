/***********************************************************************
*
*   PROGRAM: status.c
*
*   PURPOSE: Creates a Status Bar
*
***********************************************************************/

#include <windows.h>   // includes basic windows functionality
#include <commctrl.h>  // includes the common control header
#include <string.h>
#include "status.h"

HINSTANCE hInst;

/***********************************************************************
*
*   FUNCTION: WinMain (HANDLE, HANDLE, LPSTR, int)
*
*   PURPOSE:  Calls initialization function, processes message loop
*
***********************************************************************/

int APIENTRY WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
   LPSTR lpCmdLine, int nCmdShow)
{

MSG msg;                       

// MUST call this to initialize the common controls at startup
InitCommonControls ();

if (! InitApplication (hInstance))
   return (FALSE);     

// Perform initializations that apply to a specific instance.
if (! InitInstance (hInstance, nCmdShow))
   return (FALSE);

// Acquire and dispatch messages until a WM_QUIT message is received.
while (GetMessage (&msg, NULL, 0, 0))                
{
   TranslateMessage (&msg);
   DispatchMessage (&msg); 
}
return (msg.wParam);  
}


/***********************************************************************
*
*   FUNCTION: InitApplication (HANDLE)
*
*   PURPOSE:  Initializes window data and registers window class
*
***********************************************************************/

BOOL InitApplication (HANDLE hInstance)   // current instance
{

WNDCLASS wcStatus;
	
// Fill in window class structure with parameters that describe the
// main window.
wcStatus.style = 0;                     
wcStatus.lpfnWndProc = (WNDPROC)MainWndProc; 
wcStatus.cbClsExtra = 0;              
wcStatus.cbWndExtra = 0;              
wcStatus.hInstance = hInstance;       
wcStatus.hIcon = LoadIcon (hInstance, MAKEINTRESOURCE(STATUS_ICON));
wcStatus.hCursor = LoadCursor (NULL, IDC_ARROW);
wcStatus.hbrBackground = GetStockObject (WHITE_BRUSH); 
wcStatus.lpszMenuName = "StatusMenu";  
wcStatus.lpszClassName ="StatusWClass";

return (RegisterClass (&wcStatus));
}


/***********************************************************************
*
*   FUNCTION: InitInstance (HANDLE, int)
*
*   PURPOSE:  Saves instance handle and creates main window
*
***********************************************************************/

BOOL InitInstance (HANDLE hInstance, int nCmdShow) 
{

HWND hWnd;

hInst = hInstance;

hWnd = CreateWindow (
   "StatusWClass",           
   "Status Sample", 
   WS_OVERLAPPEDWINDOW,
   CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
   NULL,               
   NULL,               
   hInstance,          
   NULL);

// If window could not be created, return "failure".
if (! hWnd)
   return (FALSE);

// Make the window visible, update its client area, & return "success".
ShowWindow (hWnd, nCmdShow);
UpdateWindow (hWnd); 
return (TRUE);      
}


/***********************************************************************
*
*   FUNCTION: MainWndProc (HWND, unsigned, WORD, LONG)
*
*   PURPOSE:  Processes messages
*
***********************************************************************/

LONG APIENTRY MainWndProc (
   HWND hWnd,      // window handle
   UINT message,   // type of message
   UINT wParam,    // additional information
   LONG lParam)    // additional information
{

static HWND hWndStatus;
HDC hdc;
PAINTSTRUCT ps;
CHAR szBuf [128];
static int aWidths [4];
static HBITMAP hBmp;

switch (message) 
{
   case WM_CREATE:
      hWndStatus = CreateWindowEx ( 
         0L,                             // extended style
         STATUSCLASSNAME,                // create status bar
         "",                             // window title
         WS_CHILD | WS_BORDER |
            WS_VISIBLE | SBS_SIZEGRIP,   // window styles
         0, 0, 0, 0,                     // x, y, width, height
         hWnd,                           // parent window
         (HMENU)ID_STATUSBAR,            // ID
         hInst,                          // instance
         NULL);                          // window data

      if (hWndStatus == NULL)
         MessageBox (NULL, "Status Bar not created!", NULL, MB_OK );

      // Break the status bar into four parts.
      SendMessage (hWndStatus, SB_SETPARTS, 4, (LPARAM)aWidths);
            
      // Set the text in the first part to normal.
      SendMessage (hWndStatus, SB_SETTEXT, 0,
         (LPARAM)"Mouse position:");
            
      // Set the text in the second part to pop out.
      SendMessage (hWndStatus, SB_SETTEXT, 1 | SBT_POPOUT, 
         (LPARAM)"This text pops out.");
            
      // Set the text in the third part to have no borders.
      SendMessage (hWndStatus, SB_SETTEXT, 2 | SBT_NOBORDERS, 
         (LPARAM)"This text has no borders.");

      // Load the bitmap for the owner-drawn part of the status bar.
      hBmp = LoadBitmap (hInst, MAKEINTRESOURCE(ID_BITMAP));
            
      // Set the fourth part to be owner-drawn and pass the bitmap.
      SendMessage (hWndStatus, SB_SETTEXT, 3 | SBT_OWNERDRAW,
         (LPARAM)hBmp);
      break;

   case WM_DRAWITEM:
      if ((int)wParam == ID_STATUSBAR)
      {
         LPDRAWITEMSTRUCT lpDis;
         HDC hdcMem;
         HBITMAP hbmOld;
         BITMAP bm;

         // Save the drawing information.  This information is specific
         // to the part of the status bar to be drawn.
         lpDis = (LPDRAWITEMSTRUCT)lParam;
         // Create a compatible device context (DC) for the bit block
         // transfer (BitBlt).
         hdcMem = CreateCompatibleDC (lpDis->hDC);
         // Select the bitmap into the DC.
         hbmOld = SelectObject(hdcMem, hBmp);
         // Get the information about the bitmap's size.
         GetObject(hBmp, sizeof(bm), &bm);
         // Use BitBlt to transfer the bitmap to the part.
         BitBlt (lpDis->hDC, lpDis->rcItem.left, lpDis->rcItem.top, 
            bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, SRCCOPY);
         // Reselect the original object into the DC.
         SelectObject (hdcMem, hbmOld);
         // Delete the compatible DC.
         DeleteDC (hdcMem);
      }
      break;

   case WM_MOUSEMOVE:
      wsprintf (szBuf, "Mouse position: %d, %d.", LOWORD(lParam), 
         HIWORD(lParam));
      SendMessage (hWndStatus, SB_SETTEXT, 0, (LPARAM)(LPSTR)szBuf);
      break;

   case WM_SIZE:
      // Resize status bar to fit along bottom of the client area.
      MoveWindow (hWndStatus, 0, HIWORD(lParam) - 10, LOWORD(lParam),
         HIWORD(lParam), TRUE);
      // Set the rectangles for the multiple parts of the status bar.
      // Make each 1/4 of the width of the client area.
      aWidths [0] = LOWORD(lParam) / 4;
      aWidths [1] = LOWORD(lParam) / 2;
      aWidths [2] = LOWORD(lParam) - aWidths[0];
      aWidths [3] = -1;
      SendMessage (hWndStatus, SB_SETPARTS, 4, (LPARAM)aWidths);
      break;

   case WM_PAINT:
   {
      hdc = BeginPaint(hWnd, &ps);
      TextOut(hdc, 20, 10, hello, strlen(hello));      
      EndPaint(hWnd, &ps);
      break;
   }
		 

   case WM_COMMAND:
      switch (LOWORD(wParam))
      {
         case IDM_SIMPLE:
            // Set the status bar to simple mode.
            SendMessage (hWndStatus, SB_SIMPLE, (WPARAM)TRUE, 0L);
            // Set the text of the status bar.
            SendMessage (hWndStatus, SB_SETTEXT, 255,
               (LPARAM)"We are now in simple mode.");
            // Check the Simple menu option
            CheckMenuItem (GetMenu(hWnd), IDM_SIMPLE, 
               MF_CHECKED | MF_BYCOMMAND);
            // Uncheck the Multiple menu option.
            CheckMenuItem (GetMenu(hWnd), IDM_MULTIPLE,
               MF_UNCHECKED | MF_BYCOMMAND);
            break;

         case IDM_MULTIPLE:
            // Reset the status bar to multiple-part mode.
            SendMessage (hWndStatus, SB_SIMPLE, (WPARAM)FALSE, 0L);
            // Uncheck the Simple menu option.
            CheckMenuItem (GetMenu(hWnd), IDM_SIMPLE,
               MF_UNCHECKED | MF_BYCOMMAND);
            // Check the Multiple menu option.
            CheckMenuItem (GetMenu(hWnd), IDM_MULTIPLE,
               MF_CHECKED | MF_BYCOMMAND);
            break;

         case IDM_EXIT:
            PostQuitMessage (0);
            break;

         case IDM_ABOUT:
            DialogBox (hInst, "AboutBox", hWnd, (DLGPROC)About);
            break;

         default:
            return (DefWindowProc (hWnd, message, wParam, lParam));
      }
         break;

   case WM_DESTROY:   // message: window being destroyed
      PostQuitMessage (0);
      break;

   default:
      return (DefWindowProc (hWnd, message, wParam, lParam));
}

return (0);
}


/***********************************************************************
*
*   FUNCTION: About (HWND, UINT, UINT, LONG)
*
*   PURPOSE:  Processes messages for "About" dialog box
*
***********************************************************************/

BOOL APIENTRY About (HWND hDlg, UINT message, UINT wParam, LONG lParam)
{

switch (message)
{
   case WM_INITDIALOG:
      return (TRUE);

   case WM_COMMAND:              
      if (LOWORD(wParam) == IDOK)
      {
         EndDialog (hDlg, TRUE);
         return (TRUE);
      }
      break;
}

return (FALSE);   
}
