
// comm_app.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// Ccomm_appApp: 
// �йش����ʵ�֣������ comm_app.cpp
//

class Ccomm_appApp : public CWinApp
{
public:
	Ccomm_appApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern Ccomm_appApp theApp;