#include "Polygon.h"
#include<utility>
#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include "Direction.h"

Polygon::Polygon(){}

Polygon::Polygon( const std::vector<Point<double>>& points ){//DONE
	for ( auto& point : points )
	{
		this->points_.push_back( point );
	}
	this->shiftToGlobalOrigin();
	this->localOrigin( Point<double>( 0, 0 ) );
}

Polygon::Polygon( const Polygon& polygon ){//DONE
	for ( auto& point : polygon.points_ )
	{
		this->points_.push_back( point );
	}
	this->localOrigin( polygon.localOrigin() );
}

Polygon::Polygon( Polygon&& polygon ) noexcept{//DONE
	this->points_.swap( polygon.points_ );
	this->localOrigin( polygon.localOrigin() );
}

Polygon& Polygon::operator = ( const Polygon& polygon ){//DONE
	for ( auto& point : polygon.points_ )
	{
		this->points_.push_back( point );
	}
	this->localOrigin( polygon.localOrigin() );
	return *this;
}

Polygon& Polygon::operator = ( Polygon&& polygon ) noexcept{//DONE
	this->points_.swap( polygon.points_ );
	this->localOrigin( polygon.localOrigin() );
	return *this;
}

Point<double> Polygon::localOrigin() const{ //DONE
	if ( localOriginValue_ == nullptr )
	{
		auto minXY = this->minXY();
		localOriginValue_ = new Point<double>( minXY.first, minXY.second );
	}
	return *localOriginValue_;
}

void Polygon::localOrigin( Point<double> point ) const{ //DONE
	if ( this->localOriginValue_ == nullptr )
	{
		this->localOriginValue_ = new Point<double>( point );
		return;
	}
	*( this->localOriginValue_ ) = point;
}

Point<double> Polygon::operator[]( int i ) const{//DONE
	return this->localOrigin() + this->points_ [i];
}

int Polygon::size() const{//DONE
	return points_.size();
}

Polygon& Polygon::moveTo( Point<double> point ){//DONE (ÍÎ ÒÓÒ ÄÎ ÝÒÎÃÎ ÁÛËÎ ÍÅÏÐÀÂÈËÜÍÎ, ÌÎÆÅÒ ÏÎËÎÌÀÒÜÑß ÊÎÄ, ÍÎ Â ÖÅËÎÌ ÝÒÎ ÍÅ ÑÒÐÀØÍÎ ÅÑËÈ ÒÛ ÁÓÄÅØÜ ÏÅÐÅÏÈÑÛÂÀÒÜ)
	this->localOrigin( point );
	return *this;
}

Polygon& Polygon::translateOn( Point<double> vector ){// DONE
	this->localOrigin( localOrigin() + vector );
	return *this;
}



Polygon* Polygon::shiftToGlobalOrigin(){// DONE
	if ( localOriginValue_ != nullptr )
	{
		this->localOrigin( Point<double>( 0, 0 ) );
		return this;
	}

	std::pair<double, double> minXY = this->minXY();

	for ( auto& point : points_ )
	{
		point.x -= minXY.first;
		point.y -= minXY.second;
	}
	return this;
}

std::pair<double, double> Polygon::maxXY() const{ //Not done. Íî íàâåðíîå ìîæíî çàáèòü
	double maxX = points_ [0].x;
	double maxY = points_ [0].y;

	for ( auto& point : points_ )
	{
		if ( point.x > maxX ) maxX = point.x;
		if ( point.y > maxY ) maxY = point.y;
	}

	return std::pair<double, double>( maxX, maxY );
}

std::pair<double, double> Polygon::minXY() const{ //DONE

	if ( localOriginValue_ != nullptr ) return std::pair<double, double>( this->localOrigin().x, this->localOrigin().y );

	double minX = points_ [0].x;
	double minY = points_ [0].y;

	for ( auto& point : points_ )
	{
		if ( point.x < minX ) minX = point.x;
		if ( point.y < minY ) minY = point.y;
	}

	return std::pair<double, double>( minX, minY );
}

std::vector<std::vector<int>> Polygon::getMatrixRepresentation( double h ){ //Ïåðåíåñòè â äðóãîé êëàññ
	double accuracy = h * 0.000001;
	this->shiftToGlobalOrigin();
	auto maxXY = this->maxXY();
	auto minXY = this->minXY();
	double xSideLen = maxXY.first - minXY.first;
	double ySideLen = maxXY.second - minXY.second;
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
				 abs( points_ [i1].y - points_ [i0].y ) > 0.0000000001 )
			{
				double a = -( points_ [i1].x - points_ [i0].x ) / ( points_ [i1].y - points_ [i0].y );
				double b = -points_ [i0].x - points_ [i0].y * a;
				double yP = k * h;
				double xP = -b - a * k * h;

				if ( abs( xP - points_ [i0].x ) < 0.0000000001 )
				{
					if ( ( points_ [i1].y - yP ) * ( points_ [i0 == 0 ? size - 1 : i0 - 1].y - yP ) < 0 )
					{
						edges [k][floor( xP / h + accuracy )] += 1;
					}
					else if ( ( points_ [i1].y - yP ) * ( points_ [i0 == 0 ? size - 1 : i0 - 1].y - yP ) > 0 )
					{
						edges [k][floor( xP / h + accuracy )] += 2;
					}
				}
				else if ( abs( xP - points_ [i1].x ) > 0.0000000001 )
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
				if ( k > 0 ) matrix [k - 1][i] = 1;//Âñå Âåðíî?
				flag = !flag;
			}
			if ( flag )
			{
				matrix [k][i] = 1;
				if ( k > 0 ) matrix [k - 1][i] = 1; //Âñå âåðíî ?
			}
		}
	}

	for ( auto i = 0; i < size; i++ )
	{
		int j = ( i + 1 ) % size;
		Point<double> i1( points_ [i] );
		Point<double> i2( points_ [j] );
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
			for ( auto j = 0; j <= abs( j1.x - j2.x ); j++ ) // Áûëî i Íå ñëîìàåòñÿ ? 
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
				if ( j2 != p ) //Àíàëîãè÷íî áûëî i
				{
					double a = -( i2.x - i1.x ) / ( i2.y - i1.y );
					double b = -i1.x - i1.y * a;
					double xP = -b - a * ( p.y + check ) * h;
					if ( ( xP > 0 ? floor( xP / h + accuracy ) : ceil( xP / h - accuracy ) ) == p.x )
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
