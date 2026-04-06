#include "dns/RR/RData_X25.h"


#include <sstream>
#include <memory>


daniel::dns::RR::RData_X25::RData_X25()
	: RData( nullptr ) , pAddr( nullptr )
{

}


daniel::dns::RR::RData_X25::~RData_X25()
{
	Initialize() ;
}


void daniel::dns::RR::RData_X25::Initialize()
{
	if( nullptr != pAddr )
	{
		delete [] pAddr ;
		pAddr = nullptr ;
	}
}


uint16_t daniel::dns::RR::RData_X25::ToNullStr( uint8_t * pStr , uint16_t const & length ) const
{
	if( nullptr == pStr || 1 > length )
	{
		return 0 ;
	}

	if( nullptr == pAddr )
	{
		return 0 ;
	}

	
	std::stringstream ss ;

	ss << reinterpret_cast< char const * >( pAddr ) ;

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


bool daniel::dns::RR::RData_X25::Load( uint8_t const * pData , uint16_t const & length )
{
	if( nullptr == pData || 1 > length )
	{
		return false ;
	}
	
	uint8_t len = pData[ 0 ] ;

	if( ( 0 == len ) || ( ( len + 1 ) != length ) )
	{
		return false ;
	}

	for( uint8_t pos = 0 ; pos < len ; ++pos )
	{
		uint8_t const & ch = pData[ 1 + pos ] ;
		if( '0' > ch || '9' < ch )
		{
			return false ;
		}
	}

	pAddr = new ( std::nothrow ) uint8_t [ len + 1 ] ;
	if( nullptr == pAddr )
	{
		Initialize() ;
		return false ;
	}

	for( uint8_t pos = 0 ; pos < len ; ++pos )
	{
		pAddr[ pos ] = pData[ 1 + pos ] ;
	}

	pAddr[ len ] = '\0' ;

	return true ;
}