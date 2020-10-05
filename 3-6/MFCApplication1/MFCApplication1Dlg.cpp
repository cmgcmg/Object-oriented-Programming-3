
// MFCApplication1Dlg.cpp : ���� ����
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
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


// CMFCApplication1Dlg ��ȭ ����



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


// CMFCApplication1Dlg �޽��� ó����

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	//9x9ũ���� ������ �׸�ĭ ��ǥ���� ����ü�� �����Ѵ�.				//�ʱ�ȭ �ϴ� ��(�Լ�) ���⼭ �ʱ�ȭ�� �ϸ� �츮�� C���� int num = 0;�̶�� �ʱ�ȭ ���� ���� ���� ȿ���� ��(�����ڶ�� ���� ����)
	CFile inFile(_T("input.txt"), CFile::modeRead);						//������Ʈ���� ������ �޾ƿ��°� �ƴϰ�
	CString str;														//���� �ʱ�ȭ�ϴ°����� �ý�Ʈ������ �޾ƿ��� �� ����
	CString msg;														//���ھȿ� �ִ� �۾��� ���⼭ �������
	char buf[1000] = { 0 };											
	//���� ����� ���� cstring ����									
	memset(&buf, NULL, sizeof(buf));								
	inFile.Read(buf, sizeof(buf));									
	inFile.Close();													
	for (int y = 0; y < 9; y++) {
		for (int x = 0; x < 9; x++) {
			if (y == 0 && x == 0) str = strtok(buf, " ");
			else str = strtok(NULL, " \n");

			sdk[y][x].rc = { (1 + x) * 40, (1 + y) * 40, (40 * (x + 2)) + 1, (40 * (y + 2)) + 1 };
			sdk[y][x].input = _ttoi(str);

			if (sdk[y][x].input != 0)		//input�� int������ �Ǿ� �ֱ� ������ '0' �� �ʿ� ���� 0�� �ᵵ �ν��� ��. 
			{
				sdk[y][x].grayBox = true;	//ȸ�� �ڽ� �Ǻ���, �̰� ���� �ʱ�ȭ ������ ���⼭ �ؾ� ����� ȸ���ڽ����� �Ǻ� ������(��������� ����ü�� �Ұ� ���� ����������.
			}

			sdk[y][x].Duplicate = false;
		}
	}
	win = false;
	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CMFCApplication1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

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
		/*81ĭ�� �׸�ĭ�� ����鼭 �޸����� �ҷ��� ������ �ǿ� ���ڵ��� ���*/
		for (int y = 0; y < 9; y++)
		{	
			for (int x = 0; x < 9; x++) {

				dc.Rectangle(sdk[y][x].rc); //���⼭ ó�� �׸�ĭ�� 81�������	
				/*0�� �ƴҽ� ȸ������ ĥ�Ѵ�.*/
				if (sdk[y][x].grayBox == true) { //ȸ������ �Ұ� ���ΰ� Ʈ�簪�϶� ���ڸ� ȸ��ó������
					CBrush brush, *oldBrush;
					brush.CreateSolidBrush(RGB(211, 211, 211));
					oldBrush = dc.SelectObject(&brush);
					/*������ ���� �׸�ĭ�� �����*/
					dc.Rectangle(sdk[y][x].rc);
					dc.SelectObject(oldBrush);
					brush.DeleteObject();
					sdk[y][x].clicked = false;
					/*��ĥ�� ���� ���ڵ��� ���*/
				}
				if (sdk[y][x].input != 0)	//ȸ��ó�� ���ڰ� ���� ���� �� ���� ���ڸ� �� �ٿ��� ���ڿ� �� �������� ������ ���⿡ ���� ����ϴ� ���� ������ ��. 0�� �ƴ� ���ڵ鸸 ��Ÿ���� �Ǳ� ������
				{							//���� �ٸ� ���ǹ� ���� != 0�� ���ָ� �ڵ����� 0�� �ƴ� ���ڰ� �Ǹ� ����� �ǰ� �� �̰� ���� ���ߵ� ������Ʈ�Լ��� ��� ������Ʈ�� ���ֱ� ������
					CString str;
					/*Duplicate�� ture�� ��� ���������� ��ĥ*/
					if (sdk[y][x].Duplicate == true) {
						dc.SetTextColor(RGB(255, 0, 0));
					}
					else
						dc.SetTextColor(RGB(0, 0, 0));
					dc.SetBkMode(TRANSPARENT);
					str.Format(_T("%d"), sdk[y][x].input);				//input�� ��Ʈ���̱� ������ �̷��� �������� ���� ���� �޾ƿ� �� ����
					dc.TextOut((sdk[y][x].rc.right + sdk[y][x].rc.left) / 2 - 5, (sdk[y][x].rc.bottom + sdk[y][x].rc.top) / 2 - 5, str);		//��� �κ� ���� ��ǥ�� ������ �߾� ��ǥ, �̰� �˾Ƽ� �����ٶ�
				}
			}
		}
		/*Click Event�� ���� ���� �� ���� ����*/
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
		/*���� �����ϴ� �κ�*/
		if (win == true)
		{
			MessageBox(_T("������ �����մϴ�"), _T("Sudoku"), MB_ICONASTERISK);
		}
		
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication1Dlg::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	
	/*Click event�� ó���ϴ� �κ�*/
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (sdk[i][j].rc.PtInRect(point))
			{	
				sdk[i][j].clicked = true;	//Click event ����
			}
			else
			{
				sdk[i][j].clicked = false; //Click event ����
			}
		}
	}

	Invalidate(TRUE);
	CDialogEx::OnLButtonDblClk(nFlags, point);
}


