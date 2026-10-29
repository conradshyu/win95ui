//THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
//ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
//THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//
// Copyright  1994-1995  Microsoft Corporation.  All Rights Reserved.
//
//  PROGRAM:    Animat.c
//
//  PURPOSE:    Demonstrates how to manipulate the animation control
//
//	PLATFORMS:	Windows 95
//
//	FUNCTIONS:	
//		WinMain() - calls initialization function, processes message loop
//		InitApplication() - Initializes window data nd registers window
//		InitInstance() -saves instance handle and creates main window
//		MainWindProc() Processes messages
//		About() - Process messages for "About" dialog box
//
//	SPECIAL INSTRUCTIONS: N/A
//

#include <windows.h>    // includes basic windows functionality
#include <string.h>     // includes the string functions
#include <commctrl.h>   // includes the common controls
#include "resource.h"   // includes the definitions for the resources
#include "animat.h"     // includes the application-specific information

//
//
//   FUNCTION: WinMain(HANDLE, HANDLE, LPSTR, int)
//
//   PURPOSE: Main entry point for the application. 
//
//   COMMENTS:
//	
//	This function calls the initialization functions and processes
//	the main message loop.
// 
int APIENTRY WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow
	)
{
	MSG msg;                       

    InitCommonControls();

    // if the initialization fails, return.
	if (!InitApplication(hInstance))
		return (FALSE);     

	// Perform initializations that apply to a specific instance 
	if (!InitInstance(hInstance, nCmdShow))
		return (FALSE);

	// Acquire and dispatch messages until a WM_QUIT message is received. 
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


//
//
//   FUNCTION: InitApplication(HANDLE) 
//
//   PURPOSE: Initializes window data and registers window class 
//
//   COMMENTS:
//
//		This function registers the window class for the main window.	
// 
BOOL InitApplication(HANDLE hInstance)
{
        WNDCLASS  wcSample;
	
	// Fill in window class structure with parameters that describe the       
	// main window.                                                           

        wcSample.style = 0;                     
        wcSample.lpfnWndProc = (WNDPROC)MainWndProc; 
        wcSample.cbClsExtra = 0;              
        wcSample.cbWndExtra = 0;              
        wcSample.hInstance = hInstance;       
        wcSample.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(EXE_ICON));
        wcSample.hCursor = LoadCursor(NULL, IDC_ARROW);
        wcSample.hbrBackground = GetStockObject(WHITE_BRUSH); 
        wcSample.lpszMenuName =  "OPTIONSMENU";  
        wcSample.lpszClassName = "SampleWClass";

        return (RegisterClass(&wcSample));

}


//
//
//   FUNCTION: InitInstance(HANDLE, int)
//
//   PURPOSE: Creates the main window.
//
//   COMMENTS: N/A
//	
// 
BOOL InitInstance(
	HANDLE          hInstance,
	int             nCmdShow) 
{
	HWND hWndMain;

	hWndMain = CreateWindow(
                "SampleWClass",           
                "Animate Control Sample", 
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL,               
		NULL,               
		hInstance,          
		NULL);

	/* If window could not be created, return "failure" */
	if (!hWndMain)
		return (FALSE);

	/* Make the window visible; update its client area; and return "success" */
	ShowWindow(hWndMain, nCmdShow);
	UpdateWindow(hWndMain); 
	return (TRUE);      

}

//
//   FUNCTION: MainWndProc(HWND, UINT, UINT, LONG)
//
//  PURPOSE:  Processes messages for the main window procedure 
//
//    MESSAGES:
//	
//	WM_CREATE - creates the main MLE for the window
//	WM_COMMAND - processes the menu commands for the application
//	WM_SIZE - sizes the MLE to fill the client area of the window
//	WM_DESTROY - posts a quit message and returns
//
LONG APIENTRY MainWndProc(
	HWND hWnd,                // window handle                   
	UINT message,             // type of message                 
	UINT wParam,              // additional information          
	LONG lParam)              // additional information          
{

	static HWND hWndA;

	switch (message) 
	{
        case WM_CREATE:
			break;


        case WM_COMMAND:
            switch( LOWORD( wParam ))
			{
                case IDM_ANIMATE:
					// Show the Animation demo dialog
                    DialogBox((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), MAKEINTRESOURCE(IDD_ANIMATE), hWnd, (DLGPROC)Demo);
                    break;

				case IDM_EXIT:
					PostQuitMessage(0);
					break;

				case IDM_ABOUT:
                    DialogBox((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), "AboutBox", hWnd, (DLGPROC)About);
					break;

				default:
					return (DefWindowProc(hWnd, message, wParam, lParam));

		}
		break;

		case WM_DESTROY:                  /* message: window being destroyed */
			PostQuitMessage(0);
			break;

		default:
			return (DefWindowProc(hWnd, message, wParam, lParam));
	}
	return (0);
}


//
//  FUNCTION: About(HWND, UINT, UINT, LONG)
//
//  PURPOSE:  Processes messages for the "About" dialog box 
//
//  MESSAGES:
//	
//	WM_INITDIALOG - initalizes the dialog box
//	WM_COMMAND - processes the input
//	
BOOL APIENTRY About(
   HWND hDlg,
	UINT message,
	UINT wParam,
	LONG lParam)
{
	switch (message)
	{
	   case WM_INITDIALOG:
		  return TRUE;

	   case WM_COMMAND:              
		  if (LOWORD(wParam) == IDOK)
		 {
			  EndDialog(hDlg, TRUE);
			  return TRUE;
		  }
		  break;

		default:
			return FALSE;
	}

}

//
//  FUNCTION: Demo(HWND, UINT, UINT, LONG)
//
//  PURPOSE:  Processes messages for the "Animation Demo" dialog box 
//
//  MESSAGES:
//	
//	WM_INITDIALOG - initalizes the dialog box
//	WM_COMMAND - processes the input
//	
BOOL APIENTRY Demo(
    HWND hDlg,
	UINT message,
	UINT wParam,
	LONG lParam)
{
    static BOOL bStart;
    static int iSeek;

	switch (message)
	{
	   case WM_INITDIALOG:
          bStart = FALSE;
          iSeek = 1;
		  return TRUE;

	   case WM_COMMAND:              
		  if (LOWORD(wParam) == IDOK)
		  {
			  EndDialog(hDlg, TRUE);
			  return TRUE;
		  }
		  else if (HIWORD(wParam) == BN_CLICKED)
          {
            switch (LOWORD(wParam))
            {
                case IDC_PLAY:
                    if (!bStart)
                    {
                        bStart = TRUE;
                        
                        Animate_Open(GetDlgItem(hDlg, IDC_ANIMATE), "WIN95.AVI");
      				    Animate_Play(GetDlgItem(hDlg, IDC_ANIMATE),0, -1, -1);
                    }
                    break;

                case IDC_STOP:
                    if (bStart)
                    {
                        bStart = FALSE;
                        Animate_Stop(GetDlgItem(hDlg, IDC_ANIMATE) );
                    }
                    break;

                case IDC_SEEK:
                    if (bStart)
                    {
                        Animate_Seek(GetDlgItem(hDlg, IDC_ANIMATE), iSeek);
                        if (iSeek < NUM_FRAMES)
                            iSeek++;
                    }
                    break;
            }
          }
          break;

		default:
			return FALSE;
	}

}

