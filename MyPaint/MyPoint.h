#pragma once

class MyPoint {
public:
	MyPoint(int x = 0, int y = 0) : x(x), y(y) {}
	int getX() const { return x; }
	int getY() const { return y; }
	void setX(int x) { this->x = x; }
	void setY(int y) { this->y = y; }
private:
	int x, y;
};