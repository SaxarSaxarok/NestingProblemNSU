#pragma once
template<typename T>
struct Point{
	T x, y;

	Point( T x_ = 0, T y_ = 0 ): x( x_ ), y( y_ ){};
	Point( const Point& p ): x( p.x ), y( p.y ){};
	Point& operator=( const Point& p ){ // ћожет быть исправить, что-то должен возвращать ?
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
};

