#include "dns/RR/RData_ATMA.h"


#include <sstream>
#include <iomanip>
#include <memory>


daniel::dns::RR::RData_ATMA::RData_ATMA()
	: RData( nullptr ) , format( 0 ) , pAddress( nullptr )
{

}


daniel::dns::RR::RData_ATMA::~RData_ATMA()
{
	Initialize() ;
}


void daniel::dns::RR::RData_ATMA::Initialize()
{
	if( nullptr != pAddress )
	{
		delete [] pAddress ;
		pAddress = nullptr ;
	}

	format = 0 ;
}


uint16_t daniel::dns::RR::RData_ATMA::ToNullStr( uint8_t * pStr , uint16_t const & length ) const
{
	if( nullptr == pStr || 1 > length )
	{
		return 0 ;
	}

	if( nullptr == pAddress || 1 < format )
	{
		return 0 ;
	}

	
	std::stringstream ss ;

	if( 0 == format )
	{
		for( uint16_t pos = 0 ; pos < binlen ; ++pos )
		{
			if( 0 == ( ( pos + 1 ) % 2 ) )
			{
				ss << "." ;
			}
			ss << std::hex << std::setfill( '0' ) << std::setw( 2 ) << static_cast< uint16_t >( pAddress[ pos ] ) ;
		} 
		ss << std::dec << std::setfill( ' ' ) << std::setw( 0 ) ;
	}
	else if( 1 == format )
	{
		ss << reinterpret_cast< char const * >( pAddress ) ;
	}
	else
	{
		// UNKNOWN error
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


bool daniel::dns::RR::RData_ATMA::Load( uint8_t const * pData , uint16_t const & length )
{
	if( nullptr == pData || 1 > length )
	{
		return false ;
	}

	Initialize() ;
	
	format = pData[ 0 ] ;
	if( 1 < format )
	{
		Initialize() ;
		return false ;
	}

	if( 0 >= ( length - 1 ) )
	{
		Initialize() ;
		return false ;
	}

	binlen = length - 1 ;
	pAddress = new ( std::nothrow ) uint8_t [ binlen + 1 ] ;
	if( nullptr == pAddress )
	{
		Initialize() ;
		return false ;
	}

	for( uint16_t pos = 0 ; pos < binlen ; ++pos )
	{
		pAddress[ pos ] = pData[ 1 + pos ] ;
	}

	pAddress[ binlen ] = '\0' ;

	return true ;
}


uint8_t daniel::dns::RR::RData_ATMA::GetFormat() const
{
	return format ;
}


uint8_t const * daniel::dns::RR::RData_ATMA::GetAddress() const
{
	return pAddress ;
}