// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (C) 1993-1995  Microsoft Corporation.  All Rights Reserved.
//
//  MODULE:   dragdrop.cpp
//
//  PURPOSE:  
//
//  FUNCTIONS:
//
//    
//  COMMENTS:
//

#include <windows.h>            // required for all Windows applications
#include <windowsx.h>
#include <commctrl.h>           // TreeView declarations live here
#include <shlobj.h>
#include "globals.h"            // prototypes specific to this application
#include "dragdrop.h"


//---------------------------------------------------------------------
//                    IUnknown Methods
//---------------------------------------------------------------------


STDMETHODIMP CDropSource::QueryInterface(REFIID iid, void FAR* FAR* ppv) 
{
    OutputDebugString("CDropSource::QueryInterface\r\n");

    if(iid == IID_IUnknown || iid == IID_IDropSource)
    {
      *ppv = this;
      ++m_refs;
      return NOERROR;
    }
    *ppv = NULL;

    return E_NOINTERFACE;
}


STDMETHODIMP_(ULONG) CDropSource::AddRef(void)
{
    OutputDebugString("CDropSource::AddRef\r\n");

    return ++m_refs;
}


STDMETHODIMP_(ULONG) CDropSource::Release(void)
{
    OutputDebugString("CDropSource::Release\r\n");

    if(--m_refs == 0)
    {
      delete this;
      return 0;
    }
    return m_refs;
}  

//---------------------------------------------------------------------
//                    CDropSource Constructor
//---------------------------------------------------------------------        
 
CDropSource::CDropSource()
{
    m_refs = 1;  
}

//---------------------------------------------------------------------
//                    IDropSource Methods
//---------------------------------------------------------------------  

STDMETHODIMP CDropSource::QueryContinueDrag(BOOL fEscapePressed, 
                                            DWORD grfKeyState)
{  
    OutputDebugString("CDropSource::QueryContinueDrag\r\n");

    if (fEscapePressed)
        return DRAGDROP_S_CANCEL;
    else if (!(grfKeyState & MK_LBUTTON) && !(grfKeyState & MK_RBUTTON))
        return DRAGDROP_S_DROP;
    else
        return NOERROR;                  
}

STDMETHODIMP CDropSource::GiveFeedback(DWORD dwEffect)
{
    OutputDebugString("CDropSource::GiveFeedback\r\n");

    return DRAGDROP_S_USEDEFAULTCURSORS;
}


extern "C" {
LPDROPSOURCE CreateDropSource(void)
{
   return ((LPDROPSOURCE) new CDropSource);
}
}