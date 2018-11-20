#include "stdafx.h"
#include "MyRectangle.h"

IMPLEMENT_SERIAL(MyRectangle,MyShape, 1)

void MyRectangle::drawShape(CPaintDC &dc) {
	dc.Rectangle(begin.getX(), begin.getY(), end.getX(), end.getY());
}
