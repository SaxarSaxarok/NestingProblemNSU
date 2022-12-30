#pragma once
template<typename T>
struct Point{
	T x, y;

	Point( T x_ = 0, T y_ = 0 ): x( x_ ), y( y_ ){};
	Point( const Point& p ): x( p.x ), y( p.y ){};
	void operator=( const Point& p ){ // Может быть исправить, что-то должен возвращать ?
		this->x = p.x;
		this->y = p.y;
		return *this;
	}
	bool operator==( const Point& p ) const{
		return ( this->x == p.x && this->y == p.y );
	}

	bool operator!=( const Point& p ) const{
		return !( *this == p );
	}

	bool operator <( const Point& p ) const{
		return this->y < p.y || this->y == p.y && this->x < p.x;
	}

	Point operator + ( const Point& other ) const{
		return Point( this->x + other.x, this->y + other.y );
	}

	Point operator - ( const Point& other ) const{
		return Point( this->x - other.x, this->y - other.y );
	}

	Point operator - () const{
		return Point( -this->x, -this->y);
	}

	Point operator *( const T scalar ){
		return Point( this->x * scalar, this->y * scalar );
	}

	double operator^( const Point& other ) const{
		return this->x * other.y - this->y * other.x;
	}

	bool isAngleConvex( const Point& p1, const Point& p2, const Point& p3 ){
		return ( p2 - p1 ) ^ ( p3 - p2 )>0.0000001; //Поменять
	}
};