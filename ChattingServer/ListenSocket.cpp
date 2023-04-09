// ListenSocket.cpp : ���� �����Դϴ�.
//
#include "stdafx.h"
#include "ChattingServer.h"
#include "ListenSocket.h"
#include<iostream>
using namespace std;
//���� ���� -> ����Ǿ����� �� ����Ǿ�����
//���� ���� ����? ���� ���� �����ϱ�

// CListenSocket

CListenSocket::CListenSocket()
{
}

CListenSocket::~CListenSocket()
{
}

//�׷��ϱ�, ���ݱ��� �޼����� ���� ���� 
// CListenSocket ��� �Լ�
void CListenSocket::BroadCast(char* pszBuffer, int len)
{
	
	POSITION pos;
	pos = m_ptrChildSocketList.GetHeadPosition();
	CChildSocket* pChild = NULL;
	
	while(pos != NULL)
	{
		pChild = (CChildSocket*)m_ptrChildSocketList.GetNext(pos);
		if(pChild != NULL)
		{
			//�� �޼����� �ٽ� �ش�. 
			pChild->Send(pszBuffer, len*2);
		}
	}
}

void CListenSocket::CloseChildSocket(CChildSocket* pChild)
{
	POSITION pos;
	//� ����� �����ٸ�?
	pos = m_ptrChildSocketList.Find(pChild);
	if(pos != NULL)
	{
		//������ ������ �����Ѵ�.
		if(pChild != NULL)
		{
			//���� ���� �˴ٿ�
			pChild->ShutDown();
			pChild->Close();
		}
		//�����Ѵ�.
		m_ptrChildSocketList.RemoveAt(pos);
		delete pChild;
	}
}
#include "ChattingServerDlg.h"
void CListenSocket::OnAccept(int nErrorCode)
{
	CString tmp = _T(""), strIPAddress = _T("");
	UINT uPortNumber = 0;
   CChildSocket* pChild = new CChildSocket;
   BOOL check=Accept(*pChild);
   //
   if(check == FALSE){
     delete pChild; 
     AfxMessageBox(_T("����������"));
     return;
   }

   SOCKADDR_IN addr;
   // CListenSocket ��ü�� �ּҸ� CChildSocket ��ü�� �˷��ֱ� ���� �Լ��� ȣ��  
   pChild->SetListenSocket(this); // CChildSocket Ŭ������ ����ڰ� ������ �Լ�
   CChattingServerDlg* pMain = (CChattingServerDlg*)AfxGetMainWnd();//���� ���̾�α׸� ȣ���Ѵ�.
   POSITION pos;
   pos = m_ptrChildSocketList.AddTail(pChild);
   if (pos != NULL) {
	   if (pChild != NULL) {
		   pChild->GetPeerName(strIPAddress, uPortNumber);
	   }
	   pMain->m_client.AddString(strIPAddress);
	   pMain->player.push_back(0); //player���Ϳ� �÷��̾� �߰�. ���Ϳ� �� ������� �÷��̾� ��ȣ. ���빰�� ��ġ(now)
	   pMain->Invalidate();
	   int n= (pMain->m_client.GetCount())+1;//n�� �÷��̾� ��ȣ

	   char buf[1024];
	   
	  // buf = (char*)n;
	   //strcpy(buf, s.c_str());
	   //buf[0] = pMain->m_client.GetCount() + 1; buf[1] = 0; buf[2] = 0;
	   itoa(n, buf, 1024);
	   //sprintf(buf, "%d", n);
	   //BroadCast(buf, 1024);
	   SingleCast();

	   CString s;
	   s.Format(L"%s", buf);
	  
	   //AfxMessageBox(s);
	   //delete pChild; --> �̰� ���� �ٷ� ����ƴٰ� ����...���� ��!
   }


  //Ŭ���̾�Ʈ�� ������ ���� ����Ʈ-m_client-�� ����Ѵ�.
  pMain->m_List.AddString(_T("���� ���� ���"));
  //pMain->m_client.AddString(strIPAddress);
  pMain->m_List.SetCurSel(pMain->m_List.GetCount() -1);

  CAsyncSocket::OnAccept(nErrorCode);
}
//Ŭ���̾�Ʈ�� ������ ��,
void CListenSocket::CloseClientSocket(CSocket* pChild)
{
	CChattingServerDlg* pMain = (CChattingServerDlg*)AfxGetMainWnd();//���� ���̾�α׸� ȣ���Ѵ�.
	POSITION pos;
	CString strIPAddress = _T("");
	UINT uPortNumber = 0;
	int count = pMain->m_client.GetCount();
	pos = m_ptrChildSocketList.Find(pChild);
	if (pos != NULL) {
		if (pChild != NULL) {
			//���� ���� ���϶�! Ŭ���̾�Ʈ�� ������ �̷��� �Ѵ�.

			pChild->GetPeerName(strIPAddress, uPortNumber);
			AfxMessageBox(strIPAddress); //test --> ����ī
			AfxMessageBox(L"�÷��̾��� ������ ����Ǿ����ϴ�."); //test ����ī--> 
			//����Ʈ ��Ʈ�� ���� �� �� �ڿ������� �����!!!
			CString strFind = _T("");
			CString strTemp = _T("");
			int nIndex = pMain->m_client.FindStringExact(-1, strIPAddress);
			if (nIndex != LB_ERR)
			{
				pMain->m_client.GetText(nIndex, strFind); //index�� ��ġ�� ã�� ���ڿ� �ҷ�����
				pMain->m_client.DeleteString(nIndex);
				//strTemp.Format(_T("%d:%s"), nIndex, strFind);
				pMain->player.erase(pMain->player.begin() + nIndex);
				//AfxMessageBox(strTemp);
				pMain->Invalidate();
			}
			pChild->ShutDown();
			pChild->Close();

			m_ptrChildSocketList.RemoveAt(pos);

			delete pChild;
		}
    }
}


