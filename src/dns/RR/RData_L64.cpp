#include "dns/RR/RData_L64.h"


#include <sstream>
#include <iomanip>


daniel::dns::RR::RData_L64::RData_L64()
	: RData( nullptr ) , locator( 0 )
{

}


daniel::dns::RR::RData_L64::~RData_L64()
{
	Initialize() ;
}


void daniel::dns::RR::RData_L64::Initialize()
{
	locator = 0 ;
}


uint16_t daniel::dns::RR::RData_L64::ToNullStr( uint8_t * pStr , uint16_t const & length ) const
{
	if( nullptr == pStr || 1 > length )
	{
		return 0 ;
	}

	
	std::stringstream ss ;

	for( int8_t pos = 3 ; pos >= 0 ; --pos )
	{
		uint16_t val = static_cast< uint16_t >( locator >> ( pos * 16 ) ) ;

		if( 3 != pos )
		{
			ss << ":" ;
		}
		ss << std::hex << std::setw( 4 ) << std::setfill( '0' ) << val ;
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


bool daniel::dns::RR::RData_L64::Load( uint8_t const * pData , uint16_t const & length )
{
	if( nullptr == pData || 1 > length )
	{
		return false ;
	}
	
	if( 8 != length )
	{
		return false ;
	}

	locator = ( ( static_cast< uint64_t >( pData[ 0 ] ) << 56 ) & 0xFF00000000000000 )
		    | ( ( static_cast< uint64_t >( pData[ 1 ] ) << 48 ) & 0x00FF000000000000 )
		    | ( ( static_cast< uint64_t >( pData[ 2 ] ) << 40 ) & 0x0000FF0000000000 )
		    | ( ( static_cast< uint64_t >( pData[ 3 ] ) << 32 ) & 0x000000FF00000000 )
	        | ( ( static_cast< uint64_t >( pData[ 4 ] ) << 24 ) & 0x00000000FF000000 )
		    | ( ( static_cast< uint64_t >( pData[ 5 ] ) << 16 ) & 0x0000000000FF0000 )
		    | ( ( static_cast< uint64_t >( pData[ 6 ] ) <<  8 ) & 0x000000000000FF00 )
		    | ( ( static_cast< uint64_t >( pData[ 7 ] ) <<  0 ) & 0x00000000000000FF ) ;

	return true ;
}


uint32_t daniel::dns::RR::RData_L64::GetLocator() const
{
	return locator ;
}