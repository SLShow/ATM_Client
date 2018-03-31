// ATM_OSDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ATM_Client.h"
#include "ATM_OSDlg.h"
#include "afxdialogex.h"

#include "FindResultDlg.h"
#include "GetMoneyDlg.h"
#include "PutMoneyDlg.h"
#include "AlterPWDDlg.h"
#include "GiveOtherDlg.h"

#include<Windows.h>
#include <mysql.h>
#include <string>
#include <iostream>
#pragma comment(lib,"libmysql.lib")
using namespace std;

// CATM_OSDlg 对话框

IMPLEMENT_DYNAMIC(CATM_OSDlg, CDialogEx)

CATM_OSDlg::CATM_OSDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_OS, pParent)
{

}

CATM_OSDlg::~CATM_OSDlg()
{
}

void CATM_OSDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CATM_OSDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_AlterPwd, &CATM_OSDlg::OnClickedButtonAlterpwd)
	ON_BN_CLICKED(IDC_BUTTON_DoWhat, &CATM_OSDlg::OnClickedButtonDowhat)
	ON_BN_CLICKED(IDC_BUTTON_Find, &CATM_OSDlg::OnClickedButtonFind)
	ON_BN_CLICKED(IDC_BUTTON_GetMoney, &CATM_OSDlg::OnClickedButtonGetmoney)
	ON_BN_CLICKED(IDC_BUTTON_GiveOther, &CATM_OSDlg::OnClickedButtonGiveother)
	ON_BN_CLICKED(IDC_BUTTON_Language, &CATM_OSDlg::OnClickedButtonLanguage)
	ON_BN_CLICKED(IDC_BUTTON_PutMoney, &CATM_OSDlg::OnClickedButtonPutmoney)
	ON_BN_CLICKED(IDC_BUTTON_Quit, &CATM_OSDlg::OnClickedButtonQuit)
END_MESSAGE_MAP()


// CATM_OSDlg 消息处理程序

extern CString FindName;
extern CString FindPWD;
//
//MYSQL myCont;
//MYSQL_RES *result = NULL;
//MYSQL_ROW sql_row;
//int res;
//bool isConnected = false;
//bool sql_connect=false;

BOOL CATM_OSDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	//const char user[] = "root";
	//const char pswd[] = "";
	//const char host[] = "localhost";//如果不是本机数据库，填写服务器ip地址
	//const char database[] = "bank";
	//unsigned int port = 3306;
	//
	//mysql_init(&myCont);//初始化

	//sql_connect=mysql_real_connect(&myCont, host, user, pswd, database, port, NULL, 0);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CATM_OSDlg::OnClickedButtonAlterpwd()
{
	// TODO: 在此添加控件通知处理程序代码
	CAlterPWDDlg dlg;
	dlg.DoModal();
}


void CATM_OSDlg::OnClickedButtonDowhat()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CATM_OSDlg::OnClickedButtonFind()
{
	CFindResultDlg dlg;
	dlg.DoModal();
	//if (sql_connect)
	//{
	//	//this->UpdateData(true);
	//	isConnected = true;
	//	mysql_query(&myCont, "SET NAMES GBK"); //设置编码格式
	//	CString strSQL;
	//	strSQL.Format("select * from cardinfo where name='%s'and pwd='%s'",FindName,FindPWD);
	//	res = mysql_query(&myCont, strSQL);//查询
	//	if (!res)
	//	{
	//		result = mysql_store_result(&myCont);//存储查询结果
	//		if (result)
	//		{
	//			sql_row = mysql_fetch_row(result);//获取具体的数据

	//			if (sql_row != NULL)
	//			{
	//				CFindResultDlg dlg;
	//				dlg.m_id = sql_row[0];
	//				dlg.m_name = sql_row[1];
	//				double ban = atoi(sql_row[3]);
	//				dlg.m_banlance = ban;
	//				dlg.m_personid = sql_row[4];
	//				this->UpdateData(FALSE);
	//				dlg.DoModal();
	//			}
	//		}
	//	}
	//	else
	//	{
	//		MessageBox("无结果!");
	//	}
	//}
	//else
	//{
	//	MessageBox("数据库连接失败!");
	//}
	//if (result != NULL)
	//	mysql_free_result(result);//释放查询结果
	//if (isConnected)
	//{
	//	mysql_close(&myCont);//关闭连接
	//}
}


void CATM_OSDlg::OnClickedButtonGetmoney()//取款
{
	// TODO: 在此添加控件通知处理程序代码
	CGetMoneyDlg dlg;
	dlg.DoModal();
}


void CATM_OSDlg::OnClickedButtonGiveother()
{
	// TODO: 在此添加控件通知处理程序代码
	CGiveOtherDlg dlg;
	dlg.DoModal();
}


void CATM_OSDlg::OnClickedButtonLanguage()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CATM_OSDlg::OnClickedButtonPutmoney()
{
	// TODO: 在此添加控件通知处理程序代码
	CPutMoneyDlg dlg;
	dlg.DoModal();
}


void CATM_OSDlg::OnClickedButtonQuit()
{
	// TODO: 在此添加控件通知处理程序代码
	MessageBox("谢谢使用！");
	CDialogEx::OnOK();

}



