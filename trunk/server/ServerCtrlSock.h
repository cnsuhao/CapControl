//Download by http://www.NewXing.com
#if !defined(AFX_SERVERCTRLSOCK_H__B1F9977B_1E17_45DE_8789_12243DA7ABC4__INCLUDED_)
#define AFX_SERVERCTRLSOCK_H__B1F9977B_1E17_45DE_8789_12243DA7ABC4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ServerCtrlSock.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CServerCtrlSock command target


class CServerCtrlSock : public CAsyncSocket
{
// Attributes
public:

// Operations
public:
	CServerCtrlSock();
	virtual ~CServerCtrlSock();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CServerCtrlSock)
	public:
	//ÖØÔØOnConnect()º¯Êý
	virtual void OnConnect(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CServerCtrlSock)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERVERCTRLSOCK_H__B1F9977B_1E17_45DE_8789_12243DA7ABC4__INCLUDED_)
