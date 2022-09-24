#pragma once
#include "Polygon.h"
class Item: public Polygon{
private:
	std::vector<std::vector<int>> matrix;
	std::vector<std::vector<int>> rotationsOfMatrix [4];
	std::vector<std::vector<int>> rotationsOfShifts [4];
	int id;
public:
	std::vector<int>orderedIndexes[4];

	Item( int id, std::vector<Point<float>> points, float h );
	Item( int id, Polygon polygon, float h );
	bool operator< (Item const& item );
	bool operator<= ( Item const& item );
	bool operator> ( Item const& item );
	bool operator>= ( Item const& item );

private:
	std::vector < std::vector<int>> calculateShifts( std::vector<std::vector<int>> matrix );
	std::vector <std::vector<int>> rotateMatrixBy90( std::vector<std::vector<int>> matrix );
	void calculateAllRotations();
	void calculateAllOrderedIndexes();
};

