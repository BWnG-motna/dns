#pragma once


#include "Common.h"
#include "Node.h"

#include <iterator>
#include <utility>
#include <type_traits>

namespace daniel
{
	
namespace ds
{


template < typename NodeType >
class LinkedListIterator
{
	
private :
	NodeType * pCurr ;

	template < typename _NodeType >
	friend class LinkedListIterator ;

public :
	using iterator_category = std::bidirectional_iterator_tag ;
	using value_type        = std::remove_pointer_t< decltype( std::declval< NodeType >().GetData() ) > ;
	using difference_type   = std::ptrdiff_t ;
	using pointer           = std::add_pointer_t< value_type > ;
	using reference         = std::add_lvalue_reference_t< value_type > ;

public :	
	reference operator*()  const ;
	pointer   operator->() const ;

	LinkedListIterator & operator++() ;
	LinkedListIterator   operator++( int ) ;
	LinkedListIterator & operator--() ;
	LinkedListIterator   operator--( int ) ;

	bool operator==( LinkedListIterator const & o ) const ;
	bool operator!=( LinkedListIterator const & o ) const ;

public :
	explicit LinkedListIterator( NodeType * p = nullptr ) ;
	         LinkedListIterator( LinkedListIterator< std::remove_const_t< NodeType > > const & rhs ) ;



} ; // class LinkedListIterator


}   // namespace ds

}   // namespace daniel