//Download by http://www.NewXing.com
// ClientCtrlSock.cpp : implementation file
//

#include "stdafx.h"
#include "ClientPlus.h"
#include "ClientCtrlSock.h"

#include "clientplusdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClientCtrlSock
//基类析造函数
CClientCtrlSock::CClientCtrlSock()
{
}
//基类析构函数
CClientCtrlSock::~CClientCtrlSock()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
//ClassWizard定义的消息映射(自动)
#if 0
BEGIN_MESSAGE_MAP(CClientCtrlSock, CAsyncSocket)
	//{{AFX_MSG_MAP(CClientCtrlSock)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CClientCtrlSock member functions

//重载OnConnect()函数
void CClientCtrlSock::OnConnect(int nErrorCode) 
{
	//成功连接
	if (nErrorCode==0)
	{
		AfxMessageBox("Success in connecting Server!");
	}

	//连接失败
	else
	{
		AfxMessageBox("can't connected to Server!");
	}
	// TODO: Add your specialized code here and/or call the base class
	
	//调用基类OnConnect()函数
	CAsyncSocket::OnConnect(nErrorCode);
}

//重载OnReceive()函数
void CClientCtrlSock::OnReceive(int nErrorCode) 
{
	//获得应用程序主窗口
	CClientPlusDlg* pDlg=(CClientPlusDlg*)::AfxGetMainWnd();

	//服务控制信息
	SERVER_CTRL_MSG msg;

	//初始化服务控制信息
	memset(&msg,0,sizeof(SERVER_CTRL_MSG));

	//从缓存中接收服务控制信息
	Receive(&msg,sizeof(SERVER_CTRL_MSG));

	//解码
	pDlg->ExcuteServerCommand(msg);
	// TODO: Add your specialized code here and/or call the base class

	//调用基类OnReceive()函数
	CAsyncSocket::OnReceive(nErrorCode);
}
