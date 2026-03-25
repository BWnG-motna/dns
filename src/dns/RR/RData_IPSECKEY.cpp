#include "dns/RR/RData_IPSECKEY.h"

#include "baseEncoding/Base64.h"


#include <sstream>


daniel::dns::RR::RData_IPSECKEY::RData_IPSECKEY()
	: RData( nullptr )    , precedence( 0 ) , gatewayType( IPSECKEY::Gateway::Invalid ) , algorithm( IPSECKEY::Algorithm::Invalid ) ,
	  pGateway( nullptr ) , pKey( nullptr ) , pkLen( 0 )
{

}


daniel::dns::RR::RData_IPSECKEY::~RData_IPSECKEY()
{
	Initialize() ;
}


void daniel::dns::RR::RData_IPSECKEY::Initialize()
{
	if( nullptr == pGateway )
	{
		delete [] pGateway ;
		pGateway = nullptr ;
	}

	if( nullptr == pKey )
	{
		delete [] pKey ;
		pKey = nullptr ;
	}

	gatewayType = IPSECKEY::Gateway::Invalid ;
	algorithm   = IPSECKEY::Algorithm::Invalid ;
	precedence  = 0 ;
	pkLen       = 0 ;
}


uint16_t daniel::dns::RR::RData_IPSECKEY::ToNullStr( uint8_t * pStr , uint16_t const & length ) const
{
	if( nullptr == pStr || 1 > length )
	{
		return 0 ;
	}

	
	std::stringstream ss ;

	ss << static_cast< uint16_t >( precedence  ) << " "
	   << static_cast< uint16_t >( gatewayType ) << " "
	   << static_cast< uint16_t >( algorithm   ) << " " ;

	/**/ if(    IPSECKEY::Gateway::NoGateway == gatewayType 
		     || IPSECKEY::Gateway::FQDN      == gatewayType )
	{
		ss << reinterpret_cast< char const * >( pGateway ) << " " ;
	}
	else if(    IPSECKEY::Gateway::IPv4 == gatewayType )
	{
		ss << static_cast< uint16_t >( pGateway[ 0 ] ) << "."
		   << static_cast< uint16_t >( pGateway[ 1 ] ) << "."
		   << static_cast< uint16_t >( pGateway[ 2 ] ) << "."
		   << static_cast< uint16_t >( pGateway[ 3 ] ) << " " ;
	}
	else if(    IPSECKEY::Gateway::IPv6 == gatewayType )
	{
		uint16_t addr[ 8 ] ;
		uint8_t  addrPos = 0 ;
		for( uint8_t pos = 0 ; pos < 16 ; pos += 2 )
		{
			addr[ addrPos++ ]
				= ( ( pGateway[ pos + 0 ] << 8 ) & 0xFF00 )
				| ( ( pGateway[ pos + 1 ] << 0 ) & 0x00FF ) ;
		}

		uint8_t ipv6[ 50 ] ;
		GetCompressedIPv6( ipv6 , 50 , addr ) ;

		ss << reinterpret_cast< char const * >( ipv6 ) << " " ;
	}

	if( nullptr != pKey && 0 < pkLen )
	{
		uint8_t p[ 1024 ] ;

		uint16_t pBytes = 0 ;
		baseEncoding::Base64 base64 ;
		base64.Encode( reinterpret_cast< char * >( p ) , 1024 , pKey , pkLen , true , & pBytes ) ;

		ss << reinterpret_cast< char const * >( p ) ;
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


bool daniel::dns::RR::RData_IPSECKEY::Load( uint8_t const * pData , uint16_t const & length )
{
	if( nullptr == pData || 1 > length )
	{
		return false ;
	}
	
	if( 3 > length )
	{
		return false ;
	}

	Initialize() ;

	precedence = pData[ 0 ] ;

	if( true == IPSECKEY::IsValidGateway( pData[ 1 ] ) )
	{
		gatewayType = enumFromUint8< IPSECKEY::Gateway >( pData[ 1 ] ) ;
	}
	else
	{
		Initialize() ;
		return false ;
	}

	if( true == IPSECKEY::IsValidAlgorithm( pData[ 2 ] ) ) 
	{
		algorithm = enumFromUint8< IPSECKEY::Algorithm >( pData[ 2 ] ) ;
	}
	else
	{
		Initialize() ;
		return false ;
	}

	bool     isFixed  = IPSECKEY::IsFixedLen( gatewayType ) ;
	uint16_t fixedLen = IPSECKEY::GetFixedLen( gatewayType ) ;
	uint16_t nextPos  = 0 ;

	if( true == isFixed && 0 < fixedLen )
	{
		pGateway = new ( std::nothrow ) uint8_t [ fixedLen + 1 ] ;
		if( nullptr == pGateway )
		{
			Initialize() ;
			return false ;
		}

		for( uint16_t pos = 0 ; pos < fixedLen ; ++pos )
		{
			pGateway[ pos ] = pData[ 3 + pos ] ;
		}

		pGateway[ fixedLen ] = '\0' ;

		nextPos = 3 + fixedLen ;
	}
	else if( false == isFixed && IPSECKEY::Gateway::FQDN == gatewayType )
	{
		uint16_t len       = GetDNDataLen( & ( pData[ 3 ] ) ) ;
		uint16_t allocSize = ( 0 < len ) ? ( len + 1 ) : 2 ;

		pGateway = new ( std::nothrow ) uint8_t [ allocSize ] ;
		if( nullptr == pGateway )
		{
			Initialize() ;
			return false ;
		}  

		if( 0 < len )
		{ 
			len = GetDNData( pGateway , len + 1 , & ( pData[ 3 ] ) ) ; 
		}
		else
		{
			pGateway[ 0 ] = '.' ;
			pGateway[ 1 ] = '\0' ;
		}

		len = SkipDName( & ( pData[ 3 ] ) , length - 3 ) ;

		nextPos = 3 + len ;
	}
	else
	{
		pGateway = new ( std::nothrow ) uint8_t [ 2 ] ;
		if( nullptr == pGateway )
		{
			Initialize() ;
			return false ;
		}

		pGateway[ 0 ] = '.' ;
		pGateway[ 1 ] = '\0' ;

		nextPos = 3 ;
	}

	pkLen = length - nextPos ;
	
	if( 0 < pkLen )
	{
		pKey  = new ( std::nothrow ) uint8_t [ pkLen ] ;
		if( nullptr == pKey )
		{
			Initialize() ;
			return false ;
		}

		for( uint16_t pos = 0 ; pos < pkLen ; ++pos )
		{
			pKey[ pos ] = pData[ nextPos + pos ] ;
		}
	}
	else
	{
		pkLen = 0 ;
		pKey  = nullptr ;
	}


	return true ;
}


uint8_t daniel::dns::RR::RData_IPSECKEY::GetPrecedence() const
{
	return precedence ;
}


daniel::dns::RR::IPSECKEY::Gateway daniel::dns::RR::RData_IPSECKEY::GetGatewayType() const
{
	return gatewayType ;
}


daniel::dns::RR::IPSECKEY::Algorithm daniel::dns::RR::RData_IPSECKEY::GetAlgorithm() const
{
	return algorithm ;
}


uint8_t const * daniel::dns::RR::RData_IPSECKEY::GetGateway() const
{
	return pGateway ;
}


uint8_t const * daniel::dns::RR::RData_IPSECKEY::GetPublicKey() const
{
	return pKey ;
}


uint16_t daniel::dns::RR::RData_IPSECKEY::GetPublcKeyLen() const
{
	return pkLen ;
}