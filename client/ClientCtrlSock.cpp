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
//�������캯��
CClientCtrlSock::CClientCtrlSock()
{
}
//������������
CClientCtrlSock::~CClientCtrlSock()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
//ClassWizard�������Ϣӳ��(�Զ�)
#if 0
BEGIN_MESSAGE_MAP(CClientCtrlSock, CAsyncSocket)
	//{{AFX_MSG_MAP(CClientCtrlSock)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CClientCtrlSock member functions

//����OnConnect()����
void CClientCtrlSock::OnConnect(int nErrorCode) 
{
	//�ɹ�����
	if (nErrorCode==0)
	{
		AfxMessageBox("Success in connecting Server!");
	}

	//����ʧ��
	else
	{
		AfxMessageBox("can't connected to Server!");
	}
	// TODO: Add your specialized code here and/or call the base class
	
	//���û���OnConnect()����
	CAsyncSocket::OnConnect(nErrorCode);
}

//����OnReceive()����
void CClientCtrlSock::OnReceive(int nErrorCode) 
{
	//���Ӧ�ó���������
	CClientPlusDlg* pDlg=(CClientPlusDlg*)::AfxGetMainWnd();

	//���������Ϣ
	SERVER_CTRL_MSG msg;

	//��ʼ�����������Ϣ
	memset(&msg,0,sizeof(SERVER_CTRL_MSG));

	//�ӻ����н��շ��������Ϣ
	Receive(&msg,sizeof(SERVER_CTRL_MSG));

	//����
	pDlg->ExcuteServerCommand(msg);
	// TODO: Add your specialized code here and/or call the base class

	//���û���OnReceive()����
	CAsyncSocket::OnReceive(nErrorCode);
}
