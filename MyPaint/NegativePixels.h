#pragma once
#include "PixelsHC.h"
class NegativePixels:public PixelsHC
{
public:
	NegativePixels(int);
	void DrawPixels(CPaintDC &dc);
	void setColours(CPaintDC & dc);
	~NegativePixels();
private:
	COLORREF *NegColors;
};

