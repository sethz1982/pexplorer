// PExplorer.h : main header file for the PEXPLORER application
//

#if !defined(AFX_PEXPLORER_H__36BC2574_535C_4D53_A884_98D3BE07154E__INCLUDED_)
#define AFX_PEXPLORER_H__36BC2574_535C_4D53_A884_98D3BE07154E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CPExplorerApp:
// See PExplorer.cpp for the implementation of this class
//

class CPExplorerApp : public CWinApp
{
public:
	CPExplorerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPExplorerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CPExplorerApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PEXPLORER_H__36BC2574_535C_4D53_A884_98D3BE07154E__INCLUDED_)