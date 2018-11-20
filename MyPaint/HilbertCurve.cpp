#include "stdafx.h"
#include "HilbertCurve.h"
#include "MyPaintDlg.h"


int last2bits(int x) {
	return (x & 3);
}

HilbertCurve::HilbertCurve()
{
	depth = 0;
}
HilbertCurve::HilbertCurve(int n = 1)
{
	depth = n;
	arr = new CPoint[n*n];
	double d = (350) / (n - 1);
	if (n == 64)
		d += 0.5;
	if (n == 128)
		d += 0.75;
	if (n == 256)
		d+=0.4;
		
	for (int i = 0; i < n*n; i += 1) {
		arr[i] = hindex2xy(i, n);
		arr[i].SetPoint(arr[i].x*d+182, arr[i].y*d+57);
	}
}

CPoint HilbertCurve::hindex2xy(int hindex, int N)
{

	CPoint p0(0, 0);
	CPoint p1(0, 1);
	CPoint p2(1, 1);
	CPoint p3(1, 0);
	CPoint positions[4];
	positions[0] = p0;
	positions[1] = p1;
	positions[2] = p2;
	positions[3] = p3;

	CPoint tmp = positions[last2bits(hindex)];
	hindex = (hindex >> 2);

	// 2. iteratively compute coords
	int x = tmp.x;
	int y = tmp.y;

	for (int n = 4; n <= N; n *= 2) {
		int n2 = n / 2;

		int temp;
		switch (last2bits(hindex)) {
		case 0: /* case A: left-bottom */
			temp = x;
			x = y;
			y = temp;
			break;

		case 1: /* case B: left-upper */
			x = x;
			y = y + n2;
			break;

		case 2: /* case C: right-upper */
			x = x + n2;
			y = y + n2;
			break;

		case 3: /* case D: right-bottom */
			temp = y;
			y = (n2 - 1) - x;
			x = (n2 - 1) - temp;
			x = x + n2;
			break;
		}

		hindex = (hindex >> 2);
	}
	CPoint rp(x, y);
	return rp;
}

void HilbertCurve::Draw(CPaintDC &dc,int x,int y,BOOL sm)
{
	
	CPoint prev = arr[0];
	CPoint cur;

	for (int i = 1; i < depth*depth; i++)
	{		if(sm)
		    Sleep(1);
		cur = arr[i];
		dc. MoveTo(prev.x,prev.y);
		dc.LineTo(cur.x, cur.y);
		prev = cur;
	}


}




HilbertCurve::~HilbertCurve()
{
}
