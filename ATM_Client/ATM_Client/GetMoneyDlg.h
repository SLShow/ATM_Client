#pragma once


// CGetMoneyDlg �Ի���

class CGetMoneyDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGetMoneyDlg)

public:
	CGetMoneyDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CGetMoneyDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_GetMoney };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int m_howmuch;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
