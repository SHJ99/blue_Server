// ChattingServerDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "ChattingServer.h"
#include "ChattingServerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CChattingServerDlg 대화 상자




CChattingServerDlg::CChattingServerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChattingServerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CChattingServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_List);
	DDX_Control(pDX, IDC_LIST2, m_client);
	DDX_Control(pDX, IDC_LIST3, m_dice);
	DDX_Control(pDX, IDC_LIST4, p_num);
	DDX_Control(pDX, IDC_LIST5, p_city);
	DDX_Control(pDX, IDC_LIST6, p_structure);
	DDX_Control(pDX, IDC_LIST7, p_price);
}

BEGIN_MESSAGE_MAP(CChattingServerDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CChattingServerDlg 메시지 처리기

BOOL CChattingServerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	/////////////////////////////////////////////////////////////////////////
	//Listen 소켓 생성
	/////////////////////////////////////////////////////////////////////////
	m_pListenSocket = new CListenSocket;
	//TCP 소켓을 생성하고 21000번 포트에서 연결을 대기한다.
	//port(번지수보다 더 큰 단위) ,nSocketType
	if(m_pListenSocket->Create(7000, SOCK_STREAM))
	{
		//
		if(m_pListenSocket->Listen())
		{
		}
		else
		{
			//만일, 이미 해당 포트를 열어둔 프로그램이 있다면 실패한다.
			AfxMessageBox(_T("Failed to LISTEN."));
		}
	}
	else
	{
		AfxMessageBox(_T("Failed to create socket for listen.") );
	}

	now = 0;
	turn = 0;
	
	CString str; //city배열에 도시명 넣기

	str.Format(L"출발");
	city[0] = str;
	str.Format(L"타이베이");
	city[1] = str;
	str.Format(L"베이징");
	city[2] = str;
	str.Format(L"마닐라");
	city[3] = str;
	str.Format(L"제주도");
	city[4] = str;
	str.Format(L"싱가포르");
	city[5] = str;
	str.Format(L"카이로");
	city[6] = str;
	str.Format(L"이스탄불");
	city[7] = str;
	str.Format(L"무인도");
	city[8] = str;
	str.Format(L"아테네");
	city[9] = str;
	str.Format(L"코펜하겐");
	city[10] = str;
	str.Format(L"스톡홀름");
	city[11] = str;
	str.Format(L"콩코드여객기");
	city[12] = str;
	str.Format(L"베른");
	city[13] = str;
	str.Format(L"베를린");
	city[14] = str;
	str.Format(L"오타와");
	city[15] = str;
	str.Format(L"복지기금수령");
	city[16] = str;
	str.Format(L"부에노스아이레스");
	city[17] = str;
	str.Format(L"상파울로");
	city[18] = str;
	str.Format(L"시드니");
	city[19] = str;
	str.Format(L"부산");
	city[20] = str;
	str.Format(L"하와이");
	city[21] = str;
	str.Format(L"리스본");
	city[22] = str;
	str.Format(L"마드리드");
	city[23] = str;
	str.Format(L"우주여행");
	city[24] = str;
	str.Format(L"도쿄");
	city[25] = str;
	str.Format(L"파리");
	city[26] = str;
	str.Format(L"로마");
	city[27] = str;
	str.Format(L"런던");
	city[28] = str;
	str.Format(L"뉴욕");
	city[29] = str;
	str.Format(L"복지기금접수");
	city[30] = str;
	str.Format(L"서울");
	city[31] = str;
	
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CChattingServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CChattingServerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}

	CClientDC dc(this);
	//CBrush myBrush(RGB(224, 240, 250));
	//dc.SelectObject(&myBrush);
	int j = 0;
	for (int i = 7; i >= 0; i--) { //아래
		dc.Rectangle(110 + i * 100, 810, 210 + i * 100, 910);

		location[j].x = i * 100 + 160;  //배열에 각 칸 위치정보 삽입
		location[j].y = 860;
		j++;
	}
	for (int i = 7; i >= 0; i--) { //왼쪽
		dc.Rectangle(10, 110 + i * 100, 110, 210 + i * 100);
		location[j].x = 60;
		location[j].y = i * 100 + 160;
		j++;
	}
	for (int i = 0; i < 8; i++) { //위
		dc.Rectangle(10 + i * 100, 10, 110 + i * 100, 110);
		location[j].x = i * 100 + 60;
		location[j].y = 60;
		j++;
	}
	for (int i = 0; i < 8; i++) { //오른쪽
		dc.Rectangle(810, 10 + i * 100, 910, 110 + i * 100);
		location[j].x = 860;
		location[j].y = i * 100 + 60;
		j++;
	}
	for (int i = 0; i < 32; i++) { //게임판에 도시명 출력
		SetBkMode(dc, TRANSPARENT);
		CString tmp = city[i];
		if (city[i].GetLength() > 4)
			tmp = city[i].Left(4);
		dc.TextOutW(location[i].x - 45, location[i].y - 45, tmp);
	}
	

	COLORREF c[5] = { RGB(255, 0, 0), RGB(0, 0, 255), RGB(255, 255, 0), RGB(255, 255, 255) };
	
	for (int i = 0; i < player.size(); i++) {
		go = location[player[i]];
		CBrush col = c[i];		
		dc.SelectObject(col);
		if(i==0) dc.Ellipse(go.x - 40, go.y - 40, go.x, go.y);
		else if(i==1) dc.Ellipse(go.x, go.y - 40, go.x + 40, go.y);
		else if(i==2) dc.Ellipse(go.x-40, go.y, go.x , go.y + 40);
		else if(i==3) dc.Ellipse(go.x, go.y, go.x, go.y + 40);
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CChattingServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CChattingServerDlg::OnDestroy()
{
   CDialog::OnDestroy();

   //화면을 닫았을 때, 연결된 모든 클라이언트를 닫아준다. 
   //소켓 리스트에서 null이 아니면 계속 반복시킨다.
   POSITION pos;
   pos=m_pListenSocket->m_ptrChildSocketList.GetHeadPosition( );
   CChildSocket* pChild = NULL;

   while(pos != NULL){
	   //그 다음 연결된 소켓을 끊는다.
     pChild=(CChildSocket* )m_pListenSocket->m_ptrChildSocketList.GetNext(pos);

     if(pChild != NULL){
		 //연결된 클라이언트 셧다운
		 pChild->ShutDown();
         //닫기
		 pChild->Close(); 
         delete pChild;
       }
   }
   //자신(서버)도 셧다운
   m_pListenSocket->ShutDown();
   m_pListenSocket->Close();
}


BOOL CChattingServerDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CRect rect;
	GetClientRect(&rect);
	CBrush myBrush(RGB(214, 230, 240)); // dialog background color.

	CBrush* pOld = pDC->SelectObject(&myBrush);
	BOOL bRes = pDC->PatBlt(0, 0, rect.Width(), rect.Height(), PATCOPY);
	pDC->SelectObject(pOld); // restore old brush
	return bRes; // CDialog::OnEraseBkgnd(pDC);
}


HBRUSH CChattingServerDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkColor(RGB(214, 230, 240));
	}


	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}
