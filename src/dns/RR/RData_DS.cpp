#include "dns/RR/RData_DS.h"

#include <sstream>
#include <iomanip>


daniel::dns::RR::RData_DS::RData_DS()
	: RData( nullptr ) , keyTag( 0 ) , algorithm( SECAlgo::INVALID ) , digestType( SECDigest::INVALID ) , digestLen( 0 )
{
	digest[ 0 ] = '\0' ;
}


uint16_t daniel::dns::RR::RData_DS::ToNullStr( uint8_t * pStr , uint16_t const & length ) const
{
	if( nullptr == pStr || 1 > length )
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
		ss << std::setw( 2 ) << std::setfill( '0' ) << static_cast< uint16_t >( digest[ pos ] ) ;
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
	

	keyTag
		= ( ( pData[ 0 ] <<  8 ) & 0xFF00 )
		| ( ( pData[ 1 ] <<  0 ) & 0x00FF ) ;

	if( false == IsValidAlgo( pData[ 2 ] ) )
	{
		return false ;
	}
	else
	{
		algorithm = daniel::enumFromUint8< SECAlgo >( pData[ 2 ] ) ;
	}

	if( false == IsValidDigest( pData[ 3 ] ) )
	{
		return false ;
	}
	else
	{
		digestType = daniel::enumFromUint8< SECDigest >( pData[ 3 ] ) ;
	}
	
	uint16_t digestPos = 0 ;
	for( uint16_t pos = 4 ; pos < length && digestPos < digestMaxLen ; ++pos )
	{
		digest[ digestPos++ ] = pData[ pos ] ;
	}

	digestLen = digestPos ;

	if( digestLen != RR::GetDigestLen( digestType ) )
	{
		return false ;
	}

	return true ;
}


uint16_t daniel::dns::RR::RData_DS::GetKeyTag() const
{
	return keyTag ;
}


daniel::dns::RR::SECAlgo daniel::dns::RR::RData_DS::GetAlgorithm() const
{
	return algorithm ;
}


uint16_t daniel::dns::RR::RData_DS::GetDigestLen() const
{
	return digestLen ;
}


uint8_t const * daniel::dns::RR::RData_DS::GetDigest() const
{
	return digest ;
}