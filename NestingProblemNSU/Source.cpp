#include<vector>
#include "Point.h"
#include "Polygon.h"
#include "Item.h"
#include <iostream>

int main(){
	Point<float> P1( 1.0f, 0.0f );
	Point<float> P2( 0.3f, 3.0f );
	Point<float> P3( 3.0f, 3.7f );
	Point<float> P4( 2.1f, 0.0f );
	std::vector<Point<float>> vec {P1,P2,P3,P4};
	Polygon polygon( vec );

	float area = polygon.area();
	auto point = polygon.barycenter();
	polygon.shiftToOrigin();
	point = polygon.barycenter();
	Item item = Item( polygon, 2.6 );
}