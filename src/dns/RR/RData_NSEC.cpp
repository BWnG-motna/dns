#include "dns/RR/RData_NSEC.h"
#include "dns/QType.h"
#include "baseEncoding/Base32Hex.h"

#include <sstream>
#include <iomanip>
#include <iostream>


daniel::dns::RR::RData_NSEC::RData_NSEC()
	: RData( nullptr ) , nextDNameLen( 0 )
{
	for( uint8_t pos = 0 ; pos < 50 ; ++pos )
	{
		nextDName[ pos ] = 0 ;
	}
}


uint16_t daniel::dns::RR::RData_NSEC::ToNullStr( uint8_t * pStr , uint16_t const & length ) const
{
	std::stringstream ss ;

	/* next owner name */
	ss << nextDNameLen ;
	
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

	nextDNameLen = GetDNData( nextDName , sizeof( nextDName ) , pData ) ;
	uint16_t len = SkipDName( pData , length ) ; 

	uint16_t pos = len ;
	while( ( pos + 2 ) <= length  )
	{
		uint8_t window   = pData[ pos++ ] ;
		uint8_t blockLen = pData[ pos++ ] ;

		if( 32 < blockLen || ( pos + blockLen ) > length )
		{
			return false ;
		}

		for( uint8_t arrPos = 0 ; arrPos < blockLen ; ++arrPos )
		{
			for( uint8_t bitPos = 0 ; bitPos < 8 ; ++bitPos )
			{
				if( 0 < ( pData[ pos + arrPos ] & ( 0x01U << bitPos ) ) )
				{
					uint16_t type = ( window * 256 ) + ( arrPos * 8 ) + bitPos ;
					tbm[ window ].SetBit( type ) ;
				}
			} 
		}

		pos += blockLen ;

	}

	return true ;
}


uint8_t daniel::dns::RR::RData_NSEC::GetNextDNameLength() const 
{
	return nextDNameLen ;
}


uint16_t daniel::dns::RR::RData_NSEC::GetTypeCount() const
{
	uint16_t typeCount = 0 ;

	for( uint16_t pos = 0 ; pos < 256 ; ++pos )
	{
		if( true == tbm[ pos ].IsSet() )
		{
			typeCount += tbm[ pos ].GetSetCount() ;
		}
	}

	return typeCount ;
}


uint8_t const * daniel::dns::RR::RData_NSEC::GetNextDName() const 
{
	return nextDName ;
}


uint16_t const * daniel::dns::RR::RData_NSEC::GetTypes() const 
{
	uint16_t typesPos = 0 ;
	for( uint16_t pos = 0 ; pos < 256 ; ++pos )
	{
		if( true == tbm[ pos ].IsSet() )
		{
			uint8_t  count = tbm[ pos ].GetSetCount() ;
			uint16_t const * tArr = tbm[ pos ].GetTypes() ;

			for( uint16_t tPos = 0 ; tPos < count ; ++tPos )
			{
				if( 512 > typesPos )
				{
					types[ typesPos++ ] = tArr[ tPos ] ; 
				}
			}
		}
	}

	return types ;
}