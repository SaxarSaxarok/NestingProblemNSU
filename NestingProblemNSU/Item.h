#pragma once
#include "Polygon.h"
class Item: public Polygon{
private:
	std::vector<std::vector<int>> matrix_;
	std::vector<std::vector<int>> rotationsOfMatrix_ [4];
	std::vector<std::vector<int>> rotationsOfShifts_ [4];
	std::vector<int>orderedIndexes_ [4];
	int id_;
	int currentRotation_;
public:

	void rotate();
	const std::vector<std::vector<int>>& matrix() const;
	const std::vector<std::vector<int>>& shifts() const;
	const std::vector<int>& orderedIndexes() const;

	 std::vector<std::vector<int>>& matrix() ;
	 std::vector<std::vector<int>>& shifts();
	 std::vector<int>& orderedIndexes();

	int currentRotation() const;
	void currentRotation( int rotation );


	Item( int id, std::vector<Point<float>> points, float h );
	Item( int id, Polygon polygon, float h );

	bool operator< (Item const& item ) const;
	bool operator<= ( Item const& item ) const;
	bool operator> ( Item const& item ) const;
	bool operator>= ( Item const& item ) const;

private:
	std::vector < std::vector<int>> calculateShifts( std::vector<std::vector<int>> matrix );
	std::vector <std::vector<int>> rotateMatrixBy90( std::vector<std::vector<int>> matrix );
	void calculateAllRotations();
	void calculateAllOrderedIndexes();
};

