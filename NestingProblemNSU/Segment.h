#pragma once
#include <optional>
#include "Point.h"
class Segment{
public:
	Point<double> a;
	Point<double> b;
	Point<double> minPoint;
	Point<double> maxPoint;

	Segment( Point<double> _a, Point<double> _b );
private:
	enum class ñomparison{ LEFT, RIGHT, INNER }; // rename?

public:

	static std::optional<Point<double>> intersection( const Segment& that, const Segment& other);
	Segment::ñomparison CompareWithPoint( const Point<double>& point ); //rename

};

