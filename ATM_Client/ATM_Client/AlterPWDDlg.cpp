// AlterPWDDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ATM_Client.h"
#include "AlterPWDDlg.h"
#include "afxdialogex.h"

#include<Windows.h>
#include <mysql.h>
#include <string>
#include <iostream>
#pragma comment(lib,"libmysql.lib")
using namespace std;

// CAlterPWDDlg �Ի���

IMPLEMENT_DYNAMIC(CAlterPWDDlg, CDialogEx)

CAlterPWDDlg::CAlterPWDDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_AlterPWD, pParent)
	, m_pwd(_T(""))
	, m_pwdagain(_T(""))
{

}

CAlterPWDDlg::~CAlterPWDDlg()
{
}

void CAlterPWDDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_pwd, m_pwd);
	DDV_MaxChars(pDX, m_pwd, 6);
	//  DDX_Text(pDX, IDC_EDIT2_PWDAgain, m_pwdagain);
	DDX_Text(pDX, IDC_EDIT2_PWDAgain, m_pwdagain);
	DDV_MaxChars(pDX, m_pwdagain, 6);
}


BEGIN_MESSAGE_MAP(CAlterPWDDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAlterPWDDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CAlterPWDDlg ��Ϣ�������

extern CString FindName;
extern CString FindPWD;

void CAlterPWDDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->UpdateData(TRUE);

	if (m_pwd == m_pwdagain)
	{
		const char user[] = "root";
		const char pswd[] = "";
		const char host[] = "localhost";//������Ǳ������ݿ⣬��д������ip��ַ
		const char database[] = "bank";
		unsigned int port = 3306;
		MYSQL myCont;
		MYSQL_RES *result = NULL;
		MYSQL_ROW sql_row;
		int res;
		mysql_init(&myCont);//��ʼ��
		bool isConnected = false;

		if (mysql_real_connect(&myCont, host, user, pswd, database, port, NULL, 0))//�������ݿ�
		{
			this->UpdateData(TRUE);
			isConnected = true;
			mysql_query(&myCont, "SET NAMES GBK"); //���ñ����ʽ
			CString strSQL;
			strSQL.Format("update cardinfo set pwd = '%s' where name = '%s'and pwd = '%s'", m_pwd, FindName, FindPWD);
			res = mysql_query(&myCont, strSQL);//��ѯ

			if (!res)
			{
				result = mysql_store_result(&myCont);//�洢��ѯ���
				MessageBox("�����޸ĳɹ���");
			}
			else
			{
				MessageBox("�޽��!");
			}
		}
		else
		{
			MessageBox("���ݿ�����ʧ��!");
		}
		if (result != NULL)
			mysql_free_result(result);//�ͷŲ�ѯ���
		if (isConnected)
		{
			mysql_close(&myCont);//�ر�����
		}

	}
	else
		MessageBox("�������벻һ�£�");

	CDialogEx::OnOK();
}
