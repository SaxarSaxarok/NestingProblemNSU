#include "Polygon.h"
#include<utility>
#include <stdexcept>
#include <algorithm>
#include <iostream>

Polygon::Polygon( const std::vector<Point<float>>& points ){
	for ( auto& point : points )
	{
		this->points.push_back( point );
	}
}

Polygon::Polygon( const Polygon& polygon_ ){
	for ( auto& point : polygon_.points )
	{
		this->points.push_back( point );
	}
}

Point<float> Polygon::operator[]( int i ){
	if ( i > -1 && i < this->points.size() )
		return this->points [i];
	else
		throw std::out_of_range( "The index is out of range" );
}

float Polygon::getArea(){
	float result = 0.0;
	for ( auto i = 0; i < this->points.size(); i++ )
	{
		result += this->points [i].x * this->points [i + 1].y;
		result -= this->points [i + 1].x * this->points [i].y;
	}
	return result / 2;
}

int Polygon::size(){
	return points.size();
}




Polygon* Polygon::shiftToOrigin(){
	std::pair<float, float> minXY = getMinXY();

	for ( auto& point : points )
	{
		point.x -= minXY.first;
		point.y -= minXY.second;
	}

	return this;
}

std::pair<float, float> Polygon::getMaxXY(){
	float maxX = points [0].x;
	float maxY = points [0].y;

	for ( auto& point : points )
	{
		if ( point.x > maxX ) maxX = point.x;
		if ( point.y > maxY ) maxY = point.y;
	}

	return std::pair<float, float>( maxX, maxY );
}

std::pair<float, float> Polygon::getMinXY(){
	float minX = points [0].x;
	float minY = points [0].y;

	for ( auto& point : points )
	{
		if ( point.x < minX ) minX = point.x;
		if ( point.y < minY ) minY = point.y;
	}

	return std::pair<float, float>( minX, minY );
}

std::vector<std::vector<int>> Polygon::getMatrixRepresentation( float h ){
	float accuracy = h * 0.000001;
	this->shiftToOrigin();
	auto maxXY = this->getMaxXY();
	auto minXY = this->getMinXY();
	float xSideLen = maxXY.first - minXY.first;
	float ySideLen = maxXY.second - minXY.second;
	int nX = ceil( xSideLen / h );
	int nY = ceil( ySideLen / h );

	std::vector<std::vector<int>> edges( nX + 1, std::vector<int>( nY, 0 ) );

	for ( int k = 0; k < nY; k++ )
	{
		for ( int i0 = 0; i0 < this->size(); i0++ )
		{
			int i1 = ( i0 + 1 ) % this->size();
			if ( ( std::min( points [i0].y, points [i1].y ) <= k * h ) &&
				 k * h <= std::max( points [i0].y, points [i1].y ) &&
				 abs( points [i1].y - points [i0].y ) > FLT_EPSILON )
			{
				float a = -( points [i1].x - points [i0].x ) / ( points [i1].y - points [i0].y );
				float b = -points [i0].x - points [i0].y * a;
				float yP = k * h;
				float xP = -b - a * k * h;

				if ( abs( xP - points [i0].x ) < FLT_EPSILON )
				{
					if ( ( points [i1].y - yP ) * ( points [( ( ( i0 - 1 ) % this->size() ) + this->size() ) % this->size()].y - yP ) < 0 )
					{
						edges [floor( xP / h + accuracy )][k] += 1;
					}
					else if ( ( points [i1].y - yP ) * ( points [( ( ( i0 - 1 ) % this->size() ) + this->size() ) % this->size()].y - yP ) > 0 )
					{
						edges [floor( xP / h + accuracy )][k] += 2;
					}
				}
				else if ( abs( xP - points [i1].x ) > FLT_EPSILON )
				{
					edges [floor( xP / h + accuracy )][k] += 1;
				}
			}
		}
	}
	std::vector<std::vector<int>>matrix( nX + 1, std::vector<int>( nY + 1, 0 ) );

	for ( int k = 0; k < nY; k++ )
	{
		bool flag = false;

		for ( int i = 0; i <= nX; i++ )
		{
			if ( ( edges [i][k] % 2 == 0 ) and ( edges [i][k] != 0 ) )
			{
				matrix [i][k] = 1;
			}
			else if ( edges [i][k] % 2 == 1 )
			{
				matrix [i][k] = 1;
				if ( k > 0 ) matrix [i][k - 1] = 1;//Все Верно?
				flag = !flag;
			}
			if ( flag )
			{
				matrix [i][k] = 1;
				if ( k > 0 ) matrix [i][k - 1] = 1; //Все верно ?
			}
		}
	}

	for ( int i = 0; i < this->size(); i++ )
	{
		int j = ( i + 1 ) % this->size();
		Point<float> i1( points [i] );
		Point<float> i2( points [j] );

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
			for ( int j = 0; j <= abs( j1.x - j2.x ); j++ ) // Было i Не сломается ? 
			{
				matrix [p.x][p.y] = 1;
				p.x += stepX;
			}
		}
		else
		{
			for ( int j = 0; j <= abs( j1.x - j2.x ) + abs( j1.y - j2.y ); j++ )
			{
				matrix [p.x][p.y] = 1;
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
	for ( int i = 0; i < matrix.size(); i++ ) matrix [i].pop_back();

	for ( int i = 0; i < matrix.size(); i++ )
	{
		for ( int j = 0; j < matrix [i].size(); j++ )
		{
			std::cout << matrix [i][j] << ' ';
		}
		std::cout << "\n";
	}
	return matrix;
}