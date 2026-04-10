#include "dns/RR/RData_NIMLOC.h"


#include <sstream>
#include <iomanip>
#include <memory>


daniel::dns::RR::RData_NIMLOC::RData_NIMLOC()
	: RData( nullptr ) , binlen( 0 ) , pBinary( nullptr )
{

}


daniel::dns::RR::RData_NIMLOC::~RData_NIMLOC()
{
	Initialize() ;
}


void daniel::dns::RR::RData_NIMLOC::Initialize()
{
	if( nullptr != pBinary )
	{
		delete [] pBinary ;
		pBinary = nullptr ;
	}

	binlen = 0 ;
}


uint16_t daniel::dns::RR::RData_NIMLOC::ToNullStr( uint8_t * pStr , uint16_t const & length ) const
{
	if( nullptr == pStr || 1 > length )
	{
		return 0 ;
	}

	if( nullptr == pBinary ) 
	{
		return 0 ;
	}


	std::stringstream ss ;

	for( uint16_t pos = 0 ; pos < binlen ; ++pos )
	{
		ss << std::hex << std::setfill( '0' ) << std::setw( 2 ) << static_cast< uint16_t >( pBinary[ pos ] ) ;
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


bool daniel::dns::RR::RData_NIMLOC::Load( uint8_t const * pData , uint16_t const & length )
{
	if( nullptr == pData || 1 > length )
	{
		return false ;
	}

	Initialize() ;

	binlen = length ;

	pBinary = new ( std::nothrow ) uint8_t [ binlen ] ;
	if( nullptr == pBinary )
	{
		Initialize() ;
		return false ;
	}

	for( uint16_t pos = 0 ; pos < binlen ; ++pos )
	{
		pBinary[ pos ] = pData[ pos ] ;
	}

	return true ;
}


uint16_t daniel::dns::RR::RData_NIMLOC::GetLength() const
{
	return binlen ;
}


uint8_t const * daniel::dns::RR::RData_NIMLOC::GetBinary() const
{
	return pBinary ;
}