//Download by http://www.NewXing.com
// ClientStreamSock.cpp : implementation file
//

#include "stdafx.h"
#include "ClientPlus.h"
#include "ClientStreamSock.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "ClientPlusdlg.h"
/////////////////////////////////////////////////////////////////////////////
// CClientStreamSock
//基类构造函数
CClientStreamSock::CClientStreamSock()
{
}
//基类析构函数
CClientStreamSock::~CClientStreamSock()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
//ClassWizard定义的消息映射(自动)
#if 0
BEGIN_MESSAGE_MAP(CClientStreamSock, CAsyncSocket)
	//{{AFX_MSG_MAP(CClientStreamSock)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CClientStreamSock member functions

//重载OnConnect()函数
void CClientStreamSock::OnConnect(int nErrorCode) 
{
	//获得应用程序主窗口
	CClientPlusDlg* pDlg=(CClientPlusDlg*)::AfxGetMainWnd();

	//正常
	if (nErrorCode==0)
	{
		//连接
		pDlg->m_ClientCtrlSock.Connect(pDlg->m_strIPAddr,5555);
	}

	//出错
	else
	{
		AfxMessageBox("can't connect to server!");
	}

	// TODO: Add your specialized code here and/or call the base class
	//调用基类OnConnect()函数
	CAsyncSocket::OnConnect(nErrorCode);
}

//重载OnReceive()函数
void CClientStreamSock::OnReceive(int nErrorCode) 
{
	//获得应用程序主窗口
	CClientPlusDlg* pDlg=(CClientPlusDlg*)::AfxGetMainWnd();

	//存放接收到的数据
	VIDEO_DATA VideoData;

	//初始化
	memset(&VideoData,0,sizeof(VIDEO_DATA));

	//调用Receive()接收缓存中的数据
	Receive(&VideoData,sizeof(VIDEO_DATA));
	
	//数据大小合适
    if (VideoData.nUsedSize>0 && VideoData.nUsedSize<MAPBUFSIZE)
	{
		DWORD Result;
		//调用ICDecompress()解压缩
		if (VideoData.bKeyFrame)
		{
			//如果是关键帧
			Result=ICDecompress(pDlg->m_CV.hic,0,
				&pDlg->m_InInfo.bmiHeader,VideoData.Buf,
				&pDlg->m_pOutInfo->bmiHeader,pDlg->m_pOutBuf);
		} 
		else
		{
			//如果是普通帧
			Result=ICDecompress(pDlg->m_CV.hic,ICDECOMPRESS_NOTKEYFRAME,
				&pDlg->m_InInfo.bmiHeader,VideoData.Buf,
				&pDlg->m_pOutInfo->bmiHeader,pDlg->m_pOutBuf);
		}


		//解压成功
		if (Result==ICERR_OK)
		{
			//获取设备上下文
			CDC* pDC=pDlg->GetDC();

			//直接在显示器上显示位图
			if(!SetDIBitsToDevice(
				pDC->GetSafeHdc(),0,0,
				pDlg->m_pOutInfo->bmiHeader.biWidth,
				pDlg->m_pOutInfo->bmiHeader.biHeight,0,0,0,
				pDlg->m_pOutInfo->bmiHeader.biHeight,
				pDlg->m_pOutBuf,pDlg->m_pOutInfo,DIB_RGB_COLORS))
			{
				//显示失败
				return; 
			}
		}
	}

	// TODO: Add your specialized code here and/or call the base class	
	//调用基类的OnReceive()函数
	CAsyncSocket::OnReceive(nErrorCode);
}
