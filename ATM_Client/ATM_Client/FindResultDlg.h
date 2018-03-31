#pragma once


// CFindResultDlg 对话框

class CFindResultDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFindResultDlg)

public:
	CFindResultDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CFindResultDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_FindResult };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	double m_banlance;
	CString m_id;
	CString m_name;
	CString m_personid;
	virtual BOOL OnInitDialog();
};
