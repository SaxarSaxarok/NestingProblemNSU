#include "Pallet.h"
#include <iostream>


Pallet::Pallet( double w, double h, double pixelSize ): width_( w ), heigth_( h ), pixelSize_( pixelSize ){
	discreteWidth_ = floor( width_ / pixelSize ); //?
	discreteHeigth_ = floor( heigth_ / pixelSize ); //?
	shifts_ = std::vector<std::vector<int>>( discreteHeigth_, std::vector<int>( 1, -discreteWidth_ ) );//Верно ?
}

std::vector<Item>& Pallet::items(){
	return items_;
}

bool Pallet::packItem( Item& item ){

	int optimalX = discreteWidth_ + 1;
	int optimalY = discreteHeigth_ + 1;
	int optimalRotation = 0;
	bool isPlaced = false;
	for ( int i = 0; i < 4; i++ )
	{
		int x = 0, y = 0;
		item.currentRotation( i );
		isPlaced = findPlacePosition( item, x, y );

		if ( optimalY > y + item.matrix().size() || ( optimalY == y + item.matrix().size() && optimalX > x ) )
		{
			optimalY = y + item.matrix().size();
			optimalX = x;
			optimalRotation = i;
		}
	}
	if ( isPlaced )
	{
		item.currentRotation( optimalRotation );
		item.rotate()
			.moveTo( Point<double>( optimalX * pixelSize_, ( optimalY - item.matrix().size() ) * pixelSize_ ) );
		/*std::cout << item.currentRotation() << std::endl;*/
		placeItem( item, optimalX, optimalY - item.matrix().size() );
		items_.push_back( item );
		std::cout << item.id_ << std::endl;
	}
	return isPlaced;
}

bool Pallet::findPlacePosition( Item& item, int& optimalX, int& optimalY ) const{
	optimalX = 0;
	optimalY = 0;
	int shift = 0;
	int badLine = 0;
	bool isPlaced = false;

	while ( !isPlaced && ( ( optimalY + item.shifts().size() ) <= shifts_.size() ) )
	{
		while ( !isPlaced && ( ( optimalX + shift + item.matrix( 0 ).size() ) <= discreteWidth_ ) )//Not sure
		{
			optimalX += shift;
			isPlaced = isItemCanPlace( item, optimalX, optimalY, badLine, shift );
		}
		if ( !isPlaced )
		{
			optimalY++;
			optimalX = 0;
			shift = 0;
		}
	}
	return isPlaced;
}

bool Pallet::isItemCanPlace( Item& item, int x, int y, int& badLine, int& shift ) const{
	bool isPlaced = true;
	int j = 0;

	if ( y < badLine && item.shifts().size() > 25 )
	{
		isPlaced = isRowCanPlace( item.shifts( badLine - y ), item.matrix( 0 ).size(), shifts_ [badLine], x, shift );
		if ( !isPlaced ) return isPlaced;
	}
	while ( j < item.shifts().size() && isPlaced )
	{
		isPlaced = isRowCanPlace( item.shifts( item.orderedIndexes( j ) ), item.matrix( 0 ).size(), shifts_ [item.orderedIndexes( j ) + y], x, shift );
		j += 1;
	}
	badLine = item.orderedIndexes( j - 1 ) + y;
	return isPlaced;
}

bool Pallet::isRowCanPlace( const std::vector<int>& itemRow, int rowLength, const std::vector<int>& palletRow, int x, int& shift ) const{
	bool isPlaced = true;
	shift = 0;
	int writeReadHead = 0;
	while ( isPlaced && writeReadHead < rowLength )
	{
		Point<int> pal = getPixel( palletRow, x + writeReadHead );
		Point<int> it = getPixel( itemRow, writeReadHead );
		isPlaced = isPixelCanPlace( pal.x, it.x, itemRow [it.y], shift );
		writeReadHead += shift;
	}
	return isPlaced;
}

Point<int> Pallet::getPixel( const std::vector<int>& row, int iter ) const{
	int r = 0;
	int i = -1;
	int sign = 1;

	while ( r < iter + 1 )
	{
		i += 1;
		r += abs( row [i] );
	}
	if ( row [i] < 0 ) sign = -1;
	return Point<int>( sign * ( r - iter ), i );
}

bool Pallet::isPixelCanPlace( int palletPixel, int itemPixel, int itemUnit, int& shift ) const{
	bool isPlaced = false;
	shift = 0;
	if ( itemPixel < 0 || palletPixel < 0 )
	{
		isPlaced = true;
		shift = -std::min( itemPixel, palletPixel );
	}
	else
	{
		isPlaced = false;
		shift = palletPixel + itemUnit - itemPixel;
	}
	return isPlaced;
}

void Pallet::placeItem( const Item& item, int x, int y ){
	for ( int i = 0; i < item.shifts().size(); i++ )
	{
		placeRow( item.shifts( i ), shifts_ [y + i], x );
	}
}

void Pallet::placeRow( const std::vector<int>& itemRow, std::vector<int>& palletRow, int x ){
	int numberFirstPositiveUnit = 0;
	if ( itemRow [numberFirstPositiveUnit] < 0 )
	{
		x -= itemRow [numberFirstPositiveUnit];
		numberFirstPositiveUnit = 1;
	}
	for ( int numberPositiveUnit = numberFirstPositiveUnit; numberPositiveUnit < itemRow.size(); numberPositiveUnit += 2 )
	{
		placeUnit( itemRow, palletRow, x, numberPositiveUnit );
		if ( numberPositiveUnit + 2 < itemRow.size() )
		{
			x += itemRow [numberPositiveUnit] + abs( itemRow [numberPositiveUnit + 1] );
		}
	}
}

