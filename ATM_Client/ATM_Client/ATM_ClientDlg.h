
// ATM_ClientDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CATM_ClientDlg 对话框
class CATM_ClientDlg : public CDialogEx
{
// 构造
public:
	CATM_ClientDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ATM_CLIENT_DIALOG };
#endif

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
	CString m_name;
	CString m_pwd;
	afx_msg void OnBnClickedOk();
	CEdit m_clearname;
	CEdit m_clearpwd;
};
