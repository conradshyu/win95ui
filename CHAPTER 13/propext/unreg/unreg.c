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
    // Try opening the registry key:
    //HKEY_CLASSES_ROOT\CLSID\{771a9da0-731a-11ce-993c-00aa004adb6c}\InprocServer32
    RegDeleteKey(HKEY_CLASSES_ROOT, "CLSID\\{771a9da0-731a-11ce-993c-00aa004adb6c}");

    // Now delete the following key:
    // HKEY_CLASSES_ROOT\NWCFile\shellex\PropertySheetHandlers\NWCPage
    RegDeleteKey(HKEY_CLASSES_ROOT, "NWCFile");

    // Delete the key:
    // HKEY_CLASSES_ROOT\*\shellex\PropertySheetHandlers\NWCPage
    RegDeleteKey(HKEY_CLASSES_ROOT, "*\\shellex\\PropertySheetHandlers\\NWCPage");
    
    return 1;
}
