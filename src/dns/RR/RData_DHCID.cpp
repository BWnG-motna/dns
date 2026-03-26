#include "dns/RR/RData_DHCID.h"


#include "baseEncoding/Base64.h"


#include <sstream>
#include <memory>


daniel::dns::RR::RData_DHCID::RData_DHCID()
	: RData( nullptr ) , id( 0xFFFF ) , digestType( 0 ) , pDigest( nullptr )
{

}


daniel::dns::RR::RData_DHCID::~RData_DHCID()
{
	Initialize() ;
}


void daniel::dns::RR::RData_DHCID::Initialize()
{
	if( nullptr != pDigest )
	{
		delete [] pDigest ;
		pDigest = nullptr ;
	}

	id         = 0xFFFF ;
	digestType = 0 ;
}


uint16_t daniel::dns::RR::RData_DHCID::ToNullStr( uint8_t * pStr , uint16_t const & length ) const
{
	if( nullptr == pStr || 1 > length )
	{
		return 0 ;
	}

	if( nullptr == pDigest || 1 > digestLen )
	{
		return 0 ;
	}

	uint16_t  inLen = 3 + digestLen ;
	uint16_t outLen = ( inLen + 2 ) / 3 * 4 ;
	uint8_t * pIn   = nullptr ;
	uint8_t * pOut  = nullptr ;

	pIn  = new ( std::nothrow ) uint8_t [  inLen ] ;
	pOut = new ( std::nothrow ) uint8_t [ outLen ] ;
	
	if( nullptr == pIn || nullptr == pOut )
	{
		if( nullptr != pIn )
		{
			delete [] pIn ;
		}

		if( nullptr != pOut )
		{
			delete [] pOut ;
		}

		return 0 ;
	}

	for( uint16_t pos = 0 ; pos < digestLen ; ++pos )
	{
		pIn[ 3 + pos ] = pDigest[ pos ] ;
	}

	pIn[ 0 ] = static_cast< uint16_t >( ( id >> 8 ) & 0x00FF ) ;
	pIn[ 1 ] = static_cast< uint16_t >( ( id >> 0 ) & 0x00FF ) ;
	pIn[ 2 ] = digestType ;

	uint16_t pBytes = 0 ;
	baseEncoding::Base64 base64 ;
	base64.Encode( reinterpret_cast< char * >( pOut ) , outLen , pIn , inLen , true , & pBytes ) ;


	
	std::stringstream ss ;

	ss << reinterpret_cast< char const * >( pOut ) ;

	std::string s = ss.str() ;
	uint16_t len  = static_cast< uint16_t >( s.length() ) ;

	for( uint16_t pos = 0 ; pos < length && pos < len ; ++pos )
	{
		pStr[ pos ] = s[ pos ] ;
	}

	uint16_t less = len < ( length - 1 ) ? len : ( length - 1 ) ;
	pStr[ less ] = '\0' ;

	delete [] pIn  ;
	delete [] pOut ;

	return less ;
}


bool daniel::dns::RR::RData_DHCID::Load( uint8_t const * pData , uint16_t const & length )
{
	if( nullptr == pData || 1 > length )
	{
		return false ;
	}

	if( 4 > length )
	{
		return false ;
	}

	Initialize() ;

	id = ( ( pData[ 0 ] << 8 ) & 0xFF00 )
	   | ( ( pData[ 1 ] << 0 ) & 0x00FF ) ;

	if( false == DHCID::IsValidId( id ) )
	{
		Initialize() ;
		return false ;
	}

	digestType = pData[ 2 ] ;

	if( false == DHCID::IsValidDigestType( digestType ) )
	{
		Initialize() ;
		return false ;
	}

	digestLen = length - 3 ;
	pDigest   = new ( std::nothrow ) uint8_t [ digestLen ] ;
	if( nullptr == pDigest )
	{
		Initialize() ;
		return false ;
	}

	for( uint16_t pos = 0 ; pos < digestLen ; ++pos )
	{
		pDigest[ pos ] = pData[ 3 + pos ] ;
	}

	return true ;
}


uint16_t daniel::dns::RR::RData_DHCID::GetId() const
{
	return id ;
}


uint16_t daniel::dns::RR::RData_DHCID::GetDigestLen() const
{
	return digestLen ;
}


uint8_t daniel::dns::RR::RData_DHCID::GetDigestType() const
{
	return digestType ;
}


uint8_t const * daniel::dns::RR::RData_DHCID::GetDigest() const
{
	return pDigest ;
}