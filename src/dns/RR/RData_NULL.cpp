#include "dns/RR/RData_NULL.h"


#include <sstream>
#include <iomanip>


daniel::dns::RR::RData_NULL::RData_NULL()
	: RData( nullptr ) , binlen( 0 ) 
{
	binary[ 0 ] = '\0' ;
}


uint16_t daniel::dns::RR::RData_NULL::ToNullStr( uint8_t * pStr , uint16_t const & length ) const
{
	if( nullptr == pStr || 1 > length )
	{
		return 0 ;
	}

	std::stringstream ss ;

	ss << static_cast< uint16_t >( binlen ) ;
	std::string lenStr = ss.str() ;

	ss.str( "" ) ;
	ss.clear() ;

	ss << "\\# " << lenStr << " " ;
	for( uint16_t pos = 0 ; pos < binlen ; ++pos )
	{
		if( 0 != pos )
		{
			ss << " " ;
		}
		ss << std::hex << std::setfill( '0' ) << std::setw( 2 ) << binary[ pos ] ;
	} 
	ss << std::dec << std::setfill( ' ' ) << std::setw( 0 ) ;

	std::string rs = ss.str() ;
	uint32_t rslen = static_cast< uint32_t >( rs.length() ) ;
	uint16_t rlen = ( rslen > length ) ? ( length - 1 ) : rslen ;    

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

	for( uint16_t pos = 0 ; pos < length ; ++pos )
	{
		binary[ pos ] = pData[ pos ] ;
	}

	binlen = length ;

	return true ;
}