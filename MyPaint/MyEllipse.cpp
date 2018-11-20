#include "stdafx.h"
#include "MyEllipse.h"

IMPLEMENT_SERIAL(MyEllipse, MyShape, 1)

void MyEllipse::drawShape(CPaintDC &dc) {
	dc.Ellipse(begin.getX(), begin.getY(), end.getX(), end.getY());
}