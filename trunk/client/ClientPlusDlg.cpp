//Download by http://www.NewXing.com
// ClientPlusDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ClientPlus.h"
#include "ClientPlusDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClientPlusDlg dialog

CClientPlusDlg::CClientPlusDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CClientPlusDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CClientPlusDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CClientPlusDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CClientPlusDlg)
	DDX_Control(pDX, IDC_STATIC_IMAGE, m_Image);
	DDX_Control(pDX, IDC_IPADDRESS1, m_IPCtrl);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CClientPlusDlg, CDialog)
	//{{AFX_MSG_MAP(CClientPlusDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_WM_DESTROY()//注销窗口
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClientPlusDlg message handlers

BOOL CClientPlusDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// 保证IDM_ABOUTBOX在有效的系统命令范围内
	//若ASSERT()内的表达式不成立，则终止程序
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	//初始化网络
	this->InitNetWork();
	//返回
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CClientPlusDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CClientPlusDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CClientPlusDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

//初始化网络
void CClientPlusDlg::InitNetWork()
{
	//初始化socket
	::AfxSocketInit();

	//创建CClientStreamSock类型套接字
	this->m_ClientStreamSock.Create(0,SOCK_STREAM,FD_CONNECT|FD_READ|FD_WRITE);

	//创建CClientStrSock类型套接字
	this->m_ClientCtrlSock.Create(0,SOCK_STREAM,FD_CONNECT|FD_READ|FD_WRITE);
}

//按钮单击响应函数
void CClientPlusDlg::OnButton1() 
{
	//IP地址的4个字段
	BYTE Field0,Field1,Field2,Field3;

	//返回非0的IP字段
	int NonBlank=this->m_IPCtrl.GetAddress(Field0,Field1,Field2,Field3);

	//非法IP地址
	if (NonBlank!=4)
	{
		//报错
		MessageBox("Please enter the complete IP Address!");

		//返回
		return;
	}

	//取得IP地址
	m_strIPAddr.Format("%d.%d.%d.%d",Field0,Field1,Field2,Field3);

	//尝试连接服务端
	this->m_ClientStreamSock.Connect(m_strIPAddr,5555);
}

//解码
void CClientPlusDlg::ExcuteServerCommand(SERVER_CTRL_MSG msg)
{
	//位图信息
	if (strcmp(msg.strCommand,"Set Bitmap Info")==0)
	{
		memcpy(&m_InInfo,msg.strContent,sizeof(BITMAPINFO));
	}

	//编-解码器设置信息
	if (strcmp(msg.strCommand,"Set COMPVARS")==0)
	{
		//复制解码器设置信息
		memcpy(&this->m_CV,msg.strContent,sizeof(COMPVARS));
		
		//打开解码器
		m_CV.hic=ICOpen(m_CV.fccType,m_CV.fccHandler,ICMODE_DECOMPRESS);

		//打开失败
		if (m_CV.hic==NULL)
		{
			//提示
			MessageBox("please install the proper decompressor!");

			//返回
			return;
		}

		//打开成功
		else
		{
			//设置解码数据输出格式的大小
		    this->m_OutFormatSize=ICDecompressGetFormatSize(
				this->m_CV.hic,&this->m_InInfo.bmiHeader); 

			//设置解码数据输出格式的大小
			this->m_pOutInfo=(BITMAPINFO*)new BYTE[this->m_OutFormatSize];

			//设置编码器输出格式
			ICDecompressGetFormat(this->m_CV.hic,&this->m_InInfo, this->m_pOutInfo); 

			//输出缓存大小
			this->m_OutBufSize=this->m_pOutInfo->bmiHeader.biSizeImage;

			//输出缓存
			this->m_pOutBuf=new BYTE[this->m_OutBufSize];

			//初始化输出缓存
			memset(this->m_pOutBuf,0,this->m_OutBufSize);

			//声明解码器可以开始工作
			ICDecompressBegin(this->m_CV.hic,&this->m_InInfo, this->m_pOutInfo);
		}
	}
}

//注销解码器
void CClientPlusDlg::UnInitDecompressor()
{
	if (m_CV.hic!=NULL)
	{
		//删除解码器输出格式
		delete[] this->m_pOutInfo;

		//删除解码器输出缓存
		delete[] this->m_pOutBuf;

		//关闭解码器
		ICClose(m_CV.hic);
	}
}

//注销窗口
void CClientPlusDlg::OnDestroy() 
{
	//调用基类OnDestroy()函数
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	//注销解码器
	UnInitDecompressor();
}

//显示位图
void CClientPlusDlg::ShowImage(BYTE *Buf)
{
	//设备上下文
	CDC* pDC=GetDC();

	//在显示器上输出位图
	SetDIBitsToDevice(
		pDC->GetSafeHdc(),0,0,m_pOutInfo->bmiHeader.biWidth,
		m_pOutInfo->bmiHeader.biHeight,0,0,0,
		m_pOutInfo->bmiHeader.biHeight,Buf,m_pOutInfo,
		DIB_RGB_COLORS);
}
