; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CRange
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "mfcprog.h"
LastPage=0

ClassCount=6
Class1=CMfcprogApp
Class2=CMfcprogDoc
Class3=CMfcprogView
Class4=CMainFrame

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class5=CAboutDlg
Resource3=IDD_Range
Class6=CRange

[CLS:CMfcprogApp]
Type=0
HeaderFile=mfcprog.h
ImplementationFile=mfcprog.cpp
Filter=N

[CLS:CMfcprogDoc]
Type=0
HeaderFile=mfcprdoc.h
ImplementationFile=mfcprdoc.cpp
Filter=N

[CLS:CMfcprogView]
Type=0
HeaderFile=mfcprvw.h
ImplementationFile=mfcprvw.cpp
Filter=C
LastObject=IDM_RANGE
VirtualFilter=VWC

[CLS:CMainFrame]
Type=0
HeaderFile=mainfrm.h
ImplementationFile=mainfrm.cpp
Filter=T
LastObject=CMainFrame



[CLS:CAboutDlg]
Type=0
HeaderFile=mfcprog.cpp
ImplementationFile=mfcprog.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=IDM_START
Command2=IDM_STOP
Command3=IDM_RANGE
Command4=ID_APP_EXIT
Command5=ID_APP_ABOUT
CommandCount=5

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_UNDO
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_NEXT_PANE
Command13=ID_PREV_PANE
CommandCount=13

[DLG:IDD_Range]
Type=1
Class=CRange
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_MIN,edit,1350631552
Control6=IDC_MAX,edit,1350631552

[CLS:CRange]
Type=0
HeaderFile=mfcprvw.h
ImplementationFile=mfcprvw.cpp
Filter=D
VirtualFilter=dWC
LastObject=CRange

