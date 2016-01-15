//Download by http://www.NewXing.com
// ClientPlusDlg.h : header file
//

#if !defined(AFX_CLIENTPLUSDLG_H__2B0FA4C0_27A9_4E5E_9B47_08E1820E883C__INCLUDED_)
#define AFX_CLIENTPLUSDLG_H__2B0FA4C0_27A9_4E5E_9B47_08E1820E883C__INCLUDED_

#include "ClientStreamSock.h"	// Added by ClassView
#include "ClientCtrlSock.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CClientPlusDlg dialog
#include "vfw.h"
#pragma comment(lib,"vfw32.lib")
class CClientPlusDlg : public CDialog
{
// Construction
public:
	
	//解码器输出缓存
	BYTE* m_pOutBuf;

	//解码器输出缓存大小
	DWORD m_OutBufSize;

	//解码器输入格式
	BITMAPINFO m_InInfo;

	//解码器输出格式
	BITMAPINFO* m_pOutInfo;

	//解码器输出格式大小
	long m_OutFormatSize;

	//解码器设置COMPVARS结构
	COMPVARS m_CV;

	//CClientCtrlSock类型套接字
	CClientCtrlSock m_ClientCtrlSock;

	//服务端IP地址
	CString m_strIPAddr;

	//CClientStreamSock类型套接字
	CClientStreamSock m_ClientStreamSock;

	//注销解码器
	void UnInitDecompressor();

	//解码
	void ExcuteServerCommand(SERVER_CTRL_MSG msg);

	//初始化网络
	void InitNetWork();

	//显示位图
	void ShowImage(BYTE* Buf);

	//标准构造函数
	CClientPlusDlg(CWnd* pParent = NULL);	

// Dialog Data
	//{{AFX_DATA(CClientPlusDlg)
	enum { IDD = IDD_CLIENTPLUS_DIALOG };
	CStatic	m_Image;
	CIPAddressCtrl	m_IPCtrl;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientPlusDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CClientPlusDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENTPLUSDLG_H__2B0FA4C0_27A9_4E5E_9B47_08E1820E883C__INCLUDED_)
