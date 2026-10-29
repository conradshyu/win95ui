; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
ODLFile=mfcview.odl
ClassCount=4
Class1=CMfcviewApp
LastClass=CFileView
NewFileInclude2=#include "mfcview.h"
ResourceCount=1
NewFileInclude1=#include "stdafx.h"
Class2=CFileView
LastTemplate=CView
Resource1=IDR_VIEWERMENU
Class3=CMyFrame
Class4=CMyView

[CLS:CMfcviewApp]
Type=0
HeaderFile=mfcview.h
ImplementationFile=mfcview.cpp
Filter=N
LastObject=CMfcviewApp

[CLS:CFileView]
Type=0
HeaderFile=fileview.h
ImplementationFile=fileview.cpp
Filter=N
LastObject=CFileView
VirtualFilter=C

[MNU:IDR_VIEWERMENU]
Type=1
Command1=ID_FILE_EXIT
CommandCount=1

[CLS:CMyFrame]
Type=0
HeaderFile=fileview.h
ImplementationFile=fileview.cpp
Filter=T
LastObject=ID_FILE_EXIT
VirtualFilter=fWC

[CLS:CMyView]
Type=0
HeaderFile=fileview.h
ImplementationFile=fileview.cpp
Filter=C
LastObject=CMyView

