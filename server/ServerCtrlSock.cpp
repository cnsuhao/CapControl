//Download by http://www.NewXing.com
// ServerCtrlSock.cpp : implementation file
//

#include "stdafx.h"
#include "ServerPlus.h"
#include "ServerCtrlSock.h"

#include "ServerPlusdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CServerCtrlSock
//基类构造函数
CServerCtrlSock::CServerCtrlSock()
{
}
//基类析造函数
CServerCtrlSock::~CServerCtrlSock()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
//ClassWizard定义的消息映射(自动)
#if 0
BEGIN_MESSAGE_MAP(CServerCtrlSock, CAsyncSocket)
	//{{AFX_MSG_MAP(CServerCtrlSock)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CServerCtrlSock member functions

//重载OnConnect()函数
void CServerCtrlSock::OnConnect(int nErrorCode) 
{
	//获取应用程序主窗口
	CServerPlusDlg* pDlg=(CServerPlusDlg*)::AfxGetMainWnd();

	// TODO: Add your specialized code here and/or call the base class
	//调用基类的OnConnect()函数
	CAsyncSocket::OnConnect(nErrorCode);
}
