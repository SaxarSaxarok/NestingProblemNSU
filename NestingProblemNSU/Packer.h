#pragma once
#include <vector>
#include "Pallet.h"
class Packer{
private:

	std::vector<Item> items;
	float width;
	float height;
	float pixelSize;

public:
	std::vector<Pallet> pallets;


	Packer( float width, float heigth, float pixelSize, const std::vector<Item>& items );
	void pack();
};

