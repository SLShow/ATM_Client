#pragma once


// CGiveOtherDlg �Ի���

class CGiveOtherDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGiveOtherDlg)

public:
	CGiveOtherDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CGiveOtherDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_GiveOther };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_id;
	int m_howmuch;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
