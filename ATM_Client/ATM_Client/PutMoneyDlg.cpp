// PutMoneyDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"

#include "ATM_Client.h"
#include "PutMoneyDlg.h"
#include "afxdialogex.h"

#include<Windows.h>
#include <mysql.h>
#include <string>
#include <iostream>
#pragma comment(lib,"libmysql.lib")
using namespace std;

// CPutMoneyDlg �Ի���

IMPLEMENT_DYNAMIC(CPutMoneyDlg, CDialogEx)

CPutMoneyDlg::CPutMoneyDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_PutMoney, pParent)
	, m_howmuch(0)
{

}

CPutMoneyDlg::~CPutMoneyDlg()
{
}

void CPutMoneyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_puthowmuch, m_howmuch);
	DDV_MinMaxInt(pDX, m_howmuch, 100, 500000);
}


BEGIN_MESSAGE_MAP(CPutMoneyDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CPutMoneyDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CPutMoneyDlg ��Ϣ�������

extern CString FindName;
extern CString FindPWD;

void CPutMoneyDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CString FindID;
	double FindBanlance = 0.0;

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
					FindID = sql_row[0];
					double ban = atoi(sql_row[3]);
					FindBanlance = ban;

					FindBanlance = FindBanlance + m_howmuch;
					strSQL.Format("update cardinfo set banlance='%lf' where id='%s'", FindBanlance, FindID);
					res = mysql_query(&myCont, strSQL);
					if (!res)
					{
						result = mysql_store_result(&myCont);//�洢��ѯ���
						MessageBox("���ɹ���");
					}

					this->UpdateData(TRUE);
					strSQL.Format("insert into putmoney values('%s','%s','%d','%lf',NOW())", FindID, FindName, m_howmuch, FindBanlance);
					res = mysql_query(&myCont, strSQL);
					if (!res)
					{
						result = mysql_store_result(&myCont);//�洢��ѯ���
					}
					else
					{
						MessageBox("����¼�޸�ʧ��!");
					}

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

	CDialogEx::OnOK();
}


BOOL CPutMoneyDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetDlgItemText(IDC_EDIT_puthowmuch, NULL);
	//SetDlgItemText(IDC_EDIT_Puthowmuch, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}
