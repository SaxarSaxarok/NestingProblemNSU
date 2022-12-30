#pragma once
#include "Point.h"
#include<vector>
#include <ostream>
#include "Arrangement.h"

class Polygon{
protected:
	std::vector<Point<double>> points_;
	mutable Point<double>* localOriginValue_ = nullptr;

public:

	//---------------------------CONSTRUCTORS--------------------------//

	Polygon();
	Polygon( const std::vector<Point<double>>& points_ );
	Polygon( const Polygon& polygon_ );
	Polygon( Polygon&& points ) noexcept;
	Polygon& operator = ( const Polygon& );
	Polygon& operator = ( Polygon&& ) noexcept;
	//---------------------------GETTERS------------------------------//

	Point<double> localOrigin() const;
	Point<double> operator [] ( int index ) const;
	int size() const;
	std::pair<double, double> maxXY() const;
	std::pair<double, double> minXY() const;
	std::vector<std::vector<int>> getMatrixRepresentation( double h );

	//---------------------------MUTATORS------------------------------//

	Polygon& moveTo( Point<double> point );
	Polygon& translateOn( Point<double> vector );
	Polygon* shiftToGlobalOrigin();
	Polygon& rotateOn( double radians);

	//---------------------------NFP----------------------------------//

	static std::vector<Segment> reducedConvolution( const Polygon& that, const Polygon& other );
	static Arrangement minkowskiSum( const Polygon& that, const Polygon& other );
	static Arrangement nfp( const Polygon& that, const Polygon& other );

	//-------------------------PRINT----------------------------------//

	std::ostream& print( std::ostream& out );
	friend std::ostream& operator << ( std::ostream& out, Polygon& object );

private:
	void localOrigin( Point<double> point ) const;
};

