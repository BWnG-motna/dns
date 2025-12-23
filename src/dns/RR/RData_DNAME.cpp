#include "dns/RR/RData_DNAME.h"


#include <cstring>


daniel::dns::RR::RData_DNAME::RData_DNAME( uint8_t const * pRef )
	: RData( pRef )
{
	dname[ 0 ] = '\0' ;
}


uint16_t daniel::dns::RR::RData_DNAME::ToNullStr( uint8_t * pStr , uint16_t const & length ) const
{
	if( nullptr == pStr || 1 > length )
	{
		return 0 ;
	}

	uint16_t len = static_cast< uint16_t >( strlen( reinterpret_cast< char const * >( dname ) ) ) ;

	for( uint16_t pos = 0 ; pos < len && pos < length ; ++pos )
	{
		pStr[ pos ] = dname[ pos ] ;
	}

	uint16_t less = len < ( length - 1 ) ? len : ( length - 1 ) ;
	pStr[ less ] = '\0' ;

	return less ;
}


bool daniel::dns::RR::RData_DNAME::Load( uint8_t const * pData , uint16_t const & length )
{
	if( nullptr == pData || 1 > length )
	{
		return false ;
	}

	uint16_t len = GetDNData( dname , sizeof( dname ) , pData ) ;
	if( 1 > len )
	{
		return false ;
	}

	return true ;
}


uint8_t const * daniel::dns::RR::RData_DNAME::GetDName() const
{
	return dname ;
}