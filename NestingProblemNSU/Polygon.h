#pragma once
#include "Point.h"
#include<vector>

class Polygon{
private:
	std::vector<Point<float>> points;
	mutable Point<float>* barycenterValue;
	mutable float* areaValue;

public:


	Polygon();
	Polygon( const std::vector<Point<float>>& points_ );
	Polygon( const Polygon& polygon_ );
	Polygon( Polygon&& points );

	Point<float> barycenter() const;
	float area() const;
	Point<float> operator [] ( int index ) const;

	int size() const;

	std::pair<float, float> MaxXY() const;
	std::pair<float, float> MinXY() const;

	std::vector<std::vector<int>> getMatrixRepresentation( float h );

	Polygon* shiftToOrigin();
};

