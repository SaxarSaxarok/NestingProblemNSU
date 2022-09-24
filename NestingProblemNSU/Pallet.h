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
public:

	Pallet( float w, float h, float pixelSize);

	bool placeItem( const Item& item );
};

