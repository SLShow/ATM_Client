#pragma once


// CGiveOtherDlg 对话框

class CGiveOtherDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGiveOtherDlg)

public:
	CGiveOtherDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CGiveOtherDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_GiveOther };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_id;
	int m_howmuch;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
