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

    // Delete the key
    // HKEY_CLASSES_ROOT\QuickView\.TXT\{e83b63c0-6ff5-11ce-993c-00aa004adb6c}
    RegDeleteKey(HKEY_CLASSES_ROOT, "QuickView\\.TXT\\{e83b63c0-6ff5-11ce-993c-00aa004adb6c}");

    // Now delete the key
    // HKEY_CLASSES_ROOT\CLSID\{e83b63c0-6ff5-11ce-993c-00aa004adb6c}
    RegDeleteKey(HKEY_CLASSES_ROOT, "CLSID\\{e83b63c0-6ff5-11ce-993c-00aa004adb6c}");

    // Delete the following value:
    // HKEY_CLASSES_ROOT\txtfile\CLSID  =  {e83b63c0-6ff5-11ce-993c-00aa004adb6c}
    if (RegOpenKey(HKEY_CLASSES_ROOT, "txtfile", &hCR) == ERROR_SUCCESS) 
    {
	    HKEY hCLSID;
        if (RegOpenKey(hCR, "CLSID", &hCLSID) == ERROR_SUCCESS)
        {
             RegDeleteValue(hCLSID, "{e83b63c0-6ff5-11ce-993c-00aa004adb6c}");
             RegCloseKey(hCLSID);
        }
        RegCloseKey(hCR);
    }

    return 1;
}
