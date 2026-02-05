#include "ds/Node.h"

#include "dns/EDNS0/EDNS0_OPTION.h"
#include "dns/RR/SVC/SvcParam.h"
#include "dns/RR/SEC/TypeBitMap.h"


template < typename T >
daniel::ds::Node< T >::Node()
	: pData( nullptr ) , pPrev( nullptr ) , pNext( nullptr )
{

}


template < typename T >
daniel::ds::Node< T >::Node( T * pDat )
{
	pData = pDat ;
}


template < typename T >
daniel::ds::Node< T >::~Node()
{
	delete pData ;

	pData = nullptr ;
	pPrev = nullptr ;
	pNext = nullptr ;
}


template < typename T >
T * daniel::ds::Node< T >::GetData() const
{
	return pData ;
}


template < typename T >
daniel::ds::Node< T > * daniel::ds::Node< T >::GetPrev() const
{
	return pPrev ;
}


template < typename T >
daniel::ds::Node< T > * daniel::ds::Node< T >::GetNext() const
{
	return pNext ;
}


template < typename T >
void daniel::ds::Node< T >::SetData( T * pDat )
{
	pData = pDat ;
}


template < typename T >
void daniel::ds::Node< T >::SetPrev( Node * pNode )
{
	pPrev = pNode ;
}


template < typename T >
void daniel::ds::Node< T >::SetNext( Node * pNode )
{
	pNext = pNode ;
}


template class daniel::ds::Node< uint16_t > ;
template class daniel::ds::Node< daniel::dns::EDNS0_OPTION > ;
template class daniel::ds::Node< daniel::dns::RR::SVC::SvcParam > ;
template class daniel::ds::Node< daniel::dns::RR::SEC::TypeBitMap > ;