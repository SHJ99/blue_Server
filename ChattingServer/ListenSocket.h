#pragma once

// CListenSocket ��� ����Դϴ�.
#include "ChildSocket.h"
class CListenSocket : public CAsyncSocket
{
public:
	CListenSocket();
	virtual ~CListenSocket();

	//����� Ŭ���̾�Ʈ ���� ����Ʈ
	CPtrList m_ptrChildSocketList;
	POSITION pos_d;
	//int pnum;

	void BroadCast(char* pszBuffer, int len);
	void CloseChildSocket(CChildSocket* pChild);
	virtual void OnAccept(int nErrorCode);
	void CloseClientSocket(CSocket* pChild);
	void SendDice(int dice, int player);
//	int SingleCast(int* count);
//	void SingleCast(int* count);
	void SingleCast();
//	void multicast(int money);
	void multicast(CString money);
};


