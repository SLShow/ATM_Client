
// ATM_ClientDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CATM_ClientDlg �Ի���
class CATM_ClientDlg : public CDialogEx
{
// ����
public:
	CATM_ClientDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ATM_CLIENT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString m_name;
	CString m_pwd;
	afx_msg void OnBnClickedOk();
	CEdit m_clearname;
	CEdit m_clearpwd;
};
