========================================================================
       MICROSOFT FOUNDATION CLASS LIBRARY : FCSPIN
========================================================================


AppWizard has created this FCSPIN application for you.  This application
not only demonstrates the basics of using the Microsoft Foundation classes
but is also a starting point for writing your application.

This file contains a summary of what you will find in each of the files that
make up your FCSPIN application.


FCSPIN.MAK
    This project file is compatible with the Visual C++ development
	environment. 

    It is also compatible with the NMAKE program provided with Visual C++. 

    To build a debug version of the program from the MS-DOS prompt, type
nmake /f FCSPIN.MAK CFG="Win32 Debug"
    or to build a release version of the program, type
nmake /f FCSPIN.MAK CFG="Win32 Release"

FCSPIN.H
    This is the main header file for the application.  It includes other
    project specific headers (including RESOURCE.H) and declares the
    CFcspinApp application class.

FCSPIN.CPP
    This is the main application source file that contains the application
    class CFcspinApp.

FCSPIN.RC
    This is a listing of all of the Microsoft Windows resources that the
    program uses.  It includes the icons, bitmaps, and cursors that are stored
    in the RES subdirectory.  This file can be directly edited in the
    Visual C++ development environment.

RES\FCSPIN.ICO
    This is an icon file, which is used as the application's icon.  This
    icon is included by the main resource file FCSPIN.RC.

RES\FCSPIN.RC2
    This file contains resources that are not edited by the Visual C++
	development environment.  You should place all resources not
	editable by the resource editor in this file.


FCSPIN.CLW
    This file contains information used by ClassWizard to edit existing
    classes or add new classes.  ClassWizard also uses this file to store
    information needed to create and edit message maps and dialog data
    maps and to create prototype member functions.

/////////////////////////////////////////////////////////////////////////////

For the main frame window:

mainfrm.H, mainfrm.CPP
    These files contain the frame class CMainFrame, which is derived from
    CFrameWnd and controls all SDI frame features.


/////////////////////////////////////////////////////////////////////////////

AppWizard creates one document type and one view:

fcspidoc.H, fcspidoc.CPP - the document
    These files contain your CFcspinDoc class.  Edit these files to
    add your special document data and to implement file saving and loading
    (via CFcspinDoc::Serialize).

fcspivw.H, fcspivw.CPP - the view of the document
    These files contain your CFcspinView class.
    CFcspinView objects are used to view CFcspinDoc objects.
    



/////////////////////////////////////////////////////////////////////////////
Other standard files:

STDAFX.H, STDAFX.CPP
    These files are used to build a precompiled header (PCH) file
    named FCSPIN.PCH and a precompiled types file named STDAFX.OBJ.

RESOURCE.H
    This is the standard header file, which defines new resource IDs.
    Visual C++ reads and updates this file.

/////////////////////////////////////////////////////////////////////////////
Other notes:

AppWizard uses "TODO:" to indicate parts of the source code you
should add to or customize.

/////////////////////////////////////////////////////////////////////////////
