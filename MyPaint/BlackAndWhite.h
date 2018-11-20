#pragma once
#include "PixelsHC.h"
class BlackAndWhite :public PixelsHC
{
public:
	BlackAndWhite(int);
	void DrawPixels(CPaintDC &dc);
	void setColours(CPaintDC &dc);

	~BlackAndWhite();
private:
	COLORREF *BlackWhiteCol;
};

