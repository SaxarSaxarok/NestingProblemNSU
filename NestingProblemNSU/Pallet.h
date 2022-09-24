#pragma once
#include <vector>
#include "Item.h"

class Pallet{
private:

	float width;
	float heigth;
	int discreteWidth;
	int discreteHeigth;
	float pixelSize;
	std::vector<Item> items;
	std::vector<std::vector<int>> shifts;
public:

	Pallet( float w, float h, float pixelSize);

	bool placeItem( const Item& item );

private:
	bool isCanPlace( const Item& item, int& minxindex, int& minYindex );
	bool findFirstColumnAndRowForItemRow( int row, const std::vector<int>& rowShifts, int& currentMinX, int& currentMinY);
};

