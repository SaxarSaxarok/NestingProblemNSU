#include "Pallet.h"


Pallet::Pallet( float w, float h, float pixelSize ): width( w ), heigth( h ), pixelSize( pixelSize ){
	discreteWidth = floor( width / pixelSize );
	discreteHeigth = floor( heigth / pixelSize );
	shifts = std::vector<std::vector<int>>( discreteHeigth, std::vector<int>( 1, -discreteWidth ) );//Верно ?
}

bool Pallet::placeItem( const Item& item ){

	int optimalX = 0;
	int optomalY = 0;

	for ( int i = 0; i < 4; i++ )
	{
		int minYindex = 0;
		int minXindex = 0;
		bool isPlaced = false;
		while ( !isPlaced )
		{
			for ( auto index : item.orderedIndexes [i] )
			{
				if ( !findFirstColumnAndRowForItemRow( index, item.rotationsOfShifts [i][index], minYindex, minXindex ) ) return false; //Сразу убрали все ненужные случаи когда не было места, что какая-то строка не влазила
			}
			isCanPlace( item, minXindex, minYindex ); // Проверить можно ли с такими дискретными координатами разместить, если нет, то демаем нужные сдвиг обновляя в случае чего минимальны X/Y и снова запуская то что выше
		}
	}
	return true;
}



bool Pallet::isCanPlace( const Item& item, int& minXindex, int& minYindex ){
	return true; //TODO
}

bool Pallet::findFirstColumnAndRowForItemRow( int row, const std::vector<int>& rowShifts, int& currentMinX, int& currentMinY ){

	int rowItemWidth = 0;
	for ( auto shift : rowShifts )
	{
		rowItemWidth += abs( shift );
	}
	if ( rowShifts [0] < 0 ) rowItemWidth += rowShifts [0] + rowShifts [rowShifts.size() - 1];

	while ( true )
	{
		int x = 0;

		for ( auto shift : shifts [row + currentMinY] )
		{
			if ( currentMinX <= x )
			{
				if ( rowItemWidth < -shift )
				{
					currentMinX = x;
					return true;
				}
			}
			x += abs( shift );
		}
		currentMinY++;
		if ( currentMinY > discreteHeigth - 1 ) return false;
	}
}




