#include "dns/RR/RData_AAAA.h"


daniel::dns::RR::RData_AAAA::RData_AAAA()
	: RData( nullptr )
{

}


daniel::dns::RR::RData_AAAA::~RData_AAAA()
{
	Initalize() ;
}


void daniel::dns::RR::RData_AAAA::Initalize()
{
	for( uint16_t pos = 0 ; pos < 8 ; ++pos )
	{
		address[ pos ] = 0 ;
	}
}


uint16_t daniel::dns::RR::RData_AAAA::ToNullStr( uint8_t * pStr , uint16_t const & length ) const
{
	if( nullptr == pStr || 1 > length )
	{
		return false ;
	}

	uint8_t addrStr[ 40 ] = { 0 , } ;
	if( false == GetCompressedIPv6( addrStr , 40 , address ) )
	{
		pStr[ 0 ] = '\0' ;
		return 0 ;
	}

	uint16_t pos = 0 ;
	while( pos < length && '\0' != addrStr[ pos ] )
	{
		pStr[ pos ] = addrStr[ pos ] ;
		++pos ;
	}

	pStr[ pos ] = '\0' ;

	return pos ;
}


bool daniel::dns::RR::RData_AAAA::Load( uint8_t const * pData , uint16_t const & length )
{
	if( nullptr == pData || 1 > length )
	{
		return false ;
	}

	if( 16 != length )
	{
		return false ;
	}

	for( uint8_t aPos = 0 , rPos = 0 ; rPos < length ; rPos += 2 , ++aPos )
	{
		address[ aPos ] = ( ( pData[ rPos + 0 ] << 8 ) & 0xFF00 )
		                | ( ( pData[ rPos + 1 ] << 0 ) & 0x00FF ) ; 

	}

	return true ;
}


void daniel::dns::RR::RData_AAAA::GetAddress( uint16_t ( & addr )[ 8 ] )
{
	for( uint8_t pos = 0 ; pos < 8 ; ++pos )
	{
		addr[ pos ] = address[ pos ] ;
	}
}