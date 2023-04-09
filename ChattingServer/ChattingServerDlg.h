// ChattingServerDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"
#include<vector>
#include "ListenSocket.h"
using namespace std;
// CChattingServerDlg 대화 상자
class CChattingServerDlg : public CDialog
{
// 생성입니다.
public:
	CListenSocket* m_pListenSocket;
	CChattingServerDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_CHATTINGSERVER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListBox m_List;
	afx_msg void OnDestroy();
	CListBox m_client;
	CListBox m_dice;
	CPoint location[32];
	CPoint go;
	int now;
	vector<int>player;
	int turn;
	CListBox p_num;
	CListBox p_city;
	CListBox p_structure;
	CString city[32];
	CListBox p_price;
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
