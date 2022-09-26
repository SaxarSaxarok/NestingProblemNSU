#pragma once
#include <vector>
#include "Item.h"

class Pallet{
private:

	double width_;
	double heigth_;
	int discreteWidth_;
	int discreteHeigth_;
	double pixelSize_;
	std::vector<Item> items_;
	std::vector<std::vector<int>> shifts_;
public:

	Pallet( double w, double h, double pixelSize );
	std::vector<Item>& items();
	bool packItem( Item& item );

private:
	bool findPlacePosition( Item& item, int& optimalX, int& optimalY ) const;
	bool isItemCanPlace( Item& item, int x, int y, int& badLine, int& shift ) const;
	bool isRowCanPlace( const std::vector<int>& itemRow, int rowLength, const std::vector<int>& paleteRow, int x, int& shift ) const;
	Point<int> getPixel( const std::vector<int>& paleteRow, int iter ) const;
	bool isPixelCanPlace( int palletPixel, int itemPixel, int itemUnit, int& shift ) const;

	void placeItem( Item& item, int x, int y );
	void placeRow( std::vector<int>& itemRow, std::vector<int>& palletRow, int x );
	void placeUnit( std::vector<int>& itemRow, std::vector<int>& palletRow, int x, int numberUnit );
};

