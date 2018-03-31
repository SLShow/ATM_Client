// AlterPWDDlg.cpp : 实现文件
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

// CAlterPWDDlg 对话框

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


// CAlterPWDDlg 消息处理程序

extern CString FindName;
extern CString FindPWD;

void CAlterPWDDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	this->UpdateData(TRUE);

	if (m_pwd == m_pwdagain)
	{
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
			strSQL.Format("update cardinfo set pwd = '%s' where name = '%s'and pwd = '%s'", m_pwd, FindName, FindPWD);
			res = mysql_query(&myCont, strSQL);//查询

			if (!res)
			{
				result = mysql_store_result(&myCont);//存储查询结果
				MessageBox("密码修改成功！");
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

	}
	else
		MessageBox("两次密码不一致！");

	CDialogEx::OnOK();
}
