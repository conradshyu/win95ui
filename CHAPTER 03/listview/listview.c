/****************************************************************************
*
*
*    PROGRAM: ListView.c
*
*    PURPOSE: Demonstrates the use of the new list view control in Chicago
*
****************************************************************************/

#include <windows.h>    // includes basic windows functionality
#include <commctrl.h>   // includes the common control header
#include <stdio.h>
#include <string.h>
#include "listview.h"

// global current instance
HINSTANCE hInst;

// global array of houses
HOUSEINFO rgHouseInfo[] = 
{
	{"100 Berry Lane", "Redmond", 175000, 3, 2 },
	{"523 Apple Road", "Redmond", 125000, 4, 2},
	{"1212 Peach Street", "Redmond",200000, 4, 3},
	{"22 Daffodil Lane", "Bellevue", 2500000, 4, 4},
	{"33542 Orchid Road", "Bellevue", 180000, 3, 2},
	{"64134 Lily Street", "Bellevue", 250000, 4, 3},
	{"33 Nicholas Lane", "Seattle", 350000, 3, 2},
	{"555 Tracy Road", "Seattle", 140000, 3, 2},
	{"446 Jean Street", "Seattle", 225000, 4, 3}
};


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
	WNDCLASS  wcListview;
	
	/* Fill in window class structure with parameters that describe the       */
	/* main window.                                                           */

	wcListview.style = 0;                     
	wcListview.lpfnWndProc = (WNDPROC)MainWndProc; 
	wcListview.cbClsExtra = 0;              
	wcListview.cbWndExtra = 0;              
	wcListview.hInstance = hInstance;       
	wcListview.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(APP_ICON));
	wcListview.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcListview.hbrBackground = GetStockObject(WHITE_BRUSH); 
	wcListview.lpszMenuName =  "ListviewMenu";  
	wcListview.lpszClassName = "ListviewWClass";

	return (RegisterClass(&wcListview));

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
	HWND hWndMain;

	hInst = hInstance;

	hWndMain = CreateWindow(
		"ListviewWClass",
		"Listview Sample", 
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

/****************************************************************************
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
	static HWND hWndListView;
	DWORD dwStyle;

	switch (message) 
	{

		case WM_CREATE:

			hWndListView = CreateListView( hWnd );
			if (hWndListView == NULL)
				MessageBox (NULL, "Listview not created!", NULL, MB_OK );
		 
			break;

		case WM_NOTIFY:
			return( NotifyHandler(hWnd, message, wParam, lParam));
			break;

		case WM_COMMAND:

			switch( LOWORD( wParam ))
			{

				case IDM_LARGEICON:
					dwStyle = GetWindowLong(hWndListView, GWL_STYLE);
					
					if ((dwStyle & LVS_TYPEMASK) != LVS_ICON)
						SetWindowLong(hWndListView, GWL_STYLE,
							(dwStyle & ~LVS_TYPEMASK) | LVS_ICON);
					break;

				case IDM_SMALLICON:
					dwStyle = GetWindowLong(hWndListView, GWL_STYLE);
					
					if ((dwStyle & LVS_TYPEMASK) != LVS_SMALLICON)
						SetWindowLong(hWndListView, GWL_STYLE,
							(dwStyle & ~LVS_TYPEMASK) | LVS_SMALLICON);
					break;

				case IDM_LISTVIEW:
					dwStyle = GetWindowLong(hWndListView, GWL_STYLE);

					if ((dwStyle & LVS_TYPEMASK) != LVS_LIST)
						SetWindowLong(hWndListView, GWL_STYLE,
							(dwStyle & ~LVS_TYPEMASK) | LVS_LIST);
					break;

				case IDM_REPORTVIEW:
					dwStyle = GetWindowLong(hWndListView, GWL_STYLE);

					if ((dwStyle & LVS_TYPEMASK) != LVS_REPORT)
						SetWindowLong(hWndListView, GWL_STYLE,
							(dwStyle & ~LVS_TYPEMASK) | LVS_REPORT);
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

		case WM_SIZE:
            MoveWindow(hWndListView, 0, 0, LOWORD(lParam),HIWORD(lParam),TRUE);
            break;

		case WM_DESTROY:                  /* message: window being destroyed */
			PostQuitMessage(0);
			break;

		default:
			return (DefWindowProc(hWnd, message, wParam, lParam));
	}
	return (0);
}



