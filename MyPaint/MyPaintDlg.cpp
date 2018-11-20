
// MyPaintDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MyPaint.h"
#include "MyPaintDlg.h"
#include "MyEllipse.h"
#include "MyRectangle.h"
#include "MyLine.h"
#include "afxdialogex.h"
#include "AddCommand.h"
#include "resource.h"
#include "HilbertCurve.h"
#include "PixelsHC.h"
#include "BlackAndWhite.h"
#include "NegativePixels.h"
#include "BlackAndWhiteFactory.h"
#include "NegativePixelsFactory.h"
#include <math.h>  
#include <vector>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMyPaintDlg dialog




CMyPaintDlg::CMyPaintDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMyPaintDlg::IDD, pParent), pic1(FALSE), curve(FALSE), bool_pix(FALSE), slow_mo(FALSE),drag(FALSE)
{
	curColor = RGB(255, 0, 0);
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyPaintDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK3, pic1);
	DDX_Check(pDX, IDC_CHECK1, curve);
	DDX_Check(pDX, IDC_CHECK5, bool_pix);
	DDX_Check(pDX, IDC_CHECK2, slow_mo);
	DDX_Check(pDX, IDC_CHECK4, drag);
}

BEGIN_MESSAGE_MAP(CMyPaintDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_BUTTON1, &CMyPaintDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMyPaintDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMyPaintDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMyPaintDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CMyPaintDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CMyPaintDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_CHECK3, &CMyPaintDlg::OnBnClickedCheck3)
	ON_BN_CLICKED(IDC_CHECK1, &CMyPaintDlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK5, &CMyPaintDlg::OnBnClickedCheck5)
	ON_COMMAND(ID_RESOLUTION_1, &CMyPaintDlg::OnResolution1)
	ON_COMMAND(ID_PICTURE_FEARLOATHING, &CMyPaintDlg::OnPictureFearloathing)
	ON_COMMAND(ID_PICTURE_PIC2, &CMyPaintDlg::OnPicturePic2)
	ON_COMMAND(ID_PICTURE_PIC3, &CMyPaintDlg::OnPicturePic3)
	ON_COMMAND(ID_CURVE_SLOWMOTION, &CMyPaintDlg::OnCurveSlowmotion)
	ON_BN_CLICKED(IDC_CHECK2, &CMyPaintDlg::OnBnClickedCheck2)
	ON_COMMAND(ID_RESOLUTION_2, &CMyPaintDlg::OnResolution2)
	ON_COMMAND(ID_RESOLUTION_3, &CMyPaintDlg::OnResolution3)
	ON_COMMAND(ID_RESOLUTION_4, &CMyPaintDlg::OnResolution4)
	ON_COMMAND(ID_RESOLUTION_5, &CMyPaintDlg::OnResolution5)
	ON_COMMAND(ID_RESOLUTION_6, &CMyPaintDlg::OnResolution6)
	ON_COMMAND(ID_RESOLUTION_7, &CMyPaintDlg::OnResolution7)
	ON_COMMAND(ID_RESOLUTION_8, &CMyPaintDlg::OnResolution8)
	ON_BN_CLICKED(IDC_CHECK4, &CMyPaintDlg::OnBnClickedCheck4)

	ON_COMMAND(ID_FILE_SAVE32771, &CMyPaintDlg::SaveFile)
	ON_COMMAND(ID_FILE_OPEN32772, &CMyPaintDlg::OpenFIle)
	ON_BN_CLICKED(IDC_BUTTON7, &CMyPaintDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CMyPaintDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CMyPaintDlg::OnBnClickedButton9)
END_MESSAGE_MAP()



// CMyPaintDlg message handlers

