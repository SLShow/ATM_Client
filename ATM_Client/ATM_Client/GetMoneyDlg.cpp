// GetMoneyDlg.cpp : 实现文件
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

// CGetMoneyDlg 对话框

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


// CGetMoneyDlg 消息处理程序


extern CString FindName;
extern CString FindPWD;

void CGetMoneyDlg::OnBnClickedOk()
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
		//strSQL.Format("update cardinfo set banlance=banlance-'%lf' where name='%s'and pwd='%s'",m_howmuch, FindName, FindPWD);
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
					if (FindBanlance < m_howmuch)
						MessageBox("余额不足！");
					else
					{
						FindBanlance = FindBanlance - m_howmuch;
						strSQL.Format("update cardinfo set banlance='%lf' where name='%s'and pwd='%s'", FindBanlance, FindName, FindPWD);
						res = mysql_query(&myCont, strSQL);
						if (!res)
						{
							result = mysql_store_result(&myCont);//存储查询结果
							MessageBox("取款成功！");
						}

						this->UpdateData(TRUE);
						m_howmuch = -m_howmuch;
						strSQL.Format("insert into getmoney values('%s','%s','%d','%lf',NOW())", FindID, FindName, m_howmuch, FindBanlance);
						res = mysql_query(&myCont, strSQL);
						
						if (!res)
						{
							result = mysql_store_result(&myCont);//存储查询结果
						}
						else
						{
							MessageBox("取款记录修改失败!");
						}
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


BOOL CGetMoneyDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	
	SetDlgItemText(IDC_EDIT_gethowmuch, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
