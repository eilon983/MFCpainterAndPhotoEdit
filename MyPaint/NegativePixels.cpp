#include "stdafx.h"
#include "NegativePixels.h"
#include "PixelsHC.h"
#include "HilbertCurve.h"

NegativePixels::NegativePixels(int depth) : PixelsHC(depth)
{
	NegColors = new COLORREF[depth*depth];

}
void NegativePixels::DrawPixels(CPaintDC & dc)
{
	double d = (350) / (depth - 1);
	d++;
	for (int i = 0; i < depth*depth; i += 1)
	{
		CBrush myBrush, *oldBrush;
		myBrush.CreateSolidBrush(NegColors[i]);
		oldBrush = dc.SelectObject(&myBrush);
		dc.FillRect(CRect(arr[i].x, arr[i].y, arr[i].x + d, arr[i].y + d), &myBrush);
		dc.SelectObject(oldBrush);
	}
}
void NegativePixels::setColours(CPaintDC & dc)
{
	for (int i = 0; i < depth*depth; i++)
		colours[i] = dc.GetPixel(arr[i]);

	for (int i = 0; i < depth*depth; i++)
	{
		COLORREF clr = colours[i];
		int R = GetRValue(clr);
		int B = GetBValue(clr);
		int G = GetGValue(clr);
		R = 255 - R;
		B = 255 - B;
		G = 255 - G;
		NegColors[i] = COLORREF RGB(R, G, B);
	}
}

NegativePixels::~NegativePixels()
{
	delete[]NegColors;
}
