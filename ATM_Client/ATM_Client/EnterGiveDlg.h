#pragma once


// CEnterGiveDlg 对话框

class CEnterGiveDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CEnterGiveDlg)

public:
	CEnterGiveDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CEnterGiveDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_EnterGive };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_name;
	CString m_id;
	int m_howmuch;
	afx_msg void OnBnClickedOk();
};
