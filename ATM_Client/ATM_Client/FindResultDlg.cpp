// FindResultDlg.cpp : 实现文件
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

// CFindResultDlg 对话框

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


// CFindResultDlg 消息处理程序

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
	const char host[] = "localhost";//如果不是本机数据库，填写服务器ip地址
	const char database[] = "bank";
	unsigned int port = 3306;

	mysql_init(&myCont);//初始化

	if (mysql_real_connect(&myCont, host, user, pswd, database, port, NULL, 0))
	{
		//this->UpdateData(true);
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

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
