// ChattingServer.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CChattingServerApp:
// �� Ŭ������ ������ ���ؼ��� ChattingServer.cpp�� �����Ͻʽÿ�.
//

class CChattingServerApp : public CWinApp
{
public:
	CChattingServerApp();

// �������Դϴ�.
	public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CChattingServerApp theApp;