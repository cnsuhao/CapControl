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
//控制信息
typedef struct _SERVER_CTRL_MSG
{
	//控制信息类型
	char strCommand[100];
	//实际使用大小
	DWORD nContentUsedByte;
	//控制信息内容
	char strContent[1000];
}SERVER_CTRL_MSG;

#define MAPBUFSIZE	24576
//视频数据
typedef struct _VIDEO_DATA
{
	//是否关键帧
	BOOL bKeyFrame;
	//视频帧序号
	DWORD nSampleNum;
	//视频帧实际大小
	DWORD nUsedSize;
	//缓存
	BYTE Buf[MAPBUFSIZE];
}VIDEO_DATA;

class CServerPlusDlg : public CDialog
{
// Construction
public:
	//是否连接
	BOOL m_bConnect;

	//实际发送的视频帧数目
	DWORD m_SampleNum;

	//CServerCtrlSock类型套接字
	CServerCtrlSock m_ServerCtrlSock;

	//CServerStreamSock类型套接字
	CServerStreamSock m_ServerStreamSock;

	//CListenSock类型套接字
	CListenSock m_ListenSock;

	//捕获窗口句柄
	HWND m_hWndCapture;

	//编码器输出格式大小
	DWORD m_OutFormatSize;

	//编码器输出缓存大小
	DWORD m_OutBufferSize;

	//编码器输出实际尺寸
	long m_OutActSize;

	//编码器输入格式
	BITMAPINFO m_InInfo;

	//编码器输出格式
	BITMAPINFO *m_pOutInfo;

	//描述编码器设置
	COMPVARS m_CV;
	
	//初始化网络
	void InitNetWork();

	//设置位图的BITMAPINFOHEADER结构
	void FillBitmapStruct();

	//编码压缩并发送
	void CompressFrame(LPVIDEOHDR lpVHdr);

	//帧采集回调函数
	static LRESULT CALLBACK FrameCallBack(HWND hWnd,LPVIDEOHDR lpVHdr);

	//初始化视频采集设备
	void InitVideoCard();

	//初始化编码器
	void InitCompressor();

	//使视频采集设备无效
	void UnInitVideoCard();

	//使编码器无效
	void UnInitCompressor();
	
	//标准构造函数
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
