#include "dns/RR/RData_SOA.h"


#include <sstream>


daniel::dns::RR::RData_SOA::RData_SOA( uint8_t const * pRef )
	: RData( pRef ) , serial( 0 ) , refresh( 0 ) , retry( 0 ) , expire( 0 ) , minimum( 0 )
{
	mname[ 0 ] = '\0' ;
	rname[ 0 ] = '\0' ;
}


uint16_t daniel::dns::RR::RData_SOA::ToNullStr( uint8_t * pStr , uint16_t const & length ) const
{
	if( nullptr == pStr || 1 > length )
	{
		return 0 ;
	}

	std::stringstream ss ;

	ss << reinterpret_cast< char const * >( mname ) << " " 
       << reinterpret_cast< char const * >( rname ) << " " 
       << serial  << " " 
       << refresh << " " 
       << retry   << " " 
       << expire  << " " 
       << minimum ;

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


bool daniel::dns::RR::RData_SOA::Load( uint8_t const * pData , uint16_t const & length )
{
	if( nullptr == pData || 1 > length )
	{
		return false ;
	}

	uint16_t slen[ 2 ] = { 0 , 0 } ;
	uint16_t blen[ 2 ] = { 0 , 0 } ;

	slen[ 0 ] = SkipDName( & ( pData[         0 ] ) , length ) ; 
	slen[ 1 ] = SkipDName( & ( pData[ slen[ 0 ] ] ) , length - slen[ 0 ] ) ;

	blen[ 0 ] = GetDNData( mname , sizeof( mname ) , & pData[         0 ] ) ;
	blen[ 1 ] = GetDNData( rname , sizeof( rname ) , & pData[ slen[ 0 ] ] ) ;

	if( 1 > blen[ 0 ] || 1 > blen[ 1 ] )
	{
		return false ;
	}

	uint16_t pos = slen[ 0 ] + slen[ 1 ] ;

	serial
		= ( ( pData[ pos + 0 ] << 24 ) & 0xFF000000 )
		| ( ( pData[ pos + 1 ] << 16 ) & 0x00FF0000 )
		| ( ( pData[ pos + 2 ] <<  8 ) & 0x0000FF00 )
		| ( ( pData[ pos + 3 ] <<  0 ) & 0x000000FF ) ;

	pos += 4 ;

	refresh
		= ( ( pData[ pos + 0 ] << 24 ) & 0xFF000000 )
		| ( ( pData[ pos + 1 ] << 16 ) & 0x00FF0000 )
		| ( ( pData[ pos + 2 ] <<  8 ) & 0x0000FF00 )
		| ( ( pData[ pos + 3 ] <<  0 ) & 0x000000FF ) ;

	pos += 4 ;

	retry
		= ( ( pData[ pos + 0 ] << 24 ) & 0xFF000000 )
		| ( ( pData[ pos + 1 ] << 16 ) & 0x00FF0000 )
		| ( ( pData[ pos + 2 ] <<  8 ) & 0x0000FF00 )
		| ( ( pData[ pos + 3 ] <<  0 ) & 0x000000FF ) ;

	pos += 4 ;

	expire
		= ( ( pData[ pos + 0 ] << 24 ) & 0xFF000000 )
		| ( ( pData[ pos + 1 ] << 16 ) & 0x00FF0000 )
		| ( ( pData[ pos + 2 ] <<  8 ) & 0x0000FF00 )
		| ( ( pData[ pos + 3 ] <<  0 ) & 0x000000FF ) ;

	pos += 4 ;

	minimum
		= ( ( pData[ pos + 0 ] << 24 ) & 0xFF000000 )
		| ( ( pData[ pos + 1 ] << 16 ) & 0x00FF0000 )
		| ( ( pData[ pos + 2 ] <<  8 ) & 0x0000FF00 )
		| ( ( pData[ pos + 3 ] <<  0 ) & 0x000000FF ) ;

	return true ;
}