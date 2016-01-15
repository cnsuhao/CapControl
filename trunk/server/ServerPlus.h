//Download by http://www.NewXing.com
// ServerPlus.h : main header file for the SERVERPLUS application
//

#if !defined(AFX_SERVERPLUS_H__2FE98DCC_F8EB_4FBD_9E92_BD3AAFD05684__INCLUDED_)
#define AFX_SERVERPLUS_H__2FE98DCC_F8EB_4FBD_9E92_BD3AAFD05684__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CServerPlusApp:
// See ServerPlus.cpp for the implementation of this class
//

class CServerPlusApp : public CWinApp
{
public:
	CServerPlusApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CServerPlusApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CServerPlusApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERVERPLUS_H__2FE98DCC_F8EB_4FBD_9E92_BD3AAFD05684__INCLUDED_)
