#include "MatrixRepresentation.h"
#include <iostream>

MatrixRepresentation::MatrixRepresentation( Polygon polygon, float h ){
	float accuracy = h * 0.000001;
	polygon.shiftToOrigin();
	auto maxXY = polygon.getMaxXY();
	auto minXY = polygon.getMinXY();
	float xSideLen = maxXY.first - minXY.first;
	float ySideLen = maxXY.second - minXY.second;
	int nX = ceil( xSideLen / h );
	int nY = ceil( ySideLen / h );

	std::vector<std::vector<int>> edges( nX + 1, std::vector<int>( nY, 0 ) );

	for ( int k = 0; k < nY; k++ )
	{
		for ( int i0 = 0; i0 < polygon.size(); i0++ )
		{
			int i1 = ( i0 + 1 ) % polygon.size();
			if ( ( std::min( polygon [i0].y, polygon [i1].y ) <= k * h ) &&
				 k * h <= std::max( polygon [i0].y, polygon [i1].y ) &&
				 abs( polygon [i1].y - polygon [i0].y ) > FLT_EPSILON )
			{
				float a = -( polygon [i1].x - polygon [i0].x ) / ( polygon [i1].y - polygon [i0].y );
				float b = -polygon [i0].x - polygon [i0].y * a;
				float yP = k * h;
				float xP = -b - a * k * h;

				if ( abs( xP - polygon [i0].x ) < FLT_EPSILON )
				{
					if ( ( polygon [i1].y - yP ) * ( polygon [( ( ( i0 - 1 ) % polygon.size() ) + polygon.size() ) % polygon.size()].y - yP ) < 0 )
					{
						edges [floor( xP / h + accuracy )][k] += 1;
					}
					else if ( ( polygon [i1].y - yP ) * ( polygon [( ( ( i0 - 1 ) % polygon.size() ) + polygon.size() ) % polygon.size()].y - yP ) > 0 )
					{
						edges [floor( xP / h + accuracy )][k] += 2;
					}
				}
				else if ( abs( xP - polygon [i1].x ) > FLT_EPSILON )
				{
					edges [floor( xP / h + accuracy )][k] += 1;
				}
			}
		}
	}
	matrix = std::vector<std::vector<int>>( nX + 1, std::vector<int>( nY + 1, 0 ) );

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

	for ( int i = 0; i < polygon.size(); i++ )
	{
		int j = ( i + 1 ) % polygon.size();
		Point<float> i1( polygon [i] );
		Point<float> i2( polygon [j] );

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
}
