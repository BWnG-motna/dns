#include "ds/LinkedList.h"

#include "dns/EDNS0/EDNS0_OPTION.h"
#include "dns/RR/SVC/SvcParam.h"
#include "dns/RR/SEC/TypeBitMap.h"

#include <memory>
#include <iostream>
#include <iomanip>


#define DEBUG_OR_TEST ( 0 )


template < typename T >
daniel::ds::LinkedList< T >::LinkedList()
	: pHead( nullptr ) , pTail( nullptr ) , nodeCount( 0 )
{

}


template < typename T >
daniel::ds::LinkedList< T >::~LinkedList()
{
	if( nullptr == pHead )
	{
		pHead = nullptr ;
		pTail = nullptr ;
		return ;
	}

	Node< T > * pNode = pHead ;
	while( nullptr != pNode )
	{
		Node< T > * pCurr = pNode ;

		pNode = pNode->GetNext() ;
		pHead = pNode ;

		if( nullptr != pNode )
		{
			pNode->SetPrev( nullptr ) ;
		}
		
		delete pCurr ;
	}

	pTail = nullptr ;

	nodeCount = 0 ;
}


template < typename T >
bool daniel::ds::LinkedList< T >::Insert( T * pDat ) noexcept
{
	Node< T > * pNode = new ( std::nothrow ) Node< T >() ;
	if( nullptr == pNode )
	{
		return false ;
	}

	pNode->SetData( pDat ) ; 

	if( nullptr == pHead )
	{
		pHead = pNode ;
		pTail = pNode ;
	}
	else
	{
		pNode->SetPrev( pTail ) ;
		pTail->SetNext( pNode ) ;
		pTail = pNode ;
	}

#if ( DEBUG_OR_TEST )

	Dbg() ;

#endif

	++nodeCount ;

	return true ;
}


template < typename T >
uint32_t daniel::ds::LinkedList< T >::GetCount() const
{
	return nodeCount ;
}


template < typename T >
typename daniel::ds::LinkedList< T >::iterator daniel::ds::LinkedList< T >::begin()
{
	return iterator( pHead ) ;
}


template < typename T >
typename daniel::ds::LinkedList< T >::iterator daniel::ds::LinkedList< T >::end()
{
	return iterator( nullptr ) ;
}


template < typename T >
typename daniel::ds::LinkedList< T >::reverse_iterator daniel::ds::LinkedList< T >::rbegin()
{
	return reverse_iterator( end() ) ;
}


template < typename T >
typename daniel::ds::LinkedList< T >::reverse_iterator daniel::ds::LinkedList< T >::rend()
{
	return reverse_iterator( begin() ) ;
}


template < typename T >
typename daniel::ds::LinkedList< T >::const_iterator daniel::ds::LinkedList< T >::begin() const
{
	return const_iterator( const_cast< Node< T > * >( pHead ) ) ;
}


template < typename T >
typename daniel::ds::LinkedList< T >::const_iterator daniel::ds::LinkedList< T >::end() const
{
	return const_iterator( nullptr ) ;
}



template < typename T >
typename daniel::ds::LinkedList< T >::const_reverse_iterator daniel::ds::LinkedList< T >::rbegin() const
{
	return const_reverse_iterator( end() ) ;
}


template < typename T >
typename daniel::ds::LinkedList< T >::const_reverse_iterator daniel::ds::LinkedList< T >::rend() const
{
	return const_reverse_iterator( begin() ) ;
}


template < typename T >
typename daniel::ds::LinkedList< T >::const_iterator daniel::ds::LinkedList< T >::cbegin() const
{
	return const_iterator( const_cast< Node< T > * >( pHead ) ) ;
}


template < typename T >
typename daniel::ds::LinkedList< T >::const_iterator daniel::ds::LinkedList< T >::cend() const
{
	return const_iterator( nullptr ) ;
}


template < typename T >
typename daniel::ds::LinkedList< T >::const_reverse_iterator daniel::ds::LinkedList< T >::crbegin() const
{
	return const_reverse_iterator( end() ) ;
}


template < typename T >
typename daniel::ds::LinkedList< T >::const_reverse_iterator daniel::ds::LinkedList< T >::crend() const
{
	return const_reverse_iterator( begin() ) ;
}



template < typename T >
void daniel::ds::LinkedList< T >::Dbg() const
{
	std::cout << "+++++++++++++++++++++++++" << std::endl ;
	std::cout << "pHead: 0x" << std::hex << std::setw( 16 ) << std::setfill( '0' ) << reinterpret_cast< uintptr_t >( pHead ) << std::endl ;
	std::cout << "pTail: 0x" << std::hex << std::setw( 16 ) << std::setfill( '0' ) << reinterpret_cast< uintptr_t >( pTail ) << std::endl ;
	std::cout << "-------------------------" << std::endl ;

	Node< T > * pNode = pHead ;
	while( nullptr != pNode )
	{
		std::cout << "pPrev: 0x" << std::hex << std::setw( 16 ) << std::setfill( '0' ) << reinterpret_cast< uintptr_t >( pNode->GetPrev() ) << std::endl ;
		std::cout << "pNode: 0x" << std::hex << std::setw( 16 ) << std::setfill( '0' ) << reinterpret_cast< uintptr_t >( pNode            ) << std::endl ;
		std::cout << "pNext: 0x" << std::hex << std::setw( 16 ) << std::setfill( '0' ) << reinterpret_cast< uintptr_t >( pNode->GetNext() ) << std::endl ;
		std::cout << std::endl ;

		pNode = pNode->GetNext() ;
	}
}


template class daniel::ds::LinkedList< uint16_t > ;
template class daniel::ds::LinkedList< daniel::dns::EDNS0_OPTION > ;
template class daniel::ds::LinkedList< daniel::dns::RR::SVC::SvcParam > ;
template class daniel::ds::LinkedList< daniel::dns::RR::SEC::TypeBitMap > ;