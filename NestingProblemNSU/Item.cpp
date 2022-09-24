#include "Item.h"

Item::Item( int id, std::vector<Point<float>> points, float h ): id( id ), Polygon( points ){
	matrix = this->getMatrixRepresentation( h );
	calculateAllRotations();
}
Item::Item( int id, Polygon polygon, float h ) : id( id ), Polygon( polygon ){
	matrix = this->getMatrixRepresentation( h );
	calculateAllRotations();
}

std::vector<std::vector<int>> Item::calculateShifts(std::vector<std::vector<int>> matrix){
	std::vector<std::vector<int>> shifts;
	for ( auto j = 0; j < matrix.size(); j++ )
	{
		shifts.push_back( std::vector<int>() );
		int beforeValue = matrix [j][0];
		int sum = 1;

		for ( auto i = 1; i < matrix [j].size(); i++ )
		{

			if ( matrix [j][i] == beforeValue )
			{
				sum += 1;
			}
			else
			{
				if ( beforeValue == 0 ) sum *= -1;
				shifts [j].push_back( sum );
				beforeValue = matrix [j][i];
				sum = 1;
			}
		}
		if ( beforeValue == 0 ) sum *= -1;
		shifts [j].push_back( sum );
	}
	return shifts;
}



std::vector<std::vector<int>> Item::rotateMatrixBy90( std::vector<std::vector<int>> matrix ){
	std::vector<std::vector<int>> rotMatrix( matrix [0].size(), std::vector<int>( matrix.size(), 0 ) );

	for ( int i = 0; i < rotMatrix.size(); i++ )
	{
		for ( int j = 0; j < rotMatrix [i].size(); j++ )
		{
			rotMatrix [i][j] = matrix [matrix.size() - 1 - j][i];
		}
	}

	return rotMatrix;
}

void Item::calculateAllRotations(){
	rotationsOfMatrix [0] = matrix;
	rotationsOfMatrix [1] = rotateMatrixBy90( matrix );
	rotationsOfMatrix [2] = rotateMatrixBy90( rotationsOfMatrix [1] );
	rotationsOfMatrix [3] = rotateMatrixBy90( rotationsOfMatrix [2] );

	for ( int i = 0; i < 4; i++ ) rotationsOfShifts [i] = calculateShifts( rotationsOfMatrix [i] );
}
