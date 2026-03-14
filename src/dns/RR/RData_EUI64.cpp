#include "dns/RR/RData_EUI64.h"


#include <sstream>
#include <iomanip>


daniel::dns::RR::RData_EUI64::RData_EUI64()
	: RData( nullptr )
{
	Initialize() ;
}


daniel::dns::RR::RData_EUI64::~RData_EUI64()
{
	Initialize() ;
}


void daniel::dns::RR::RData_EUI64::Initialize()
{
	for( uint8_t pos = 0 ; pos < addrMaxLen ; ++pos )
	{
		address[ pos ] = 0 ;
	}
}


uint16_t daniel::dns::RR::RData_EUI64::ToNullStr( uint8_t * pStr , uint16_t const & length ) const
{
	if( nullptr == pStr || 1 > length )
	{
		return 0 ;
	}

	
	std::stringstream ss ;

	for( uint8_t pos = 0 ; pos < addrMaxLen ; ++pos )
	{
		if( 0 != pos )
		{
			ss << "-" ;
		}

		ss << std::hex << std::setw( 2 ) << std::setfill( '0' ) << static_cast< uint16_t >( address[ pos ] ) ;
	}

	ss << std::dec << std::setw( 0 ) ;

	std::string s = ss.str() ;
	uint16_t len  = static_cast< uint16_t >( s.length() ) ;

	for( uint16_t pos = 0 ; pos < length && pos < len ; ++pos )
	{
		pStr[ pos ] = s[ pos ] ;
	}

	uint16_t less = len < ( length - 1 ) ? len : ( length - 1 ) ;
	pStr[ less ] = '\0' ;

	return less ;
}


bool daniel::dns::RR::RData_EUI64::Load( uint8_t const * pData , uint16_t const & length )
{
	if( nullptr == pData || 1 > length )
	{
		return false ;
	}
	
	if( addrMaxLen != length )
	{
		return false ;
	}

	Initialize() ;

	for( uint8_t pos = 0 ; pos < addrMaxLen ; ++pos )
	{
		address[ pos ] = pData[ pos ] ;
	}

	return true ;
}


void daniel::dns::RR::RData_EUI64::GetAddress( uint8_t ( & addr )[ addrMaxLen ] )
{
	for( uint8_t pos = 0 ; pos < addrMaxLen ; ++pos )
	{
		addr[ pos ] = address[ pos ] ;
	}
}