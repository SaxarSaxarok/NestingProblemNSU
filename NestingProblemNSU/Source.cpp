#include<vector>
#include "Point.h"
#include "Polygon.h"
#include "Item.h"
#include <iostream>
#include "Packer.h"
#include <ctime>

int main(){
	Point<float> P1( 1.0f, 0.0f );
	Point<float> P2( 0.3f, 3.0f );
	Point<float> P3( 3.0f, 3.7f );
	Point<float> P4( 2.1f, 0.0f );
	std::vector<Point<float>> vec {P1,P2,P3,P4};
	std::vector<Item> items;
	for ( int i = 0; i < 400; i++ )
	{
		items.push_back( Item( i, vec, 1 ) );
	}
	Packer packer( 1000,1000, 1, items);
	unsigned int start_time = clock();
	packer.pack();
	unsigned int end_time = clock();
	std::cout << end_time-start_time;
	int a;
	std::cin >> a;
}