=========================================================
       Programming the Windows 95 User Interface
                    COMPANION DISC
       COPYRIGHT (C) 1995 BY Nancy Winnick Cluts
=========================================================

This companion disc contains the sample source code and
related support files for the examples presented in
Programming the Windows 95 User Interface by Nancy Winnick
Cluts. Note that you need the Win32 SDK to compile these
programs.


		     INSTALLATION

The files on the CD-ROM are not compressed. Run the Setup
program to install the files to your hard disk. (The files
can be dragged to your hard disk using Windows Explorer,
but they will have the read-only attribute if you do so.)


             KNOWN PROBLEMS AND WORK-AROUNDS


If you build any of the MFC samples on the companion disc,
you might get the following three errors:


  error c2065: 'TCM_GETBKCOLOR' : undeclared identifer

  error c2065: 'TCM_SETBKCOLOR' : undeclared identifer

  error c2857: '#include' statement specified with the
                /Ycstdafx.h command-line option was not
                found in the source file


To get around this problem, change the target from
Win32 Release to Win32 Debug and rebuild.

You cannot break a line in a REG file, and there is no
continuation character. Long lines are broken in the book,
however, to fit on the printed page.

Instead of using the most recently registered file viewer
for a particular file type, the system might use the one
registered first. To get around this, you must unregister
all file viewers for a file type before registering the
one you want.


To unregister the file viewer from the MFCVIEW sample in
chapter 12, run:

  \Cluts\Chapter 12\Mfcview\Unreg\Windebug\Unreg.exe


To unregister user interface extensions from the samples
in chapter 13, run:

  \Cluts\Chapter 13\Ctxtmenu\Unreg\Windebug\Unreg.exe
  \Cluts\Chapter 13\Propext\Unreg\Windebug\Unreg.exe
  \Cluts\Chapter 13\Shellext\Unreg\Windebug\Unreg.exe

The Unregister programs remove the Registry entries for
the programs but do not remove the associated DLLs from
your hard disk. You can manually remove the DLLs using
Windows Explorer.


Every effort was made to ensure the accuracy of the book and
this disc.  Should you encounter a problem, please contact
us at the following address:

    Microsoft Press
    Attn: Programming the Windows 95 User Interface
    One Microsoft Way
    Redmond, WA  98052-6399

No telephone calls, please.
