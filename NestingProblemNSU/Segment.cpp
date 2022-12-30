#include <algorithm>
#include "Segment.h"
#include "Direction.h"
Segment::Segment( Point<double> _a, Point<double> _b ){
	this->a = _a;
	this->b = _b;
	this->maxPoint = std::max( _a, _b );
	this->minPoint = std::min( _a, _b );
}

std::optional<Point<double>> Segment::intersection( const Segment& that, const Segment& other ){
	Point<double> a = that.maxPoint - that.minPoint;
	Point<double> b = other.minPoint - other.maxPoint;
	Point<double> c = other.minPoint - that.minPoint;
	if ( abs( a ^ b ) < 0.00000001 )
	{
		double l1 = ( c ^ b ) / ( a ^ b );
		double l2 = ( a ^ c ) / ( a ^ b );

		if ( 0 <= l1 && l1 <= 1 && 0 <= l2 && l2 <= 1 )
		{
			if ( ( 0 == l1 && ( 0 == l2 || l2 == 1 ) ) ||
				 ( 1 == l1 && ( 0 == l2 || l2 == 1 ) ) )
			{
				return std::nullopt;
			}
			return that.minPoint + a * l1;
		}
	}
	return std::nullopt;
}

Segment::ñomparison Segment::CompareWithPoint( const Point<double>& point ){
	Direction a = Direction( this->minPoint, this->maxPoint );
	Direction b = Direction( this->minPoint, point );

	if ( a == b || a.isZero() || b.isZero() ) return Segment::ñomparison::INNER;
	double signedArea = a.direction ^ b.direction;

	return abs( signedArea ) < 0.000001 ? Segment::ñomparison::INNER : signedArea < 0 ? Segment::ñomparison::RIGHT : Segment::ñomparison::LEFT;
}
