#include "dns/RR/RData_URI.h"


#include <sstream>
#include <memory>


daniel::dns::RR::RData_URI::RData_URI()
	: RData( nullptr ) , priority( 0 ) , weight( 0 ) , pTarget( nullptr )
{

}


daniel::dns::RR::RData_URI::~RData_URI()
{
	Initialize() ;
}


void daniel::dns::RR::RData_URI::Initialize()
{
	if( nullptr != pTarget )
	{
		delete [] pTarget ;
		pTarget = nullptr ;
	}

	priority = 0 ;
	weight   = 0 ;
}


uint16_t daniel::dns::RR::RData_URI::ToNullStr( uint8_t * pStr , uint16_t const & length ) const
{
	if( nullptr == pStr || 1 > length )
	{
		return 0 ;
	}

	if( nullptr == pTarget )
	{
		return 0 ;
	}


	std::stringstream ss ;

	ss << static_cast< uint16_t>( priority ) << '\t'
	   << static_cast< uint16_t>( weight   ) << '\t'
	   << reinterpret_cast< char const * >( pTarget ) ;

	std::string s = ss.str() ;
	uint16_t len  = static_cast< uint16_t >( s.length() ) ;

	for( uint16_t pos = 0 ; pos < length && pos < len ; ++pos )
	{
		pStr[ pos ] = s[ pos ] ;
	}

	uint16_t less = len < length ? len : length ;
	pStr[ less ] = '\0' ;

	return less ;
}


bool daniel::dns::RR::RData_URI::Load( uint8_t const * pData , uint16_t const & length )
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

	priority
		= ( ( pData[ 0 ] << 8 ) & 0xFF00 )
		| ( ( pData[ 1 ] << 0 ) & 0x00FF ) ;

	weight
		= ( ( pData[ 2 ] << 8 ) & 0xFF00 )
		| ( ( pData[ 3 ] << 0 ) & 0x00FF ) ;

	uint16_t targetlen = length - 4 ; 

	pTarget = new ( std::nothrow ) uint8_t [ targetlen + 1 ] ;
	if( nullptr == pTarget )
	{
		Initialize() ;
		return false ;
	}

	for( uint16_t pos = 0 ; pos < targetlen ; ++pos )
	{
		pTarget[ pos ] = pData[ 4 + pos ] ; 
	}

	return true ;
}


uint16_t daniel::dns::RR::RData_URI::GetPriority() const
{
	return priority ;
}


uint16_t daniel::dns::RR::RData_URI::GetWeight() const
{
	return weight ;
}


uint8_t const * daniel::dns::RR::RData_URI::GetTarget() const
{
	return pTarget ;
}