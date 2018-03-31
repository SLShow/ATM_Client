// PutMoneyDlg.cpp : 实现文件
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

// CPutMoneyDlg 对话框

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


// CPutMoneyDlg 消息处理程序

extern CString FindName;
extern CString FindPWD;

void CPutMoneyDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码

	CString FindID;
	double FindBanlance = 0.0;

	const char user[] = "root";
	const char pswd[] = "";
	const char host[] = "localhost";//如果不是本机数据库，填写服务器ip地址
	const char database[] = "bank";
	unsigned int port = 3306;
	MYSQL myCont;
	MYSQL_RES *result = NULL;
	MYSQL_ROW sql_row;
	int res;
	mysql_init(&myCont);//初始化
	bool isConnected = false;

	if (mysql_real_connect(&myCont, host, user, pswd, database, port, NULL, 0))//连接数据库
	{
		this->UpdateData(TRUE);
		isConnected = true;
		mysql_query(&myCont, "SET NAMES GBK"); //设置编码格式
		CString strSQL;
		strSQL.Format("select * from cardinfo where name='%s'and pwd='%s'", FindName, FindPWD);
		res = mysql_query(&myCont, strSQL);//查询
		if (!res)
		{
			result = mysql_store_result(&myCont);//存储查询结果
			if (result)
			{
				sql_row = mysql_fetch_row(result);//获取具体的数据

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
						result = mysql_store_result(&myCont);//存储查询结果
						MessageBox("存款成功！");
					}

					this->UpdateData(TRUE);
					strSQL.Format("insert into putmoney values('%s','%s','%d','%lf',NOW())", FindID, FindName, m_howmuch, FindBanlance);
					res = mysql_query(&myCont, strSQL);
					if (!res)
					{
						result = mysql_store_result(&myCont);//存储查询结果
					}
					else
					{
						MessageBox("存款记录修改失败!");
					}

				}

			}
		}
		else
		{
			MessageBox("无结果!");
		}
	}
	else
	{
		MessageBox("数据库连接失败!");
	}
	if (result != NULL)
		mysql_free_result(result);//释放查询结果
	if (isConnected)
	{
		mysql_close(&myCont);//关闭连接
	}

	CDialogEx::OnOK();
}


BOOL CPutMoneyDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetDlgItemText(IDC_EDIT_puthowmuch, NULL);
	//SetDlgItemText(IDC_EDIT_Puthowmuch, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
