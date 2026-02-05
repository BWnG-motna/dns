#pragma once


#include "Common.h"
#include "Node.h"

#include "LinkedListIterator.h"


#include <iterator>


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
	using       iterator = LinkedListIterator< Node< T > > ;
	using const_iterator = LinkedListIterator< Node< T > const > ;

	using       reverse_iterator = std::reverse_iterator< iterator > ;
	using const_reverse_iterator = std::reverse_iterator< const_iterator > ;

	iterator begin() ;
	iterator end()   ;

	reverse_iterator rbegin() ;
	reverse_iterator rend()   ;

	const_iterator  begin() const ;
	const_iterator  end()   const ;
	const_iterator cbegin() const ;
	const_iterator cend()   const ;

	const_reverse_iterator  rbegin() const ;
	const_reverse_iterator  rend()   const ;
	const_reverse_iterator crbegin() const ;
	const_reverse_iterator crend()   const ;

public :
	bool Insert( T * pDat ) noexcept ;

public :
	uint32_t GetCount() const ;

public :
	 LinkedList() ;
	~LinkedList() ;

} ; // class LinkedList
	

}   // namespace ds

}   // namespace daniel