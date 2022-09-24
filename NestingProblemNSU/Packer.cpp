#include "Packer.h"


Packer::Packer( float width, float heigth, float pixelSize, const std::vector<Item>& items ): width(width), height( heigth ), items(items), pixelSize(pixelSize){
	pallets.push_back( Pallet( width, height, pixelSize ) );
}

void Packer::pack(){
	for ( auto& item : items )
	{
		if ( !pallets [pallets.size() - 1].placeItem( item ) )
		{
			pallets.push_back( Pallet( width, height, pixelSize ) );
		}
	}
}
