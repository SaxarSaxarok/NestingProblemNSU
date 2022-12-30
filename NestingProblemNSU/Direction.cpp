#include "Direction.h"
#include <cmath>

Direction::Direction( Point<double> vec ){
	this->direction = vec;
}

Direction::Direction( const Point<double>& begin, const Point<double>& end ){
	this->direction = end - begin;
}

bool Direction::operator==( const Direction& other )const{
	return compare_ccw_angle( *this, other ) == Direction::�omparison::EQUAL;
}

bool Direction::operator<( const Direction& other )const{
	return compare_ccw_angle( *this, other ) == Direction::�omparison::LESS;
}

bool Direction::operator>( const Direction& other )const{
	return compare_ccw_angle( *this, other ) == Direction::�omparison::GREATER;
}

bool Direction::operator<=( const Direction& other )const{
	return ( *this ) == other || ( *this ) < other;
}

bool Direction::operator>=( const Direction& other )const{
	return ( *this ) == other || ( *this ) > other;
}

bool Direction::isBetween( const Direction& p, const Direction& q, const Direction& r ){
	if ( ( p == q ) || ( p == r ) ) // ???
	{
		return true;
	}
	if ( q < p )
	{
		return ( p < r ) || ( r <= q );
	}
	return ( p < r ) && ( r <= q );
}

bool Direction::isZero(){
	return this->direction.x * this->direction.x + this->direction.y * this->direction.y < 0.0000000001;
}

Direction::�omparison Direction::compare_ccw_angle( const Direction& that, const Direction& other ){
	int quadrant1 = that.direction.x >= 0 ? ( that.direction.y >= 0 ? 1 : 4 ) : ( that.direction.y >= 0 ? 2 : 3 );
	int quadrant2 = other.direction.x >= 0 ? ( other.direction.y >= 0 ? 1 : 4 ) : ( other.direction.y >= 0 ? 2 : 3 );

	if ( quadrant1 > quadrant2 ) return Direction::�omparison::GREATER;
	if ( quadrant1 < quadrant2 ) return Direction::�omparison::LESS;

	double psevdoProd = that.direction ^ other.direction;
	return abs( psevdoProd ) < 0.00000001 ? Direction::�omparison::EQUAL : psevdoProd > 0 ? Direction::�omparison::LESS : Direction::�omparison::GREATER; //EPSILON
}
