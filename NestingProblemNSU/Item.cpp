#include "Item.h"
#include <algorithm>
#include <iostream>

Item::Item( int id, std::vector<Point<double>>& points, double h ): id_( id ),currentRotation_(0), Polygon( points ){
	matrix_ = this->getMatrixRepresentation( h );
	calculateAllRotations();
	calculateAllOrderedIndexes();
}
Item::Item( int id, Polygon& polygon, double h ) : id_( id ),currentRotation_(0) ,Polygon( polygon ){
	matrix_ = this->getMatrixRepresentation( h );
	calculateAllRotations();
	calculateAllOrderedIndexes();
}

Item& Item::rotate(){
	if ( currentRotation_ == 0 ) return;
	for ( auto& point : points_ )
	{
		if ( currentRotation_ == 1 )
		{
			std::swap( point.x, point.y );
			point.y *= -1;
		}
		else if ( currentRotation_ == 2 )
		{
			point.x *= -1;
			point.y *= -1;
		}
		else if ( currentRotation_ == 3 )
		{
			std::swap( point.x, point.y );
			point.x *= -1;
		}
	}
	this->shiftToOrigin();
}

const std::vector<std::vector<int>>& Item::matrix() const{
	return rotationsOfMatrix_ [this->currentRotation_];
}

const std::vector<int>& Item::matrix( int i ) const{
	return rotationsOfMatrix_ [currentRotation_][i];
}

int Item::matrix( int i, int j ) const{
	return rotationsOfMatrix_ [currentRotation_][i][j];
}

const std::vector<std::vector<int>>& Item::shifts() const{
	return rotationsOfShifts_ [currentRotation_];
}

const std::vector<int>& Item::shifts( int i ) const{
	return rotationsOfShifts_ [currentRotation_][i];
}

int Item::shifts( int i, int j ) const{
	return rotationsOfShifts_ [currentRotation_][i][j];
}

const std::vector<int>& Item::orderedIndexes() const{
	return orderedIndexes_ [currentRotation_];
}

int Item::orderedIndexes( int i ) const{
	return orderedIndexes_ [currentRotation_][i];
}

int Item::currentRotation() const{
	return currentRotation_;
}

void Item::currentRotation( int rotation ){
	currentRotation_ = rotation;
}

bool Item::operator<( Item const& item ) const{
	return this->matrix_.size() * this->matrix_[0].size() - item.matrix_.size() * item.matrix_ [0].size() < 0;
}

bool Item::operator<=( Item const& item ) const{
	return ( *this ) < item || matrix_.size() * this->matrix_ [0].size() == item.matrix_.size() * item.matrix_ [0].size();
}

bool Item::operator>( Item const& item ) const{
	return !( ( *this ) < item );
}

bool Item::operator>=( Item const& item ) const{
	return !( ( *this ) <= item ) || this->matrix_ [0].size() == item.matrix_.size() * item.matrix_ [0].size();
}

std::vector<std::vector<int>> Item::calculateShifts( const std::vector<std::vector<int>>& matrix ){
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



std::vector<std::vector<int>> Item::rotateMatrixBy90(const std::vector<std::vector<int>>& matrix ){
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
	rotationsOfMatrix_ [0] = matrix_;
	rotationsOfMatrix_ [1] = rotateMatrixBy90( matrix_ );
	rotationsOfMatrix_ [2] = rotateMatrixBy90( rotationsOfMatrix_ [1] );
	rotationsOfMatrix_ [3] = rotateMatrixBy90( rotationsOfMatrix_ [2] );

	for ( int i = 0; i < 4; i++ ) rotationsOfShifts_ [i] = calculateShifts( rotationsOfMatrix_ [i] );
}

void Item::calculateAllOrderedIndexes(){
	for ( int i = 0; i < 4; i++ )
	{
		std::vector<std::pair<int, int>> indexAndMaxElement( rotationsOfMatrix_ [i].size(), std::pair<int, int>( 0, 0 ) );

		for ( int j = 0; j < rotationsOfMatrix_ [i].size(); j++ )
		{
			indexAndMaxElement [j].first = j;
			indexAndMaxElement [j].second = rotationsOfShifts_ [i][j][std::distance( rotationsOfShifts_ [i][j].begin(), std::max_element( rotationsOfShifts_ [i][j].begin(), rotationsOfShifts_ [i][j].end() ) )];
		}
		sort( indexAndMaxElement.begin(), indexAndMaxElement.end(), []( std::pair<int, int> a, std::pair<int, int> b ) {
			return ( a.second > b.second );
		} );
		orderedIndexes_ [i] = std::vector<int>( rotationsOfShifts_ [i].size() );

		for ( int j = 0; j < orderedIndexes_ [i].size(); j++ )
		{
			orderedIndexes_ [i][j] = indexAndMaxElement [j].first;
		}
	}
}
