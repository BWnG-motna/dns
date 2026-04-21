#include "dns/RR/RData_L32.h"


#include <sstream>


daniel::dns::RR::RData_L32::RData_L32()
	: RData( nullptr ) , locator( 0 )
{

}


daniel::dns::RR::RData_L32::~RData_L32()
{
	Initialize() ;
}


void daniel::dns::RR::RData_L32::Initialize()
{
	locator = 0 ;
}


uint16_t daniel::dns::RR::RData_L32::ToNullStr( uint8_t * pStr , uint16_t const & length ) const
{
	if( nullptr == pStr || 1 > length )
	{
		return 0 ;
	}

	
	std::stringstream ss ;

	ss << static_cast< uint16_t >( ( locator >> 24 ) & 0x000000FF ) << "."
	   << static_cast< uint16_t >( ( locator >> 16 ) & 0x000000FF ) << "."
	   << static_cast< uint16_t >( ( locator >>  8 ) & 0x000000FF ) << "."
	   << static_cast< uint16_t >( ( locator >>  0 ) & 0x000000FF ) ;

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


bool daniel::dns::RR::RData_L32::Load( uint8_t const * pData , uint16_t const & length )
{
	if( nullptr == pData || 1 > length )
	{
		return false ;
	}
	
	if( 4 != length )
	{
		return false ;
	}

	locator = ( ( pData[ 0 ] << 24 ) & 0xFF000000 )
			| ( ( pData[ 1 ] << 16 ) & 0x00FF0000 )
			| ( ( pData[ 2 ] <<  8 ) & 0x0000FF00 )
			| ( ( pData[ 3 ] <<  0 ) & 0x000000FF ) ;

	return true ;
}


uint32_t daniel::dns::RR::RData_L32::GetLocator() const
{
	return locator ;
}