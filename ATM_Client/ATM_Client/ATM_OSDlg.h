#pragma once


// CATM_OSDlg 对话框

class CATM_OSDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CATM_OSDlg)

public:
	CATM_OSDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CATM_OSDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_OS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickedButtonAlterpwd();
	afx_msg void OnClickedButtonDowhat();
	afx_msg void OnClickedButtonFind();
	afx_msg void OnClickedButtonGetmoney();
	afx_msg void OnClickedButtonGiveother();
	afx_msg void OnClickedButtonLanguage();
	afx_msg void OnClickedButtonPutmoney();
	afx_msg void OnClickedButtonQuit();
	virtual BOOL OnInitDialog();
};
