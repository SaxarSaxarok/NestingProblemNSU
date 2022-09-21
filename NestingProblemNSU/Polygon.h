#pragma once
#include "Point.h"
#include<vector>

class Polygon{
private:
	std::vector<Point<float>> points;
public:
	Polygon(){};
	Polygon( const std::vector<Point<float>>& points_ );
	Polygon( const Polygon& polygon_ );

	Point<float> operator [] ( int index );

	int size();

	float getArea();

	std::pair<float, float> getMaxXY();

	std::pair<float, float> getMinXY();

	std::vector<std::vector<int>> getMatrixRepresentation( float h );

	Polygon* shiftToOrigin();
};