BOOL CMFCApplication1Dlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	//Ű �Է½� Event ����
	if (pMsg->message == WM_KEYDOWN)  
	{	
		//���ڸ޼��� �ڽ�
		/*�� ���ڰ� �Է� �Ǹ� ó���ϴ� �κ�*/
		int row = 0;
		int cal = 0;
		int Overlap = 0;
		int check = 0;

		/*1�� �Է¹޾��� ��� MessageBox�� ���� ���ڸ� �Է�*/
		if (pMsg->wParam - 48 == 1)
		{	

			MessageBox(L"1.", L"Ű����", MB_OK);

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
			//���� ���� �ߺ��� ã�� ���� for��
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
			//���� ���� �ߺ��� ã�� ���� for��
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
		/*2�� �Է¹޾��� ��� MessageBox�� ���� ���ڸ� �Է�*/
		else if (pMsg->wParam - 48 == 2)
		{
			MessageBox(L"2", L"Ű����", MB_OK);

			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					if (sdk[i][j].clicked == true) {
						sdk[i][j].input = 2;
					}
				}
			}//���� ���� �ߺ��� ã�� ���� for��
		}
		/*3�� �Է¹޾��� ��� MessageBox�� ���� ���ڸ� �Է�*/
		else if (pMsg->wParam - 48 == 3)
		{
			MessageBox(L"3", L"Ű����", MB_OK);

			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					if (sdk[i][j].clicked == true) {
						sdk[i][j].input = 3;
					}
				}
			}
		}
		/*4�� �Է¹޾��� ��� MessageBox�� ���� ���ڸ� �Է�*/
		else if (pMsg->wParam - 48 == 4)
		{
			MessageBox(L"4", L"Ű����", MB_OK);

			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					if (sdk[i][j].clicked == true) {
						sdk[i][j].input = 4;
					}
				}
			}
		}
		/*5�� �Է¹޾��� ��� MessageBox�� ���� ���ڸ� �Է�*/
		else if (pMsg->wParam - 48 == 5)
		{
			MessageBox(L"5", L"Ű����", MB_OK);

			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					if (sdk[i][j].clicked == true) {
						sdk[i][j].input = 5;
					}
				}
			}
		}
		/*6�� �Է¹޾��� ��� MessageBox�� ���� ���ڸ� �Է�*/
		else if (pMsg->wParam - 48 == 6)
		{
			MessageBox(L"6", L"Ű����", MB_OK);

			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					if (sdk[i][j].clicked == true) {
						sdk[i][j].input = 6;
					}
				}
			}
		}
		/*7�� �Է¹޾��� ��� MessageBox�� ���� ���ڸ� �Է�*/
		else if (pMsg->wParam - 48 == 7)
		{
			MessageBox(L"7", L"Ű����", MB_OK);

			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					if (sdk[i][j].clicked == true) {
						sdk[i][j].input = 7;
					}
				}
			}
		}
		/*8�� �Է¹޾��� ��� MessageBox�� ���� ���ڸ� �Է�*/
		else if (pMsg->wParam - 48 == 8)
		{
			MessageBox(L"8", L"Ű����", MB_OK);

			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					if (sdk[i][j].clicked == true) {
						sdk[i][j].input = 8;
					}
				}
			}
		}
		/*9�� �Է¹޾��� ��� MessageBox�� ���� ���ڸ� �Է�*/
		else if (pMsg->wParam - 48 == 9)
		{
			MessageBox(L"9", L"Ű����", MB_OK);

			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					if (sdk[i][j].clicked == true) {
						sdk[i][j].input = 9;
					}
				}
			}
		}
		/*escŰ�� �Է¹޾��� ��� MessageBox�� ���� ���� ���ڸ� �����.*/
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
			//���� ���� �ߺ��� ã�� ���� for��
			for (int i = 0; i < 9; i++)
			{
				if (i == row) continue;

				if (sdk[i][cal].input == Overlap) {
					sdk[i][cal].Duplicate = false;
					//sdk[row][cal].Duplicate = true;
				}

			}
			//���� ���� �ߺ��� ã�� ���� for��
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
		//MessageBox(L"���ڸ� �Է��Ͻÿ�..", L"Ű����", MB_OK);
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}
