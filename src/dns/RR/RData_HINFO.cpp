#include "dns/RR/RData_HINFO.h"


#include <cstring>


daniel::dns::RR::RData_HINFO::RData_HINFO( uint8_t const * pRef )
	: RData( pRef )
{
	cpu[ 0 ] = '\0' ;
	os [ 0 ] = '\0' ;
}


uint16_t daniel::dns::RR::RData_HINFO::ToNullStr( uint8_t * pStr , uint16_t const & length ) const
{
	if( nullptr == pStr || 1 > length )
	{
		return 0 ;
	}

	uint16_t cpulen = static_cast< uint16_t >( strlen( reinterpret_cast< char const * >( cpu ) ) ) ;
	uint16_t  oslen = static_cast< uint16_t >( strlen( reinterpret_cast< char const * >(  os ) ) ) ;

	uint16_t len = cpulen + oslen + 1 ;

	if( length <= len )
	{
		return 0 ;
	}

	uint16_t pos = 0 ;
	for( uint16_t bPos = 0 ; bPos < cpulen ; ++bPos )
	{
		pStr[ pos++ ] = cpu[ bPos ] ;
	}

	pStr[ pos++ ] = ' ' ;

	for( uint16_t bPos = 0 ; bPos <  oslen ; ++bPos )
	{
		pStr[ pos++ ] =  os[ bPos ] ;
	}

	pStr[ pos ] = '\0' ;

	return pos ;
}


bool daniel::dns::RR::RData_HINFO::Load( uint8_t const * pData , uint16_t const & length )
{
	if( nullptr == pData || 1 > length )
	{
		return false ;
	}

	uint16_t len[ 3 ] = { 0 , 0 , 0 } ;

	len[ 0 ] = SkipDName( pData , length ) ; 

	len[ 1 ] = GetDNData( cpu , sizeof( cpu ) , & pData[        0 ] , false ) ;
	len[ 2 ] = GetDNData(  os , sizeof(  os ) , & pData[ len[ 0 ] ] , false ) ;

	if( 1 > len[ 1 ] || 1 > len[ 2 ] )
	{
		return false ;
	}

	return true ;
}


uint8_t const * daniel::dns::RR::RData_HINFO::GetCPUInfo() const
{
	return cpu ;
}


uint8_t const * daniel::dns::RR::RData_HINFO::GetOSInfo() const
{
	return os ;
}