//Download by http://www.NewXing.com
#if !defined(AFX_CLIENTCTRLSOCK_H__693ECEAE_889F_4799_BF7C_194B5BD2D07E__INCLUDED_)
#define AFX_CLIENTCTRLSOCK_H__693ECEAE_889F_4799_BF7C_194B5BD2D07E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ClientCtrlSock.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CClientCtrlSock command target
typedef struct _SERVER_CTRL_MSG
{
	char strCommand[100];
	DWORD nContentUsedByte;
	char strContent[1000];
}SERVER_CTRL_MSG;

class CClientCtrlSock : public CAsyncSocket
{
// Attributes
public:

// Operations
public:
	CClientCtrlSock();
	virtual ~CClientCtrlSock();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientCtrlSock)
	public:
	//重载OnConnect()函数
	virtual void OnConnect(int nErrorCode);
	//重载OnReceive()函数
	virtual void OnReceive(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CClientCtrlSock)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENTCTRLSOCK_H__693ECEAE_889F_4799_BF7C_194B5BD2D07E__INCLUDED_)
