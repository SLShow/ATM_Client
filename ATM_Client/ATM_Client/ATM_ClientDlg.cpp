
// ATM_ClientDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ATM_Client.h"
#include "ATM_ClientDlg.h"
#include "afxdialogex.h"

#include "ATM_OSDlg.h"

#include<Windows.h>
#include <mysql.h>
#include <string>
#include <iostream>
#pragma comment(lib,"libmysql.lib")
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CATM_ClientDlg �Ի���



CATM_ClientDlg::CATM_ClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ATM_CLIENT_DIALOG, pParent)
	, m_name(_T(""))
	, m_pwd(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CATM_ClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_name, m_name);
	DDX_Text(pDX, IDC_EDIT_pwd, m_pwd);
	DDX_Control(pDX, IDC_EDIT_name, m_clearname);
	DDX_Control(pDX, IDC_EDIT_pwd, m_clearpwd);
}

BEGIN_MESSAGE_MAP(CATM_ClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CATM_ClientDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CATM_ClientDlg ��Ϣ�������

BOOL CATM_ClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CATM_ClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CATM_ClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CATM_ClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


CString FindName;
CString FindPWD;

void CATM_ClientDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	UpdateData(TRUE);
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
		isConnected = true;
		mysql_query(&myCont, "SET NAMES GBK"); //���ñ����ʽ
		CString strSQL;
		strSQL.Format("select * from cardinfo where name='%s'and pwd='%s'", m_name, m_pwd);
		
		FindName = m_name;
		FindPWD = m_pwd;
		res = mysql_query(&myCont, strSQL);//��ѯ

		m_clearname.SetSel(0, -1);//��ձ༭��
		m_clearname.Clear();
		m_clearpwd.SetSel(0, -1);
		m_clearpwd.Clear();

		if (!res)
		{
			result = mysql_store_result(&myCont);//�洢��ѯ���
			if (result)
			{
				sql_row = mysql_fetch_row(result);//��ȡ���������

				if (sql_row != NULL)
				{
					CATM_OSDlg dlg;
					dlg.DoModal();
				}
				else
				{
					MessageBox("�������!");
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

	//CDialogEx::OnOK();
}
