#include "stdafx.h"
#include "BlackAndWhite.h"
#include "PixelsHC.h"
#include "HilbertCurve.h"

BlackAndWhite::BlackAndWhite(int depth) : PixelsHC(depth)
{
	BlackWhiteCol = new COLORREF[depth*depth];

}
void BlackAndWhite::DrawPixels(CPaintDC & dc)
{
	double d = (350) / (depth - 1);
	d++;
	for (int i = 0; i < depth*depth; i += 1)
	{
		CBrush myBrush, *oldBrush;
		myBrush.CreateSolidBrush(BlackWhiteCol[i]);
		oldBrush = dc.SelectObject(&myBrush);
		dc.FillRect(CRect(arr[i].x, arr[i].y, arr[i].x + d, arr[i].y + d), &myBrush);
		dc.SelectObject(oldBrush);
	}
}

void BlackAndWhite::setColours(CPaintDC & dc)
{
	for (int i = 0; i < depth*depth; i++)
		colours[i] = dc.GetPixel(arr[i]);
	for (int i = 0; i < depth*depth; i++)
	{

		long val;

		COLORREF clr = colours[i];

		int R = GetRValue(clr);
		int B = GetBValue(clr);
		int G = GetGValue(clr);
		val = (R + B + G) / 3;
		BlackWhiteCol[i] = COLORREF RGB(val, val, val);
	}
}

BlackAndWhite::~BlackAndWhite()
{
	delete BlackWhiteCol;
}
