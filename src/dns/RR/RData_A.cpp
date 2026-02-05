#include "dns/RR/RData_A.h"


#include <sstream>


daniel::dns::RR::RData_A::RData_A()
	: RData( nullptr ) , address( 0 )
{

}


daniel::dns::RR::RData_A::~RData_A()
{
	Initalize() ;
}


void daniel::dns::RR::RData_A::Initalize()
{
	address = 0 ;
}


uint16_t daniel::dns::RR::RData_A::ToNullStr( uint8_t * pStr , uint16_t const & length ) const
{
	if( nullptr == pStr || 1 > length )
	{
		return 0 ;
	}

	
	std::stringstream ss ;

	ss << static_cast< uint16_t >( ( address >> 24 ) & 0x000000FF ) << "."
	   << static_cast< uint16_t >( ( address >> 16 ) & 0x000000FF ) << "."
	   << static_cast< uint16_t >( ( address >>  8 ) & 0x000000FF ) << "."
	   << static_cast< uint16_t >( ( address >>  0 ) & 0x000000FF ) ;

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


bool daniel::dns::RR::RData_A::Load( uint8_t const * pData , uint16_t const & length )
{
	if( nullptr == pData || 1 > length )
	{
		return false ;
	}
	
	if( 4 != length )
	{
		return false ;
	}

	address = ( ( pData[ 0 ] << 24 ) & 0xFF000000 )
			| ( ( pData[ 1 ] << 16 ) & 0x00FF0000 )
			| ( ( pData[ 2 ] <<  8 ) & 0x0000FF00 )
			| ( ( pData[ 3 ] <<  0 ) & 0x000000FF ) ;

	return true ;
}


void daniel::dns::RR::RData_A::GetAddress( uint8_t ( & addr )[ 4 ] )
{
	addr[ 0 ] = static_cast< uint8_t >( ( address >> 24 ) & 0x000000FF ) ;
	addr[ 1 ] = static_cast< uint8_t >( ( address >> 16 ) & 0x000000FF ) ;
	addr[ 2 ] = static_cast< uint8_t >( ( address >>  8 ) & 0x000000FF ) ;
	addr[ 3 ] = static_cast< uint8_t >( ( address >>  0 ) & 0x000000FF ) ;
}