#include "dns/RR/RData_NXT.h"
#include "dns/QType.h"

#include <sstream>
#include <iomanip>
#include <memory>


daniel::dns::RR::RData_NXT::RData_NXT()
	: RData( nullptr ) , pNextDName( nullptr ) , nextDNameLen( 0 ) , pTypes( nullptr )
{
	for( uint8_t pos = 0 ; pos < 16 ; ++pos )
	{
		pTbm[ pos ] = 0 ;
	}
}


daniel::dns::RR::RData_NXT::~RData_NXT()
{
	Initialize() ;
}


void daniel::dns::RR::RData_NXT::Initialize()
{
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

	for( uint8_t pos = 0 ; pos < 16 ; ++pos )
	{
		pTbm[ pos ] = 0 ;
	}

	nextDNameLen = 0 ;
}


uint16_t daniel::dns::RR::RData_NXT::ToNullStr( uint8_t * pStr , uint16_t const & length ) const
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
	ss << pNextDName << " " ;
	
	/* types */
	uint16_t typeCount = GetTypeCount() ;
	uint16_t const * types = GetTypes() ;

	for( uint16_t pos = 0 ; pos < typeCount ; ++pos )
	{
		ss << " " << ToString( enumFromUint16< dns::QType >( types[ pos ] ) ) ;
	}

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


bool daniel::dns::RR::RData_NXT::Load( uint8_t const * pData , uint16_t const & length )
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


	Initialize() ;

	pNextDName = new ( std::nothrow ) uint8_t [ dlen + 1 ] ;
	if( nullptr == pNextDName )
	{
		Initialize() ;
		return false ;
	}

	nextDNameLen = GetDNData( pNextDName , dlen + 1 , pData ) ;
	uint16_t len = SkipDName( pData , length ) ; 

	if( length <= len )
	{
		Initialize() ;
		return false ;
	}

	uint16_t bitSize = length - len ;

	for( uint16_t pos = 0 ; pos < bitSize ; ++pos )
	{
		pTbm[ pos ] = pData[ len + pos ] ;
	}

	for( uint16_t pos = bitSize ; pos < 16 ; ++pos )
	{
		pTbm[ pos ] = 0 ;
	}

	return true ;
}


uint8_t daniel::dns::RR::RData_NXT::GetNextDNameLength() const 
{
	return nextDNameLen ;
}


uint8_t daniel::dns::RR::RData_NXT::GetTypeCount() const
{
	uint8_t count = 0 ;

	for( uint8_t pos = 0 ; pos < 16 ; ++pos )
	{
		uint8_t dat = pTbm[ pos ] ;

		for( uint8_t bitPos = 0 ; bitPos < 8 ; ++bitPos )
		{
			if( 0 < ( dat & ( 0x1 << bitPos ) ) )
			{
				++count ;
			}
		} 
	}

	return count ;
}


uint8_t const * daniel::dns::RR::RData_NXT::GetNextDName() const 
{
	return pNextDName ;
}


uint16_t const * daniel::dns::RR::RData_NXT::GetTypes() const 
{
	if( nullptr != pTypes )
	{
		delete [] pTypes ;
		pTypes = nullptr ;
	}

	uint8_t count = GetTypeCount() ;
	if( 0 == count )
	{
		return pTypes ;
	}

	pTypes = new ( std::nothrow ) uint16_t[ count ] ;
	if( nullptr == pTypes )
	{
		return pTypes ;
	}

	uint8_t typePos = 0 ;
	for( uint8_t pos = 0 ; pos < 16 ; ++pos )
	{
		uint8_t dat = pTbm[ pos ] ;

		for( int8_t bitPos = 7 , bitVal = 0 ; bitPos >= 0 ; --bitPos , ++bitVal )
		{
			if( 0 < ( dat & ( 0x1 << bitPos ) ) )
			{
				pTypes[ typePos++ ] = 8 * pos + bitPos ; 
			}
		} 
	}

	return pTypes ;
}