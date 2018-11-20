#pragma once


class HilbertCurve
{
public:
	
	HilbertCurve();
	HilbertCurve(int);
	int getDepth() { return depth; }
	CPoint *getArr() { return arr; }
	CPoint hindex2xy(int, int );
	void Draw(CPaintDC &dc,int x,int y,BOOL);
	~HilbertCurve();
protected:
	int depth;
	CPoint *arr;
};

