#pragma once


// CFindResultDlg �Ի���

class CFindResultDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFindResultDlg)

public:
	CFindResultDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CFindResultDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_FindResult };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	double m_banlance;
	CString m_id;
	CString m_name;
	CString m_personid;
	virtual BOOL OnInitDialog();
};
