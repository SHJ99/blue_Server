// ChildSocket.cpp : ���� �����Դϴ�.
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


// CChildSocket ��� �Լ�

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

	//�޼��� �ޱ�
	char szBuffer[1024];
	::ZeroMemory(szBuffer, 1024);
	
	//api �Լ�, 1024 ũ�⸸ŭ 0�� Ŭ�����Ų��. 
	//����� Ŭ���̾�Ʈ�� IP�ּҿ� ��Ʈ ��ȣ�� �˾Ƴ���.
	//��Ʈ ������ ������ ���� �ʴ´�. length 
	GetPeerName(strIPAddress, uPortNumber);
	//������ char �����͸� �����Ѵ�.
	int len;

	if ((len = Receive(szBuffer, 1024)) > 0) {
		CChattingServerDlg* pMain = (CChattingServerDlg*)AfxGetMainWnd();//���� ���̾�α׸� ȣ���Ѵ�.
		//tmp.Format(_T("%s"), szBuffer);
		if (isdigit(szBuffer[0])) { //isdigit �Լ��� 0~9 �� �ش��ϴ� ASCII ���� �Է����� ������ 0�� �ƴ� ��(True)
			tmp.Format(_T("%s"), szBuffer);
			int d = _ttoi(tmp);

			if (d > 1000) { //Ŭ���̾�Ʈ���� ���� ����� �����. ��� �� ������ 1000 �̻�.
				
				pMain->p_price.AddString(tmp);
				pMain->Invalidate();
			}
			else { //d�� 1000 ����, �� �ֻ��� ���� ���
				CListenSocket* pServerSocket = (CListenSocket*)m_pListenSocket;

				for (int i = 0; i < d; i++) { //�ֻ��� ����ŭ �÷��̾� ���� ���� ��ġ���� ����
					pMain->player[pMain->turn]++;
					if (pMain->player[pMain->turn] > 31)
						pMain->player[pMain->turn] = 0; //������
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

				dex=pMain->p_city.FindString(-1, css); //ã�Ҵٸ� �ε��� ��ȣ ����
				
				if (dex!=-1) { //����Ḧ ��� Ŭ���̾�Ʈ�� ����
					pMain->p_price.GetText(dex, cs);
					Send((LPCTSTR)cs, cs.GetLength() * 2);
					//cs.Format(L"%d sell money", dex);
					//pServerSocket->multicast(cs);
					AfxMessageBox(cs);
				}
				
				
				if (pMain->turn + 1 >= pMain->m_client.GetCount()) //���� �ѱ��
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
				//pServerSocket->SendDice(d, j); //j�� �÷��̾� ��ȣ. 1 2 3 4 �� �ϳ�.
				//j = 0;
				pServerSocket->BroadCast(szBuffer, len);

			}
		}
		else{
			//�����͸� �����Ͽ��ٸ� ���� �޽����� ����Ʈ�� ����Ѵ�.
			//CChattingServerDlg* pMain = (CChattingServerDlg*)AfxGetMainWnd();//���� ���̾�α׸� ȣ���Ѵ�.
			tmp.Format(_T("%s"), szBuffer);
			CString st=tmp.Left(3);
			CString st2 = L"buy";
			CString gubun = tmp.Left(1);
			CString sharp = L";";
			//st.Format(_T("%s%s%s"), szBuffer[0], szBuffer[1], szBuffer[2]);
			
			//st.Format(_T("%s"), "buy hotel");
			//if (tmp.Compare(_T("buy hotel")))

			if (st.Compare(st2)==0) { //�÷��̾ �ǹ����� ���� ���. ������ ���ڿ� ���� buy �� ���.
				//�̹� ���� �Ѿ���� -1�� �ǹ����� ���
				const int cp = (pMain->turn+1) % pMain->player.size(); //���� ���� �÷��̾� ��ȣ
				//if (cp == 1)
				//	cp = pMain->player.size(); //���� �÷��̾�, �� ���� �ǹ� ���� ������ ���� ����� �÷��̾� ��ȣ�� cp(current player)
				//else
				//	cp = pMain->turn-1;

				CString s, s2;
				s.Format(L"%d", cp); //�÷��̾� ��ȣ
				pMain->p_num.AddString(s);

				pMain->Invalidate();

				//s.Format(L"%s", pMain->city[pMain->player[pMain->turn]]); //���ø�
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
				//s.Format(L"%s", szBuffer); //�ǹ� ����
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
				//�����ǿ� �޽����� ���� ����Ѵ�.
				pMain->m_List.AddString(tmp);
				pMain->m_List.SetCurSel(pMain->m_List.GetCount() - 1);

				//����� ��� Ŭ���̾�Ʈ�� �ش� �޽����� �����Ѵ�.
				CListenSocket* pServerSocket = (CListenSocket*)m_pListenSocket;
				//������ ���� �޽����� �ٽ� ��� Ŭ���̾�Ʈ�� ����Ʈ�� �ѷ��ش�.
				pServerSocket->BroadCast(szBuffer, len);
			}
		}
		////������ int �����͸� �����Ѵ�.
	}

	CSocket::OnReceive(nErrorCode);
}

#include "ListenSocket.h"

void CChildSocket::OnClose(int nErrorCode)
{
   CListenSocket *pServerSocket=(CListenSocket *)m_pListenSocket; 
   //Ŭ���̾�Ʈ ������ �ݴ´�.
   pServerSocket->CloseClientSocket(this);
   CSocket::OnClose(nErrorCode);
}
