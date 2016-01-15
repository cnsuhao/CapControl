//Download by http://www.NewXing.com
#if !defined(AFX_CLIENTSTREAMSOCK_H__EC94F69F_11BE_48DD_B2EF_2F5D569B9F6C__INCLUDED_)
#define AFX_CLIENTSTREAMSOCK_H__EC94F69F_11BE_48DD_B2EF_2F5D569B9F6C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ClientStreamSock.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CClientStreamSock command target
#define MAPBUFSIZE	24576
typedef struct _VIDEO_DATA
{
	BOOL bKeyFrame;
	DWORD nSampleNum;
	DWORD nUsedSize;
	BYTE Buf[MAPBUFSIZE];
}VIDEO_DATA;

class CClientStreamSock : public CAsyncSocket
{
// Attributes
public:

// Operations
public:
	CClientStreamSock();
	virtual ~CClientStreamSock();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientStreamSock)
	public:
	//重载OnConnect()函数，通知套接字已经完成连接
	virtual void OnConnect(int nErrorCode);
	//重载OnReceive()函数，通知套接字调用Receive()函数接收数据
	virtual void OnReceive(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CClientStreamSock)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENTSTREAMSOCK_H__EC94F69F_11BE_48DD_B2EF_2F5D569B9F6C__INCLUDED_)
