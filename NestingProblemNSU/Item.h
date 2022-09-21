#pragma once
#include "Polygon.h"
class Item
{
private:
	Polygon polygon;
	std::vector<std::vector<int>> matrix;
	std::vector<std::vector<int>> shifts;
public:
	Item( Polygon& polygon , float h);

private:

void makeShifts();
};
