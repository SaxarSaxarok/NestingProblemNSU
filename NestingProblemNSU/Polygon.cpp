#include "Polygon.h"
#include<utility>
#include <stdexcept>
#include <algorithm>

Polygon::Polygon ( const std::vector<Point<float>>& points ){
	for ( auto& point : points )
	{
		this->points.push_back ( point );
	}
}

Polygon::Polygon ( const Polygon& polygon_ ){
	for ( auto& point : polygon_.points )
	{
		this->points.push_back ( point );
	}
}

Point<float> Polygon::operator[]( int i ){
	if ( i > -1 && i < this->points.size () )
		return this->points [i];
	else
		throw std::out_of_range ( "The index is out of range" );
}

float Polygon::getArea (){
	float result=0.0;
	for ( auto i=0; i < this->points.size (); i++ )
	{
		result+=this->points [i].x * this->points [i + 1].y;
		result-=this->points [i + 1].x * this->points [i].y;
	}
	return result / 2;
}

int Polygon::size (){
	return points.size ();
}




Polygon* Polygon::shiftToOrigin (){
	std::pair<float, float> minXY=getMinXY ();

	for ( auto& point : points )
	{
		point.x-=minXY.first;
		point.y-=minXY.second;
	}

	return this;
}

std::pair<float, float> Polygon::getMaxXY (){
	float maxX=points [0].x;
	float maxY=points [0].y;

	for ( auto& point : points )
	{
		if ( point.x > maxX ) maxX=point.x;
		if ( point.y > maxY ) maxY=point.y;
	}

	return std::pair<float, float> ( maxX, maxY );
}

std::pair<float, float> Polygon::getMinXY (){
	float minX=points [0].x;
	float minY=points [0].y;

	for ( auto& point : points )
	{
		if ( point.x < minX ) minX=point.x;
		if ( point.y < minY ) minY=point.y;
	}

	return std::pair<float, float> ( minX, minY );
}
