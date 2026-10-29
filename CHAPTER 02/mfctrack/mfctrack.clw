; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMfctrackView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "mfctrack.h"
LastPage=0

ClassCount=9
Class1=CMfctrackApp
Class2=CMfctrackDoc
Class3=CMfctrackView
Class4=CMainFrame

ResourceCount=6
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class5=CAboutDlg
Resource3=IDD_PAGESIZE
Class6=CRange
Resource4=IDD_Range
Resource5=IDD_LINESIZE
Class7=CFrequency
Class8=CLineSize
Class9=CPageSize
Resource6=IDD_FREQUENCY

[CLS:CMfctrackApp]
Type=0
HeaderFile=mfctrack.h
ImplementationFile=mfctrack.cpp
Filter=N
LastObject=ID_APP_ABOUT

[CLS:CMfctrackDoc]
Type=0
HeaderFile=mfctrdoc.h
ImplementationFile=mfctrdoc.cpp
Filter=N
LastObject=CMfctrackDoc

[CLS:CMfctrackView]
Type=0
HeaderFile=mfctrvw.h
ImplementationFile=mfctrvw.cpp
Filter=C
VirtualFilter=VWC
LastObject=CMfctrackView

[CLS:CMainFrame]
Type=0
HeaderFile=mainfrm.h
ImplementationFile=mainfrm.cpp
Filter=T
LastObject=CMainFrame



[CLS:CAboutDlg]
Type=0
HeaderFile=mfctrack.cpp
ImplementationFile=mfctrack.cpp
Filter=D
LastObject=CAboutDlg

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
Command1=IDM_RANGE
Command2=IDM_FREQUENCY
Command3=IDM_PAGESIZE
Command4=IDM_LINESIZE
Command5=ID_APP_EXIT
Command6=ID_VIEW_STATUS_BAR
Command7=ID_APP_ABOUT
CommandCount=7

[DLG:IDD_Range]
Type=1
Class=CRange
ControlCount=8
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDE_MIN,edit,1350631552
Control7=IDE_MAX,edit,1350631552
Control8=IDE_SLIDER,edit,1350631552

[CLS:CRange]
Type=0
HeaderFile=mfctrvw.h
ImplementationFile=mfctrvw.cpp
Filter=D
LastObject=CRange
VirtualFilter=dWC

[DLG:IDD_FREQUENCY]
Type=1
Class=CFrequency
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDE_FREQUENCY,edit,1350631552
Control6=IDE_SLIDER,edit,1350631552

[DLG:IDD_PAGESIZE]
Type=1
Class=CPageSize
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDE_PAGESIZE,edit,1350631552
Control6=IDE_SLIDER,edit,1350631552

[DLG:IDD_LINESIZE]
Type=1
Class=CLineSize
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDE_LINESIZE,edit,1350631552
Control6=IDE_SLIDER,edit,1350631552

[CLS:CFrequency]
Type=0
HeaderFile=mfctrvw.h
ImplementationFile=mfctrvw.cpp
Filter=D
LastObject=CFrequency
VirtualFilter=dWC

[CLS:CLineSize]
Type=0
HeaderFile=mfctrvw.h
ImplementationFile=mfctrvw.cpp
Filter=D
LastObject=CLineSize
VirtualFilter=dWC

[CLS:CPageSize]
Type=0
HeaderFile=mfctrvw.h
ImplementationFile=mfctrvw.cpp
Filter=D
LastObject=CPageSize
VirtualFilter=dWC

