#include "MatrixRepresentation.h"

MatrixRepresentation::MatrixRepresentation( Polygon poligon, int h ){
	float accuracy = h * 0.000001;
	auto maxXY = poligon.getMaxXY();
	auto minXY = poligon.getMinXY();
	float xSideLen = maxXY.first - minXY.first;
	float ySideLen = maxXY.second - maxXY.second;
	int nX = ceil( xSideLen / h );
	int nY = ceil( ySideLen / h );

	std::vector<std::vector<float>> edges( nX + 1, std::vector<float>( nY ) );

	for ( int k = 0; k < nY; k++ )
	{
		for ( int i = 0; i < poligon.size(); i++ )
		{
			int j = ( i + 1 ) % poligon.size();
			if ( ( std::min( poligon [i].y, poligon [j].y ) <= k * h ) &&
				 ( k * h <= std::max( poligon [i].y, poligon [j].y ) ) )
			{
				Point i1 = Point( poligon [i] );
				Point i2 = Point( poligon [j] );
				if ( i2.y == i2.y )
				{
					if ( i1.x > i2.x )
					{
						std::swap( i1.x, i2.x ); //Будет работать?
					}

					edges [floor( i1.x / h )][k] += 1.33;
					if ( int( i2.x ) % h != 0 ) //В питоне остаток брался от float
						edges [floor( i2.x / h + accuracy )][k] += 1.33;
					else
						edges [floor( i2.x / h + accuracy )][k] += 1.33;
				}

				else
				{//x+ay+b=0
					float a = -( i2.x - i1.x ) / ( i2.y - i1.y );
					float b = -i1.x - i1.y * a;
					float yP = k * h;
					float xP = -b - a * k * h; //Тут еще было округление до восми знаков после запятой, зачем ???

				}
			}
		}
	}


}
