#include "dns/RR/RData_NSEC.h"
#include "dns/QType.h"
#include "baseEncoding/Base32Hex.h"


#include <sstream>
#include <iomanip>
#include <memory>


daniel::dns::RR::RData_NSEC::RData_NSEC()
	: RData( nullptr ) , pNextDName( nullptr ) , pTbm( nullptr ) , nextDNameLen( 0 ) , pTypes( nullptr )
{

}


daniel::dns::RR::RData_NSEC::~RData_NSEC()
{
	Initalize() ;
}


void daniel::dns::RR::RData_NSEC::Initalize()
{
	if( nullptr != pTbm )
	{
		delete pTbm ;
		pTbm = nullptr ;
	}

	if( nullptr != pNextDName )
	{
		delete [] pNextDName ;
		pNextDName = nullptr ;
	}

	if( nullptr != pTypes )
	{
		delete [] pTypes ;
		pTypes = nullptr ;
	}

	nextDNameLen = 0 ;
}


uint16_t daniel::dns::RR::RData_NSEC::ToNullStr( uint8_t * pStr , uint16_t const & length ) const
{
	if( nullptr == pStr || 1 > length )
	{
		return 0 ;
	}

	if( nullptr == pNextDName )
	{
		return 0 ;
	}


	std::stringstream ss ;

	/* next owner name */
	ss << pNextDName ;
	
	/* types */
	uint16_t typeCount = GetTypeCount() ;
	uint16_t const * types = GetTypes() ;

	ss << " (" ;

	for( uint16_t pos = 0 ; pos < typeCount ; ++pos )
	{
		ss << " " << ToString( enumFromUint16< dns::QType >( types[ pos ] ) ) ;
	}

	ss << " )" ;

	/* output */
	std::string str = ss.str() ;
	uint16_t len = static_cast< uint16_t >( str.length() ) ;
	
	for( uint16_t pos = 0 ; pos < len && pos < length ; ++pos )
	{
		pStr[ pos ] = str[ pos ] ;
	}

	uint16_t less = len < ( length - 1 ) ? len : ( length - 1 ) ;
	pStr[ less ] = '\0' ;

	return less  ;
}


bool daniel::dns::RR::RData_NSEC::Load( uint8_t const * pData , uint16_t const & length )
{
	if( nullptr == pData || 1 > length )
	{
		return false ;
	}


	uint16_t dlen = GetDNDataLen( pData ) ;
	if( 1 > dlen )
	{
		return false ;
	}


	Initalize() ;

	pNextDName = new ( std::nothrow ) uint8_t [ dlen + 1 ] ;
	if( nullptr == pNextDName )
	{
		Initalize() ;
		return false ;
	}

	nextDNameLen = GetDNData( pNextDName , dlen + 1 , pData ) ;
	uint16_t len = SkipDName( pData , length ) ; 

	uint16_t pos = len ;
	while( ( pos + 2 ) <= length  )
	{
		uint8_t window   = pData[ pos++ ] ;
		uint8_t blockLen = pData[ pos++ ] ;

		if( 32 < blockLen || ( pos + blockLen ) > length )
		{
			Initalize() ;
			return false ;
		}

		for( uint8_t arrPos = 0 ; arrPos < blockLen ; ++arrPos )
		{
			for( uint8_t bitPos = 0 ; bitPos < 8 ; ++bitPos )
			{
				if( 0 < ( pData[ pos + arrPos ] & ( 0x01U << bitPos ) ) )
				{
					uint16_t type = ( window * 256 ) + ( arrPos * 8 ) + bitPos ;
					bool is = SetType( window , type ) ;
					if( false == is )
					{
						Initalize() ;
						return is ;
					}
				}
			} 
		}

		pos += blockLen ;

	}

	return true ;
}


bool daniel::dns::RR::RData_NSEC::SetType( uint8_t const & window , uint8_t const & type )
{
	if( nullptr == pTbm )
	{
		pTbm = new ( std::nothrow ) ds::LinkedList< SEC::TypeBitMap >() ;
		if( nullptr == pTbm )
		{

			return false ;
		}
	}

	ds::LinkedList< SEC::TypeBitMap >::iterator posIter = pTbm->begin() ;
	ds::LinkedList< SEC::TypeBitMap >::iterator endIter = pTbm->end() ;

	while( posIter != endIter )
	{
		SEC::TypeBitMap const & tbm = *posIter ;
		if( true == tbm.IsSet() && window == tbm.GetNo() )
		{
			break ;
		} 

		++posIter ;
	}

	if( posIter != endIter )
	{
		( *posIter ).SetBit( type ) ;
		return true ;
	}

	SEC::TypeBitMap * p = new ( std::nothrow ) SEC::TypeBitMap() ;
	if( nullptr == p )
	{
		return false ;
	}

	p->SetBit( type ) ;

	pTbm->Insert( p ) ;

	return true ;
}


uint8_t daniel::dns::RR::RData_NSEC::GetNextDNameLength() const 
{
	return nextDNameLen ;
}


uint16_t daniel::dns::RR::RData_NSEC::GetTypeCount() const
{
	if( nullptr == pTbm )
	{
		return 0 ;
	}

	ds::LinkedList< SEC::TypeBitMap >::const_iterator posIter = pTbm->begin() ;
	ds::LinkedList< SEC::TypeBitMap >::const_iterator endIter = pTbm->end() ;


	uint16_t typeCount = 0;

	while( posIter != endIter )
	{
		SEC::TypeBitMap const & p = *posIter ;

		if( true == p.IsSet() )
		{
			typeCount += p.GetSetCount() ;
		}

		++posIter ;
	}

	return typeCount ;
}


uint8_t const * daniel::dns::RR::RData_NSEC::GetNextDName() const 
{
	return pNextDName ;
}


uint16_t const * daniel::dns::RR::RData_NSEC::GetTypes() const 
{
	uint16_t typeCount = GetTypeCount() ;
	if( 1 > typeCount )
	{
		return nullptr ;
	}

	ds::LinkedList< SEC::TypeBitMap >::const_iterator posIter = pTbm->begin() ;
	ds::LinkedList< SEC::TypeBitMap >::const_iterator endIter = pTbm->end() ;

	if( nullptr != pTypes )
	{
		delete [] pTypes ;
		pTypes = nullptr ;
	}

	pTypes = new ( std::nothrow ) uint16_t [ typeCount ] ;
	if( nullptr == pTypes )
	{
		return nullptr ;
	}

	uint16_t typePos = 0 ;
	while( posIter != endIter )
	{
		SEC::TypeBitMap const & tbm = *posIter ;

		if( true != tbm.IsSet() )
		{
			++posIter ;
			continue ; 
		}

		uint8_t  count = tbm.GetSetCount() ;
		uint16_t const * tArr = tbm.GetTypes() ;

		for( uint16_t tPos = 0 ; tPos < count ; ++tPos )
		{
			pTypes[ typePos++ ] = tArr[ tPos ] ;
		}

		++posIter ;
	}

	return pTypes ;
}