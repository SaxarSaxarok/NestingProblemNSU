#include "SweepLine.h"

bool StatusKey::operator==( const StatusKey& other ){
    return this->minPoint == other.minPoint && this->maxPoint == other.maxPoint;
}

bool StatusKey::operator!=( const StatusKey& other ){
    return !( ( *this ) == other );
}

bool StatusKey::operator<( const StatusKey& other ){
    return ( *this ) != other && true;
}

bool StatusKey::operator>( const StatusKey& other ){
    return ( *this ) != other && true;
}
