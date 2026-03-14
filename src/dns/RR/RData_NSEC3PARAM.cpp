#include "dns/RR/RData_NSEC3PARAM.h"
#include "dns/QType.h"
#include "baseEncoding/Base32Hex.h"


#include <sstream>
#include <iomanip>
#include <memory>


daniel::dns::RR::RData_NSEC3PARAM::RData_NSEC3PARAM()
	: RData( nullptr )  , hashAlgo( SEC::SECHashAlgo::INVALID )   , 
	  flags( 0 )        , iterations( 0 )       , saltLength( 0 ) , 
	  pSalt( nullptr )
{

}


daniel::dns::RR::RData_NSEC3PARAM::~RData_NSEC3PARAM()
{
	Initialize() ;
}


void daniel::dns::RR::RData_NSEC3PARAM::Initialize()
{
	if( nullptr != pSalt )
	{
		delete [] pSalt ;
		pSalt = nullptr ;
	}

	hashAlgo = SEC::SECHashAlgo::INVALID ;

	flags        = 0 ;
	iterations   = 0 ;
	saltLength   = 0 ;
}


uint16_t daniel::dns::RR::RData_NSEC3PARAM::ToNullStr( uint8_t * pStr , uint16_t const & length ) const
{
	if( nullptr == pStr || 1 > length )
	{
		return 0 ;
	}

	if( 0 < saltLength && nullptr == pSalt )
	{
		return 0 ;
	}


	std::stringstream ss ;

	ss << static_cast< uint16_t >( hashAlgo ) << '\t'
	   << static_cast< uint16_t >( IsOptOut() ? 1 : 0 ) << '\t'
	   << static_cast< uint16_t >( iterations ) << '\t' ;

	/* salt */
	for( uint8_t pos = 0 ; pos < saltLength ; ++pos )
	{
		ss << std::setw( 2 ) << std::setfill( '0' ) << std::hex << static_cast< uint16_t >( pSalt[ pos ] ) ;
	}

	/* output */
	std::string str = ss.str() ;
	uint16_t len = static_cast< uint16_t >( str.length() ) ;
	
	for( uint16_t pos = 0 ; pos < len && pos < length ; ++pos )
	{
		pStr[ pos ] = str[ pos ] ;
	}

	uint16_t less = len < ( length - 1 ) ? len : ( length - 1 ) ;
	pStr[ less ] = '\0' ;

	return less  ;
}


bool daniel::dns::RR::RData_NSEC3PARAM::Load( uint8_t const * pData , uint16_t const & length )
{
	if( nullptr == pData || 1 > length )
	{
		return false ;
	}

	if( 5 > length )
	{
		return false ;
	}

	Initialize() ;

	if( false == SEC::IsValidHashAlgo( pData[ 0 ] ) )
	{
		Initialize() ;
		return false ;
	}
	else
	{
		hashAlgo = daniel::enumFromUint8< SEC::SECHashAlgo >( pData[ 0 ] ) ;
	}

	flags = pData[ 1 ] ;

	iterations 
		= ( ( pData[ 2 ] << 8 ) & 0xFF00 )
		| ( ( pData[ 3 ] << 0 ) & 0x00FF ) ;

	saltLength = pData[ 4 ] ;

	if( 5 + saltLength > length ) 
	{
		Initialize() ;
		return false ;
	}

	if( 0 < saltLength )
	{
		pSalt = new ( std::nothrow ) uint8_t [ saltLength ] ;
		if( nullptr == pSalt )
		{
			Initialize() ;
			return false ;
		}
	}

	uint8_t saltPos = 0 ;
	for( uint8_t pos = 0 ; pos < saltLength ; ++pos )
	{
		pSalt[ saltPos++ ] = pData[ 5 + pos ] ;
	}

	return true ;
}


daniel::dns::RR::SEC::SECHashAlgo daniel::dns::RR::RData_NSEC3PARAM::GetHashAlgo() const 
{
	return hashAlgo ;
}


uint8_t daniel::dns::RR::RData_NSEC3PARAM::GetFlags() const
{
	return flags ;
}


uint16_t daniel::dns::RR::RData_NSEC3PARAM::GetIterations() const 
{
	return iterations ;
}


uint8_t daniel::dns::RR::RData_NSEC3PARAM::GetSaltLength() const 
{
	return saltLength ;
}


bool daniel::dns::RR::RData_NSEC3PARAM::IsOptOut() const
{
	return ( 0 < ( flags & 0x80 ) ) ? true : false ; 
}


uint8_t const * daniel::dns::RR::RData_NSEC3PARAM::GetSalt() const
{
	return pSalt ;
}