BOOL CMyPaintDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	isPressed = false;
	hilbert_depth =5;
	bit_pic = 3;

	
	drag_index = -1;
	m_menu = GetMenu();
	for (int i = 0; i < 8; i++)
		res[i] = FALSE;
	
	static MyLineFactory lineFactory;
	factory = &lineFactory;

	static PixelsFactory pf;
	ef = &pf;
	

	
	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMyPaintDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMyPaintDlg::OnPaint()
{



	if (drag)
	{
		hcur = AfxGetApp()->LoadCursorW(MAKEINTRESOURCE(IDC_AFXBARRES_HAND));
		SetClassLong(m_hWnd, GCL_HCURSOR, (LONG)hcur);
	}
	else
	{
		hcur = AfxGetApp()->LoadCursorW(MAKEINTRESOURCE(IDC_UPARROW));
		SetClassLong(m_hWnd, GCL_HCURSOR, (LONG)hcur);
	}

	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);

		if (pic1 == TRUE)
		{
			CBitmap bmp;
			if (bit_pic == 1)
				bmp.LoadBitmap(IDB_BITMAP1);
			if (bit_pic == 2)
				bmp.LoadBitmap(IDB_BITMAP2);
			if (bit_pic == 3)
				bmp.LoadBitmap(IDB_BITMAP3);

			// Get the size of the bitmap
			BITMAP bmpInfo;
			bmp.GetBitmap(&bmpInfo);

			// Create an in-memory DC compatible with the
			// display DC we''re using to paint
			CDC dcMemory;
			dcMemory.CreateCompatibleDC(&dc);

			// Select the bitmap into the in-memory DC
			CBitmap* pOldBitmap = dcMemory.SelectObject(&bmp);

			// Find a centerpoint for the bitmap in the client area
			CRect rect;
			GetClientRect(&rect);
			int nX = rect.left + (rect.Width() - bmpInfo.bmWidth) / 2;
			int nY = rect.top + (rect.Height() - bmpInfo.bmHeight) / 2;

			dc.BitBlt(nX, nY, bmpInfo.bmWidth, bmpInfo.bmHeight, &dcMemory,
				0, 0, SRCCOPY);

			dcMemory.SelectObject(pOldBitmap);




		}

		if (curve == TRUE)
		{

			HilbertCurve hc(pow(2, hilbert_depth));
			hc.Draw(dc, 182, 57, slow_mo);
		}
		if ((bool_pix == TRUE) && (curve == FALSE))
		{
			PixelsHC *p = ef->create(pow(2, hilbert_depth));
			p->setColours(dc);
			p->DrawPixels(dc);

		}
		for (int i = 0; i < shapes.size(); ++i)
			shapes[i]->draw(dc);


		CBitmap bmp2;
		bmp2.LoadBitmap(IDB_BITMAP5);
		BITMAP bmpInfo;
		bmp2.GetBitmap(&bmpInfo);
		CDC dcMemory;
		dcMemory.CreateCompatibleDC(&dc);
		CBitmap* pOldBitmap = dcMemory.SelectObject(&bmp2);
		dc.BitBlt(20,40, bmpInfo.bmWidth + 30, bmpInfo.bmHeight + 90, &dcMemory,
			0, 0, SRCCOPY);
		dcMemory.SelectObject(pOldBitmap);


	}


	CDialogEx::OnPaint();
}
// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMyPaintDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMyPaintDlg::OnLButtonDown(UINT nFlags, CPoint point)
{


	if (point.x < 131)
	{
		CClientDC dc(this);
		curColor = dc.GetPixel(point);
	}
	else
	{
		if (drag)
		{
			for (int i = 0; i < shapes.size(); ++i)
			{
				if (shapes[i]->isIn(point))
				{
					drag_index = i;
					i = shapes.size() + 1;
				}
			}
		}

		else
		{
			MyShape *s = factory->create();
			Command *command = new AddCommand(shapes, s);
			done.push(command);
			command->perform();

			s->setBegin(MyPoint(point.x, point.y));
			s->setColor(curColor);
			//shapes.push_back(s);
		}
		isPressed = true;

		CDialogEx::OnLButtonDown(nFlags, point);
	}
}

void CMyPaintDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	if ((drag) && (drag_index != -1))
	{
		int tx = shapes[drag_index]->getBegin().getX() - point.x;
		int ty = shapes[drag_index]->getBegin().getY() - point.y;
		tx *= -1;
		ty *= -1;
		shapes[drag_index]->setBegin(MyPoint(point.x, point.y));
		shapes[drag_index]->setEnd(MyPoint(tx + shapes[drag_index]->getEnd().getX(), ty + shapes[drag_index]->getEnd().getY()));
		drag_index = -1;
		Invalidate();
	}
	isPressed = false;
	CDialogEx::OnLButtonUp(nFlags, point);
}

void CMyPaintDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if (isPressed)
	{
		if (!(drag))
			shapes[shapes.size() - 1]->setEnd(MyPoint(point.x, point.y));

		Invalidate();
	}

	CDialogEx::OnMouseMove(nFlags, point);
}

void CMyPaintDlg::OnBnClickedButton1()
{
	//shape = 0;
	static MyLineFactory lineFactory;
	factory = &lineFactory;
}
void CMyPaintDlg::OnBnClickedButton2()
{
	static MyRectangleFactory rectangleFactory;
	factory = &rectangleFactory;
}
void CMyPaintDlg::OnBnClickedButton3()
{
	static MyEllipseFactory ellipseFactory;
	factory = &ellipseFactory;
}


void CMyPaintDlg::OnBnClickedButton4()
{
	// UNDO
	
	if (done.empty())
		return;
	Command *command = done.top();
	done.pop();
	undone.push(command);
	command->rollback();
	Invalidate();
}
void CMyPaintDlg::OnBnClickedButton5()
{
	// ReDO
	if (undone.empty())
		return;

	Command *command = undone.top();
	undone.pop();
	done.push(command);
	command->perform();
	Invalidate();	
}
void CMyPaintDlg::OnBnClickedButton6()
{

		
	while (!done.empty())
	{
		Command *command = done.top();
		done.pop();
		command->rollback();
		
	}
	while (!undone.empty())
	{
		Command *command = undone.top();
		undone.pop();
		command->rollback();
	}
	Invalidate();
	

}

void CMyPaintDlg::OnBnClickedCheck3()
{
	UpdateData(TRUE);
	Invalidate();
}

void CMyPaintDlg::OnBnClickedCheck1()
{
	UpdateData(TRUE);
	Invalidate();
}
void CMyPaintDlg::OnBnClickedCheck5()
{
	UpdateData(TRUE);
	Invalidate();
}

void CMyPaintDlg::OnPictureFearloathing()
{
	bit_pic = 1;
	CheckMenuPic(bit_pic);
	Invalidate();
}
void CMyPaintDlg::OnPicturePic2()
{
	// TODO: Add your command handler code here
	bit_pic = 2;
	CheckMenuPic(bit_pic);
	Invalidate();
}
void CMyPaintDlg::OnPicturePic3()
{
	// TODO: Add your command handler code here
	bit_pic = 3;
	CheckMenuPic(bit_pic);
	Invalidate();
}

void CMyPaintDlg::OnCurveSlowmotion()
{
	// TODO: Add your command handler code here
	UpdateData(TRUE);
	Invalidate();
}
void CMyPaintDlg::OnBnClickedCheck2()
{
	UpdateData(TRUE);
	Invalidate();
}

void CMyPaintDlg::OnResolution1()
{
	hilbert_depth = 1;
	CheckMenuRes(hilbert_depth);
	//res[hilbert_depth] = hilbert_depth;


	
}
void CMyPaintDlg::OnResolution2()
{
	// TODO: Add your command handler code here
	hilbert_depth = 2;
	CheckMenuRes(hilbert_depth);
}
void CMyPaintDlg::OnResolution3()
{
	// TODO: Add your command handler code here
	hilbert_depth = 3;
	CheckMenuRes(hilbert_depth);
}
void CMyPaintDlg::OnResolution4()
{
	// TODO: Add your command handler code here
	hilbert_depth = 4;
	CheckMenuRes(hilbert_depth);
}
void CMyPaintDlg::OnResolution5()
{
	// TODO: Add your command handler code here
	hilbert_depth = 5;
	CheckMenuRes(hilbert_depth);
}
void CMyPaintDlg::OnResolution6()
{
	// TODO: Add your command handler code here
	hilbert_depth = 6;
	CheckMenuRes(hilbert_depth);
}
void CMyPaintDlg::OnResolution7()
{
	// TODO: Add your command handler code here
	hilbert_depth = 7;
	CheckMenuRes(hilbert_depth);
}

void CMyPaintDlg::OnResolution8()
{
	// TODO: Add your command handler code here
	hilbert_depth = 8;
	CheckMenuRes(hilbert_depth);
}

void CMyPaintDlg::OnBnClickedCheck4()
{
	UpdateData(TRUE);
	Invalidate();// TODO: Add your control notification handler code here
}

