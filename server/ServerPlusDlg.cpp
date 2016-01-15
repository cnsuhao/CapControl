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
	//�Ѵ����ƶ�����Ļ��
	MoveWindow(1024-rect.right,-500,rect.right,rect.bottom);
	//����������ͼ��
	ModifyStyleEx(WS_EX_APPWINDOW,WS_EX_TOOLWINDOW);

	// TODO: Add extra initialization here
	this->m_bConnect=FALSE;//δ����
	this->m_SampleNum=0;//��ʼ���ɼ�֡
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
//ʹ��������Ч
void CServerPlusDlg::UnInitCompressor()
{
	//��������Ч
	if (m_CV.hic!=NULL)
	{
		//ɾ�������ʽ
		delete[] m_pOutInfo;

		//��������
		::ICSeqCompressFrameEnd(&m_CV);

		//�ͷ�COMPVARS�ṹ��Դ
		ICCompressorFree(&m_CV);

		//�رձ�����
		ICClose(m_CV.hic);
	}
}
//��ʼ��������
void CServerPlusDlg::InitCompressor()
{	
	//��ʼ��m_CV
    memset(&m_CV,0,sizeof(COMPVARS));

	//����COMPVARS�ṹ
	//�ֹ�����COMPVARS�ṹ
	m_CV.dwFlags=ICMF_COMPVARS_VALID;
	//COMPVARS�ṹ��С
	m_CV.cbSize=sizeof(m_CV);
	//ʹ��divx������
	m_CV.fccHandler=mmioFOURCC('m','s','v','c');
	//����������
	m_CV.fccType=ICTYPE_VIDEO;
	//�򿪱�����,hicΪ���������
	m_CV.hic=ICOpen(ICTYPE_VIDEO,mmioFOURCC('m','s','v','c'),ICMODE_COMPRESS);
	//��������(kb/s)
	m_CV.lDataRate=780;
	//�ؼ�֡��
	m_CV.lKey=15;
	//Ĭ����������
	m_CV.lQ=ICQUALITY_DEFAULT;
	//�����ֶ�
	m_CV.lKeyCount=0;
	m_CV.lpbiIn=NULL;
	m_CV.lpBitsOut=NULL;
	m_CV.lpBitsPrev=NULL;
	m_CV.lpState=NULL;
	m_CV.cbState=0;
	m_CV.lFrame=0;

	//�������򿪳ɹ�
	if (m_CV.hic!=NULL)
	{
		//�����������ʽ��С
		m_OutFormatSize=ICCompressGetFormatSize(m_CV.hic,&m_InInfo);

		//�����������ʽ
	    m_pOutInfo=(BITMAPINFO *)new BYTE[m_OutFormatSize];
	    ICCompressGetFormat(m_CV.hic,&m_InInfo,m_pOutInfo);

		//��������������С
		m_OutBufferSize=ICCompressGetSize(m_CV.hic,&m_InInfo,m_pOutInfo);
		
		//��ʼ����Դ��Ϊ����֡��������׼��
		ICSeqCompressFrameStart(&m_CV,&m_InInfo);
	}
	else
	{
		//��ʾ
		MessageBox("ϵͳ��Ƶѹ����ʽ��֧��!");
	}
}

void CServerPlusDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	this->UnInitCompressor();
	this->UnInitVideoCard();
	
}

//��ʼ����Ƶ�ɼ��豸
void CServerPlusDlg::InitVideoCard()
{
	//������Ƶ���񴰿�
	this->m_hWndCapture=::capCreateCaptureWindow("Capture Window",
		WS_VISIBLE|WS_CHILD,0,0,320,240,this->m_hWnd,1);

	//��������1���ɼ��豸
	capDriverConnect(this->m_hWndCapture,0);

	//������Ƶ��ʽ 
	capSetVideoFormat(this->m_hWndCapture,
		&this->m_InInfo,sizeof(BITMAPINFO));

	//����Ԥ��ģʽ(preview mode)����ʾ����
	capPreviewRate(this->m_hWndCapture,40);

	//����Ԥ��ģʽ
	capPreview(this->m_hWndCapture,TRUE);

	//����֡�ɼ��ص�����
	capSetCallbackOnFrame(this->m_hWndCapture,FrameCallBack);
}

