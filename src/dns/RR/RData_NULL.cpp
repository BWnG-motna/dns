#include "dns/RR/RData_NULL.h"


#include <sstream>
#include <iomanip>
#include <memory>


daniel::dns::RR::RData_NULL::RData_NULL()
	: RData( nullptr ) , binlen( 0 ) , pBinary( nullptr )
{

}


daniel::dns::RR::RData_NULL::~RData_NULL()
{
	Initalize() ;
}


void daniel::dns::RR::RData_NULL::Initalize()
{
	if( nullptr != pBinary )
	{
		delete [] pBinary ;
		pBinary = nullptr ;
	}

	binlen = 0 ;
}


uint16_t daniel::dns::RR::RData_NULL::ToNullStr( uint8_t * pStr , uint16_t const & length ) const
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

	ss << "\\# " << lenStr ;
	for( uint16_t pos = 0 ; pos < binlen ; ++pos )
	{
		ss << " " ;
		ss << std::hex << std::setfill( '0' ) << std::setw( 2 ) << static_cast< uint16_t >( pBinary[ pos ] ) ;
	} 
	ss << std::dec << std::setfill( ' ' ) << std::setw( 0 ) ;

	std::string rs = ss.str() ;
	uint32_t rslen = static_cast< uint32_t >( rs.length() ) ;
	uint16_t  rlen = ( rslen > length ) ? ( length - 1 ) : rslen ;    

	for( uint32_t pos = 0 ; pos < rlen ; ++pos )
	{
		pStr[ pos ] = rs[ pos ] ;
	}

	pStr[ rlen ] = '\0' ;

	return rlen ;
}


bool daniel::dns::RR::RData_NULL::Load( uint8_t const * pData , uint16_t const & length )
{
	if( nullptr == pData || 1 > length )
	{
		return false ;
	}

	Initalize() ;

	binlen = length ;

	pBinary = new ( std::nothrow ) uint8_t [ binlen ] ;
	if( nullptr == pBinary )
	{
		Initalize() ;
		return false ;
	}

	for( uint16_t pos = 0 ; pos < binlen ; ++pos )
	{
		pBinary[ pos ] = pData[ pos ] ;
	}

	return true ;
}


uint16_t daniel::dns::RR::RData_NULL::GetLength() const
{
	return binlen ;
}


uint8_t const * daniel::dns::RR::RData_NULL::GetBinary() const
{
	return pBinary ;
}