void CListenSocket::SendDice(int dice, int player)
{
	// TODO: ���⿡ ���� �ڵ� �߰�.
	pos_d = m_ptrChildSocketList.GetHeadPosition();
	CChildSocket* pChild = NULL;
	int len = sizeof dice;
	pChild = (CChildSocket*)m_ptrChildSocketList.GetNext(pos_d);
	//if(pos_d!=NULL)
		for (int i = 0; i < player; i++)
			pChild = (CChildSocket*)m_ptrChildSocketList.GetNext(pos_d);
	
	pChild->Send(&dice, len*2);
}


void CListenSocket::SingleCast()
{
	// TODO: ���⿡ ���� �ڵ� �߰�.
	POSITION pos;
	pos = m_ptrChildSocketList.GetHeadPosition();
	CChildSocket* pChild = NULL;
	int c;
	char ch[1024];
	CString str;

	while (pos != NULL)	{
		
		pChild = (CChildSocket*)m_ptrChildSocketList.GetNext(pos);
		c = m_ptrChildSocketList.GetSize()*100;

		if (pChild != NULL)	{
			//�� �޼����� �ٽ� �ش�. 
			//sprintf(ch, "%d", c);
			//sprintf(ch, "%d", c);
			//_itoa(c, ch, 10);
			//pChild->Send(ch, sizeof(ch));
			str.Format(_T("%d"), c);
			//   �̸� �ٽ� ������ �ް� �Ǹ� �̶� ����Ʈ�� ��µȴ�.(const char*)
			pChild->Send((LPCTSTR)str, str.GetLength() * 2);
			//AfxMessageBox(str);
			str= _T("");
			c=c*2;
		}
	}
}

void CListenSocket::multicast(CString money)
{
	// TODO: ���⿡ ���� �ڵ� �߰�.
	POSITION pos;
	pos = m_ptrChildSocketList.GetHeadPosition();
	CChildSocket* pChild = NULL;
	CString str;
	
	str.Format(_T("%d��"), money);
	
	while (pos != NULL)
	{
		pChild = (CChildSocket*)m_ptrChildSocketList.GetNext(pos);
		if (pChild != NULL)
		{	
			pChild->Send((LPCTSTR)money, money.GetLength() * 2);
			AfxMessageBox(str);
		}
	}
}
