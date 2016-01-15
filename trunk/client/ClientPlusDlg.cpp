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
	ON_WM_DESTROY()//ע������
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClientPlusDlg message handlers

BOOL CClientPlusDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// ��֤IDM_ABOUTBOX����Ч��ϵͳ���Χ��
	//��ASSERT()�ڵı��ʽ������������ֹ����
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
	//��ʼ������
	this->InitNetWork();
	//����
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

//��ʼ������
void CClientPlusDlg::InitNetWork()
{
	//��ʼ��socket
	::AfxSocketInit();

	//����CClientStreamSock�����׽���
	this->m_ClientStreamSock.Create(0,SOCK_STREAM,FD_CONNECT|FD_READ|FD_WRITE);

	//����CClientStrSock�����׽���
	this->m_ClientCtrlSock.Create(0,SOCK_STREAM,FD_CONNECT|FD_READ|FD_WRITE);
}

//��ť������Ӧ����
void CClientPlusDlg::OnButton1() 
{
	//IP��ַ��4���ֶ�
	BYTE Field0,Field1,Field2,Field3;

	//���ط�0��IP�ֶ�
	int NonBlank=this->m_IPCtrl.GetAddress(Field0,Field1,Field2,Field3);

	//�Ƿ�IP��ַ
	if (NonBlank!=4)
	{
		//����
		MessageBox("Please enter the complete IP Address!");

		//����
		return;
	}

	//ȡ��IP��ַ
	m_strIPAddr.Format("%d.%d.%d.%d",Field0,Field1,Field2,Field3);

	//�������ӷ����
	this->m_ClientStreamSock.Connect(m_strIPAddr,5555);
}

//����
void CClientPlusDlg::ExcuteServerCommand(SERVER_CTRL_MSG msg)
{
	//λͼ��Ϣ
	if (strcmp(msg.strCommand,"Set Bitmap Info")==0)
	{
		memcpy(&m_InInfo,msg.strContent,sizeof(BITMAPINFO));
	}

	//��-������������Ϣ
	if (strcmp(msg.strCommand,"Set COMPVARS")==0)
	{
		//���ƽ�����������Ϣ
		memcpy(&this->m_CV,msg.strContent,sizeof(COMPVARS));
		
		//�򿪽�����
		m_CV.hic=ICOpen(m_CV.fccType,m_CV.fccHandler,ICMODE_DECOMPRESS);

		//��ʧ��
		if (m_CV.hic==NULL)
		{
			//��ʾ
			MessageBox("please install the proper decompressor!");

			//����
			return;
		}

		//�򿪳ɹ�
		else
		{
			//���ý������������ʽ�Ĵ�С
		    this->m_OutFormatSize=ICDecompressGetFormatSize(
				this->m_CV.hic,&this->m_InInfo.bmiHeader); 

			//���ý������������ʽ�Ĵ�С
			this->m_pOutInfo=(BITMAPINFO*)new BYTE[this->m_OutFormatSize];

			//���ñ����������ʽ
			ICDecompressGetFormat(this->m_CV.hic,&this->m_InInfo, this->m_pOutInfo); 

			//��������С
			this->m_OutBufSize=this->m_pOutInfo->bmiHeader.biSizeImage;

			//�������
			this->m_pOutBuf=new BYTE[this->m_OutBufSize];

			//��ʼ���������
			memset(this->m_pOutBuf,0,this->m_OutBufSize);

			//�������������Կ�ʼ����
			ICDecompressBegin(this->m_CV.hic,&this->m_InInfo, this->m_pOutInfo);
		}
	}
}

//ע��������
void CClientPlusDlg::UnInitDecompressor()
{
	if (m_CV.hic!=NULL)
	{
		//ɾ�������������ʽ
		delete[] this->m_pOutInfo;

		//ɾ���������������
		delete[] this->m_pOutBuf;

		//�رս�����
		ICClose(m_CV.hic);
	}
}

//ע������
void CClientPlusDlg::OnDestroy() 
{
	//���û���OnDestroy()����
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	//ע��������
	UnInitDecompressor();
}

//��ʾλͼ
void CClientPlusDlg::ShowImage(BYTE *Buf)
{
	//�豸������
	CDC* pDC=GetDC();

	//����ʾ�������λͼ
	SetDIBitsToDevice(
		pDC->GetSafeHdc(),0,0,m_pOutInfo->bmiHeader.biWidth,
		m_pOutInfo->bmiHeader.biHeight,0,0,0,
		m_pOutInfo->bmiHeader.biHeight,Buf,m_pOutInfo,
		DIB_RGB_COLORS);
}
