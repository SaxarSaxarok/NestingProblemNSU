#include "Packer.h"
#include<algorithm>
#include<iostream>

Packer::Packer( float w, float h, float pixelSize, const std::vector<Item>& items ): width( w ), height( h ), items( items ), pixelSize( pixelSize ){
	pallets.push_back( Pallet( width, height, pixelSize ) );
	sort( this->items.begin(), this->items.end(), []( Item const &a, Item const &b ) -> bool {
		return ( a > b );
		} );
}

void Packer::pack(){
	int i = 0;
	bool isPacked = false;
	for ( auto& item : items )
	{
		while ( !isPacked )
		{
			isPacked = false;
			if ( !pallets [i].placeItem( item ) )
			{
				i++;
				if ( i > pallets.size() - 1 )
				{
					pallets.push_back( Pallet( width, height, pixelSize ) );
					if ( !pallets [i].placeItem( item ) )
					{
						std::cout << "The item is too big";
						return;
					}
					else
					{
						isPacked = true;
					}
				}
			}
			else
			{
				isPacked = true;
			}
		}
	}
}