//ʹ�ɼ��豸��Ч
void CServerPlusDlg::UnInitVideoCard()
{
	//��֡�ɼ��ص�������Ч
	capSetCallbackOnFrame(this->m_hWndCapture,FrameCallBack);

	//�Ͽ����豸�Ĺ���
	capDriverDisconnect(this->m_hWndCapture);
}

//֡�ɼ��ص�����
//�ɼ���һ֡����ʱ�͵��øú���
LRESULT CALLBACK CServerPlusDlg::FrameCallBack(HWND hWnd, LPVIDEOHDR lpVHdr)
{ 
	//��ȡ������
	CServerPlusDlg* pDlg=(CServerPlusDlg*)::AfxGetMainWnd();

	//��������״̬
	if (pDlg->m_bConnect==TRUE)
	{
		//���벢����
		pDlg->CompressFrame(lpVHdr);
	}

	//����
	return TRUE;
}

//����ѹ��������
void CServerPlusDlg::CompressFrame(LPVIDEOHDR lpVHdr)
{
	//�Ƿ�Ϊ�ؼ�֡
	BOOL bKeyFrame;

	//��Ƶ֡ʵ�ʴ�С
	m_OutActSize=this->m_InInfo.bmiHeader.biSizeImage;

	//����ѹ��
	BYTE* Buf=(BYTE*)ICSeqCompressFrame(&m_CV,0,
		lpVHdr->lpData,&bKeyFrame,(long*)&m_OutActSize);

	//��������״̬��������Ƶ���ݴ�С����
	if (this->m_bConnect==TRUE && m_OutActSize<MAPBUFSIZE)
	{
		//��Ƶ����
		VIDEO_DATA VideoData;

		//��ʼ��
		memset(&VideoData,0,sizeof(VIDEO_DATA));

		//����Ƿ�Ϊ�ؼ�֡
		VideoData.bKeyFrame=bKeyFrame;

		//������Ƶ(��)����
		memcpy(VideoData.Buf,Buf,m_OutActSize);

		//������Ƶ֡���
		VideoData.nSampleNum=this->m_SampleNum;

		//���������ʵ�ʴ�С
		VideoData.nUsedSize=m_OutActSize;

		//������������Ƶ֡����
		this->m_ServerStreamSock.Send(&VideoData,sizeof(VIDEO_DATA));

		//������Ƶ֡���
		m_SampleNum+=1;
	}
}

//����λͼ��BITMAPINFOHEADER�ṹ
void CServerPlusDlg::FillBitmapStruct()
{
	//ÿ�����صı�����
	m_InInfo.bmiHeader.biBitCount=24;
	//������ɫ����ʾλͼͬ����Ҫ
	m_InInfo.bmiHeader.biClrImportant=0;
	//λͼʵ��ʹ�õ���ɫ(ʹ��������ɫ)
	m_InInfo.bmiHeader.biClrUsed=0;
	//ѹ������
	m_InInfo.bmiHeader.biCompression=BI_RGB;
	//Ŀ���豸ƽ����
	m_InInfo.bmiHeader.biPlanes=1;
	//BITMAPINFOHEADER�ṹ��С
	m_InInfo.bmiHeader.biSize=sizeof(BITMAPINFOHEADER);
	//δѹ����RGBλͼ
	m_InInfo.bmiHeader.biSizeImage=0;
	//λͼ��
	m_InInfo.bmiHeader.biHeight=240;
	//λͼ��
	m_InInfo.bmiHeader.biWidth=320;
	//X����ֱ���
	m_InInfo.bmiHeader.biXPelsPerMeter=0;
	//Y����ֱ���
	m_InInfo.bmiHeader.biYPelsPerMeter=0;
}

//��ʼ������
void CServerPlusDlg::InitNetWork()
{
	//��ʼ��
	::AfxSocketInit();

	//����socket
	m_ListenSock.Create(5555,SOCK_STREAM,FD_ACCEPT);

	//����
	m_ListenSock.Listen();
}
