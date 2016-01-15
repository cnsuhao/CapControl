//Download by http://www.NewXing.com
// ServerPlusDlg.h : header file
//

#if !defined(AFX_SERVERPLUSDLG_H__2C96A858_E660_457A_9A4B_6A44617043C1__INCLUDED_)
#define AFX_SERVERPLUSDLG_H__2C96A858_E660_457A_9A4B_6A44617043C1__INCLUDED_

#include "ServerCtrlSock.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CServerPlusDlg dialog
#include "vfw.h"
#include "ListenSock.h"	// Added by ClassView
#include "ServerStreamSock.h"	// Added by ClassView
#pragma comment(lib,"vfw32.lib")
//������Ϣ
typedef struct _SERVER_CTRL_MSG
{
	//������Ϣ����
	char strCommand[100];
	//ʵ��ʹ�ô�С
	DWORD nContentUsedByte;
	//������Ϣ����
	char strContent[1000];
}SERVER_CTRL_MSG;

#define MAPBUFSIZE	24576
//��Ƶ����
typedef struct _VIDEO_DATA
{
	//�Ƿ�ؼ�֡
	BOOL bKeyFrame;
	//��Ƶ֡���
	DWORD nSampleNum;
	//��Ƶ֡ʵ�ʴ�С
	DWORD nUsedSize;
	//����
	BYTE Buf[MAPBUFSIZE];
}VIDEO_DATA;

class CServerPlusDlg : public CDialog
{
// Construction
public:
	//�Ƿ�����
	BOOL m_bConnect;

	//ʵ�ʷ��͵���Ƶ֡��Ŀ
	DWORD m_SampleNum;

	//CServerCtrlSock�����׽���
	CServerCtrlSock m_ServerCtrlSock;

	//CServerStreamSock�����׽���
	CServerStreamSock m_ServerStreamSock;

	//CListenSock�����׽���
	CListenSock m_ListenSock;

	//���񴰿ھ��
	HWND m_hWndCapture;

	//�����������ʽ��С
	DWORD m_OutFormatSize;

	//��������������С
	DWORD m_OutBufferSize;

	//���������ʵ�ʳߴ�
	long m_OutActSize;

	//�����������ʽ
	BITMAPINFO m_InInfo;

	//�����������ʽ
	BITMAPINFO *m_pOutInfo;

	//��������������
	COMPVARS m_CV;
	
	//��ʼ������
	void InitNetWork();

	//����λͼ��BITMAPINFOHEADER�ṹ
	void FillBitmapStruct();

	//����ѹ��������
	void CompressFrame(LPVIDEOHDR lpVHdr);

	//֡�ɼ��ص�����
	static LRESULT CALLBACK FrameCallBack(HWND hWnd,LPVIDEOHDR lpVHdr);

	//��ʼ����Ƶ�ɼ��豸
	void InitVideoCard();

	//��ʼ��������
	void InitCompressor();

	//ʹ��Ƶ�ɼ��豸��Ч
	void UnInitVideoCard();

	//ʹ��������Ч
	void UnInitCompressor();
	
	//��׼���캯��
	CServerPlusDlg(CWnd* pParent = NULL);

// Dialog Data
	//{{AFX_DATA(CServerPlusDlg)
	enum { IDD = IDD_SERVERPLUS_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CServerPlusDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CServerPlusDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERVERPLUSDLG_H__2C96A858_E660_457A_9A4B_6A44617043C1__INCLUDED_)
