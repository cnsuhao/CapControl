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
//���๹�캯��
CListenSock::CListenSock()
{
}
//������������
CListenSock::~CListenSock()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
//ClassWizard�������Ϣӳ��(�Զ�)
#if 0
BEGIN_MESSAGE_MAP(CListenSock, CAsyncSocket)
	//{{AFX_MSG_MAP(CListenSock)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CListenSock member functions

//����OnAccept()����
void CListenSock::OnAccept(int nErrorCode) 
{
	//��ȡӦ�ó���������
	CServerPlusDlg* pDlg=(CServerPlusDlg*)::AfxGetMainWnd();
	
	if (pDlg->m_ServerStreamSock.m_hSocket==INVALID_SOCKET && nErrorCode==0)
	{
		//������������
		Accept(pDlg->m_ServerStreamSock);
		//ע�������¼�
		pDlg->m_ServerStreamSock.AsyncSelect(FD_READ | FD_WRITE);
	}
	else if(pDlg->m_ServerCtrlSock==INVALID_SOCKET && nErrorCode==0)
	{
		//������������
		Accept(pDlg->m_ServerCtrlSock);

		//ע�������¼�
		pDlg->m_ServerCtrlSock.AsyncSelect(FD_READ | FD_WRITE|FD_CONNECT);

		//���ӳɹ���׼����������
		//AfxMessageBox("User Connected,Begin transporting video image!");
        
		//���ͱ������������ʽ����Ϊ���ն˽������������ʽ
		//���������Ϣ
		SERVER_CTRL_MSG msg;
		//��ʼ��
		memset(&msg,0,sizeof(SERVER_CTRL_MSG));
		//������Ϣ����Ϊ��-��������ʽ
		strcpy(msg.strCommand,"Set Bitmap Info");
		//���ÿ�����Ϣ����
		memcpy(msg.strContent,pDlg->m_pOutInfo,sizeof(BITMAPINFO));
		//������Ϣʵ�ʴ�С
		msg.nContentUsedByte=sizeof(BITMAPINFO);

		//���ͱ������������ʽ
		pDlg->m_ServerCtrlSock.Send(&msg,sizeof(SERVER_CTRL_MSG));
        
		//���ͱ�����COMPVARS�ṹ
		//��ʼ��
		memset(&msg,0,sizeof(SERVER_CTRL_MSG));
		//���������Ϣ����Ϊ��-������COMPVARS�ṹ
		strcpy(msg.strCommand,"Set COMPVARS");
		//������Ϣʵ�ʴ�С
		msg.nContentUsedByte=sizeof(COMPVARS);
		//����
		memcpy(msg.strContent,&pDlg->m_CV,sizeof(COMPVARS));
		
		//����
		pDlg->m_ServerCtrlSock.Send(&msg,sizeof(SERVER_CTRL_MSG));

		//�������ӱ�־
		pDlg->m_bConnect=TRUE;
	}

	// TODO: Add your specialized code here and/or call the base class
	//���û����OnAccept()����
	CAsyncSocket::OnAccept(nErrorCode);
}
