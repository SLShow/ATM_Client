#pragma once


// CPutMoneyDlg 对话框

class CPutMoneyDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPutMoneyDlg)

public:
	CPutMoneyDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPutMoneyDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_PutMoney };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
//	int m_howmuch;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
//	int m_howmuch;
	int m_howmuch;
};
