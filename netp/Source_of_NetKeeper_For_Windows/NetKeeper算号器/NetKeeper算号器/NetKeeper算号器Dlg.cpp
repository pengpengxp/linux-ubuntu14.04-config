// NetKeeper�����Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "NetKeeper�����.h"
#include "NetKeeper�����Dlg.h"
#include "CXKUsername.h"
#include "Ras.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
public:
	CString m_About;
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
, m_About(_T(""))
{
	m_About="NetKeeper2.5 V42\r\n���������������NetKeeperУ԰���û�\r\n�ø����ĵ�����å������״����ǵĵ�������ʧ��!\r\nBy:\tDaviYang35\r\nhttp://hi.baidu.com/daviyang\r\nCopyright (C) 2009";
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ABOUT, m_About);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CNetKeeper�����Dlg �Ի���




CNetKeeper�����Dlg::CNetKeeper�����Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNetKeeper�����Dlg::IDD, pParent)
	, m_SrcID(_T(""))
	, m_NowID(_T(""))
	, m_Pass(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CNetKeeper�����Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_SRCID, m_SrcID);
	DDX_Text(pDX, IDC_TUREID, m_NowID);
	DDX_Text(pDX, IDC_EDIT1, m_Pass);
}

BEGIN_MESSAGE_MAP(CNetKeeper�����Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(ID_CALC, &CNetKeeper�����Dlg::OnCalc)
	ON_EN_CHANGE(IDC_SRCID, &CNetKeeper�����Dlg::OnEnChangeSrcid)
	ON_BN_CLICKED(IDD_DIAL, &CNetKeeper�����Dlg::OnDial)
	ON_BN_CLICKED(IDC_ABOUT, &CNetKeeper�����Dlg::OnAbout)
END_MESSAGE_MAP()


// CNetKeeper�����Dlg ��Ϣ�������

BOOL CNetKeeper�����Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	CString temp;
	GetPrivateProfileString("Info","ID","",temp.GetBuffer(30),30,".\\user.ini");
	temp.ReleaseBuffer();
	m_SrcID=temp;
	GetPrivateProfileString("Info","PASS","",temp.GetBuffer(30),30,".\\user.ini");
	temp.ReleaseBuffer();
	m_Pass=temp;
	UpdateData(FALSE);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CNetKeeper�����Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CNetKeeper�����Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
//
HCURSOR CNetKeeper�����Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CNetKeeper�����Dlg::OnCalc()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if(m_SrcID=="")
	{
		AfxMessageBox("����������ʺ�!\r\n����@֮��Ĳ��֣�����еĻ�");
		return;
	}
	CXKUsername username(m_SrcID);
	m_NowID=username.Realusername();
	UpdateData(FALSE);
}

void CNetKeeper�����Dlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnOK();
}

void CNetKeeper�����Dlg::OnEnChangeSrcid()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	if(m_SrcID!="")
		this->OnCalc();
	else
	{
		m_NowID="�������ʺ�";
		UpdateData(FALSE);
	}
}

void CNetKeeper�����Dlg::OnDial()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if(m_SrcID=="")
	{
		AfxMessageBox("����������ʺ�!\r\n����@֮��Ĳ��֣�����еĻ�");
		return;
	}
	if(m_Pass=="")
	{
		AfxMessageBox("������������룡\r\n���ģ��Ҷ�������벻����Ȥ");
		return;
	}
	CXKUsername username(m_SrcID);
	m_NowID=username.Realusername();
	CRas ras(this);
	if(ras.Dail("�������",NULL,username.Realusername(),m_Pass,NULL))
	{
		WritePrivateProfileString("Info","ID",m_SrcID,".\\user.ini");
		WritePrivateProfileString("Info","PASS",m_Pass,".\\user.ini");
	}
	UpdateData(FALSE);
}

void CNetKeeper�����Dlg::OnAbout()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}
