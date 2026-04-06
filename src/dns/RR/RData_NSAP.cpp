#include "dns/RR/RData_NSAP.h"


#include <sstream>
#include <iomanip>
#include <memory>


daniel::dns::RR::RData_NSAP::RData_NSAP()
	: RData( nullptr ) , binlen( 0 ) , pBinary( nullptr )
{

}


daniel::dns::RR::RData_NSAP::~RData_NSAP()
{
	Initialize() ;
}


void daniel::dns::RR::RData_NSAP::Initialize()
{
	if( nullptr != pBinary )
	{
		delete [] pBinary ;
		pBinary = nullptr ;
	}

	binlen = 0 ;
}


uint16_t daniel::dns::RR::RData_NSAP::ToNullStr( uint8_t * pStr , uint16_t const & length ) const
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

	ss << static_cast< uint16_t >( binlen ) ;
	std::string lenStr = ss.str() ;

	ss.str( "" ) ;
	ss.clear() ;

	for( uint16_t pos = 0 ; pos < binlen ; ++pos )
	{
		if( 0 == ( ( pos + 1 ) % 2 ) )
		{
			ss << "." ;
		}
		ss << std::hex << std::setfill( '0' ) << std::setw( 2 ) << static_cast< uint16_t >( pBinary[ pos ] ) ;
	} 
	ss << std::dec << std::setfill( ' ' ) << std::setw( 0 ) ;

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


bool daniel::dns::RR::RData_NSAP::Load( uint8_t const * pData , uint16_t const & length )
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


uint16_t daniel::dns::RR::RData_NSAP::GetLength() const
{
	return binlen ;
}


uint8_t const * daniel::dns::RR::RData_NSAP::GetBinary() const
{
	return pBinary ;
}