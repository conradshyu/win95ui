; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CShortcutView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "shortcut.h"
LastPage=0

ClassCount=7
Class1=CShortcutApp
Class2=CShortcutDoc
Class3=CShortcutView
Class4=CMainFrame

ResourceCount=4
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class5=CAboutDlg
Resource3=IDD_CREATE
Class6=CreateShortCut
Resource4=IDD_RESOLVE
Class7=ResolveShortCut

[CLS:CShortcutApp]
Type=0
HeaderFile=shortcut.h
ImplementationFile=shortcut.cpp
Filter=N
VirtualFilter=AC
LastObject=CShortcutApp

[CLS:CShortcutDoc]
Type=0
HeaderFile=shortdoc.h
ImplementationFile=shortdoc.cpp
Filter=N

[CLS:CShortcutView]
Type=0
HeaderFile=shortvw.h
ImplementationFile=shortvw.cpp
Filter=C
LastObject=CShortcutView

[CLS:CMainFrame]
Type=0
HeaderFile=mainfrm.h
ImplementationFile=mainfrm.cpp
Filter=T
VirtualFilter=fWC
LastObject=CMainFrame



[CLS:CAboutDlg]
Type=0
HeaderFile=shortcut.cpp
ImplementationFile=shortcut.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=IDM_CREATE
Command2=IDM_RESOLVE
Command3=ID_APP_EXIT
Command4=ID_APP_ABOUT
CommandCount=4

[DLG:IDD_CREATE]
Type=1
Class=CreateShortCut
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=ID_LBOX,listbox,1352728835
Control4=ID_STATIC,static,1342308352
Control5=IDC_CHECK1,button,1342242819

[CLS:CreateShortCut]
Type=0
HeaderFile=reatesho.h
ImplementationFile=reatesho.cpp
Filter=D
LastObject=CreateShortCut
VirtualFilter=dWC

[DLG:IDD_RESOLVE]
Type=1
Class=ResolveShortCut
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_LIST1,listbox,1352728835

[CLS:ResolveShortCut]
Type=0
HeaderFile=resolves.h
ImplementationFile=resolves.cpp
Filter=D
VirtualFilter=dWC
LastObject=ResolveShortCut

