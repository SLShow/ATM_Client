#pragma once


// CAlterPWDDlg �Ի���

class CAlterPWDDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAlterPWDDlg)

public:
	CAlterPWDDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAlterPWDDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_AlterPWD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_pwd;
//	CString m_pwdagain;
	CString m_pwdagain;
	afx_msg void OnBnClickedOk();
};
