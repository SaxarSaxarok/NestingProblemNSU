#include<vector>
#include "Point.h"
#include "Polygon.h"

int main(){
	Point<float> P1(1, 0);
	Point<float> P2(0.3, 3);
	Point<float> P3(3, 3.7);
	Point<float> P4(2.1, 0);
	std::vector<Point<float>> vec {P1,P2,P3,P4};
	Polygon polygon( vec );

	std::vector<std::vector<int>> matrix = polygon.getMatrixRepresentation( 2.6 );
}