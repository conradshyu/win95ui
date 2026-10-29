/*************************************************************************\
*
*  PROGRAM: UNREG - To unregister samples.
*  COMMENTS:
*
\*************************************************************************/


#include <windows.h>

int APIENTRY WinMain (HINSTANCE hInstance,
                      HINSTANCE hPrevInstance,
                      LPSTR     lpCmdLine,
                      int       nCmdShow)


{

    // Remove the CLSID registry entries:
    // HKEY_CLASSES_ROOT\CLSID\{87b9bd00-c65c-11cd-a259-00dd010e8c28}\InProcServer32
    RegDeleteKey(HKEY_CLASSES_ROOT, "CLSID\\{87b9bd00-c65c-11cd-a259-00dd010e8c28}");

    // Remove the GAK extension entry:
    // HKEY_CLASSES_ROOT\.gak
    RegDeleteKey(HKEY_CLASSES_ROOT, ".gak");

    //
    // Remove the shell extension registry entries.
    //
    RegDeleteKey(HKEY_CLASSES_ROOT, "GAKFile");

    //
    // Remove the first copy hook handler entry:
    // HKEY_CLASSES_ROOT\directory\shellex\CopyHookHandlers\GAKsCopyHook
    //
    RegDeleteKey(HKEY_CLASSES_ROOT, "directory\\shellex\\CopyHookHandlers\\GAKsCopyHook");

    //
    // Remove the second copy hook handler entry:
    // HKEY_CLASSES_ROOT\*\shellex\CopyHookHandlers\GAKsCopyHook
    //
    RegDeleteKey(HKEY_CLASSES_ROOT, "*\\shellex\\CopyHookHandlers\\GAKsCopyHook");

    return 1;
}
