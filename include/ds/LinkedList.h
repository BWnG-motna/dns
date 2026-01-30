#pragma once


#include "Common.h"
#include "Node.h"

#include "LinkedListIterator.h"


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
	uint32_t nodeCount ;

private :
	void Dbg() const ;

public :
	using iterator       = LinkedListIterator< Node< T > > ;
	using const_iterator = LinkedListIterator< Node< T > > ;

	iterator begin() ;
	iterator end() ;

	const_iterator  begin() const ;
	const_iterator  end()   const ;
	const_iterator cbegin() const ;
	const_iterator cend()   const ;


public :
	bool Insert( T const * pDat ) noexcept ;

public :
	uint32_t GetCount() const ;

public :
	 LinkedList() ;
	~LinkedList() ;

} ; // class LinkedList
	

}   // namespace ds

}   // namespace daniel