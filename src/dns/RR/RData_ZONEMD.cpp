#include "dns/RR/RData_ZONEMD.h"


#include <sstream>
#include <iomanip>
#include <memory>


daniel::dns::RR::RData_ZONEMD::RData_ZONEMD()
	: RData( nullptr )   , serial( 0 ) , 
	  scheme   ( ZONEMD::Scheme::Reserved   ) , 
	  algorithm( ZONEMD::HashAlgo::Reserved ) , 
	  pDigest( nullptr ) , digestLen( 0 )
{

}


daniel::dns::RR::RData_ZONEMD::~RData_ZONEMD()
{
	Initialize() ;
}


void daniel::dns::RR::RData_ZONEMD::Initialize()
{
	if( nullptr != pDigest )
	{
		delete [] pDigest ;
		pDigest = nullptr ;
	}

	serial    = 0 ;
	scheme    = ZONEMD::Scheme::Reserved ;
	algorithm = ZONEMD::HashAlgo::Reserved ;
	digestLen = 0 ;
}


uint16_t daniel::dns::RR::RData_ZONEMD::ToNullStr( uint8_t * pStr , uint16_t const & length ) const
{
	if( nullptr == pStr || 1 > length )
	{
		return 0 ;
	}

	if( nullptr == pDigest )
	{
		return 0 ;
	}

	
	std::stringstream ss ;

	ss << serial << " " ;
	ss << static_cast< uint8_t >( scheme )    << " " ;
	ss << static_cast< uint8_t >( algorithm ) << " " ;

	for( uint16_t pos = 0 ; pos < digestLen ; ++pos )
	{
		ss << std::hex << std::setw( 2 ) << std::setfill( '0' ) << static_cast< uint16_t >( pDigest[ pos ] ) ;
	}

	ss << std::dec << std::setw( 1 ) ;

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


bool daniel::dns::RR::RData_ZONEMD::Load( uint8_t const * pData , uint16_t const & length )
{
	if( nullptr == pData || 1 > length )
	{
		return false ;
	}
	
	if( 7 > length )
	{
		return false ;
	}

	Initialize() ;

	serial = ( ( pData[ 0 ] << 24 ) & 0xFF000000 )
		   | ( ( pData[ 1 ] << 16 ) & 0x00FF0000 )
		   | ( ( pData[ 2 ] <<  8 ) & 0x0000FF00 )
		   | ( ( pData[ 3 ] <<  0 ) & 0x000000FF ) ;

	if( true == ZONEMD::IsValidScheme( pData[ 4 ] ) )
	{
		scheme = enumFromUint8< ZONEMD::Scheme >( pData[ 4 ] ) ;
	}
	else
	{
		Initialize() ;
		return false ;
	}

	if( true == ZONEMD::IsValidHashAlgo( pData[ 5 ] ) ) 
	{
		algorithm = enumFromUint8< ZONEMD::HashAlgo >( pData[ 5 ] ) ;
	}

	if( 12 > length - 6 )
	{
		Initialize() ;
		return false ;
	}

	digestLen = length - 6 ;

	pDigest = new ( std::nothrow ) uint8_t [ digestLen ] ;
	if( nullptr == pDigest )
	{
		Initialize() ;
		return false ;
	}

	for( uint16_t pos = 0 ; pos < digestLen ; ++pos )
	{
		pDigest[ pos ] = pData[ 6 + pos ] ;
	}

	return true ;
}