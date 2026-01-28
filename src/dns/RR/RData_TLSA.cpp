#include "dns/RR/RData_TLSA.h"


#include <sstream>
#include <iomanip>
#include <iostream>


daniel::dns::RR::RData_TLSA::RData_TLSA()
	: RData( nullptr )
{
	
}


uint16_t daniel::dns::RR::RData_TLSA::ToNullStr( uint8_t * pStr , uint16_t const & length ) const 
{
	if( nullptr == pStr || 1 > length )
	{
		return 0 ;
	}

	std::stringstream ss ;

	ss << static_cast< uint16_t >( certUsage )    << ' '
	   << static_cast< uint16_t >( selector  )    << ' '
	   << static_cast< uint16_t >( matchingType ) << ' ' ;

	ss << std::hex << std::uppercase ;
	for( uint16_t pos = 0 ; pos < certlen ; ++pos )
	{
		ss << std::setw( 2 ) << std::setfill( '0' ) << static_cast< uint16_t >( cert[ pos ] ) ;
	}

	ss << std::setw( 0 ) << std::dec << std::setfill( ' ' ) ;

	std::string s = ss.str() ;
	uint16_t len = static_cast< uint16_t >( s.length() ) ;
	for( uint16_t pos = 0 ; pos < len && pos < length ; ++pos )
	{
		pStr[ pos ] = s[ pos ] ;
	}

	uint16_t less = len < ( length - 1 ) ? len : ( length - 1 ) ;
	pStr[ less ] = '\0' ;

	return less ;
}


bool daniel::dns::RR::RData_TLSA::Load( uint8_t const * pData , uint16_t const & length )
{
	if( nullptr == pData || 1 > length )
	{
		return false ;
	}

	if( 4 > length )
	{
		return false ;
	}


	if( IsValidCertUsage( pData[ 0 ] ) )
	{
		certUsage = enumFromUint8< CertUsage >( pData[ 0 ] ) ;
	}
	else
	{
		return false ;
	}

	if( IsValidSelector( pData[ 1 ] ) )
	{
		selector = enumFromUint8< Selector >( pData[ 1 ] ) ;
	}
	else
	{
		return false ;
	}

	if( IsValidMatchingType( pData[ 2 ] ) )
	{
		matchingType = enumFromUint8< MatchingType >( pData[ 2 ] ) ;
	}
	else
	{
		return false ;
	}

	uint16_t certPos = 0 ;
	for( uint16_t pos = 3 ; pos < length && pos < certMaxLen ; ++pos )
	{
		cert[ certPos++ ] = pData[ pos ] ;
	}

	certlen = certPos ;
	
	return true ;
}


daniel::dns::RR::CertUsage daniel::dns::RR::RData_TLSA::GetCertUsage() const
{
	return certUsage ;
}


daniel::dns::RR::Selector daniel::dns::RR::RData_TLSA::GetSelector() const
{
	return selector ;
}


daniel::dns::RR::MatchingType daniel::dns::RR::RData_TLSA::GetMatchingType() const
{
	return matchingType ;
}


uint8_t const * daniel::dns::RR::RData_TLSA::GetCertData() const 
{
	return cert ;
}