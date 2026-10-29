; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMfcexpView
LastTemplate=CPropertyPage
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "mfcexp.h"
LastPage=0

ClassCount=11
Class1=CMfcexpApp
Class2=CMfcexpDoc
Class3=CMfcexpView
Class4=CMainFrame

ResourceCount=8
Resource1=IDD_ABOUTBOX
Resource2=IDD_HOUSEPROP
Class5=CAboutDlg
Resource3=IDD_ADDHOUSE
Resource4=IDD_ADDCITY
Resource5=IDR_MAINFRAME
Class6=CAddCity
Class7=CAddHouse
Class8=CRemHouse
Resource6=IDD_AGENT
Class9=CProperties
Class10=CAgent
Class11=CHouse
Resource7=IDD_REMHOUSE
Resource8="HOUSEPOPUPMENU"

[CLS:CMfcexpApp]
Type=0
HeaderFile=mfcexp.h
ImplementationFile=mfcexp.cpp
Filter=N

[CLS:CMfcexpDoc]
Type=0
HeaderFile=mfcexdoc.h
ImplementationFile=mfcexdoc.cpp
Filter=N

[CLS:CMfcexpView]
Type=0
HeaderFile=mfcexvw.h
ImplementationFile=mfcexvw.cpp
Filter=C
VirtualFilter=VWC
LastObject=IDM_NEW

[CLS:CMainFrame]
Type=0
HeaderFile=mainfrm.h
ImplementationFile=mainfrm.cpp
Filter=T



[CLS:CAboutDlg]
Type=0
HeaderFile=mfcexp.cpp
ImplementationFile=mfcexp.cpp
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
Command4=IDM_SAVEAS
Command5=ID_APP_EXIT
Command6=IDM_ADDHOUSE
Command7=IDM_REMHOUSE
Command8=IDM_ADDCITY
Command9=IDM_PROPERTIES
Command10=IDM_LARGEICON
Command11=IDM_SMALLICON
Command12=IDM_LISTVIEW
Command13=IDM_REPORTVIEW
Command14=ID_APP_ABOUT
CommandCount=14

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

[DLG:IDD_ADDHOUSE]
Type=1
Class=CAddHouse
ControlCount=12
Control1=IDC_STATIC,static,1342308352
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDE_ADDRESS,edit,1350631552
Control7=IDC_CITY,combobox,1344340226
Control8=IDE_PRICE,edit,1350631552
Control9=IDE_BEDROOMS,edit,1350631552
Control10=IDE_BATHROOMS,edit,1350631552
Control11=IDOK,button,1342242816
Control12=IDCANCEL,button,1342242816

[DLG:IDD_ADDCITY]
Type=1
Class=CAddCity
ControlCount=4
Control1=IDC_STATIC,static,1342308352
Control2=IDE_CITY,edit,1350631552
Control3=IDOK,button,1342242816
Control4=IDCANCEL,button,1342242816

[DLG:IDD_REMHOUSE]
Type=1
Class=CRemHouse
ControlCount=4
Control1=IDC_STATIC,static,1342308352
Control2=ID_LISTBOX,listbox,1352728835
Control3=IDOK,button,1342242816
Control4=IDCANCEL,button,1342242816

[CLS:CAddCity]
Type=0
HeaderFile=mfcexvw.h
ImplementationFile=mfcexvw.cpp
Filter=D
VirtualFilter=dWC
LastObject=IDE_CITY

[CLS:CAddHouse]
Type=0
HeaderFile=mfcexvw.h
ImplementationFile=mfcexvw.cpp
Filter=D
VirtualFilter=dWC
LastObject=CAddHouse

[CLS:CRemHouse]
Type=0
HeaderFile=mfcexvw.h
ImplementationFile=mfcexvw.cpp
Filter=D
VirtualFilter=dWC
LastObject=CRemHouse

[DLG:IDD_HOUSEPROP]
Type=1
Class=CHouse
ControlCount=10
Control1=IDC_STATIC,static,1342308352
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDE_ADDRESS,edit,1350631552
Control7=IDE_PRICE,edit,1350631552
Control8=IDE_BEDROOMS,edit,1350631552
Control9=IDE_BATHROOMS,edit,1350631552
Control10=IDE_CITY,combobox,1344340226

[DLG:IDD_AGENT]
Type=1
Class=CAgent
ControlCount=4
Control1=IDC_STATIC,static,1342308352
Control2=IDC_STATIC,static,1342308352
Control3=IDE_AGENTNAME,edit,1350631552
Control4=IDE_PHONE,edit,1350631552

[CLS:CProperties]
Type=0
HeaderFile=mfcexvw.h
ImplementationFile=mfcexvw.cpp
Filter=W
LastObject=CProperties

[CLS:CAgent]
Type=0
HeaderFile=mfcexvw.h
ImplementationFile=mfcexvw.cpp
Filter=D
LastObject=IDE_AGENTNAME

[CLS:CHouse]
Type=0
HeaderFile=mfcexvw.h
ImplementationFile=mfcexvw.cpp
Filter=D
LastObject=CHouse

[MNU:"HOUSEPOPUPMENU"]
Type=1
Command1=IDM_HOUSEPROPS
CommandCount=1

