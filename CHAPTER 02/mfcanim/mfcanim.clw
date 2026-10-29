; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDemo
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "mfcanim.h"
LastPage=0

ClassCount=6
Class1=CMfcanimApp
Class2=CMfcanimDoc
Class3=CMfcanimView
Class4=CMainFrame

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class5=CAboutDlg
Resource3=IDD_DEMO
Class6=CDemo

[CLS:CMfcanimApp]
Type=0
HeaderFile=mfcanim.h
ImplementationFile=mfcanim.cpp
Filter=N

[CLS:CMfcanimDoc]
Type=0
HeaderFile=mfcandoc.h
ImplementationFile=mfcandoc.cpp
Filter=N

[CLS:CMfcanimView]
Type=0
HeaderFile=mfcanvw.h
ImplementationFile=mfcanvw.cpp
Filter=C
VirtualFilter=VWC
LastObject=IDM_DEMO

[CLS:CMainFrame]
Type=0
HeaderFile=mainfrm.h
ImplementationFile=mainfrm.cpp
Filter=T



[CLS:CAboutDlg]
Type=0
HeaderFile=mfcanim.cpp
ImplementationFile=mfcanim.cpp
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
Command1=IDM_DEMO
Command2=ID_APP_EXIT
Command3=ID_APP_ABOUT
CommandCount=3

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

[DLG:IDD_DEMO]
Type=1
Class=CDemo
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDB_START,button,1342242816
Control3=IDB_STOP,button,1342242816
Control4=IDB_SEEK,button,1342242816
Control5=IDC_GENERIC1,SysAnimate32,1350631427

[CLS:CDemo]
Type=0
HeaderFile=mfcanvw.h
ImplementationFile=mfcanvw.cpp
Filter=D
VirtualFilter=dWC
LastObject=IDB_SEEK

