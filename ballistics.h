
// maiatnic.h : ������� ���� ��������� ��� ���������� PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�������� stdafx.h �� ��������� ����� ����� � PCH"
#endif

#include "resource.h"		// �������� �������


// CmaiatnicApp:
// � ���������� ������� ������ ��. maiatnic.cpp
//

class CballisticsApp : public CWinApp
{
public:
	CballisticsApp();

// ���������������
public:
	virtual BOOL InitInstance();

// ����������

	DECLARE_MESSAGE_MAP()
};

extern CballisticsApp theApp;