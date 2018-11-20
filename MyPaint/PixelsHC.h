#pragma once
#include "stdafx.h"
#include "HilbertCurve.h"

class PixelsHC:public HilbertCurve{
public:
	PixelsHC();
	~PixelsHC();
	PixelsHC(int);
	COLORREF getColor(int i) { return colours[i]; }
	virtual void DrawPixels(CPaintDC &dc);
	virtual void setColours(CPaintDC & dc);
	
protected:
	COLORREF *colours;
	
};