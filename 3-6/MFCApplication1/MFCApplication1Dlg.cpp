
// MFCApplication1Dlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCApplication1Dlg 대화 상자



CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFCAPPLICATION1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDBLCLK()
	ON_LBN_SELCHANGE(IDC_LIST1, &CMFCApplication1Dlg::OnLbnSelchangeList1)
END_MESSAGE_MAP()


// CMFCApplication1Dlg 메시지 처리기

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	//9x9크기의 각각의 네모칸 좌표들을 구조체에 저장한다.				//초기화 하는 곳(함수) 여기서 초기화를 하면 우리가 C에서 int num = 0;이라고 초기화 했을 떄랑 같은 효과를 냄(생성자라고 보면 편함)
	CFile inFile(_T("input.txt"), CFile::modeRead);						//온페인트에서 파일을 받아오는게 아니고
	CString str;														//여기 초기화하는곳에서 택스트파일을 받아오게 한 다음
	CString msg;														//상자안에 넣는 작업을 여기서 해줘야함
	char buf[1000] = { 0 };											
	//글자 출력을 위한 cstring 선언									
	memset(&buf, NULL, sizeof(buf));								
	inFile.Read(buf, sizeof(buf));									
	inFile.Close();													
	for (int y = 0; y < 9; y++) {
		for (int x = 0; x < 9; x++) {
			if (y == 0 && x == 0) str = strtok(buf, " ");
			else str = strtok(NULL, " \n");

			sdk[y][x].rc = { (1 + x) * 40, (1 + y) * 40, (40 * (x + 2)) + 1, (40 * (y + 2)) + 1 };
			sdk[y][x].input = _ttoi(str);

			if (sdk[y][x].input != 0)		//input이 int형으로 되어 있기 때문에 '0' 쓸 필요 없이 0만 써도 인식이 됨. 
			{
				sdk[y][x].grayBox = true;	//회색 박스 판별법, 이것 역시 초기화 구간을 여기서 해야 어느게 회색박스인지 판별 가능함(헤더파일의 구조체에 불값 따로 선언해줬음.
			}

			sdk[y][x].Duplicate = false;
		}
	}
	win = false;
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCApplication1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

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
		CDialogEx::OnPaint();
		CClientDC dc(this);

		for (int y = 0; y < 9; y++)
		{
			for (int x = 0; x < 9; x++)
			{
				for (int i = 0; i < 9; i++)
				{
					for (int j = 0; j < 9; j++)
					{
						if (sdk[y][x].Duplicate == false && sdk[i][j].Duplicate == false && sdk[y][x].input != 0 && sdk[i][j].input != 0)
						{
							win = true;
						}
						else win = false;
					}
				}
			}
		}
		/*81칸의 네모칸을 만들면서 메모장을 불러와 스도쿠 판에 숫자들을 출력*/
		for (int y = 0; y < 9; y++)
		{	
			for (int x = 0; x < 9; x++) {

				dc.Rectangle(sdk[y][x].rc); //여기서 처음 네모칸을 81개만들고	
				/*0이 아닐시 회색으로 칠한다.*/
				if (sdk[y][x].grayBox == true) { //회색상자 불값 여부가 트루값일때 상자를 회색처리해줌
					CBrush brush, *oldBrush;
					brush.CreateSolidBrush(RGB(211, 211, 211));
					oldBrush = dc.SelectObject(&brush);
					/*색깔을 넣은 네모칸을 만든다*/
					dc.Rectangle(sdk[y][x].rc);
					dc.SelectObject(oldBrush);
					brush.DeleteObject();
					sdk[y][x].clicked = false;
					/*색칠한 이후 숫자들을 출력*/
				}
				if (sdk[y][x].input != 0)	//회색처리 상자가 위로 가야 그 위에 숫자를 덧 붙여도 상자에 안 가려지기 때문에 여기에 숫자 출력하는 것을 선언을 함. 0이 아닌 숫자들만 나타나면 되기 때문에
				{							//구지 다른 조건문 없이 != 0만 해주면 자동으로 0이 아닌 숫자가 되면 출력이 되게 함 이건 전에 말했듯 온페인트함수가 계속 업데이트를 해주기 때문임
					CString str;
					/*Duplicate가 ture일 경우 빨간색으로 색칠*/
					if (sdk[y][x].Duplicate == true) {
						dc.SetTextColor(RGB(255, 0, 0));
					}
					else
						dc.SetTextColor(RGB(0, 0, 0));
					dc.SetBkMode(TRANSPARENT);
					str.Format(_T("%d"), sdk[y][x].input);				//input이 인트값이기 때문에 이렇게 만들어줘야 숫자 값을 받아올 수 있음
					dc.TextOut((sdk[y][x].rc.right + sdk[y][x].rc.left) / 2 - 5, (sdk[y][x].rc.bottom + sdk[y][x].rc.top) / 2 - 5, str);		//출력 부분 앞의 좌표는 상자의 중앙 좌표, 이건 알아서 수정바람
				}
			}
		}
		/*Click Event가 진행 중일 때 색을 설정*/
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				if (sdk[i][j].clicked == true)
				{
					CBrush brush, *oldBrush;
					brush.CreateSolidBrush(RGB(0, 255, 0));
					oldBrush = dc.SelectObject(&brush);
					dc.Rectangle(sdk[i][j].rc);
					dc.SelectObject(oldBrush);
					brush.DeleteObject();
				}
			}
		}
		/*게임 종료하는 부분*/
		if (win == true)
		{
			MessageBox(_T("게임을 종료합니다"), _T("Sudoku"), MB_ICONASTERISK);
		}
		
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication1Dlg::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	
	/*Click event를 처리하는 부분*/
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (sdk[i][j].rc.PtInRect(point))
			{	
				sdk[i][j].clicked = true;	//Click event 시작
			}
			else
			{
				sdk[i][j].clicked = false; //Click event 종료
			}
		}
	}

	Invalidate(TRUE);
	CDialogEx::OnLButtonDblClk(nFlags, point);
}


