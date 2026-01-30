#include "ds/LinkedListIterator.h"


#include "dns/EDNS0/EDNS0_OPTION.h"


template < typename NodeType >
daniel::ds::LinkedListIterator< NodeType >::LinkedListIterator( NodeType * p )
	: pCurr( p ) 
{

}


template < typename NodeType >
typename daniel::ds::LinkedListIterator< NodeType >::reference daniel::ds::LinkedListIterator< NodeType >::operator*() const
{
	return *( pCurr->GetData() ) ;
}


template < typename NodeType >
typename daniel::ds::LinkedListIterator< NodeType >::pointer daniel::ds::LinkedListIterator< NodeType >::operator->() const
{
	return pCurr->GetData() ;
}


template < typename NodeType >
daniel::ds::LinkedListIterator< NodeType > & daniel::ds::LinkedListIterator< NodeType >::operator++()
{
	if( nullptr != pCurr )
	{
		pCurr = pCurr->GetNext() ;
	}

	return * this ;
}


template < typename NodeType >
daniel::ds::LinkedListIterator< NodeType >   daniel::ds::LinkedListIterator< NodeType >::operator++( int )
{
	LinkedListIterator< NodeType > tmp = * this ;
	++( *this ) ;

	return tmp ;
}


template < typename NodeType >
daniel::ds::LinkedListIterator< NodeType > & daniel::ds::LinkedListIterator< NodeType >::operator--()
{
	if( nullptr != pCurr )
	{
		pCurr = pCurr->GetPrev() ;
	}

	return *this ;
}


template < typename NodeType >
daniel::ds::LinkedListIterator< NodeType >   daniel::ds::LinkedListIterator< NodeType >::operator--( int )
{
	LinkedListIterator< NodeType > tmp = * this ;
	--( *this ) ;

	return tmp ;
}


template < typename NodeType >
bool daniel::ds::LinkedListIterator< NodeType >::operator==( LinkedListIterator< NodeType > const & o ) const
{
	return ( pCurr == o.pCurr ) ? true : false ;
}


template < typename NodeType >
bool daniel::ds::LinkedListIterator< NodeType >::operator!=( LinkedListIterator< NodeType > const & o ) const
{
	return ( !( *this == o ) ) ? true : false ;
}


template class daniel::ds::LinkedListIterator< daniel::ds::Node< int > > ;
template class daniel::ds::LinkedListIterator< daniel::ds::Node< int > const > ;
template class daniel::ds::LinkedListIterator< daniel::ds::Node< daniel::dns::EDNS0_OPTION > > ;
template class daniel::ds::LinkedListIterator< daniel::ds::Node< daniel::dns::EDNS0_OPTION > const> ;