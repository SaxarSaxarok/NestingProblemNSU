#pragma once

#include <vector>
#include <string>

#include "Point.h"
#include "Segment.h"
#include "AvlTree.h"
#include "SweepLine.h"

class Arrangement;
class HalfEdge;
class Vertex;
class Face;

class BuildHandler{
private:
	Arrangement* arrangement;

	void operator ()();//Переменные
};

class Vertex{
private:
	std::vector<HalfEdge*> halfEdgesByCcwAngle; //maybe need a list, not a vector
	HalfEdge* rightHalfEdge = nullptr;

	void addHalfEdge( HalfEdge* halfEdge);
};

class HalfEdge{
	Segment originalSegment;
	Point<float> origin;
	Point<float> end;
	HalfEdge* twin = nullptr;
	HalfEdge* prev = nullptr;
	HalfEdge* next = nullptr;
	Face* face = nullptr;
	Vertex* vertex = nullptr;
public:

	static std::pair<HalfEdge, HalfEdge> createPairHalfEdges(const Segment& segment);
};

class Face{
	HalfEdge* boundaryHalfEdge;
	std::vector<HalfEdge*> holesHalfEdges;
	std::string label;
	bool isHole;
	
	//More...
	public:
	Face();
};


class Arrangement{
private:
	Face* unboundedFace = new Face();
	std::vector<Face*> faces;
	std::vector<HalfEdge*> halfEdges;
	AvlTree<Point<float>,Vertex> verticies;
	SweepLine<int,BuildHandler> builder; //Исправить

	Arrangement();
	Arrangement( const std::vector<Segment>& segments);


	void initFaces();
	
	static Arrangement subdivision( const Arrangement& that, const Arrangement& other );
	static Arrangement setUnion( const Arrangement& that, const Arrangement& other );
	static Arrangement setDifference( const Arrangement& that, const Arrangement& other );
	static Arrangement setIntersection( const Arrangement& that, const Arrangement& other );

};

