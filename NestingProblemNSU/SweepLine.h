#pragma once
#include <set>
#include<algorithm>
#include "Point.h"
#include "AvlTree.h"
#include "Segment.h"

class EventQeue: public AvlTree<Point<double>, std::set<Segment>>{ //maybe not set ? (upper segments)

	void insertEventBySegment( const Segment& segment ); //Maybe not 
	void insertEventByIntersection( const Point<double>& point, const Segment& segment1, const Segment& segment2 );

};


class StatusKey: public Segment{
public:
	Point<double>* comparisonPoint;

private:
	bool operator == ( const StatusKey& other );
	bool operator != ( const StatusKey& other );
	bool operator <  ( const StatusKey& other );
	bool operator >  ( const StatusKey& other );
};

template <class StatusValue>
class Status: public AvlTree<StatusKey, StatusValue>{
	Point<double>* comparisonPoint;

	std::set<Segment> getLowersInners(){ //TODO
		return std::set<Segment>();
	}
};


template <class StatusValue, class Handler>
class SweepLine{
	using Event = EventQeue::node*; //Так использовать ?


	Status<StatusValue> status = Status<StatusValue>();
	EventQeue eventQeue = EventQeue();
	Handler handler = Handler();

	SweepLine( const std::vector<Segment >> segments& ){

		for ( auto& segment : segments )
		{
			this->eventQeue.insertEventBySegment( segment );
		}
	}

	void build(){
		while ( this->eventQeue.root->key != nullptr )
		{
			auto aEvent = this->eventQeue.maxNode();
			this->status.comparisonPoint = &aEvent->key;
			this->handle( aEvent );
			this->status.remove( aEvent->key ); // Неоптимальное удаление
		}
	}

	void handle( Event aEvent ){ //Поработать над обращением к памяти

		std::set<Segment> segments = this->status.getLowersInners(); //maybe not set ??

		std::set<Segment> lowers;
		std::set<Segment> inners;
		std::set<Segment> uppers = aEvent->value;

		std::copy_if( segments.begin(), segments.end(), std::inserter( lowers, lowers.end() ), [aEvent]( const Segment& seg ){seg.minPoint == aEvent->key} ); //filter
		std::copy_if( segments.begin(), segments.end(), std::inserter( inners, inners.end() ), [aEvent]( const Segment& seg ){seg.minPoint != aEvent->key && seg.maxPoint != aEvent->key} ); //filter

		if ( lowers.size() + inners.size() + uppers.size() > 1 )
		{
			//intersection found
		}
		this->removeLowers();
		this->reverseInners();
		this->inserUppers();

		if ( uppers.size() + inners.size() == 0 ) this->handleOnlyLowersCase( aEvent );
		else this->handleUppersInnersCase( aEvent );

	}
	/*void handleIntersectionCase( Event event );
	void removeLowers( Event event );
	void reverseInners( Event event );
	void insertUppers( Event event );
	void handleOnlyLowersCase( Event event );
	void handleUppersInnersCase( Event event );
	void findNewEvent( Event event, const Segment& segment1, const Segment& segment2 );*/

};

