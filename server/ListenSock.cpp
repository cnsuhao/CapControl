//Download by http://www.NewXing.com
// ListenSock.cpp : implementation file
//

#include "stdafx.h"
#include "ServerPlus.h"
#include "ListenSock.h"

#include "ServerPlusDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListenSock
//基类构造函数
CListenSock::CListenSock()
{
}
//基类析构函数
CListenSock::~CListenSock()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
//ClassWizard定义的消息映射(自动)
#if 0
BEGIN_MESSAGE_MAP(CListenSock, CAsyncSocket)
	//{{AFX_MSG_MAP(CListenSock)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CListenSock member functions

//重载OnAccept()函数
void CListenSock::OnAccept(int nErrorCode) 
{
	//获取应用程序主窗口
	CServerPlusDlg* pDlg=(CServerPlusDlg*)::AfxGetMainWnd();
	
	if (pDlg->m_ServerStreamSock.m_hSocket==INVALID_SOCKET && nErrorCode==0)
	{
		//接受连接请求
		Accept(pDlg->m_ServerStreamSock);
		//注册网络事件
		pDlg->m_ServerStreamSock.AsyncSelect(FD_READ | FD_WRITE);
	}
	else if(pDlg->m_ServerCtrlSock==INVALID_SOCKET && nErrorCode==0)
	{
		//接受连接请求
		Accept(pDlg->m_ServerCtrlSock);

		//注册网络事件
		pDlg->m_ServerCtrlSock.AsyncSelect(FD_READ | FD_WRITE|FD_CONNECT);

		//连接成功，准备发送数据
		//AfxMessageBox("User Connected,Begin transporting video image!");
        
		//发送编码器的输出格式以作为接收端解码器的输入格式
		//服务控制信息
		SERVER_CTRL_MSG msg;
		//初始化
		memset(&msg,0,sizeof(SERVER_CTRL_MSG));
		//控制信息类型为编-解码器格式
		strcpy(msg.strCommand,"Set Bitmap Info");
		//设置控制信息内容
		memcpy(msg.strContent,pDlg->m_pOutInfo,sizeof(BITMAPINFO));
		//控制信息实际大小
		msg.nContentUsedByte=sizeof(BITMAPINFO);

		//发送编码器的输出格式
		pDlg->m_ServerCtrlSock.Send(&msg,sizeof(SERVER_CTRL_MSG));
        
		//发送编码器COMPVARS结构
		//初始化
		memset(&msg,0,sizeof(SERVER_CTRL_MSG));
		//服务控制信息类型为编-解码器COMPVARS结构
		strcpy(msg.strCommand,"Set COMPVARS");
		//控制信息实际大小
		msg.nContentUsedByte=sizeof(COMPVARS);
		//复制
		memcpy(msg.strContent,&pDlg->m_CV,sizeof(COMPVARS));
		
		//发送
		pDlg->m_ServerCtrlSock.Send(&msg,sizeof(SERVER_CTRL_MSG));

		//设置连接标志
		pDlg->m_bConnect=TRUE;
	}

	// TODO: Add your specialized code here and/or call the base class
	//调用基类的OnAccept()函数
	CAsyncSocket::OnAccept(nErrorCode);
}
