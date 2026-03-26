#include "dns/RR/RData_A6.h"


#include <sstream>
#include <iomanip>


daniel::dns::RR::RData_A6::RData_A6()
	: RData( nullptr ) , prefixLen( 0 ) , prefix( nullptr ) , addrSuffixBeg( 0 )
{
	for( uint8_t pos = 0 ; pos < 16 ; ++pos )
	{
		addrSuffix[ pos ] = 0 ;
	}
}


daniel::dns::RR::RData_A6::~RData_A6()
{
	Initialize() ;
}


void daniel::dns::RR::RData_A6::Initialize()
{
	if( nullptr != prefix )
	{
		delete [] prefix ;
		prefix = nullptr ;
	}

	for( uint8_t pos = 0 ; pos < 16 ; ++pos )
	{
		addrSuffix[ pos ] = 0 ;
	}

	addrSuffixBeg = 0 ;
	prefixLen     = 0 ;
}


uint16_t daniel::dns::RR::RData_A6::ToNullStr( uint8_t * pStr , uint16_t const & length ) const
{
	if( nullptr == pStr || 1 > length )
	{
		return 0 ;
	}

	
	std::stringstream ss ;

	ss << static_cast< uint16_t >( prefixLen ) << " " ;

	uint16_t addr[ 8 ] ;
	uint8_t  addrPos = 0 ;
	for( uint8_t pos = 0 ; pos < 16 ; pos += 2 )
	{
		addr[ addrPos++ ] 
			= ( ( addrSuffix[ pos + 0 ] << 8 ) & 0xFF00 )
			| ( ( addrSuffix[ pos + 1 ] << 0 ) & 0x00FF ) ;
	}

	uint8_t buf[ 50 ] ;
	GetCompressedIPv6( buf , 50 , addr ) ;

	ss << reinterpret_cast< char const * >( buf ) << " " ;

	if( nullptr != prefix )
	{
		ss << reinterpret_cast< char const * >( prefix ) ;
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


bool daniel::dns::RR::RData_A6::Load( uint8_t const * pData , uint16_t const & length )
{
	if( nullptr == pData || 1 > length )
	{
		return false ;
	}

	if( 128 < pData[ 0 ] )
	{
		return false ;
	}
	
	Initialize() ;

	prefixLen = pData[ 0 ] ;
	
	uint8_t suffixBits = 128 - prefixLen ;
	uint8_t suffixOcts = ( suffixBits / 8 ) + ( ( 0 < ( suffixBits % 8 ) ) ? 1 : 0 ) ; 

	if( ( 1 + suffixOcts ) > length )
	{
		Initialize() ;
		return false ;
	}

	addrSuffixBeg = 16 - suffixOcts ;

	for( uint8_t pos = 0 ; pos < addrSuffixBeg ; ++pos )
	{
		addrSuffix[ pos ] = 0 ;
	}

	for( uint8_t pos = 0 ; pos < suffixOcts ; ++pos )
	{
		addrSuffix[ addrSuffixBeg + pos ] = pData[ 1 + pos ] ;
	}

	if( 0 == prefixLen )
	{
		prefix = nullptr ;
		return true ;
	}

	uint16_t pos       = 1 + suffixOcts ;
	uint16_t len       = GetDNDataLen( & ( pData[ pos ] ) ) ;
	uint16_t allocSize = ( 0 < len ) ? ( len + 1 ) : 2 ;

	prefix = new ( std::nothrow ) uint8_t [ allocSize ] ;
	if( nullptr == prefix )
	{
		Initialize() ;
		return false ;
	}

	GetDNData( prefix , len + 1 , & ( pData[ pos ] ) ) ; 

	return true ;
}