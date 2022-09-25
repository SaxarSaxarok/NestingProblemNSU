#pragma once
#include <vector>
#include "Item.h"

class Pallet{
private:

	float width_;
	float heigth_;
	int discreteWidth_;
	int discreteHeigth_;
	float pixelSize_;
	std::vector<Item> items_;
	std::vector<std::vector<int>> shifts_;
public:

	Pallet( float w, float h, float pixelSize );

	bool packItem( Item& item );

private:
	bool findPlacePosition( Item& item, int& optimalX, int& optimalY );
	bool isItemCanPlace( Item& item, int x, int y, int& badLine, int& shift );
	bool isRowCanPlace( const std::vector<int>& itemRow, int rowLength, const std::vector<int>& paleteRow, int x, int& shift );
	Point<int> getPixel( const std::vector<int>& paleteRow, int iter );
	bool isPixelCanPlace( int palletPixel, int itemPixel, int itemUnit, int& shift );

	void placeItem( Item& item, int x, int y );
	void placeRow( std::vector<int>& itemRow, std::vector<int>& palletRow, int x );
	void placeUnit( std::vector<int>& itemRow, std::vector<int>& palletRow, int x, int numberUnit );
};

