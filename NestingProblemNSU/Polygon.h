#pragma once
#include "Point.h"
#include<vector>

class Polygon{
private:
	std::vector<Point> points;
public:
	Polygon(){};
	Polygon( const std::vector<Point>& points_ );
	Polygon( const Polygon& polygon_ );

	Point operator [] ( int index );

	int size();

	float getArea();

	std::pair<float, float> getMaxXY();

	std::pair<float, float> getMinXY();

	Polygon* shiftToOrigin();
};

