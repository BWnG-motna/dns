#pragma once


#include "Common.h"
#include "Node.h"


namespace daniel
{
	
namespace ds
{


template < typename T >
class LinkedList
{

private :
	Node< T > * pHead ;
	Node< T > * pTail ;

private :
	void Dbg() const ;

public :
	bool Insert( T const * pDat ) noexcept ;

public :
	 LinkedList() ;
	~LinkedList() ;

} ; // class LinkedList
	

}   // namespace ds

}   // namespace daniel