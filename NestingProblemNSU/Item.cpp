#include "Item.h"
#include <algorithm>
#include <iostream>

Item::Item( int id, std::vector<Point<float>> points, float h ): id( id ), Polygon( points ){
	matrix = this->getMatrixRepresentation( h );
	calculateAllRotations();
	calculateAllOrderedIndexes();
}
Item::Item( int id, Polygon polygon, float h ) : id( id ), Polygon( polygon ){
	matrix = this->getMatrixRepresentation( h );
	calculateAllRotations();
	calculateAllOrderedIndexes();
}

bool Item::operator<( Item const& item ) const{
	return this->matrix.size() * this->matrix [0].size() - item.matrix.size() * item.matrix [0].size() < 0;
}

bool Item::operator<=( Item const& item ) const{
	return ( *this ) < item || matrix.size() * this->matrix [0].size() == item.matrix.size() * item.matrix [0].size();
}

bool Item::operator>( Item const& item ) const{
	return !( ( *this ) < item );
}

bool Item::operator>=( Item const& item ) const{
	return !( ( *this ) <= item ) || this->matrix [0].size() == item.matrix.size() * item.matrix [0].size();
}

std::vector<std::vector<int>> Item::calculateShifts( std::vector<std::vector<int>> matrix ){
	std::vector<std::vector<int>> shifts;
	for ( auto j = 0; j < matrix.size(); j++ )
	{
		shifts.push_back( std::vector<int>() );
		int beforeValue = matrix [j][0];
		int sum = 1;

		for ( auto i = 1; i < matrix [j].size(); i++ )
		{

			if ( matrix [j][i] == beforeValue )
			{
				sum += 1;
			}
			else
			{
				if ( beforeValue == 0 ) sum *= -1;
				shifts [j].push_back( sum );
				beforeValue = matrix [j][i];
				sum = 1;
			}
		}
		if ( beforeValue == 0 ) sum *= -1;
		shifts [j].push_back( sum );
	}
	return shifts;
}



std::vector<std::vector<int>> Item::rotateMatrixBy90( std::vector<std::vector<int>> matrix ){
	std::vector<std::vector<int>> rotMatrix( matrix [0].size(), std::vector<int>( matrix.size(), 0 ) );

	for ( int i = 0; i < rotMatrix.size(); i++ )
	{
		for ( int j = 0; j < rotMatrix [i].size(); j++ )
		{
			rotMatrix [i][j] = matrix [matrix.size() - 1 - j][i];
		}
	}

	return rotMatrix;
}

void Item::calculateAllRotations(){
	rotationsOfMatrix [0] = matrix;
	rotationsOfMatrix [1] = rotateMatrixBy90( matrix );
	rotationsOfMatrix [2] = rotateMatrixBy90( rotationsOfMatrix [1] );
	rotationsOfMatrix [3] = rotateMatrixBy90( rotationsOfMatrix [2] );

	for ( int i = 0; i < 4; i++ ) rotationsOfShifts [i] = calculateShifts( rotationsOfMatrix [i] );

	for ( int i = 0; i < 4; i++ )
	{
		std::cout << "Rotation number " << i<<'\n';
		for ( int j = 0; j < rotationsOfShifts [i].size(); j++ )
		{
			for ( int k = 0; k < rotationsOfShifts [i][j].size(); k++ )
			{
				std::cout << rotationsOfShifts [i][j][k] << ' ';
			}
			std::cout << '\n';
		}
	}
	std::cout << '\n';
}

void Item::calculateAllOrderedIndexes(){
	for ( int i = 0; i < 4; i++ )
	{
		std::vector<std::pair<int, int>> indexAndMaxElement( rotationsOfMatrix [i].size(), std::pair<int, int>( 0, 0 ) );

		for ( int j = 0; j < rotationsOfMatrix [i].size(); j++ )
		{
			indexAndMaxElement [j].first = j;
			indexAndMaxElement [j].second = rotationsOfShifts [i][j][std::distance( rotationsOfShifts [i][j].begin(), std::max_element( rotationsOfShifts [i][j].begin(), rotationsOfShifts [i][j].end() ) )];
		}
		sort( indexAndMaxElement.begin(), indexAndMaxElement.end(), []( std::pair<int, int> a, std::pair<int, int> b ) {
			return ( a.second > b.second );
		} );
		orderedIndexes [i] = std::vector<int>( rotationsOfShifts [i].size() );

		for ( int j = 0; j < orderedIndexes [i].size(); j++ )
		{
			orderedIndexes [i][j] = indexAndMaxElement [j].first;
		}
	}

	for ( int i = 0; i < 4; i++ )
	{
		std::cout << "Rotation on " << i * 90 << " degrees"<<'\n'<<"Number of indexes: ";

		for ( int j = 0; j < orderedIndexes [i].size(); j++ )
		{
			std::cout << orderedIndexes [i][j] << ' ';
		}
		std::cout << '\n';
	}
}