void Pallet::placeUnit( const std::vector<int>& item_line, std::vector<int>& pallet_line, int x, int number_item_unit ){ //Code from python
	Point<int> pal = getPixel( pallet_line, x );
	int pallet_pixel = pal.x;
	int number_pallet_unit = pal.y;
	int number_pixels_left = pallet_line [number_pallet_unit] - pallet_pixel;
	int number_pixels_right = pallet_pixel + item_line [number_item_unit];

	if ( 0 < number_pallet_unit && number_pallet_unit + 1 < pallet_line.size() )
	{
		if ( number_pixels_left == 0 && number_pixels_right == 0 )
		{
			pallet_line [number_pallet_unit - 1] += -pallet_line [number_pallet_unit];
			pallet_line.erase( pallet_line.begin() + number_pallet_unit );
			pallet_line [number_pallet_unit - 1] += pallet_line [number_pallet_unit];
			pallet_line.erase( pallet_line.begin() + number_pallet_unit );
		}
		else if ( number_pixels_left != 0 && number_pixels_right != 0 )
		{
			pallet_line.insert( pallet_line.begin() + number_pallet_unit + 1, number_pixels_right );
			pallet_line [number_pallet_unit] = item_line [number_item_unit];
			pallet_line.insert( pallet_line.begin() + number_pallet_unit, number_pixels_left );
		}
		else if ( number_pixels_left == 0 && number_pixels_right != 0 )
		{
			pallet_line [number_pallet_unit] = number_pixels_right;
			pallet_line [number_pallet_unit - 1] += item_line [number_item_unit];
		}
		else
		{
			pallet_line [number_pallet_unit] = number_pixels_left;
			pallet_line [number_pallet_unit + 1] += item_line [number_item_unit];
		}
	}
	else if ( number_pallet_unit == 0 && pallet_line.size() != 1 )
	{
		if ( number_pixels_left == 0 && number_pixels_right == 0 )
		{
			pallet_line.erase( pallet_line.begin() + number_pallet_unit );
			pallet_line [number_pallet_unit] += item_line [number_item_unit];
		}
		else if ( number_pixels_left != 0 && number_pixels_right != 0 )
		{
			pallet_line.insert( pallet_line.begin() + number_pallet_unit + 1, number_pixels_right );
			pallet_line [number_pallet_unit] = item_line [number_item_unit];
			pallet_line.insert( pallet_line.begin() + number_pallet_unit, number_pixels_left );
		}
		else if ( number_pixels_left == 0 && number_pixels_right != 0 )
		{
			pallet_line [number_pallet_unit] = number_pixels_right;
			pallet_line.insert( pallet_line.begin() + number_pallet_unit, item_line [number_item_unit] );
		}
		else
		{
			pallet_line [number_pallet_unit] = number_pixels_left;
			pallet_line [number_pallet_unit + 1] += item_line [number_item_unit];
		}
	}
	else if ( number_pallet_unit == pallet_line.size() - 1 && pallet_line.size() != 1 )
	{
		if ( number_pixels_left == 0 && number_pixels_right == 0 )
		{
			pallet_line.pop_back(); //Change
			pallet_line [number_pallet_unit - 1] += item_line [number_item_unit];
		}
		else if ( number_pixels_left != 0 && number_pixels_right != 0 )
		{
			pallet_line.insert( pallet_line.begin() + number_pallet_unit + 1, number_pixels_right );
			pallet_line [number_pallet_unit] = item_line [number_item_unit];
			pallet_line.insert( pallet_line.begin() + number_pallet_unit, number_pixels_left );
		}
		else if ( number_pixels_left == 0 && number_pixels_right != 0 )
		{
			pallet_line [number_pallet_unit] = number_pixels_right;
			pallet_line [number_pallet_unit - 1] += item_line [number_item_unit];
		}
		else
		{
			pallet_line [number_pallet_unit] = number_pixels_left;
			pallet_line.insert( pallet_line.begin() + number_pallet_unit + 1, item_line [number_item_unit] );
		}
	}
	else if ( pallet_line.size() == 1 )
	{
		if ( number_pixels_left == 0 && number_pixels_right == 0 )
		{
			pallet_line [number_pallet_unit] *= -1;
		}
		else if ( number_pixels_left != 0 && number_pixels_right != 0 )
		{
			pallet_line.insert( pallet_line.begin() + number_pallet_unit + 1, number_pixels_right );
			pallet_line [number_pallet_unit] = item_line [number_item_unit];
			pallet_line.insert( pallet_line.begin() + number_pallet_unit, number_pixels_left );
		}
		else if ( number_pixels_left == 0 && number_pixels_right != 0 )
		{
			pallet_line [number_pallet_unit] = number_pixels_right;
			pallet_line.insert( pallet_line.begin() + number_pallet_unit, item_line [number_item_unit] );
		}
		else
		{
			pallet_line [number_pallet_unit] = number_pixels_left;
			pallet_line.insert( pallet_line.begin() + number_pallet_unit + 1, item_line [number_item_unit] );
		}
	}
	else
	{
		return;
	}

}
