; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=Combo
LastTemplate=CComboBox
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "mfctool.h"
LastPage=0

ClassCount=7
Class1=CMfctoolApp
Class2=CMfctoolDoc
Class3=CMfctoolView
Class4=CMainFrame

ResourceCount=2
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class5=CAboutDlg
Class6=ToolBar
Class7=Combo

[CLS:CMfctoolApp]
Type=0
HeaderFile=mfctool.h
ImplementationFile=mfctool.cpp
Filter=N

[CLS:CMfctoolDoc]
Type=0
HeaderFile=mfctodoc.h
ImplementationFile=mfctodoc.cpp
Filter=N

[CLS:CMfctoolView]
Type=0
HeaderFile=mfctovw.h
ImplementationFile=mfctovw.cpp
Filter=C
VirtualFilter=VWC
LastObject=CMfctoolView

[CLS:CMainFrame]
Type=0
HeaderFile=mainfrm.h
ImplementationFile=mainfrm.cpp
Filter=T



[CLS:CAboutDlg]
Type=0
HeaderFile=mfctool.cpp
ImplementationFile=mfctool.cpp
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
Command1=IDM_NEW
Command2=IDM_OPEN
Command3=IDM_SAVE
Command4=IDM_EXIT
Command5=IDM_CUT
Command6=IDM_COPY
Command7=IDM_PASTE
Command8=IDM_ABOUT
CommandCount=8

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

[CLS:ToolBar]
Type=0
HeaderFile=mfctovw.h
ImplementationFile=mfctovw.cpp
Filter=W
LastObject=ToolBar

[CLS:Combo]
Type=0
HeaderFile=mfctovw.h
ImplementationFile=mfctovw.cpp
Filter=W
VirtualFilter=cWC
LastObject=Combo

