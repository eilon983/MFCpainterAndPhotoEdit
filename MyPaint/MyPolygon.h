#pragma once

#include "MyShape.h"

class MyPolygon : public MyShape {
	DECLARE_SERIAL(MyPolygon)
	virtual void drawShape(CPaintDC &dc) = 0;

};


