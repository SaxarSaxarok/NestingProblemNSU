#pragma once
struct Point
{
	float x, y;

	Point(float x_ = 0, float y_ = 0) : x(x_), y(y_) {};
	Point(const Point& p) : x(p.x), y(p.y) {};
	Point& operator=(const Point& p) {
		this->x = p.x;
		this->y = p.y;
	}
};

