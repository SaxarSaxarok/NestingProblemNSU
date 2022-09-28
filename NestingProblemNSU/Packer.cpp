#include "Packer.h"
#include<algorithm>
#include<iostream>

Packer::Packer( double w, double h, double pixelSize, const std::vector<Item>& items ): width( w ), items(items),  height( h ), pixelSize( pixelSize ){
	pallets.push_back( Pallet( width, height, pixelSize ) );
	sort( this->items.begin(), this->items.end(), []( Item const& a, Item const& b ) -> bool
		  { return a.area()>b.area(); } );
}

void Packer::pack(){
	int i = 0;
	bool isPacked = false;
	for ( auto& item : items )
	{
		isPacked = false;
		while ( !isPacked )
		{
			if ( !pallets [i].packItem( item ) )
			{
				i++;
				if ( i > pallets.size() - 1 )
				{
					pallets.push_back( Pallet( width, height, pixelSize ) );
					if ( !pallets [i].packItem( item ) )
					{
						std::cout << "The item is too big";
						return;
					}
					else
					{
						isPacked = true;
						i = 0;
					}
				}
			}
			else
			{
				isPacked = true;
				i = 0;
			}
		}
	}
}
