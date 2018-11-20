#include "stdafx.h"
#include "MyShape.h"

IMPLEMENT_SERIAL(MyShape, CObject, 1)

MyShape::MyShape() {
	fg = RGB(255, 255, 255); bg = RGB(0, 0, 0); shape_col = RGB(0, 0, 0);
}
void MyShape::setBegin(const MyPoint &p) { begin = p; }
void MyShape::setEnd(const MyPoint &p) { end = p; }
void MyShape::setColor(COLORREF & col)
{
	bg = col;
}
//virtual void MyShape::drawShape(CPaintDC &dc) = 0;
void MyShape::draw(CPaintDC &dc) {
	CPen pen(PS_SOLID, 0.1, fg);
	CBrush brush(bg);
	CPen *oldPen = dc.SelectObject(&pen);
	CBrush *oldBrush = dc.SelectObject(&brush);
	drawShape(dc);
	dc.SelectObject(oldPen);
	dc.SelectObject(oldBrush);
}
bool MyShape::isIn(CPoint &p)
{
	if (begin.getX() < p.x && end.getX() > p.x && begin.getY() < p.y && end.getY() > p.y)
		return true;
	else return false;
}

void MyShape::Serialize(CArchive& archive) {
	if (archive.IsStoring())
	{
		archive << bg << fg << begin.getX() << begin.getY() 
			<< end.getX() << end.getY();
	}
	else
	{
		int bx, by, ex, ey;
		archive >> bg >> fg >> bx >> by >> ex >> ey;

		begin.setX(bx);
		begin.setY(by);
		end.setX(ex);
		end.setY(ey);
	}
}