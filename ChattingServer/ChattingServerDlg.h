// ChattingServerDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"
#include<vector>
#include "ListenSocket.h"
using namespace std;
// CChattingServerDlg ��ȭ ����
class CChattingServerDlg : public CDialog
{
// �����Դϴ�.
public:
	CListenSocket* m_pListenSocket;
	CChattingServerDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_CHATTINGSERVER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
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
