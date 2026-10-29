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
    HKEY hCR;

    // Delete the registry key:
    // HKEY_CLASSES_ROOT\CLSID\{5fbcd2e0-73dd-11ce-993c-00aa004adb6c}\InProcServer32
    RegDeleteKey(HKEY_CLASSES_ROOT, "CLSID\\{5fbcd2e0-73dd-11ce-993c-00aa004adb6c}");

    // Delete the registry key:
    // [HKEY_CLASSES_ROOT\*\shellex\ContextMenuHandlers\NWCMenu]
    RegDeleteKey(HKEY_CLASSES_ROOT, "*\\shellex\\ContextMenuHandlers\\NWCMenu");

    if (RegOpenKey(HKEY_CLASSES_ROOT, "*", &hCR) == ERROR_SUCCESS)
    {
        HKEY hShell;
        if (RegOpenKey(hCR, "shellex", &hShell) == ERROR_SUCCESS)
        {
            HKEY hCtxt;
            if (RegOpenKey(hShell, "ContextMenuHandlers", &hCtxt) == ERROR_SUCCESS)
            {
                RegDeleteValue(hCtxt, "NWCMenu");
                RegCloseKey(hCtxt);
            }
            RegCloseKey(hShell);
        }
        RegCloseKey(hCR);
    }

    return 1;
}
