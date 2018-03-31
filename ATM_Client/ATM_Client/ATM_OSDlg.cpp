// ATM_OSDlg.cpp : ʵ���ļ�
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

// CATM_OSDlg �Ի���

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


// CATM_OSDlg ��Ϣ�������

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

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	//const char user[] = "root";
	//const char pswd[] = "";
	//const char host[] = "localhost";//������Ǳ������ݿ⣬��д������ip��ַ
	//const char database[] = "bank";
	//unsigned int port = 3306;
	//
	//mysql_init(&myCont);//��ʼ��

	//sql_connect=mysql_real_connect(&myCont, host, user, pswd, database, port, NULL, 0);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void CATM_OSDlg::OnClickedButtonAlterpwd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CAlterPWDDlg dlg;
	dlg.DoModal();
}


void CATM_OSDlg::OnClickedButtonDowhat()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CATM_OSDlg::OnClickedButtonFind()
{
	CFindResultDlg dlg;
	dlg.DoModal();
	//if (sql_connect)
	//{
	//	//this->UpdateData(true);
	//	isConnected = true;
	//	mysql_query(&myCont, "SET NAMES GBK"); //���ñ����ʽ
	//	CString strSQL;
	//	strSQL.Format("select * from cardinfo where name='%s'and pwd='%s'",FindName,FindPWD);
	//	res = mysql_query(&myCont, strSQL);//��ѯ
	//	if (!res)
	//	{
	//		result = mysql_store_result(&myCont);//�洢��ѯ���
	//		if (result)
	//		{
	//			sql_row = mysql_fetch_row(result);//��ȡ���������

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
	//		MessageBox("�޽��!");
	//	}
	//}
	//else
	//{
	//	MessageBox("���ݿ�����ʧ��!");
	//}
	//if (result != NULL)
	//	mysql_free_result(result);//�ͷŲ�ѯ���
	//if (isConnected)
	//{
	//	mysql_close(&myCont);//�ر�����
	//}
}


void CATM_OSDlg::OnClickedButtonGetmoney()//ȡ��
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CGetMoneyDlg dlg;
	dlg.DoModal();
}


void CATM_OSDlg::OnClickedButtonGiveother()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CGiveOtherDlg dlg;
	dlg.DoModal();
}


void CATM_OSDlg::OnClickedButtonLanguage()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CATM_OSDlg::OnClickedButtonPutmoney()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CPutMoneyDlg dlg;
	dlg.DoModal();
}


void CATM_OSDlg::OnClickedButtonQuit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	MessageBox("ллʹ�ã�");
	CDialogEx::OnOK();

}



