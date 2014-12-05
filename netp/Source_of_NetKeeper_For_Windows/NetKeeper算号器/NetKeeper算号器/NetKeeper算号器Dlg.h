// NetKeeper算号器Dlg.h : 头文件
//

#pragma once
#include "resource.h"

// CNetKeeper算号器Dlg 对话框
class CNetKeeper算号器Dlg : public CDialog
{
// 构造
public:
	CNetKeeper算号器Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_NETKEEPER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCalc();
	afx_msg void OnBnClickedCancel();
	// 原始帐号
	CString m_SrcID;
	// 当前拨号ID
	CString m_NowID;
	afx_msg void OnBnClickedOk();
	afx_msg void OnEnChangeSrcid();
	afx_msg void OnDial();
	// 登陆密码
	CString m_Pass;
	afx_msg void OnBnClickedDial();
	afx_msg void OnAbout();
	afx_msg void OnBnClickedCalc();
};
