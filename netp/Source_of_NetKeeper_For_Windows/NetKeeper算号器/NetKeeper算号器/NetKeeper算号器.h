// NetKeeper�����.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CNetKeeper�����App:
// �йش����ʵ�֣������ NetKeeper�����.cpp
//

class CNetKeeper�����App : public CWinApp
{
public:
	CNetKeeper�����App();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CNetKeeper�����App theApp;