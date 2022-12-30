#pragma once

#include "Point.h"

class Direction{
public:
	Point<double> direction;
public:

	Direction( Point<double> vec );
	Direction( const Point<double>& begin, const Point<double>& end );

	bool operator <  ( const Direction& other ) const;
	bool operator <= ( const Direction& other ) const;
	bool operator >  ( const Direction& other ) const;
	bool operator >= (const  Direction& other ) const;
	bool operator == ( const Direction& other ) const;

	static bool isBetween( const Direction& p, const Direction& q, const Direction& r );
	bool isZero();

private:
	enum class ñomparison{ LESS, EQUAL, GREATER, INCOMPARABLY}; // rename?
	static Direction::ñomparison compare_ccw_angle( const Direction& that, const Direction& other );

};

