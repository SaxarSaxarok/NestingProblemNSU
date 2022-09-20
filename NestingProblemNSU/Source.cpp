#include "MatrixRepresentation.h"
#include <iostream>

int main(){
	Point<float> P1(1, 0);
	Point<float> P2(0.3, 3);
	Point<float> P3(3, 3.7);
	Point<float> P4(2.1, 0);
	std::vector<Point<float>> vec {P1,P2,P3,P4};
	Polygon polygon( vec );

	MatrixRepresentation matrix( vec, 2.6 );
}