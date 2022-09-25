#include<vector>
#include "Point.h"
#include "Polygon.h"
#include "Item.h"
#include <iostream>
#include "Packer.h"

int main(){
	Point<float> P1( 1.0f, 0.0f );
	Point<float> P2( 0.3f, 3.0f );
	Point<float> P3( 3.0f, 3.7f );
	Point<float> P4( 2.1f, 0.0f );
	std::vector<Point<float>> vec {P1,P2,P3,P4};
	Polygon polygon( vec );
	Item item1( 1, vec, 2.6 );
	Item item2( 2, vec, 2.6 );
	Item item3( 3, vec, 2.6 );
	Packer packer( 10,10,2.6,std::vector<Item>{item1,item2,item3} );
	packer.pack();
}