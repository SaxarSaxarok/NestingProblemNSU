#include "Polygon.h"
#include<utility>
#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <iomanip>

Polygon::Polygon(): barycenterValue_( nullptr ), areaValue_( nullptr ){}

Polygon::Polygon( const std::vector<Point<float>>& points_ ) : barycenterValue_( nullptr ), areaValue_( nullptr ){
	for ( auto& point : points_ )
	{
		this->points_.push_back( point );
	}
}

Polygon::Polygon( const Polygon& polygon_ ): barycenterValue_( nullptr ), areaValue_( nullptr ){
	for ( auto& point : polygon_.points_ )
	{
		this->points_.push_back( point );
	}
}

Polygon::Polygon( Polygon&& polygon ) noexcept: barycenterValue_( nullptr ), areaValue_( nullptr ){
	this->points_.swap( polygon.points_ );
}

Polygon& Polygon::operator = ( const Polygon& polygon ){
	barycenterValue_ = nullptr;
	areaValue_ = nullptr;
	for ( auto& point : polygon.points_ )
	{
		this->points_.push_back( point );
	}
	return *this;
}

Polygon& Polygon::operator = ( Polygon&& polygon ) noexcept{
	barycenterValue_ = nullptr;
	areaValue_ = nullptr;
	this->points_.swap( polygon.points_ );
	return *this;
}

Point<float> Polygon::operator[]( int i ) const{
	if ( i > -1 && i < this->points_.size() )
		return this->points_ [i];
	else
		throw std::out_of_range( "The index is out of range" );
}

int Polygon::size() const{
	return points_.size();
}

void Polygon::moveTo( Point<float> vector ){
	for ( auto& point : points_ )
	{
		point.x += vector.x;
		point.y += vector.y;
	}
}

Point<float> Polygon::barycenter() const{
	if ( barycenterValue_ == nullptr )
	{
		float xsum = 0.0;
		float ysum = 0.0;
		int size = this->size();
		for ( int i = 0; i < size - 1; i++ )
		{
			float areaSum = points_ [i].x * points_ [i + 1].y - points_ [i + 1].x * points_ [i].y;

			xsum += ( points_ [i].x + points_ [i + 1].x ) * areaSum;
			ysum += ( points_ [i].y + points_ [i + 1].y ) * areaSum;
		}
		xsum += ( points_ [size - 1].x + points_ [0].x ) * points_ [size - 1].x * points_ [0].y - points_ [0].x * points_ [size - 1].y;
		ysum += ( points_ [0].y + points_ [size - 1].y ) * points_ [0].x * points_ [size - 1].y - points_ [size - 1].x * points_ [0].y;

		barycenterValue_ = new Point<float>( xsum / ( -area() * 6 ), ysum / ( -area() * 6 ) );
	}
	return *barycenterValue_;
}

float Polygon::area() const{
	if ( areaValue_ == nullptr )
	{
		float area = 0.0f;
		int size = this->size();

		for ( int i = 0; i < size - 1; i++ )
		{
			area += points_ [i].x * points_ [i + 1].y - points_ [i + 1].x * points_ [i].y;
		}
		area += points_ [size - 1].x * points_ [0].y - points_ [size - 1].y * points_ [0].x;
		area = abs( area ) / 2;
		areaValue_ = new float( area );
	}
	return *areaValue_;
}




Polygon* Polygon::shiftToOrigin(){
	std::pair<float, float> minXY = MinXY();

	for ( auto& point : points_ )
	{
		point.x -= minXY.first;
		point.y -= minXY.second;
	}
	barycenterValue_ = nullptr;
	return this;
}

std::pair<float, float> Polygon::MaxXY() const{
	float maxX = points_ [0].x;
	float maxY = points_ [0].y;

	for ( auto& point : points_ )
	{
		if ( point.x > maxX ) maxX = point.x;
		if ( point.y > maxY ) maxY = point.y;
	}

	return std::pair<float, float>( maxX, maxY );
}

std::pair<float, float> Polygon::MinXY() const{
	float minX = points_ [0].x;
	float minY = points_ [0].y;

	for ( auto& point : points_ )
	{
		if ( point.x < minX ) minX = point.x;
		if ( point.y < minY ) minY = point.y;
	}

	return std::pair<float, float>( minX, minY );
}

