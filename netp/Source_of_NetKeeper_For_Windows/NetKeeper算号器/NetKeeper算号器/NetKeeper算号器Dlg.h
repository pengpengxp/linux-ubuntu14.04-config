// NetKeeper�����Dlg.h : ͷ�ļ�
//

#pragma once
#include "resource.h"

// CNetKeeper�����Dlg �Ի���
class CNetKeeper�����Dlg : public CDialog
{
// ����
public:
	CNetKeeper�����Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_NETKEEPER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCalc();
	afx_msg void OnBnClickedCancel();
	// ԭʼ�ʺ�
	CString m_SrcID;
	// ��ǰ����ID
	CString m_NowID;
	afx_msg void OnBnClickedOk();
	afx_msg void OnEnChangeSrcid();
	afx_msg void OnDial();
	// ��½����
	CString m_Pass;
	afx_msg void OnBnClickedDial();
	afx_msg void OnAbout();
	afx_msg void OnBnClickedCalc();
};
