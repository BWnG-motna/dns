#include "ds/LinkedList.h"

#include "dns/EDNS0/EDNS0_OPTION.h"


#include <memory>
#include <iostream>
#include <iomanip>


template < typename T >
daniel::ds::LinkedList< T >::LinkedList()
	: pHead( nullptr ) , pTail( nullptr )
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
}


template < typename T >
bool daniel::ds::LinkedList< T >::Insert( T const * pDat ) noexcept
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

	Dbg() ;

	return true ;
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


template class daniel::ds::LinkedList< int > ;
template class daniel::ds::LinkedList< daniel::dns::EDNS0_OPTION > ;