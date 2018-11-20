#pragma once

#include "MyPoint.h"

class MyShape : public CObject {
public:
	DECLARE_SERIAL(MyShape)
	MyShape();
	MyPoint getBegin() { return begin; }
	MyPoint getEnd() { return end; }
	void setBegin(const MyPoint &p);
	void setEnd(const MyPoint &p);
	void setColor(COLORREF &col);
	bool isIn(CPoint &p);
	virtual void drawShape(CPaintDC &dc) {}
	void draw(CPaintDC &dc);
	void Serialize(CArchive& archive);
protected:
	MyPoint begin, end;
	COLORREF fg, bg;
	COLORREF shape_col;
};