/****************************************************************************
* 
*    FUNCTION: CreateListView(HWND)
*
*    PURPOSE:  Creates the list view window and initializes it
*
****************************************************************************/
HWND CreateListView (HWND hWndParent)                                     
{
	HWND hWndList;      		// handle to list view window
	RECT rcl;           		// rectangle for setting size of window
	HICON hIcon;        		// handle to an icon
	int index;					// index used in for loops
	HIMAGELIST hSmall, hLarge;	// handles to image lists for small and
                                // large icons
	LV_COLUMN lvC;				// list view column structure
	char szText[MAX_PATH];		// place to store some text
	LV_ITEM lvI;				// list view item structure
	int iSubItem;				// index into column header string table

	// Ensure that the common control DLL is loaded.
	InitCommonControls();

	// Get the size and position of the parent window.
	GetClientRect(hWndParent, &rcl);

	// Create the list view window that starts out in details view
    // and supports label editing.
	hWndList = CreateWindowEx( 0L,
		WC_LISTVIEW,                // list view class
		"",                         // no default text
		WS_VISIBLE | WS_CHILD | WS_BORDER | LVS_REPORT |
		    LVS_EDITLABELS | WS_EX_CLIENTEDGE,	// styles
		0, 0,
		rcl.right - rcl.left, rcl.bottom - rcl.top,
		hWndParent,
		(HMENU) ID_LISTVIEW,
		hInst,
		NULL );

	if (hWndList == NULL )
		return NULL;


	// Initialize the list view window.
	// First initialize the image lists you will need:
    // create image lists for the small and the large icons.

	hSmall = ImageList_Create( BITMAP_WIDTH, BITMAP_HEIGHT,
		FALSE, 3, 0 );

	hLarge = ImageList_Create( LG_BITMAP_WIDTH, LG_BITMAP_HEIGHT,FALSE, 3, 0 );

 	// Load the icons and add them to the image lists.
	for (index = REDMOND; index <= SEATTLE ; index++)
	{
		hIcon = LoadIcon ( hInst, MAKEINTRESOURCE(index));
		// You have 3 of each type of icon here, so add 3 at a time.
		for (iSubItem = 0; iSubItem < 3; iSubItem++)
		{
			if ((ImageList_AddIcon(hSmall, hIcon) == -1) ||
				(ImageList_AddIcon(hLarge, hIcon) == -1))
				return NULL;
		}
	}
	
	// Be sure that all the small icons were added.
	if (ImageList_GetImageCount(hSmall) < 3)
		return FALSE;

	// Be sure that all the large icons were added.
	if (ImageList_GetImageCount(hLarge) < 3)
		return FALSE;

	// Associate the image lists with the list view control.
	ListView_SetImageList(hWndList, hSmall, LVSIL_SMALL);

	ListView_SetImageList(hWndList, hLarge, LVSIL_NORMAL);

	// Now initialize the columns you will need.
	// Initialize the LV_COLUMN structure.
	// The mask specifies that the fmt, width, pszText, and subitem members 
	// of the structure are valid,
	lvC.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	lvC.fmt = LVCFMT_LEFT;  // left-align column
	lvC.cx = 75;            // width of column in pixels
	lvC.pszText = szText;

	// Add the columns.
	for (index = 0; index <= NUM_COLUMNS; index++)
	{
		lvC.iSubItem = index;
		LoadString( hInst, 
					IDS_ADDRESS + index,
					szText,
					sizeof(szText));
		if (ListView_InsertColumn(hWndList, index, &lvC) == -1)
			return NULL;
	}

	// Finally, add the actual items to the control.
	// Fill out the LV_ITEM structure for each of the items to add to the list.
	// The mask specifies the the pszText, iImage, lParam and state
	// members of the LV_ITEM structure are valid.
	lvI.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM | LVIF_STATE;
	lvI.state = 0;      
	lvI.stateMask = 0;  

	for (index = 0; index < NUM_ITEMS; index++)
	{
		lvI.iItem = index;
		lvI.iSubItem = 0;
		// The parent window is responsible for storing the text. 
		// The list view control will send an LVN_GETDISPINFO 
		// when it needs the text to display.
		lvI.pszText = LPSTR_TEXTCALLBACK; 
		lvI.cchTextMax = MAX_ITEMLEN;
		lvI.iImage = index;
		lvI.lParam = (LPARAM)&rgHouseInfo[index];

		if (ListView_InsertItem(hWndList, &lvI) == -1)
			return NULL;

		for (iSubItem = 1; iSubItem < NUM_COLUMNS; iSubItem++)
		{
			ListView_SetItemText( hWndList,
				index,
				iSubItem,
				LPSTR_TEXTCALLBACK);
		}
	}
	return (hWndList);
}



