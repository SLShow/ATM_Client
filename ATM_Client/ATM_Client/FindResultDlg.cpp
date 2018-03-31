// FindResultDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ATM_Client.h"
#include "FindResultDlg.h"
#include "afxdialogex.h"

#include<Windows.h>
#include <mysql.h>
#include <string>
#include <iostream>
#pragma comment(lib,"libmysql.lib")
using namespace std;

// CFindResultDlg �Ի���

IMPLEMENT_DYNAMIC(CFindResultDlg, CDialogEx)

CFindResultDlg::CFindResultDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_FindResult, pParent)
	, m_banlance(0)
	, m_id(_T(""))
	, m_name(_T(""))
	, m_personid(_T(""))
{

}

CFindResultDlg::~CFindResultDlg()
{
}

void CFindResultDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_banlance, m_banlance);
	DDX_Text(pDX, IDC_EDIT_id, m_id);
	DDX_Text(pDX, IDC_EDIT_name, m_name);
	DDX_Text(pDX, IDC_EDIT_personid, m_personid);
}


BEGIN_MESSAGE_MAP(CFindResultDlg, CDialogEx)
END_MESSAGE_MAP()


// CFindResultDlg ��Ϣ�������

extern CString FindName;
extern CString FindPWD;



BOOL CFindResultDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	MYSQL myCont;
	MYSQL_RES *result = NULL;
	MYSQL_ROW sql_row;
	int res;
	bool isConnected = false;

	const char user[] = "root";
	const char pswd[] = "";
	const char host[] = "localhost";//������Ǳ������ݿ⣬��д������ip��ַ
	const char database[] = "bank";
	unsigned int port = 3306;

	mysql_init(&myCont);//��ʼ��

	if (mysql_real_connect(&myCont, host, user, pswd, database, port, NULL, 0))
	{
		//this->UpdateData(true);
		isConnected = true;
		mysql_query(&myCont, "SET NAMES GBK"); //���ñ����ʽ
		CString strSQL;
		strSQL.Format("select * from cardinfo where name='%s'and pwd='%s'", FindName, FindPWD);
		res = mysql_query(&myCont, strSQL);//��ѯ
		if (!res)
		{
			result = mysql_store_result(&myCont);//�洢��ѯ���
			if (result)
			{
				sql_row = mysql_fetch_row(result);//��ȡ���������

				if (sql_row != NULL)
				{
					m_id = sql_row[0];
					m_name = sql_row[1];
					double ban = atoi(sql_row[3]);
					m_banlance = ban;
					m_personid = sql_row[4];
					this->UpdateData(FALSE);
				}
			}
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

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}
