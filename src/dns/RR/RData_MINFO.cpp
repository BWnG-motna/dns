#include "dns/RR/RData_MINFO.h"


#include <cstring>


daniel::dns::RR::RData_MINFO::RData_MINFO( uint8_t const * pRef )
	: RData( pRef )
{
	rmailbx[ 0 ] = '\0' ;
	emailbx[ 0 ] = '\0' ;
}


uint16_t daniel::dns::RR::RData_MINFO::ToNullStr( uint8_t * pStr , uint16_t const & length ) const
{
	if( nullptr == pStr || 1 > length )
	{
		return 0 ;
	}

	uint16_t rmbxlen = static_cast< uint16_t >( strlen( reinterpret_cast< char const * >( rmailbx ) ) ) ;
	uint16_t embxlen = static_cast< uint16_t >( strlen( reinterpret_cast< char const * >( emailbx ) ) ) ;

	uint16_t len = rmbxlen + embxlen + 1 ;

	if( length <= len )
	{
		return 0 ;
	}

	uint16_t pos = 0 ;
	for( uint16_t bPos = 0 ; bPos < rmbxlen ; ++bPos )
	{
		pStr[ pos++ ] = rmailbx[ bPos ] ;
	}

	pStr[ pos++ ] = ' ' ;

	for( uint16_t bPos = 0 ; bPos < embxlen ; ++bPos )
	{
		pStr[ pos++ ] = emailbx[ bPos ] ;
	}

	pStr[ pos ] = '\0' ;

	return pos ;
}


bool daniel::dns::RR::RData_MINFO::Load( uint8_t const * pData , uint16_t const & length )
{
	if( nullptr == pData || 1 > length )
	{
		return false ;
	}

	uint16_t len[ 3 ] = { 0 , 0 , 0 } ;

	len[ 0 ] = SkipDName( pData , length ) ; 

	len[ 1 ] = GetDNData( rmailbx , sizeof( rmailbx ) , & pData[        0 ] ) ;
	len[ 2 ] = GetDNData( emailbx , sizeof( emailbx ) , & pData[ len[ 0 ] ] ) ;

	if( 1 > len[ 1 ] || 1 > len[ 2 ] )
	{
		return false ;
	}

	return true ;
}