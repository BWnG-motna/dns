#include "dns/RR/RData_CERT.h"
#include "baseEncoding/Base64.h"


#include <sstream>
#include <memory>


daniel::dns::RR::RData_CERT::RData_CERT()
	: RData( nullptr ) , type( CERT::CertType::RESERVED ) , keyTag( 0 ) , algorithm( SEC::SECAlgo::INVALID ) , pCert( nullptr ) , certlen( 0 )
{

}


daniel::dns::RR::RData_CERT::~RData_CERT()
{
	Initialize() ;
}


void daniel::dns::RR::RData_CERT::Initialize()
{
	if( nullptr != pCert )
	{
		delete [] pCert ;
		pCert = nullptr ;
	}

	type      = CERT::CertType::RESERVED ;
	keyTag    = 0 ;
	algorithm = SEC::SECAlgo::INVALID ;
	certlen   = 0 ; 
}


uint16_t daniel::dns::RR::RData_CERT::ToNullStr( uint8_t * pStr , uint16_t const & length ) const
{
	if( nullptr == pStr || 1 > length )
	{
		return 0 ;
	}

	if( nullptr == pCert || ( nullptr != pCert && 1 > certlen ) )
	{
		return 0 ;
	}

	
	std::stringstream ss ;

	ss << static_cast< uint16_t >( type      ) << " "
	   << static_cast< uint16_t >( keyTag    ) << " "
	   << static_cast< uint16_t >( algorithm ) << " " ;
	
	{
		using T = CERT::CertType ;

		/**/ if( T::IPKIX == type || T::ISPKI == type || T::IACPKIX == type || T::URI == type )
		{
			for( uint16_t pos = 0 ; pos < certlen ; ++pos )
			{
				ss << pCert[ pos ] ;
			}
		}
		else
		{
			char     encDat[ base64exprMaxLen ] ;
			uint16_t wBytes = 0 ;

			baseEncoding::Base64 enc ;
			bool is = enc.Encode( encDat , base64exprMaxLen , pCert , certlen , true , & wBytes ) ;
			if( false == is )
			{
				return 0 ;
			}

			for( uint16_t pos = 0 ; pos < wBytes ; ++pos )
			{
				ss << encDat[ pos ] ;
			}
		}
	}

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


bool daniel::dns::RR::RData_CERT::Load( uint8_t const * pData , uint16_t const & length )
{
	if( nullptr == pData || 1 > length )
	{
		return false ;
	}

	if( 6 > length )
	{
		return false ;
	}

	Initialize() ;

	uint16_t value = 0 ;

	value = ( ( pData[ 0 ] << 8 ) & 0xFF00 )
	      | ( ( pData[ 1 ] << 0 ) & 0x00FF ) ;
	
	if( true == CERT::IsValidCertType( value ) )
	{
		type = enumFromUint16< CERT::CertType >( value ) ;
	}
	else
	{
		Initialize() ;
		return false ;
	}

	value = ( ( pData[ 2 ] << 8 ) & 0xFF00 )
	      | ( ( pData[ 3 ] << 0 ) & 0x00FF ) ;

	keyTag = value ;

	if( true == SEC::IsValidAlgo( pData[ 4 ] ) )
	{
		algorithm = enumFromUint8< SEC::SECAlgo >( pData[ 4 ] ) ;
	}
	else
	{
		Initialize() ;
		return false ;
	}


	certlen = length - 5 ;
	pCert   = new ( std::nothrow ) uint8_t [ certlen ] ;
	if( nullptr == pCert )
	{
		return false ;
	}

	for( uint16_t pos = 0 ; pos < certlen ; ++pos )
	{
		pCert[ pos ] = pData[ 5 + pos ] ;
	}

	return true ;
}



daniel::dns::RR::CERT::CertType daniel::dns::RR::RData_CERT::GetType() const
{
	return type ;
}


daniel::dns::RR::SEC::SECAlgo daniel::dns::RR::RData_CERT::GetAlgorithm() const
{
	return algorithm ;
}


uint16_t daniel::dns::RR::RData_CERT::GetKeyTag() const
{
	return keyTag ;
}


uint8_t const * daniel::dns::RR::RData_CERT::GetCert() const
{
	return pCert ;
}


uint16_t daniel::dns::RR::RData_CERT::GetCertLen() const
{
	return certlen ;
}