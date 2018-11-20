#pragma once

#include "MyPolygon.h"

class MyRectangle : public MyShape {
	DECLARE_SERIAL(MyRectangle)
	void drawShape(CPaintDC &dc);
};