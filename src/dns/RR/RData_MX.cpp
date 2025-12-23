#include "dns/RR/RData_MX.h"


#include <sstream>


daniel::dns::RR::RData_MX::RData_MX( uint8_t const * pRef )
	: RData( pRef ) , preference( 0 )
{
	exchange[ 0 ] = '\0' ; 
}


uint16_t daniel::dns::RR::RData_MX::ToNullStr( uint8_t * pStr , uint16_t const & length ) const
{
	std::stringstream ss ;

	ss << static_cast< uint16_t >( preference ) << " " << exchange ;

	std::string str = ss.str() ;
	uint16_t len = static_cast< uint16_t >( str.length() ) ;

	for( uint16_t pos = 0 ; pos < length && pos < len ; ++pos ) 
	{
		pStr[ pos ] = str[ pos ] ;
	}

	uint16_t less = len < ( length - 1 ) ? len : ( length - 1 ) ;
	pStr[ less ] = '\0' ;

	return less ;
}


bool daniel::dns::RR::RData_MX::Load( uint8_t const * pData , uint16_t const & length )
{
	if( nullptr == pData || 1 > length )
	{
		return false ;
	}
	
	if( 2 > length )
	{
		return false ;
	}


	preference
		= ( ( pData[ 0 ] << 8 ) & 0xFF00 )
		| ( ( pData[ 1 ] << 0 ) & 0x00FF ) ;

	uint16_t len = GetDNData( exchange , sizeof( exchange ) , & ( pData[ 2 ] ) ) ;
	if( 1 > len )
	{
		return false ;
	}

	return true ;
}


uint16_t daniel::dns::RR::RData_MX::GetPreference() const
{
	return preference ;
}


uint8_t const * daniel::dns::RR::RData_MX::GetExchange() const
{
	return exchange ;
}