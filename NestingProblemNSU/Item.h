#pragma once
#include "Polygon.h"
class Item: public Polygon{
private:
	std::vector<std::vector<int>> matrix_;
	std::vector<std::vector<int>> rotationsOfMatrix_ [4];
	std::vector<std::vector<int>> rotationsOfShifts_ [4];
	std::vector<int>orderedIndexes_ [4];
	int currentRotation_;
public:
	int id_;
	Item( int id, std::vector<Point<double>>& points, double h );
	Item( int id, Polygon& polygon, double h );

	const std::vector<std::vector<int>>& matrix() const;
	const std::vector<int>& matrix( int i ) const;
	int matrix( int i, int j ) const;

	const std::vector<std::vector<int>>& shifts() const;
	const std::vector<int>& shifts( int i ) const;
	int  shifts( int i, int j ) const;

	const std::vector<int>& orderedIndexes() const;
	int orderedIndexes(int i) const;


	int currentRotation() const;
	void currentRotation( int rotation );
	void rotate();

	bool operator< (Item const& item ) const;
	bool operator<= ( Item const& item ) const;
	bool operator> ( Item const& item ) const;
	bool operator>= ( Item const& item ) const;

private:
	std::vector < std::vector<int>> calculateShifts(  std::vector<std::vector<int>> const& matrix );
	std::vector <std::vector<int>> rotateMatrixBy90(  std::vector<std::vector<int>> const& matrix );
	void calculateAllRotations();
	void calculateAllOrderedIndexes();
};

