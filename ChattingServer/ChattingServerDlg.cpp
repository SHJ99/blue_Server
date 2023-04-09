// ChattingServerDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "ChattingServer.h"
#include "ChattingServerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
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


// CChattingServerDlg ��ȭ ����




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


// CChattingServerDlg �޽��� ó����

BOOL CChattingServerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	/////////////////////////////////////////////////////////////////////////
	//Listen ���� ����
	/////////////////////////////////////////////////////////////////////////
	m_pListenSocket = new CListenSocket;
	//TCP ������ �����ϰ� 21000�� ��Ʈ���� ������ ����Ѵ�.
	//port(���������� �� ū ����) ,nSocketType
	if(m_pListenSocket->Create(7000, SOCK_STREAM))
	{
		//
		if(m_pListenSocket->Listen())
		{
		}
		else
		{
			//����, �̹� �ش� ��Ʈ�� ����� ���α׷��� �ִٸ� �����Ѵ�.
			AfxMessageBox(_T("Failed to LISTEN."));
		}
	}
	else
	{
		AfxMessageBox(_T("Failed to create socket for listen.") );
	}

	now = 0;
	turn = 0;
	
	CString str; //city�迭�� ���ø� �ֱ�

	str.Format(L"���");
	city[0] = str;
	str.Format(L"Ÿ�̺���");
	city[1] = str;
	str.Format(L"����¡");
	city[2] = str;
	str.Format(L"���Ҷ�");
	city[3] = str;
	str.Format(L"���ֵ�");
	city[4] = str;
	str.Format(L"�̰�����");
	city[5] = str;
	str.Format(L"ī�̷�");
	city[6] = str;
	str.Format(L"�̽�ź��");
	city[7] = str;
	str.Format(L"���ε�");
	city[8] = str;
	str.Format(L"���׳�");
	city[9] = str;
	str.Format(L"�����ϰ�");
	city[10] = str;
	str.Format(L"����Ȧ��");
	city[11] = str;
	str.Format(L"���ڵ忩����");
	city[12] = str;
	str.Format(L"����");
	city[13] = str;
	str.Format(L"������");
	city[14] = str;
	str.Format(L"��Ÿ��");
	city[15] = str;
	str.Format(L"������ݼ���");
	city[16] = str;
	str.Format(L"�ο��뽺���̷���");
	city[17] = str;
	str.Format(L"���Ŀ��");
	city[18] = str;
	str.Format(L"�õ��");
	city[19] = str;
	str.Format(L"�λ�");
	city[20] = str;
	str.Format(L"�Ͽ���");
	city[21] = str;
	str.Format(L"������");
	city[22] = str;
	str.Format(L"���帮��");
	city[23] = str;
	str.Format(L"���ֿ���");
	city[24] = str;
	str.Format(L"����");
	city[25] = str;
	str.Format(L"�ĸ�");
	city[26] = str;
	str.Format(L"�θ�");
	city[27] = str;
	str.Format(L"����");
	city[28] = str;
	str.Format(L"����");
	city[29] = str;
	str.Format(L"�����������");
	city[30] = str;
	str.Format(L"����");
	city[31] = str;
	
	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CChattingServerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
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
	for (int i = 7; i >= 0; i--) { //�Ʒ�
		dc.Rectangle(110 + i * 100, 810, 210 + i * 100, 910);

		location[j].x = i * 100 + 160;  //�迭�� �� ĭ ��ġ���� ����
		location[j].y = 860;
		j++;
	}
	for (int i = 7; i >= 0; i--) { //����
		dc.Rectangle(10, 110 + i * 100, 110, 210 + i * 100);
		location[j].x = 60;
		location[j].y = i * 100 + 160;
		j++;
	}
	for (int i = 0; i < 8; i++) { //��
		dc.Rectangle(10 + i * 100, 10, 110 + i * 100, 110);
		location[j].x = i * 100 + 60;
		location[j].y = 60;
		j++;
	}
	for (int i = 0; i < 8; i++) { //������
		dc.Rectangle(810, 10 + i * 100, 910, 110 + i * 100);
		location[j].x = 860;
		location[j].y = i * 100 + 60;
		j++;
	}
	for (int i = 0; i < 32; i++) { //�����ǿ� ���ø� ���
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

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CChattingServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CChattingServerDlg::OnDestroy()
{
   CDialog::OnDestroy();

   //ȭ���� �ݾ��� ��, ����� ��� Ŭ���̾�Ʈ�� �ݾ��ش�. 
   //���� ����Ʈ���� null�� �ƴϸ� ��� �ݺ���Ų��.
   POSITION pos;
   pos=m_pListenSocket->m_ptrChildSocketList.GetHeadPosition( );
   CChildSocket* pChild = NULL;

   while(pos != NULL){
	   //�� ���� ����� ������ ���´�.
     pChild=(CChildSocket* )m_pListenSocket->m_ptrChildSocketList.GetNext(pos);

     if(pChild != NULL){
		 //����� Ŭ���̾�Ʈ �˴ٿ�
		 pChild->ShutDown();
         //�ݱ�
		 pChild->Close(); 
         delete pChild;
       }
   }
   //�ڽ�(����)�� �˴ٿ�
   m_pListenSocket->ShutDown();
   m_pListenSocket->Close();
}


BOOL CChattingServerDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
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

	// TODO:  ���⼭ DC�� Ư���� �����մϴ�.
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkColor(RGB(214, 230, 240));
	}


	// TODO:  �⺻���� �������� ������ �ٸ� �귯�ø� ��ȯ�մϴ�.
	return hbr;
}
