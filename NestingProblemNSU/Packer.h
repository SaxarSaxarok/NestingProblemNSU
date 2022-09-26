#pragma once
#include <vector>
#include "Pallet.h"
class Packer{
private:

	std::vector<Item> items;
	double width;
	double height;
	double pixelSize;

public:
	std::vector<Pallet> pallets;


	Packer( double width, double heigth, double pixelSize, const std::vector<Item>& items );
	void pack();
};

