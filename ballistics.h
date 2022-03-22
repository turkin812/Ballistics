
// maiatnic.h : главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить stdafx.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CmaiatnicApp:
// О реализации данного класса см. maiatnic.cpp
//

class CballisticsApp : public CWinApp
{
public:
	CballisticsApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CballisticsApp theApp;