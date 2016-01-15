//Download by http://www.NewXing.com
// ClientPlus.h : main header file for the CLIENTPLUS application
//

#if !defined(AFX_CLIENTPLUS_H__E5192907_3302_4758_84AC_E93AA5E35715__INCLUDED_)
#define AFX_CLIENTPLUS_H__E5192907_3302_4758_84AC_E93AA5E35715__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CClientPlusApp:
// See ClientPlus.cpp for the implementation of this class
//

class CClientPlusApp : public CWinApp
{
public:
	CClientPlusApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientPlusApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CClientPlusApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENTPLUS_H__E5192907_3302_4758_84AC_E93AA5E35715__INCLUDED_)
