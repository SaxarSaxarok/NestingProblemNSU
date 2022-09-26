#pragma once
#include "Point.h"
#include<vector>
#include <ostream>

class Polygon{
protected:
	mutable Point<double>* barycenterValue_;
	mutable double* areaValue_;

public:
	std::vector<Point<double>> points_;
	void moveTo(Point<double> vector);
	Polygon();
	Polygon( const std::vector<Point<double>>& points_ );
	Polygon( const Polygon& polygon_ );
	Polygon( Polygon&& points ) noexcept;
	Polygon& operator = ( const Polygon& );
	Polygon& operator = ( Polygon&& ) noexcept;

	Point<double> barycenter() const;
	double area() const;
	Point<double> operator [] ( int index ) const;

	int size() const;

	std::pair<double, double> MaxXY() const;
	std::pair<double, double> MinXY() const;

	std::vector<std::vector<int>> getMatrixRepresentation( double h );

	Polygon* shiftToOrigin();

	std::ostream& print( std::ostream& out );
	friend std::ostream& operator << ( std::ostream& out, Polygon& object );
};