/****************************************************************************
* 
*    FUNCTION: NotifyHandler(HWND, UINT, UINT, LONG)
*
*    PURPOSE: This function is the handler for the WM_NOTIFY that is 
*    sent to the parent of the list view window.
*
****************************************************************************/
LRESULT NotifyHandler( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LV_DISPINFO *pLvdi = (LV_DISPINFO *)lParam;
	NM_LISTVIEW *pNm = (NM_LISTVIEW *)lParam;
	HOUSEINFO *pHouse = (HOUSEINFO *)(pLvdi->item.lParam);
	static char szText[10];

	if (wParam != ID_LISTVIEW)
		return 0L;

	switch(pLvdi->hdr.code)
	{
		case LVN_GETDISPINFO:

			switch (pLvdi->item.iSubItem)
			{
				case 0:     // address
					pLvdi->item.pszText = pHouse->szAddress;
					break;

				case 1:     // city
					pLvdi->item.pszText = pHouse->szCity;
					break;

				case 2:     // price
					sprintf(szText, "$%u", pHouse->iPrice);
					pLvdi->item.pszText = szText;
					break;

				case 3:     // number of bedrooms
					sprintf(szText, "%u", pHouse->iBeds);
					pLvdi->item.pszText = szText;
					break;

				case 4:     // number of bathrooms
					sprintf(szText, "%u", pHouse->iBaths);
					pLvdi->item.pszText = szText;
					break;

				default:
					break;
			}
			break;

        case LVN_BEGINLABELEDIT:
            {
                HWND hWndEdit;

                // Get the handle to the edit box.
                hWndEdit = (HWND)SendMessage(hWnd, LVM_GETEDITCONTROL, 
                    0, 0);
                // Limit the amount of text that can be entered.
                SendMessage(hWndEdit, EM_SETLIMITTEXT, (WPARAM)20, 0);
            }
            break;

        case LVN_ENDLABELEDIT:
            // Save the new label information
            if ((pLvdi->item.iItem != -1) && 
                (pLvdi->item.pszText != NULL))
			    lstrcpy(pHouse->szAddress, pLvdi->item.pszText);
            break;

		case LVN_COLUMNCLICK:
			// The user clicked a column header - sort by this criterion.
			ListView_SortItems( pNm->hdr.hwndFrom,
								ListViewCompareProc,
								(LPARAM)(pNm->iSubItem));
			break;

		default:
			break;
	}
	return 0L;
}

/****************************************************************************
* 
*    FUNCTION: ListViewCompareProc(LPARAM, LPARAM, LPARAM)
*
*    PURPOSE: Callback function that sorts depending on the column click 
*
****************************************************************************/
int CALLBACK ListViewCompareProc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	HOUSEINFO *pHouse1 = (HOUSEINFO *)lParam1;
	HOUSEINFO *pHouse2 = (HOUSEINFO *)lParam2;
	LPSTR lpStr1, lpStr2;
	int iResult;


	if (pHouse1 && pHouse2)
	{
		switch( lParamSort)
		{
			case 0:     // sort by Address
				lpStr1 = pHouse1->szAddress;
				lpStr2 = pHouse2->szAddress;
				iResult = strcmpi(lpStr1, lpStr2);
				break;

			case 1:     // sort by city
				lpStr1 = pHouse1->szCity;
				lpStr2 = pHouse2->szCity;
				iResult = lstrcmpi(lpStr1, lpStr2);
				break;

			case 2:     // sort by price
				iResult = pHouse1->iPrice - pHouse2->iPrice;
				break;

			case 3:     // sort by number of bedrooms
				iResult = pHouse1->iBeds - pHouse2->iBeds;
				break;

			case 4:     // sort by number of bathrooms
				iResult = pHouse1->iBaths - pHouse2->iBaths;
				break;

			default:
				iResult = 0;
				break;

		}

	}
	return(iResult);
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
