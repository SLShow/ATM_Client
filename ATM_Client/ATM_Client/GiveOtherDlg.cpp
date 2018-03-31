// GiveOtherDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ATM_Client.h"
#include "GiveOtherDlg.h"
#include "afxdialogex.h"

#include "EnterGiveDlg.h"

#include<Windows.h>
#include <mysql.h>
#include <string>
#include <iostream>
#pragma comment(lib,"libmysql.lib")
using namespace std;

// CGiveOtherDlg 对话框

IMPLEMENT_DYNAMIC(CGiveOtherDlg, CDialogEx)

CGiveOtherDlg::CGiveOtherDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_GiveOther, pParent)
	, m_id(_T(""))
	, m_howmuch(0)
{

}

CGiveOtherDlg::~CGiveOtherDlg()
{
}

void CGiveOtherDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_id, m_id);
	DDX_Text(pDX, IDC_EDIT_houmuch, m_howmuch);
	DDV_MinMaxInt(pDX, m_howmuch, 100, 500000);
}


BEGIN_MESSAGE_MAP(CGiveOtherDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CGiveOtherDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CGiveOtherDlg 消息处理程序

extern CString FindName;
extern CString FindPWD;

void CGiveOtherDlg::OnBnClickedOk()
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
	mysql_init(&myCont);//初始化
	bool isConnected = false;

	if (mysql_real_connect(&myCont, host, user, pswd, database, port, NULL, 0))//连接数据库
	{
		this->UpdateData(TRUE);
		isConnected = true;
		mysql_query(&myCont, "SET NAMES GBK"); //设置编码格式
		CString strSQL;
		/*************************判断信息部分*************************************/

		strSQL.Format("select * from cardinfo where id = '%s'", m_id);
		res = mysql_query(&myCont, strSQL);//查询
		if (!res)
		{
			result = mysql_store_result(&myCont);//存储查询结果
			if (result)
			{
				sql_row = mysql_fetch_row(result);//获取具体的数据
				if (sql_row != NULL)
				{
					CEnterGiveDlg dlg;
					dlg.m_name = sql_row[1];
					dlg.m_id = m_id;
					dlg.m_howmuch = m_howmuch;
					this->UpdateData(false);
					dlg.DoModal();
				}
				else
					MessageBox("用户不存在！");
			}
		}
		else
		{
			MessageBox("无结果!");
		}

		///*************************转出部分*************************************/
		//strSQL.Format("select * from cardinfo where name='%s'and pwd='%s'", FindName, FindPWD);
		////strSQL.Format("update cardinfo set banlance=banlance-'%lf' where name='%s'and pwd='%s'",m_howmuch, FindName, FindPWD);
		//res = mysql_query(&myCont, strSQL);//查询
		//if (!res)
		//{
		//	result = mysql_store_result(&myCont);//存储查询结果
		//	if (result)
		//	{
		//		sql_row = mysql_fetch_row(result);//获取具体的数据

		//		if (sql_row != NULL)
		//		{
		//			FindID = sql_row[0];
		//			double ban = atoi(sql_row[3]);
		//			FindBanlance = ban;
		//			if (FindBanlance < m_howmuch)
		//				MessageBox("余额不足！");
		//			else
		//			{
		//				FindBanlance = FindBanlance - m_howmuch;
		//				strSQL.Format("update cardinfo set banlance='%lf' where name='%s'and pwd='%s'", FindBanlance, FindName, FindPWD);
		//				res = mysql_query(&myCont, strSQL);
		//				if (!res)
		//				{
		//					result = mysql_store_result(&myCont);//存储查询结果
		//					//MessageBox("转账成功！");
		//				}

		//				this->UpdateData(TRUE);
		//				m_howmuch = -m_howmuch;
		//				strSQL.Format("insert into giveother values('%s','%s','%d','%lf',NOW())", FindID, FindName, m_howmuch, FindBanlance);
		//				res = mysql_query(&myCont, strSQL);
		//				if (!res)
		//				{
		//					result = mysql_store_result(&myCont);//存储查询结果
		//				}
		//				else
		//				{
		//					MessageBox("取款记录修改失败!");
		//				}
		//			}
		//		}
		//	}
		//}
		//else
		//{
		//	MessageBox("无结果!");
		//}

		///*************************转入部分*************************************/
		//strSQL.Format("select * from cardinfo where id = '%s'",m_id);
		//res = mysql_query(&myCont, strSQL);//查询
		//if (!res)
		//{
		//	result = mysql_store_result(&myCont);//存储查询结果
		//	if (result)
		//	{
		//		sql_row = mysql_fetch_row(result);//获取具体的数据

		//		if (sql_row != NULL)
		//		{
		//			//FindID = sql_row[0];
		//			FindotherName = sql_row[1];
		//			double ban = atoi(sql_row[3]);
		//			FindBanlance = ban;

  //                this->UpdateData(TRUE);
		//			FindBanlance = FindBanlance + m_howmuch;
		//			strSQL.Format("update cardinfo set banlance='%lf' where id='%s'", FindBanlance, m_id);
		//			res = mysql_query(&myCont, strSQL);
		//			if (!res)
		//			{
		//				result = mysql_store_result(&myCont);//存储查询结果
		//				MessageBox("转账成功！");
		//			}

		//			strSQL.Format("insert into giveother values('%s','%s','%d','%lf',NOW())", m_id, FindotherName, m_howmuch, FindBanlance);
		//			res = mysql_query(&myCont, strSQL);
		//			if (!res)
		//			{
		//				result = mysql_store_result(&myCont);//存储查询结果
		//			}
		//			else
		//			{
		//				MessageBox("存款记录修改失败!");
		//			}

		//		}

		//	}
		//}
		//else
		//{
		//	MessageBox("无结果!");
		//}

		//转账结束
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


BOOL CGiveOtherDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetDlgItemText(IDC_EDIT_houmuch, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
