
#include "stdafx.h"
#include "HilbertCurve.h"
#include "PixelsHC.h"

PixelsHC::PixelsHC()
{
}

PixelsHC::~PixelsHC()
{
	delete []colours;
}

PixelsHC::PixelsHC(int depth) : HilbertCurve(depth)
{
	
	colours = new COLORREF[depth*depth];

}
void PixelsHC::DrawPixels(CPaintDC & dc)
{
	double d = 350 / depth;
	d++;
	for (int i = 0; i < depth*depth; i += 1)
	{
		CBrush myBrush, *oldBrush;
		myBrush.CreateSolidBrush(colours[i]);
		oldBrush = dc.SelectObject(&myBrush);
		dc.FillRect(CRect(arr[i].x, arr[i].y, arr[i].x + d, arr[i].y + d), &myBrush);
		dc.SelectObject(oldBrush);
	}
}
void PixelsHC::setColours(CPaintDC & dc)
{
	for (int i = 0; i < depth*depth; i++)
		colours[i] = dc.GetPixel(arr[i]);
}