BOOL CMFCApplication1Dlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	//키 입력시 Event 수행
	if (pMsg->message == WM_KEYDOWN)  
	{	
		//숫자메세지 박스
		/*각 숫자가 입력 되면 처리하는 부분*/
		int row = 0;
		int cal = 0;
		int Overlap = 0;
		int check = 0;

		/*1을 입력받았을 경우 MessageBox를 띄우고 숫자를 입력*/
		if (pMsg->wParam - 48 == 1)
		{	

			MessageBox(L"1.", L"키보드", MB_OK);

			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					if (sdk[i][j].clicked == true) {
						sdk[i][j].input = 1;
						row = i;
						cal = j;
						Overlap = sdk[i][j].input;
						//sdk[i][j].Duplicate = true;
					}
				}
			}
			//가로 세로 중복을 찾기 위한 for문
			for (int i = 0; i < 9; i++)
			{
			if (i == row) continue;

			if (sdk[i][cal].input == Overlap) {
				sdk[i][cal].Duplicate = true;
				sdk[row][cal].Duplicate = true;
			}

			else {
				sdk[i][cal].Duplicate = false;
				//sdk[row][cal].Duplicate = false;
			}
			}
			//가로 세로 중복을 찾기 위한 for문
			for (int i = 0; i < 9; i++)
			{
			if (i == cal) continue;

			if (sdk[row][i].input == Overlap) {
				sdk[row][i].Duplicate = true;
				sdk[row][cal].Duplicate = true;
				check = 1;
			}

			else {
				sdk[row][i].Duplicate = false;
				//if(check == 0)sdk[row][cal].Duplicate = false;
			}
			}
		}
		/*2를 입력받았을 경우 MessageBox를 띄우고 숫자를 입력*/
		else if (pMsg->wParam - 48 == 2)
		{
			MessageBox(L"2", L"키보드", MB_OK);

			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					if (sdk[i][j].clicked == true) {
						sdk[i][j].input = 2;
					}
				}
			}//가로 세로 중복을 찾기 위한 for문
		}
		/*3을 입력받았을 경우 MessageBox를 띄우고 숫자를 입력*/
		else if (pMsg->wParam - 48 == 3)
		{
			MessageBox(L"3", L"키보드", MB_OK);

			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					if (sdk[i][j].clicked == true) {
						sdk[i][j].input = 3;
					}
				}
			}
		}
		/*4를 입력받았을 경우 MessageBox를 띄우고 숫자를 입력*/
		else if (pMsg->wParam - 48 == 4)
		{
			MessageBox(L"4", L"키보드", MB_OK);

			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					if (sdk[i][j].clicked == true) {
						sdk[i][j].input = 4;
					}
				}
			}
		}
		/*5를 입력받았을 경우 MessageBox를 띄우고 숫자를 입력*/
		else if (pMsg->wParam - 48 == 5)
		{
			MessageBox(L"5", L"키보드", MB_OK);

			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					if (sdk[i][j].clicked == true) {
						sdk[i][j].input = 5;
					}
				}
			}
		}
		/*6을 입력받았을 경우 MessageBox를 띄우고 숫자를 입력*/
		else if (pMsg->wParam - 48 == 6)
		{
			MessageBox(L"6", L"키보드", MB_OK);

			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					if (sdk[i][j].clicked == true) {
						sdk[i][j].input = 6;
					}
				}
			}
		}
		/*7을 입력받았을 경우 MessageBox를 띄우고 숫자를 입력*/
		else if (pMsg->wParam - 48 == 7)
		{
			MessageBox(L"7", L"키보드", MB_OK);

			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					if (sdk[i][j].clicked == true) {
						sdk[i][j].input = 7;
					}
				}
			}
		}
		/*8을 입력받았을 경우 MessageBox를 띄우고 숫자를 입력*/
		else if (pMsg->wParam - 48 == 8)
		{
			MessageBox(L"8", L"키보드", MB_OK);

			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					if (sdk[i][j].clicked == true) {
						sdk[i][j].input = 8;
					}
				}
			}
		}
		/*9를 입력받았을 경우 MessageBox를 띄우고 숫자를 입력*/
		else if (pMsg->wParam - 48 == 9)
		{
			MessageBox(L"9", L"키보드", MB_OK);

			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					if (sdk[i][j].clicked == true) {
						sdk[i][j].input = 9;
					}
				}
			}
		}
		/*esc키를 입력받았을 경우 MessageBox를 띄우고 원래 숫자를 지운다.*/
		else if (pMsg->wParam == VK_ESCAPE)
		{
			int row;
			int cal;
			int Overlap;
			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					if (sdk[i][j].clicked == true) {
						Overlap = sdk[i][j].input;
						sdk[i][j].input = 0;
						sdk[i][j].clicked = false;
						sdk[i][j].Duplicate = false;
						row = i;
						cal = j;
					}
				}
			}
			//가로 세로 중복을 찾기 위한 for문
			for (int i = 0; i < 9; i++)
			{
				if (i == row) continue;

				if (sdk[i][cal].input == Overlap) {
					sdk[i][cal].Duplicate = false;
					//sdk[row][cal].Duplicate = true;
				}

			}
			//가로 세로 중복을 찾기 위한 for문
			for (int i = 0; i < 9; i++)
			{
				if (i == cal) continue;

				if (sdk[row][i].input == Overlap) {
					sdk[row][i].Duplicate = false;
					//sdk[row][cal].Duplicate = true;
					//check = 1;
				}
			}
		}
		if (pMsg->wParam == VK_ESCAPE) return true;
		//MessageBox(L"숫자를 입력하시오..", L"키보드", MB_OK);
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				sdk[i][j].clicked = false;
			}
		}
		Invalidate(TRUE);
	}

	
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CMFCApplication1Dlg::OnLbnSelchangeList1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
