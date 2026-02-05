#include "dns/RR/RData_TLSA.h"


#include <sstream>
#include <iomanip>


daniel::dns::RR::RData_TLSA::RData_TLSA()
	: RData( nullptr ) ,
	  certUsage   ( DANE::CertUsage::INVALID ) , 
	  selector    ( DANE::Selector::INVALID  ) ,
	  matchingType( DANE::MatchingType::INVALID ) ,
	  pCert( nullptr ) ,
	  certlen( 0 )
{
	
}


daniel::dns::RR::RData_TLSA::~RData_TLSA()
{
	Initalize() ;
}


void daniel::dns::RR::RData_TLSA::Initalize()
{
	if( nullptr != pCert )
	{
		delete [] pCert ;
		pCert = nullptr ;
	}

	certlen = 0 ;

	certUsage    = DANE::CertUsage::INVALID ;
	selector     = DANE::Selector::INVALID  ;
	matchingType = DANE::MatchingType::INVALID ;
}


uint16_t daniel::dns::RR::RData_TLSA::ToNullStr( uint8_t * pStr , uint16_t const & length ) const 
{
	if( nullptr == pStr || 1 > length )
	{
		return 0 ;
	}

	if( nullptr == pCert )
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
		ss << std::setw( 2 ) << std::setfill( '0' ) << static_cast< uint16_t >( pCert[ pos ] ) ;
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


	Initalize() ;

	if( DANE::IsValidCertUsage( pData[ 0 ] ) )
	{
		certUsage = enumFromUint8< DANE::CertUsage >( pData[ 0 ] ) ;
	}
	else
	{
		Initalize() ;
		return false ;
	}

	if( DANE::IsValidSelector( pData[ 1 ] ) )
	{
		selector = enumFromUint8< DANE::Selector >( pData[ 1 ] ) ;
	}
	else
	{
		Initalize() ;
		return false ;
	}

	if( DANE::IsValidMatchingType( pData[ 2 ] ) )
	{
		matchingType = enumFromUint8< DANE::MatchingType >( pData[ 2 ] ) ;
	}
	else
	{
		Initalize() ;
		return false ;
	}

	certlen = length - 3 ;

	pCert = new ( std::nothrow ) uint8_t [ certlen + 1 ] ;
	if( nullptr == pCert )
	{
		Initalize() ;
		return false ;
	}


	for( uint16_t pos = 0 ; pos < certlen ; ++pos )
	{
		pCert[ pos ] = pData[ 3 + pos ] ;
	}

	return true ;
}


daniel::dns::RR::DANE::CertUsage daniel::dns::RR::RData_TLSA::GetCertUsage() const
{
	return certUsage ;
}


daniel::dns::RR::DANE::Selector daniel::dns::RR::RData_TLSA::GetSelector() const
{
	return selector ;
}


daniel::dns::RR::DANE::MatchingType daniel::dns::RR::RData_TLSA::GetMatchingType() const
{
	return matchingType ;
}


uint8_t const * daniel::dns::RR::RData_TLSA::GetCertData() const 
{
	return pCert ;
}