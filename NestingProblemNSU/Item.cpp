#include "Item.h"

Item::Item( Polygon& polygon , float h){
	this->polygon = polygon;
	matrix = polygon.getMatrixRepresentation(h);
	makeShifts();
}

//TODO: проверить

void Item::makeShifts(){
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
				shifts[j].push_back( sum );
				beforeValue = matrix [j][i];
				sum = 1;
			}
		}
		if ( beforeValue == 0 ) sum *= -1;
		shifts[j].push_back( sum );
	}
}