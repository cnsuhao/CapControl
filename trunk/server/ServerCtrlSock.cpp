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
//���๹�캯��
CServerCtrlSock::CServerCtrlSock()
{
}
//�������캯��
CServerCtrlSock::~CServerCtrlSock()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
//ClassWizard�������Ϣӳ��(�Զ�)
#if 0
BEGIN_MESSAGE_MAP(CServerCtrlSock, CAsyncSocket)
	//{{AFX_MSG_MAP(CServerCtrlSock)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CServerCtrlSock member functions

//����OnConnect()����
void CServerCtrlSock::OnConnect(int nErrorCode) 
{
	//��ȡӦ�ó���������
	CServerPlusDlg* pDlg=(CServerPlusDlg*)::AfxGetMainWnd();

	// TODO: Add your specialized code here and/or call the base class
	//���û����OnConnect()����
	CAsyncSocket::OnConnect(nErrorCode);
}
