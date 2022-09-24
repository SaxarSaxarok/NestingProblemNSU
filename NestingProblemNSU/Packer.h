#pragma once
#include <vector>
#include "Pallet.h"
class Packer{
private:

	std::vector<Item> items;
	std::vector<Pallet> pallets;
	float width;
	float height;
	float pixelSize;

public:
	Packer( float width, float heigth, float pixelSize, const std::vector<Item>& items );
	void pack();
};