std::vector<std::vector<int>> Polygon::getMatrixRepresentation( float h ){
	float accuracy = h * 0.000001f;
	this->shiftToOrigin();
	auto maxXY = this->MaxXY();
	auto minXY = this->MinXY();
	float xSideLen = maxXY.first - minXY.first;
	float ySideLen = maxXY.second - minXY.second;
	int nX = ceil( xSideLen / h );
	int nY = ceil( ySideLen / h );
	int size = this->size();

	std::vector<std::vector<int>> edges( nY, std::vector<int>( nX + 1, 0 ) );

	for ( auto k = 0; k < nY; k++ )
	{
		for ( auto i0 = 0; i0 < size; i0++ )
		{
			int i1 = ( i0 + 1 ) % size;
			if ( ( std::min( points_ [i0].y, points_ [i1].y ) <= k * h ) &&
				 k * h <= std::max( points_ [i0].y, points_ [i1].y ) &&
				 abs( points_ [i1].y - points_ [i0].y ) > FLT_EPSILON )
			{
				float a = -( points_ [i1].x - points_ [i0].x ) / ( points_ [i1].y - points_ [i0].y );
				float b = -points_ [i0].x - points_ [i0].y * a;
				float yP = k * h;
				float xP = -b - a * k * h;

				if ( abs( xP - points_ [i0].x ) < FLT_EPSILON )
				{
					if ( ( points_ [i1].y - yP ) * ( points_ [( ( ( i0 - 1 ) % size ) + size ) % size].y - yP ) < 0 )
					{
						edges [k][floor( xP / h + accuracy )] += 1;
					}
					else if ( ( points_ [i1].y - yP ) * ( points_ [( ( ( i0 - 1 ) % size ) + size ) % size].y - yP ) > 0 )
					{
						edges [k][floor( xP / h + accuracy )] += 2;
					}
				}
				else if ( abs( xP - points_ [i1].x ) > FLT_EPSILON )
				{
					edges [k][floor( xP / h + accuracy )] += 1;
				}
			}
		}
	}
	std::vector<std::vector<int>>matrix( nY + 1, std::vector<int>( nX + 1, 0 ) );

	for ( auto k = 0; k < nY; k++ )
	{
		bool flag = false;

		for ( auto i = 0; i <= nX; i++ )
		{
			if ( ( edges [k][i] % 2 == 0 ) and ( edges [k][i] != 0 ) )
			{
				matrix [k][i] = 1;
			}
			else if ( edges [k][i] % 2 == 1 )
			{
				matrix [k][i] = 1;
				if ( k > 0 ) matrix [k - 1][i] = 1;//Все Верно?
				flag = !flag;
			}
			if ( flag )
			{
				matrix [k][i] = 1;
				if ( k > 0 ) matrix [k - 1][i] = 1; //Все верно ?
			}
		}
	}

	for ( auto i = 0; i < size; i++ )
	{
		int j = ( i + 1 ) % size;
		Point<float> i1( points_ [j] );
		Point<float> i2( points_ [i] );

		Point<int> j1( floor( i1.x / h ), floor( i1.y / h ) );
		Point<int> j2( floor( i2.x / h ), floor( i2.y / h ) );

		int stepX = 1, stepY = 1, check = 1;

		if ( j1.x > j2.x )
		{
			stepX = -1;
		}
		else if ( j1.x == j2.x )
		{
			stepX = 0;
		}
		if ( j1.y > j2.y )
		{
			stepY = -1;
			check = 0;
		}
		else if ( j1.y == j2.y )
		{
			stepY = 0;
		}

		Point<int> p( floor( i1.x / h ), floor( i1.y / h ) );
		if ( j1.y == j2.y )
		{
			for ( auto j = 0; j <= abs( j1.x - j2.x ); j++ ) // Было i Не сломается ? 
			{
				matrix [p.y][p.x] = 1;
				p.x += stepX;
			}
		}
		else
		{
			for ( auto j = 0; j <= abs( j1.x - j2.x ) + abs( j1.y - j2.y ); j++ )
			{
				matrix [p.y][p.x] = 1;
				if ( j2 != p ) //Аналогично было i
				{
					float a = -( i2.x - i1.x ) / ( i2.y - i1.y );
					float b = -i1.x - i1.y * a;
					float xP = -b - a * ( p.y + check ) * h;

					if ( floor( xP / h ) == p.x )
					{
						p.y += stepY;
					}
					else
					{
						p.x += stepX;
					}
				}
			}
		}
	}
	matrix.pop_back();
	for ( auto i = 0; i < matrix.size(); i++ ) matrix [i].pop_back();
	return matrix;
}

std::ostream& Polygon::print( std::ostream& out ){
	if ( this->points_.empty() )
		out << "There is no polygon" << std::endl;
	else
		for ( int l = 0; l < this->points_.size(); l++ )
		{
			out << '(' << l + 1 << ')'
				<< std::setw( 10 ) << this->points_ [l].x
				<< std::setw( 10 ) << this->points_ [l].y
				<< std::endl;
		}
	return out;
}

std::ostream& operator<<( std::ostream& out, Polygon& object ){
	object.print( out );
	return out;
}
