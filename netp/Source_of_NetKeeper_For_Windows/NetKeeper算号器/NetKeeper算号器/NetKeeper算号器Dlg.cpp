// NetKeeper算号器Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "NetKeeper算号器.h"
#include "NetKeeper算号器Dlg.h"
#include "CXKUsername.h"
#include "Ras.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
	CString m_About;
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
, m_About(_T(""))
{
	m_About="NetKeeper2.5 V42\r\n适用于重庆地区的NetKeeper校园网用户\r\n让该死的电信流氓软件彻底从我们的电脑上消失吧!\r\nBy:\tDaviYang35\r\nhttp://hi.baidu.com/daviyang\r\nCopyright (C) 2009";
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ABOUT, m_About);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CNetKeeper算号器Dlg 对话框




CNetKeeper算号器Dlg::CNetKeeper算号器Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNetKeeper算号器Dlg::IDD, pParent)
	, m_SrcID(_T(""))
	, m_NowID(_T(""))
	, m_Pass(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CNetKeeper算号器Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_SRCID, m_SrcID);
	DDX_Text(pDX, IDC_TUREID, m_NowID);
	DDX_Text(pDX, IDC_EDIT1, m_Pass);
}

BEGIN_MESSAGE_MAP(CNetKeeper算号器Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(ID_CALC, &CNetKeeper算号器Dlg::OnCalc)
	ON_EN_CHANGE(IDC_SRCID, &CNetKeeper算号器Dlg::OnEnChangeSrcid)
	ON_BN_CLICKED(IDD_DIAL, &CNetKeeper算号器Dlg::OnDial)
	ON_BN_CLICKED(IDC_ABOUT, &CNetKeeper算号器Dlg::OnAbout)
END_MESSAGE_MAP()


// CNetKeeper算号器Dlg 消息处理程序

BOOL CNetKeeper算号器Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	CString temp;
	GetPrivateProfileString("Info","ID","",temp.GetBuffer(30),30,".\\user.ini");
	temp.ReleaseBuffer();
	m_SrcID=temp;
	GetPrivateProfileString("Info","PASS","",temp.GetBuffer(30),30,".\\user.ini");
	temp.ReleaseBuffer();
	m_Pass=temp;
	UpdateData(FALSE);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CNetKeeper算号器Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CNetKeeper算号器Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
//
HCURSOR CNetKeeper算号器Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CNetKeeper算号器Dlg::OnCalc()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if(m_SrcID=="")
	{
		AfxMessageBox("请输入你的帐号!\r\n包含@之后的部分，如果有的话");
		return;
	}
	CXKUsername username(m_SrcID);
	m_NowID=username.Realusername();
	UpdateData(FALSE);
}

void CNetKeeper算号器Dlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	OnOK();
}

void CNetKeeper算号器Dlg::OnEnChangeSrcid()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData();
	if(m_SrcID!="")
		this->OnCalc();
	else
	{
		m_NowID="请输入帐号";
		UpdateData(FALSE);
	}
}

void CNetKeeper算号器Dlg::OnDial()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if(m_SrcID=="")
	{
		AfxMessageBox("请输入你的帐号!\r\n包含@之后的部分，如果有的话");
		return;
	}
	if(m_Pass=="")
	{
		AfxMessageBox("请输入你的密码！\r\n放心，我对你的密码不感兴趣");
		return;
	}
	CXKUsername username(m_SrcID);
	m_NowID=username.Realusername();
	CRas ras(this);
	if(ras.Dail("宽带连接",NULL,username.Realusername(),m_Pass,NULL))
	{
		WritePrivateProfileString("Info","ID",m_SrcID,".\\user.ini");
		WritePrivateProfileString("Info","PASS",m_Pass,".\\user.ini");
	}
	UpdateData(FALSE);
}

void CNetKeeper算号器Dlg::OnAbout()
{
	// TODO: 在此添加控件通知处理程序代码
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}
