
// ATM_Client.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CATM_ClientApp: 
// �йش����ʵ�֣������ ATM_Client.cpp
//

class CATM_ClientApp : public CWinApp
{
public:
	CATM_ClientApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CATM_ClientApp theApp;