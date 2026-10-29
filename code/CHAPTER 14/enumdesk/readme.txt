ENUMDESK - Based on Gen32

THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1993-1995  Microsoft Corporation.  All Rights Reserved.

PURPOSE:
    Show how to create and fill a TreeView control with a
    hierarchical list of items.  In this example, the file name
    space is enumerated, using the IShellFolder interface.
    Show how to use the ImageList in conjunction with the
    TreeView control.  In this example, we simply ask the system
    for a copy of the system image list, and associate that with
    our treeview an listview.

USES:
    Based on Gen32

COMMENTS:
    This is a 32-bit only sample.

MODULE MAP:
    Dispatch         - Message dispatching routines
    WinMain          - Calls initialization functions and processes 
                       the message loop
    Generic          - Implements the windows procedure for the main 
                       application window
    Init             - Performs application and instance specific 
                       initialization
    About            - Defines a standard about dialog box.
    Misc             - Defines the applications specific commands 
                       not related to a specific module.
