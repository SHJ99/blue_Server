#pragma once

// CChildSocket 명령 대상입니다.

class CChildSocket : public CSocket
{
public:
	CChildSocket();
	virtual ~CChildSocket();
	void SetListenSocket(CAsyncSocket* pSocket);
	CAsyncSocket* m_pListenSocket;
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	//int now;
};


