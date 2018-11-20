#pragma once

#include "MyShape.h"

class MyEllipse : public MyShape {
	DECLARE_SERIAL(MyEllipse)
	void drawShape(CPaintDC &dc);
};