; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSpin
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "fcspin.h"
LastPage=0

ClassCount=6
Class1=CFcspinApp
Class2=CFcspinDoc
Class3=CFcspinView
Class4=CMainFrame

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class5=CAboutDlg
Resource3=IDD_SPIN
Class6=CSpin

[CLS:CFcspinApp]
Type=0
HeaderFile=fcspin.h
ImplementationFile=fcspin.cpp
Filter=N

[CLS:CFcspinDoc]
Type=0
HeaderFile=fcspidoc.h
ImplementationFile=fcspidoc.cpp
Filter=N

[CLS:CFcspinView]
Type=0
HeaderFile=fcspivw.h
ImplementationFile=fcspivw.cpp
Filter=C
LastObject=IDM_SPIN
VirtualFilter=VWC

[CLS:CMainFrame]
Type=0
HeaderFile=mainfrm.h
ImplementationFile=mainfrm.cpp
Filter=T



[CLS:CAboutDlg]
Type=0
HeaderFile=fcspin.cpp
ImplementationFile=fcspin.cpp
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
Command1=IDM_SPIN
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

[DLG:IDD_SPIN]
Type=1
Class=CSpin
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_SPIN,msctls_updown32,1342177319
Control5=IDC_LINES,edit,1350631552

[CLS:CSpin]
Type=0
HeaderFile=fcspivw.h
ImplementationFile=fcspivw.cpp
Filter=D
VirtualFilter=dWC
LastObject=IDC_LINES

