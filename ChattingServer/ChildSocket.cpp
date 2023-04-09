// ChildSocket.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ChattingServer.h"
#include "ChildSocket.h"


// CChildSocket

CChildSocket::CChildSocket()
{
}

CChildSocket::~CChildSocket()
{
}


// CChildSocket 멤버 함수

void CChildSocket::SetListenSocket(CAsyncSocket* pSocket)
{
	m_pListenSocket = pSocket;
}
#include "ChattingServerDlg.h"
#include "ChildSocket.h"
#include "ListenSocket.h"
void CChildSocket::OnReceive(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
	CString tmp = _T(""), strIPAddress = _T("");
	UINT uPortNumber = 0;

	//메세지 받기
	char szBuffer[1024];
	::ZeroMemory(szBuffer, 1024);
	
	//api 함수, 1024 크기만큼 0로 클리어시킨다. 
	//연결된 클라이언트의 IP주소와 포트 번호를 알아낸다.
	//포트 네임을 받지만 쓰지 않는다. length 
	GetPeerName(strIPAddress, uPortNumber);
	//실제로 char 데이터를 수신한다.
	int len;

	if ((len = Receive(szBuffer, 1024)) > 0) {
		CChattingServerDlg* pMain = (CChattingServerDlg*)AfxGetMainWnd();//서버 다이얼로그를 호출한다.
		//tmp.Format(_T("%s"), szBuffer);
		if (isdigit(szBuffer[0])) { //isdigit 함수는 0~9 에 해당하는 ASCII 값이 입력으로 들어오면 0이 아닌 값(True)
			tmp.Format(_T("%s"), szBuffer);
			int d = _ttoi(tmp);

			if (d > 1000) { //클라이언트에서 각자 계산한 통행료. 모든 돈 단위는 1000 이상.
				
				pMain->p_price.AddString(tmp);
				pMain->Invalidate();
			}
			else { //d가 1000 이하, 즉 주사위 값인 경우
				CListenSocket* pServerSocket = (CListenSocket*)m_pListenSocket;

				for (int i = 0; i < d; i++) { //주사위 값만큼 플레이어 벡터 안의 위치정보 갱신
					pMain->player[pMain->turn]++;
					if (pMain->player[pMain->turn] > 31)
						pMain->player[pMain->turn] = 0; //시작점
				}
				
				/*
				for (int i = 0; i < pMain->p_city.GetCount(); i++) {
					CString cs;
					pMain->p_city.GetText(i, cs);
					if (pMain->city[pMain->player[pMain->turn]].Compare(cs) == 0)
						pMain->p_price.GetText(i, cs);
						Send((LPCTSTR)cs, cs.GetLength() * 2);
						break;
				}
				//*/
				
				int dex=0;
				CString cs;
				CString css = pMain->city[pMain->player[pMain->turn]];

				dex=pMain->p_city.FindString(-1, css); //찾았다면 인덱스 번호 삽입
				
				if (dex!=-1) { //통행료를 모든 클라이언트에 전송
					pMain->p_price.GetText(dex, cs);
					Send((LPCTSTR)cs, cs.GetLength() * 2);
					//cs.Format(L"%d sell money", dex);
					//pServerSocket->multicast(cs);
					AfxMessageBox(cs);
				}
				
				
				if (pMain->turn + 1 >= pMain->m_client.GetCount()) //턴을 넘긴다
					pMain->turn = 0;
				else
					pMain->turn++;

				pMain->Invalidate();
				
				//tmp.Format(_T("[%s] : %s"), strIPAddress, szBuffer);
				tmp.Format(_T("[%s] : %d"), strIPAddress, d);
				//tmp.Format(_T("[%s] : %s"), strIPAddress, di);

				pMain->m_dice.AddString(tmp);
				pMain->m_dice.SetCurSel(pMain->m_List.GetCount() - 1);

				pMain->Invalidate();

				//CListenSocket* pServerSocket = (CListenSocket*)m_pListenSocket;
				//pChild->SetListenSocket(this);
				//pMain->m_client.AddString(strIPAddress);  //pServerSocket->m_ptrChildSocketList.GetCount()
				int j = 0;
				CString str;
				for (int i = 0; i < pMain->m_client.GetCount(); i++) {
					//SetListenSocket(pServerSocket);
					pMain->m_client.GetText(i, str);
					if (strIPAddress == str)
						break;
					else
						j++;
				}
				//pServerSocket->SendDice(d, j); //j가 플레이어 번호. 1 2 3 4 중 하나.
				//j = 0;
				pServerSocket->BroadCast(szBuffer, len);

			}
		}
		else{
			//데이터를 수신하였다면 받은 메시지를 리스트에 출력한다.
			//CChattingServerDlg* pMain = (CChattingServerDlg*)AfxGetMainWnd();//서버 다이얼로그를 호출한다.
			tmp.Format(_T("%s"), szBuffer);
			CString st=tmp.Left(3);
			CString st2 = L"buy";
			CString gubun = tmp.Left(1);
			CString sharp = L";";
			//st.Format(_T("%s%s%s"), szBuffer[0], szBuffer[1], szBuffer[2]);
			
			//st.Format(_T("%s"), "buy hotel");
			//if (tmp.Compare(_T("buy hotel")))

			if (st.Compare(st2)==0) { //플레이어별 건물구입 정보 기록. 수신한 문자열 앞이 buy 일 경우.
				//이미 턴은 넘어갔으니 -1로 건물정보 기록
				const int cp = (pMain->turn+1) % pMain->player.size(); //현재 턴인 플레이어 번호
				//if (cp == 1)
				//	cp = pMain->player.size(); //전턴 플레이어, 즉 지금 건물 구입 정보를 날린 사람의 플레이어 번호가 cp(current player)
				//else
				//	cp = pMain->turn-1;

				CString s, s2;
				s.Format(L"%d", cp); //플레이어 번호
				pMain->p_num.AddString(s);

				pMain->Invalidate();

				//s.Format(L"%s", pMain->city[pMain->player[pMain->turn]]); //도시명
				////////////////////////////////////////////////////////////////////////////

				const int city_no = pMain->player[cp];

				//ASSERT(cp - 1 >= 0 && cp - 1 < pMain->player.size());
				ASSERT(city_no >= 0 && city_no < 32);
				////////////////////////////////////////////////////////////////////////////

				s.Format(L"%s", pMain->city[city_no]);
				pMain->p_city.AddString(s);

				pMain->Invalidate();

				AfxExtractSubString(s, tmp, 0, ';'); //buy Hotel
				AfxExtractSubString(s2, tmp, 1, ';');
				//s.Format(L"%s", szBuffer); //건물 종류
				pMain->p_structure.AddString(s);
				pMain->p_price.AddString(s2);

				pMain->Invalidate();
			}
			/*
			if(gubun.Compare(sharp) == 0) {

				
				CString player, city, s, s2;
				AfxExtractSubString(s, tmp, 0, ';'); //player
				AfxExtractSubString(s2, tmp, 1, ';'); //city
				AfxMessageBox(s);
				AfxMessageBox(s2);
			//
			//
			}*/
			else {
				tmp.Format(_T("[%s] : %s"), strIPAddress, szBuffer);
				//아이피와 메시지를 같이 출력한다.
				pMain->m_List.AddString(tmp);
				pMain->m_List.SetCurSel(pMain->m_List.GetCount() - 1);

				//연결된 모든 클라이언트에 해당 메시지를 전송한다.
				CListenSocket* pServerSocket = (CListenSocket*)m_pListenSocket;
				//서버가 받은 메시지를 다시 모든 클라이언트의 리스트에 뿌려준다.
				pServerSocket->BroadCast(szBuffer, len);
			}
		}
		////실제로 int 데이터를 수신한다.
	}

	CSocket::OnReceive(nErrorCode);
}

#include "ListenSocket.h"

void CChildSocket::OnClose(int nErrorCode)
{
   CListenSocket *pServerSocket=(CListenSocket *)m_pListenSocket; 
   //클라이언트 소켓을 닫는다.
   pServerSocket->CloseClientSocket(this);
   CSocket::OnClose(nErrorCode);
}
