#pragma once


// CPutMoneyDlg �Ի���

class CPutMoneyDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPutMoneyDlg)

public:
	CPutMoneyDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPutMoneyDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_PutMoney };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
//	int m_howmuch;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
//	int m_howmuch;
	int m_howmuch;
};