void CMyPaintDlg::CheckMenuPic(int n)
{
	m_menu->CheckMenuItem(ID_PICTURE_FEARLOATHING, MF_UNCHECKED | MF_BYCOMMAND);
	m_menu->CheckMenuItem(ID_PICTURE_PIC2, MF_UNCHECKED | MF_BYCOMMAND);
	m_menu->CheckMenuItem(ID_PICTURE_PIC3, MF_UNCHECKED | MF_BYCOMMAND);
	switch (n) {

	case 1:
		m_menu->CheckMenuItem(ID_PICTURE_FEARLOATHING, MF_CHECKED | MF_BYCOMMAND); break;
	case 2:
		m_menu->CheckMenuItem(ID_PICTURE_PIC2, MF_CHECKED | MF_BYCOMMAND); break;
	case 3:
		m_menu->CheckMenuItem(ID_PICTURE_PIC3, MF_CHECKED | MF_BYCOMMAND); break;
	}
}
void CMyPaintDlg::CheckMenuRes(int n)
{
		
		m_menu->CheckMenuItem(ID_RESOLUTION_1, MF_UNCHECKED | MF_BYCOMMAND);
		m_menu->CheckMenuItem(ID_RESOLUTION_2, MF_UNCHECKED | MF_BYCOMMAND);
		m_menu->CheckMenuItem(ID_RESOLUTION_3, MF_UNCHECKED | MF_BYCOMMAND);
		m_menu->CheckMenuItem(ID_RESOLUTION_4, MF_UNCHECKED | MF_BYCOMMAND);
		m_menu->CheckMenuItem(ID_RESOLUTION_5, MF_UNCHECKED | MF_BYCOMMAND);
		m_menu->CheckMenuItem(ID_RESOLUTION_6, MF_UNCHECKED | MF_BYCOMMAND);
		m_menu->CheckMenuItem(ID_RESOLUTION_7, MF_UNCHECKED | MF_BYCOMMAND);
		m_menu->CheckMenuItem(ID_RESOLUTION_8, MF_UNCHECKED | MF_BYCOMMAND);
		switch (n) {

		case 1:
			m_menu->CheckMenuItem(ID_RESOLUTION_1, MF_CHECKED | MF_BYCOMMAND);
			break;
		case 2:
			m_menu->CheckMenuItem(ID_RESOLUTION_2, MF_CHECKED | MF_BYCOMMAND); break;
		case 3:
			m_menu->CheckMenuItem(ID_RESOLUTION_3, MF_CHECKED | MF_BYCOMMAND); break;
		case 4:
			m_menu->CheckMenuItem(ID_RESOLUTION_4, MF_CHECKED | MF_BYCOMMAND); break;
		case 5:
			m_menu->CheckMenuItem(ID_RESOLUTION_5, MF_CHECKED | MF_BYCOMMAND); break;
		case 6:
			m_menu->CheckMenuItem(ID_RESOLUTION_6, MF_CHECKED | MF_BYCOMMAND); break;
		case 7:
			m_menu->CheckMenuItem(ID_RESOLUTION_7, MF_CHECKED | MF_BYCOMMAND); break;
		case 8:
			m_menu->CheckMenuItem(ID_RESOLUTION_8, MF_CHECKED | MF_BYCOMMAND); break;
		}
}

void CMyPaintDlg::SaveFile()
	{
		
		CFile file(L"shapes.bin", CFile::modeCreate | CFile::modeWrite);
		CArchive archive(&file, CArchive::store);
		archive << shapes.size();
		for (int i = 0; i < shapes.size(); ++i)
			archive << shapes[i];
	}
void CMyPaintDlg::OpenFIle()
	{
		CFile file(L"shapes.bin", CFile::modeRead);
		CArchive archive(&file, CArchive::load);
		int count;
		archive >> count;
		for (int i = 0; i < count; ++i)
		{
			MyShape *s;
			archive >> s;
			shapes.push_back(s);
		}

		Invalidate();

	}


void CMyPaintDlg::OnBnClickedButton7()
{

		//Pixels
		static PixelsFactory pf;
		ef = &pf;
		Invalidate();
	
}
void CMyPaintDlg::OnBnClickedButton8()
{
	static BlackAndWhiteFactory BW;
	ef = &BW;
	Invalidate();
}
void CMyPaintDlg::OnBnClickedButton9()
{
	static NegativePixelsFactory Neg;
	ef = &Neg;
	Invalidate();
}
