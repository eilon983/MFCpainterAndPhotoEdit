
// MyPaintDlg.h : header file
//

#pragma once

#include <vector>
#include <stack>
#include "MyShape.h"
#include "MyFactory.h"
#include "MyEllipseFactory.h"
#include "MyLineFactory.h"
#include "MyRectangleFactory.h"
#include "Resource.h"
#include "Command.h"
#include "EditFactory.h"
#include "PixelFactory.h"

using namespace std;

// CMyPaintDlg dialog
class CMyPaintDlg : public CDialogEx
{
// Construction
public:
	CMyPaintDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_MYPAINT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	vector<MyShape*> shapes;
	stack<Command*> done, undone;
	COLORREF curColor;
	bool isPressed;
	int hilbert_depth;
	int bit_pic;
	int drag_index;
	bool res[8];
	CMenu *m_menu;
	HCURSOR hcur;


	//int shape;
	MyFactory *factory;
	EditFactory *ef;
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedCheck3();
	BOOL pic1;
	BOOL curve;
	BOOL bool_pix;
	BOOL slow_mo;
	BOOL drag;
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck5();
	afx_msg void OnResolution1();
	afx_msg void OnPictureFearloathing();
	afx_msg void OnPicturePic2();
	afx_msg void OnPicturePic3();
	afx_msg void OnCurveSlowmotion();
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnResolution2();
	afx_msg void OnResolution3();
	afx_msg void OnResolution4();
	afx_msg void OnResolution5();
	afx_msg void OnResolution6();
	afx_msg void OnResolution7();
	afx_msg void OnResolution8();
	afx_msg void OnBnClickedCheck4();
	afx_msg void CheckMenuRes(int);
	afx_msg void CheckMenuPic(int);

	afx_msg void SaveFile();
	afx_msg void OpenFIle();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
};
