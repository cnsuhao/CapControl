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
//���๹�캯��
CClientStreamSock::CClientStreamSock()
{
}
//������������
CClientStreamSock::~CClientStreamSock()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
//ClassWizard�������Ϣӳ��(�Զ�)
#if 0
BEGIN_MESSAGE_MAP(CClientStreamSock, CAsyncSocket)
	//{{AFX_MSG_MAP(CClientStreamSock)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CClientStreamSock member functions

//����OnConnect()����
void CClientStreamSock::OnConnect(int nErrorCode) 
{
	//���Ӧ�ó���������
	CClientPlusDlg* pDlg=(CClientPlusDlg*)::AfxGetMainWnd();

	//����
	if (nErrorCode==0)
	{
		//����
		pDlg->m_ClientCtrlSock.Connect(pDlg->m_strIPAddr,5555);
	}

	//����
	else
	{
		AfxMessageBox("can't connect to server!");
	}

	// TODO: Add your specialized code here and/or call the base class
	//���û���OnConnect()����
	CAsyncSocket::OnConnect(nErrorCode);
}

//����OnReceive()����
void CClientStreamSock::OnReceive(int nErrorCode) 
{
	//���Ӧ�ó���������
	CClientPlusDlg* pDlg=(CClientPlusDlg*)::AfxGetMainWnd();

	//��Ž��յ�������
	VIDEO_DATA VideoData;

	//��ʼ��
	memset(&VideoData,0,sizeof(VIDEO_DATA));

	//����Receive()���ջ����е�����
	Receive(&VideoData,sizeof(VIDEO_DATA));
	
	//���ݴ�С����
    if (VideoData.nUsedSize>0 && VideoData.nUsedSize<MAPBUFSIZE)
	{
		DWORD Result;
		//����ICDecompress()��ѹ��
		if (VideoData.bKeyFrame)
		{
			//����ǹؼ�֡
			Result=ICDecompress(pDlg->m_CV.hic,0,
				&pDlg->m_InInfo.bmiHeader,VideoData.Buf,
				&pDlg->m_pOutInfo->bmiHeader,pDlg->m_pOutBuf);
		} 
		else
		{
			//�������ͨ֡
			Result=ICDecompress(pDlg->m_CV.hic,ICDECOMPRESS_NOTKEYFRAME,
				&pDlg->m_InInfo.bmiHeader,VideoData.Buf,
				&pDlg->m_pOutInfo->bmiHeader,pDlg->m_pOutBuf);
		}


		//��ѹ�ɹ�
		if (Result==ICERR_OK)
		{
			//��ȡ�豸������
			CDC* pDC=pDlg->GetDC();

			//ֱ������ʾ������ʾλͼ
			if(!SetDIBitsToDevice(
				pDC->GetSafeHdc(),0,0,
				pDlg->m_pOutInfo->bmiHeader.biWidth,
				pDlg->m_pOutInfo->bmiHeader.biHeight,0,0,0,
				pDlg->m_pOutInfo->bmiHeader.biHeight,
				pDlg->m_pOutBuf,pDlg->m_pOutInfo,DIB_RGB_COLORS))
			{
				//��ʾʧ��
				return; 
			}
		}
	}

	// TODO: Add your specialized code here and/or call the base class	
	//���û����OnReceive()����
	CAsyncSocket::OnReceive(nErrorCode);
}
