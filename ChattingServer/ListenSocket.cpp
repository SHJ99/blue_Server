// ListenSocket.cpp : 구현 파일입니다.
//
#include "stdafx.h"
#include "ChattingServer.h"
#include "ListenSocket.h"
#include<iostream>
using namespace std;
//리슨 소켓 -> 연결되었는지 안 연결되었는지
//서버 접속 실패? 서버 접속 성공하기

// CListenSocket

CListenSocket::CListenSocket()
{
}

CListenSocket::~CListenSocket()
{
}

//그러니까, 지금까지 메세지를 받은 것을 
// CListenSocket 멤버 함수
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
			//이 메세지를 다시 준다. 
			pChild->Send(pszBuffer, len*2);
		}
	}
}

void CListenSocket::CloseChildSocket(CChildSocket* pChild)
{
	POSITION pos;
	//어떤 사람이 나갔다면?
	pos = m_ptrChildSocketList.Find(pChild);
	if(pos != NULL)
	{
		//실제로 연결을 종료한다.
		if(pChild != NULL)
		{
			//실제 연결 셧다운
			pChild->ShutDown();
			pChild->Close();
		}
		//삭제한다.
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
     AfxMessageBox(_T("접속허용실패"));
     return;
   }

   SOCKADDR_IN addr;
   // CListenSocket 객체의 주소를 CChildSocket 객체에 알려주기 위한 함수를 호출  
   pChild->SetListenSocket(this); // CChildSocket 클래스에 사용자가 정의한 함수
   CChattingServerDlg* pMain = (CChattingServerDlg*)AfxGetMainWnd();//서버 다이얼로그를 호출한다.
   POSITION pos;
   pos = m_ptrChildSocketList.AddTail(pChild);
   if (pos != NULL) {
	   if (pChild != NULL) {
		   pChild->GetPeerName(strIPAddress, uPortNumber);
	   }
	   pMain->m_client.AddString(strIPAddress);
	   pMain->player.push_back(0); //player벡터에 플레이어 추가. 벡터에 든 순서대로 플레이어 번호. 내용물은 위치(now)
	   pMain->Invalidate();
	   int n= (pMain->m_client.GetCount())+1;//n은 플레이어 번호

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
	   //delete pChild; --> 이거 쓰면 바로 연결됐다가 끝남...지울 것!
   }


  //클라이언트가 접속해 옴을 리스트-m_client-에 출력한다.
  pMain->m_List.AddString(_T("서버 접속 허용"));
  //pMain->m_client.AddString(strIPAddress);
  pMain->m_List.SetCurSel(pMain->m_List.GetCount() -1);

  CAsyncSocket::OnAccept(nErrorCode);
}
//클라이언트가 닫혔을 때,
void CListenSocket::CloseClientSocket(CSocket* pChild)
{
	CChattingServerDlg* pMain = (CChattingServerDlg*)AfxGetMainWnd();//서버 다이얼로그를 호출한다.
	POSITION pos;
	CString strIPAddress = _T("");
	UINT uPortNumber = 0;
	int count = pMain->m_client.GetCount();
	pos = m_ptrChildSocketList.Find(pChild);
	if (pos != NULL) {
		if (pChild != NULL) {
			//게임 실행 중일때! 클라이언트가 나가면 이렇게 한다.

			pChild->GetPeerName(strIPAddress, uPortNumber);
			AfxMessageBox(strIPAddress); //test --> 유레카
			AfxMessageBox(L"플레이어의 연결이 종료되었습니다."); //test 유레카--> 
			//리스트 컨트롤 삭제 할 때 뒤에서부터 지우기!!!
			CString strFind = _T("");
			CString strTemp = _T("");
			int nIndex = pMain->m_client.FindStringExact(-1, strIPAddress);
			if (nIndex != LB_ERR)
			{
				pMain->m_client.GetText(nIndex, strFind); //index에 위치한 찾는 문자열 불러오기
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
	// TODO: 여기에 구현 코드 추가.
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
	// TODO: 여기에 구현 코드 추가.
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
			//이 메세지를 다시 준다. 
			//sprintf(ch, "%d", c);
			//sprintf(ch, "%d", c);
			//_itoa(c, ch, 10);
			//pChild->Send(ch, sizeof(ch));
			str.Format(_T("%d"), c);
			//   이를 다시 재전송 받게 되며 이때 리스트에 출력된다.(const char*)
			pChild->Send((LPCTSTR)str, str.GetLength() * 2);
			//AfxMessageBox(str);
			str= _T("");
			c=c*2;
		}
	}
}

void CListenSocket::multicast(CString money)
{
	// TODO: 여기에 구현 코드 추가.
	POSITION pos;
	pos = m_ptrChildSocketList.GetHeadPosition();
	CChildSocket* pChild = NULL;
	CString str;
	
	str.Format(_T("%d원"), money);
	
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
