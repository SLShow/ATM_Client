#pragma once


// CEnterGiveDlg �Ի���

class CEnterGiveDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CEnterGiveDlg)

public:
	CEnterGiveDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CEnterGiveDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_EnterGive };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_name;
	CString m_id;
	int m_howmuch;
	afx_msg void OnBnClickedOk();
};
