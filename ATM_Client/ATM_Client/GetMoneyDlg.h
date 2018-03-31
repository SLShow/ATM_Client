#pragma once


// CGetMoneyDlg 对话框

class CGetMoneyDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGetMoneyDlg)

public:
	CGetMoneyDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CGetMoneyDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_GetMoney };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_howmuch;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
