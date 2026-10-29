// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (C) 1993-1995  Microsoft Corporation.  All Rights Reserved.
//
//  MODULE:   pidl.c
//
//  PURPOSE:   Helper functions for manipulating ITEMIDLISTS
//
//  FUNCTIONS:
//
//  COMMENTS:
//

#include <windows.h>            // required for all Windows applications
#include <windowsx.h>
#include <shlobj.h>
#include "globals.h"            


LPITEMIDLIST Next(LPCITEMIDLIST pidl)
{
   LPSTR lpMem=(LPSTR)pidl;

   lpMem+=pidl->mkid.cb;

   return (LPITEMIDLIST)lpMem;
}

UINT GetSize(LPCITEMIDLIST pidl)
{
    UINT cbTotal = 0;
    if (pidl)
    {
        cbTotal += sizeof(pidl->mkid.cb);       // Null terminator
        while (pidl->mkid.cb)
        {
            cbTotal += pidl->mkid.cb;
            pidl = Next(pidl);
        }
    }

    return cbTotal;
}

LPITEMIDLIST Create(UINT cbSize)
{
    LPMALLOC lpMalloc;
    HRESULT  hr;
    LPITEMIDLIST pidl=0;

    hr=SHGetMalloc(&lpMalloc);

    if (FAILED(hr))
       return 0;

    pidl=(LPITEMIDLIST)lpMalloc->lpVtbl->Alloc(lpMalloc, cbSize);

    if (pidl)
        _fmemset(pidl, 0, cbSize);      // zero-init for external task   alloc

    if (lpMalloc) lpMalloc->lpVtbl->Release(lpMalloc);

    return pidl;
}

LPITEMIDLIST ConcatPidls(LPCITEMIDLIST pidl1, LPCITEMIDLIST pidl2)
{
    LPITEMIDLIST pidlNew;
    UINT cb1;
    UINT cb2;

    if (pidl1)  //May be NULL
       cb1 = GetSize(pidl1) - sizeof(pidl1->mkid.cb);
    else
       cb1 = 0;

    cb2 = GetSize(pidl2);

    pidlNew = Create(cb1 + cb2);
    if (pidlNew)
    {
        if (pidl1)
           hmemcpy(pidlNew, pidl1, cb1);
        hmemcpy(((LPSTR)pidlNew) + cb1, pidl2, cb2);
    }
    return pidlNew;
}

LPITEMIDLIST CopyITEMID(LPMALLOC lpMalloc, LPITEMIDLIST lpi)
{
   LPITEMIDLIST lpiTemp;

   lpiTemp=(LPITEMIDLIST)lpMalloc->lpVtbl->Alloc(lpMalloc,
                                                 lpi->mkid.cb+sizeof(lpi->mkid.cb));
   CopyMemory((PVOID)lpiTemp, (CONST VOID *)lpi, lpi->mkid.cb+sizeof(lpi->mkid.cb));

   return lpiTemp;
}

BOOL GetName(LPSHELLFOLDER lpsf,
             LPITEMIDLIST  lpi,
			 DWORD         dwFlags,
             LPSTR         lpFriendlyName)
{
   BOOL   bSuccess=TRUE;
   STRRET str;

   if (NOERROR==lpsf->lpVtbl->GetDisplayNameOf(lpsf,
                                               lpi,
                                               dwFlags,
                                               &str))
   {
      switch (str.uType)
      {
         case STRRET_WSTR:

            WideCharToMultiByte(CP_ACP,                 // CodePage
                                0,		               // dwFlags
                                str.pOleStr,            // lpWideCharStr
                                -1,                     // cchWideChar
                                lpFriendlyName,         // lpMultiByteStr
                                sizeof(lpFriendlyName), // cchMultiByte,
                                NULL,                   // lpDefaultChar,
                                NULL);                  // lpUsedDefaultChar

             break;

         case STRRET_OFFSET:

             lstrcpy(lpFriendlyName, (LPSTR)lpi+str.uOffset);
             break;

         case STRRET_CSTR:
             
             lstrcpy(lpFriendlyName, (LPSTR)str.cStr);
             break;

         default:
             bSuccess = FALSE;
             break;
      }
   }
   else
      bSuccess = FALSE;

   return bSuccess;
}

LPITEMIDLIST GetFullyQualPidl(LPSHELLFOLDER lpsf, LPITEMIDLIST lpi)
{
   char szBuff[MAX_PATH];
   OLECHAR szOleChar[MAX_PATH];
   LPSHELLFOLDER lpsfDeskTop;
   LPITEMIDLIST  lpifq;
   ULONG ulEaten, ulAttribs;
   HRESULT hr;

   if (!GetName(lpsf, lpi, SHGDN_FORPARSING, szBuff))
      return NULL;

   hr=SHGetDesktopFolder(&lpsfDeskTop);

   if (FAILED(hr))
      return NULL;

   MultiByteToWideChar(CP_ACP,
					   MB_PRECOMPOSED,
					   szBuff,
					   -1,
					   szOleChar,
					   sizeof(szOleChar));

   hr=lpsfDeskTop->lpVtbl->ParseDisplayName(lpsfDeskTop,
											NULL,
											NULL,
											szOleChar,
											&ulEaten,
											&lpifq,
											&ulAttribs);

   lpsfDeskTop->lpVtbl->Release(lpsfDeskTop);

   if (FAILED(hr))
      return NULL;

   return lpifq;
}

