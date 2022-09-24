#include "Pallet.h"


Pallet::Pallet( float w, float h, float pixelSize ): width( w ), heigth( h ), pixelSize(pixelSize){
	discreteWidth = floor( width / pixelSize );
	discreteHeigth = floor( heigth / pixelSize );
	shifts = std::vector<std::vector<int>>( discreteHeigth, std::vector<int>( 1, -discreteWidth ) );//Верно ?
}

bool Pallet::placeItem( const Item& item ){

	for ( int i = 0; i < 4; i++ )
	{
		int x = 0;
		int y = 0;
		int shift = 0;
		bool isPlaced = false;

		while ( !isPlaced && ( y + item.size() <= this->discreteHeigth ) )
		{
		}
	}
	return true;
}


