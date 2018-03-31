// EnterGiveDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ATM_Client.h"
#include "EnterGiveDlg.h"
#include "afxdialogex.h"

#include<Windows.h>
#include <mysql.h>
#include <string>
#include <iostream>
#pragma comment(lib,"libmysql.lib")
using namespace std;

// CEnterGiveDlg �Ի���

IMPLEMENT_DYNAMIC(CEnterGiveDlg, CDialogEx)

CEnterGiveDlg::CEnterGiveDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_EnterGive, pParent)
	, m_name(_T(""))
	, m_id(_T(""))
	, m_howmuch(0)
{

}

CEnterGiveDlg::~CEnterGiveDlg()
{
}

void CEnterGiveDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_name, m_name);
	DDX_Text(pDX, IDC_EDIT_id, m_id);
	DDX_Text(pDX, IDC_EDIT_howmuch, m_howmuch);
	DDV_MinMaxInt(pDX, m_howmuch, 100, 500000);
}


BEGIN_MESSAGE_MAP(CEnterGiveDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CEnterGiveDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CEnterGiveDlg ��Ϣ�������

extern CString FindName;
extern CString FindPWD;

void CEnterGiveDlg::OnBnClickedOk()
{
	CString FindID;
	CString FindotherName;
	double FindBanlance = 0.0;

	const char user[] = "root";
	const char pswd[] = "";
	const char host[] = "localhost";
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


		/*************************ת������*************************************/
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
							//MessageBox("ת�˳ɹ���");
						}

						this->UpdateData(TRUE);
						m_howmuch = -m_howmuch;
						strSQL.Format("insert into giveother values('%s','%s','%d','%lf',NOW())", FindID, FindName, m_howmuch, FindBanlance);
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

		/*************************ת�벿��*************************************/
		strSQL.Format("select * from cardinfo where id = '%s'",m_id);
		res = mysql_query(&myCont, strSQL);//��ѯ
		if (!res)
		{
			result = mysql_store_result(&myCont);//�洢��ѯ���
			if (result)
			{
				sql_row = mysql_fetch_row(result);//��ȡ���������

				if (sql_row != NULL)
				{
					//FindID = sql_row[0];
					FindotherName = sql_row[1];
					double ban = atoi(sql_row[3]);
					FindBanlance = ban;

		            this->UpdateData(TRUE);

					FindBanlance = FindBanlance + m_howmuch;
					strSQL.Format("update cardinfo set banlance='%lf' where id='%s'", FindBanlance, m_id);
					res = mysql_query(&myCont, strSQL);
					if (!res)
					{
						result = mysql_store_result(&myCont);//�洢��ѯ���
						MessageBox("ת�˳ɹ���");
					}

					strSQL.Format("insert into giveother values('%s','%s','%d','%lf',NOW())", m_id, FindotherName, m_howmuch, FindBanlance);
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

		//ת�˽���
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
