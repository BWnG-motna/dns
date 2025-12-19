#include "dns/RR/RData_RP.h"


#include <cstring>


daniel::dns::RR::RData_RP::RData_RP( uint8_t const * pRef )
	: RData( pRef )
{
	mboxDName[ 0 ] = '\0' ;
	 txtDName[ 0 ] = '\0' ;
}


uint16_t daniel::dns::RR::RData_RP::ToNullStr( uint8_t * pStr , uint16_t const & length ) const
{
	if( nullptr == pStr || 1 > length )
	{
		return 0 ;
	}

	uint16_t mboxlen = static_cast< uint16_t >( strlen( reinterpret_cast< char const * >( mboxDName ) ) ) ;
	uint16_t  txtlen = static_cast< uint16_t >( strlen( reinterpret_cast< char const * >(  txtDName ) ) ) ;

	uint16_t len = mboxlen + txtlen + 1 ;

	if( length <= len )
	{
		return 0 ;
	}

	uint16_t pos = 0 ;
	for( uint16_t bPos = 0 ; bPos < mboxlen ; ++bPos )
	{
		pStr[ pos++ ] = mboxDName[ bPos ] ;
	}

	pStr[ pos++ ] = ' ' ;

	for( uint16_t bPos = 0 ; bPos <  txtlen ; ++bPos )
	{
		pStr[ pos++ ] =  txtDName[ bPos ] ;
	}

	pStr[ pos ] = '\0' ;

	return pos ;
}


bool daniel::dns::RR::RData_RP::Load( uint8_t const * pData , uint16_t const & length )
{
	if( nullptr == pData || 1 > length )
	{
		return false ;
	}

	uint16_t len[ 3 ] = { 0 , 0 , 0 } ;

	len[ 0 ] = SkipDName( pData , length ) ; 

	len[ 1 ] = GetDNData( mboxDName , sizeof( mboxDName ) , & pData[        0 ] ) ;
	len[ 2 ] = GetDNData(  txtDName , sizeof(  txtDName ) , & pData[ len[ 0 ] ] ) ;

	if( 1 > len[ 1 ] || 1 > len[ 2 ] )
	{
		return false ;
	}

	return true ;
}