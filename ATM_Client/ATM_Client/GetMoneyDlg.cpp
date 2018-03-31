// GetMoneyDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ATM_Client.h"
#include "GetMoneyDlg.h"
#include "afxdialogex.h"

#include<Windows.h>
#include <mysql.h>
#include <string>
#include <iostream>
#pragma comment(lib,"libmysql.lib")
using namespace std;

// CGetMoneyDlg �Ի���

IMPLEMENT_DYNAMIC(CGetMoneyDlg, CDialogEx)

CGetMoneyDlg::CGetMoneyDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_GetMoney, pParent)
	, m_howmuch(0)
{

}

CGetMoneyDlg::~CGetMoneyDlg()
{
}

void CGetMoneyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_gethowmuch, m_howmuch);
	DDV_MinMaxInt(pDX, m_howmuch, 100, 50000);
}


BEGIN_MESSAGE_MAP(CGetMoneyDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CGetMoneyDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CGetMoneyDlg ��Ϣ�������


extern CString FindName;
extern CString FindPWD;

void CGetMoneyDlg::OnBnClickedOk()
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
		//strSQL.Format("update cardinfo set banlance=banlance-'%lf' where name='%s'and pwd='%s'",m_howmuch, FindName, FindPWD);
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
					if (FindBanlance < m_howmuch)
						MessageBox("���㣡");
					else
					{
						FindBanlance = FindBanlance - m_howmuch;
						strSQL.Format("update cardinfo set banlance='%lf' where name='%s'and pwd='%s'", FindBanlance, FindName, FindPWD);
						res = mysql_query(&myCont, strSQL);
						if (!res)
						{
							result = mysql_store_result(&myCont);//�洢��ѯ���
							MessageBox("ȡ��ɹ���");
						}

						this->UpdateData(TRUE);
						m_howmuch = -m_howmuch;
						strSQL.Format("insert into getmoney values('%s','%s','%d','%lf',NOW())", FindID, FindName, m_howmuch, FindBanlance);
						res = mysql_query(&myCont, strSQL);
						
						if (!res)
						{
							result = mysql_store_result(&myCont);//�洢��ѯ���
						}
						else
						{
							MessageBox("ȡ���¼�޸�ʧ��!");
						}
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


BOOL CGetMoneyDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	
	SetDlgItemText(IDC_EDIT_gethowmuch, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}
