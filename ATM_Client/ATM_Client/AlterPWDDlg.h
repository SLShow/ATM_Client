#pragma once


// CAlterPWDDlg 对话框

class CAlterPWDDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAlterPWDDlg)

public:
	CAlterPWDDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAlterPWDDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_AlterPWD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_pwd;
//	CString m_pwdagain;
	CString m_pwdagain;
	afx_msg void OnBnClickedOk();
};
