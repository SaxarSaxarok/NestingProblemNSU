#include<vector>
#include "Point.h"
#include "Polygon.h"
#include "Item.h"
#include <iostream>
#include "Packer.h"
#include <ctime>
#include <fstream>
#include <string>
#include <sstream>

std::istream& operator>>( std::istream& is, Point<double>& p ){
	is >> p.x;
	is >> p.y;
	return is;
}

int main(){

	std::ifstream file( "polygons400.txt", std::ios::in ); // открыли файл для чтения

	std::vector<Point<double>> vec;
	std::vector<Item> items;
	int i = 0;
	double h = 7.07;
	int n;
	std::string str;
	std::getline( file, str );
	std::istringstream ss( str );
	ss >> n;
	for ( int i = 0; i < n; i++ )
	{
		std::getline( file, str );
		std::istringstream ss( str );
		Point<double> p;
		while ( ss >> p )
		{
			vec.push_back( p );
		}
		vec.pop_back();
		items.push_back( Item( i, vec, h ) );
		vec.clear();
	}
	Packer packer( 2000, 2000, h, items );
	unsigned int start_time = clock();
	packer.pack();
	unsigned int end_time = clock();
	std::cout << end_time - start_time;

	i = 0;
	for (auto& pallet : packer.pallets )
	{
		std::ofstream outfile ("test"+std::to_string(i) +".txt");
		i++;
		outfile << pallet.items().size() << std::endl;
		for ( int j = 0; j < pallet.items().size(); j++ )
		{
			for ( int k = 0; k < pallet.items() [j].points_.size(); k++ )
			{
				outfile << pallet.items() [j].points_ [k].x << ' ' << pallet.items() [j].points_ [k].y << ' ';
			}
			outfile << std::endl;
		}
		outfile.close();
	}
}