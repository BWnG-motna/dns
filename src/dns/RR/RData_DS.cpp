#include "dns/RR/RData_DS.h"


#include <sstream>
#include <iomanip>
#include <memory>


daniel::dns::RR::RData_DS::RData_DS()
	: RData( nullptr ) , keyTag( 0 ) , algorithm( SEC::SECAlgo::INVALID ) , digestType( SEC::SECDigest::INVALID ) , digestLen( 0 ) , pDigest( nullptr )
{

}


daniel::dns::RR::RData_DS::~RData_DS()
{
	Initalize() ;
}


void daniel::dns::RR::RData_DS::Initalize()
{
	if( nullptr != pDigest )
	{
		delete [] pDigest ;
		pDigest = nullptr ;
	}

	digestLen = 0 ;
	keyTag    = 0 ;
	algorithm  = SEC::SECAlgo::INVALID ;
	digestType = SEC::SECDigest::INVALID ;
}


uint16_t daniel::dns::RR::RData_DS::ToNullStr( uint8_t * pStr , uint16_t const & length ) const
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

	ss << keyTag << "\t"
	   << static_cast< uint16_t >( algorithm )  << "\t"
	   << static_cast< uint16_t >( digestType ) << "\t" ;

	ss << std::hex << std::uppercase ;
	for( uint16_t pos = 0 ; pos < digestLen ; ++pos )
	{
		ss << std::setw( 2 ) << std::setfill( '0' ) << static_cast< uint16_t >( pDigest[ pos ] ) ;
	} 

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


bool daniel::dns::RR::RData_DS::Load( uint8_t const * pData , uint16_t const & length )
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
	

	keyTag
		= ( ( pData[ 0 ] <<  8 ) & 0xFF00 )
		| ( ( pData[ 1 ] <<  0 ) & 0x00FF ) ;

	if( false == SEC::IsValidAlgo( pData[ 2 ] ) )
	{
		Initalize() ;
		return false ;
	}
	else
	{
		algorithm = daniel::enumFromUint8< SEC::SECAlgo >( pData[ 2 ] ) ;
	}

	if( false == SEC::IsValidDigest( pData[ 3 ] ) )
	{
		Initalize() ;
		return false ;
	}
	else
	{
		digestType = daniel::enumFromUint8< SEC::SECDigest >( pData[ 3 ] ) ;
	}

	digestLen = length - 4 ;
	if( digestLen != SEC::GetDigestLen( digestType ) )
	{
		Initalize() ;
		return false ;
	}

	pDigest = new ( std::nothrow ) uint8_t [ digestLen ] ;
	if( nullptr == pDigest )
	{
		Initalize() ;
		return false ;
	}
	
	for( uint16_t pos = 0 ; pos < digestLen ; ++pos )
	{
		pDigest[ pos ] = pData[ 4 + pos ] ;
	}

	return true ;
}


uint16_t daniel::dns::RR::RData_DS::GetKeyTag() const
{
	return keyTag ;
}


daniel::dns::RR::SEC::SECAlgo daniel::dns::RR::RData_DS::GetAlgorithm() const
{
	return algorithm ;
}


uint16_t daniel::dns::RR::RData_DS::GetDigestLen() const
{
	return digestLen ;
}


uint8_t const * daniel::dns::RR::RData_DS::GetDigest() const
{
	return pDigest ;
}