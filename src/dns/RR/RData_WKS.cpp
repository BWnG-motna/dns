#include "dns/RR/RData_WKS.h"


#include <sstream>


daniel::dns::RR::RData_WKS::RData_WKS()
	: RData( nullptr ) , address( 0 ) , protocol( 0 )
{

}


daniel::dns::RR::RData_WKS::~RData_WKS()
{
	Initalize() ;
}


void daniel::dns::RR::RData_WKS::Initalize()
{
	address  = 0 ;
	protocol = 0 ;
}


uint16_t daniel::dns::RR::RData_WKS::ToNullStr( uint8_t * pStr , uint16_t const & length ) const
{
	if( nullptr == pStr || 1 > length )
	{
		return 0 ;
	}

	
	std::stringstream ss ;

	ss << static_cast< uint16_t >( ( address >> 24 ) & 0x000000FF ) << "."
	   << static_cast< uint16_t >( ( address >> 16 ) & 0x000000FF ) << "."
	   << static_cast< uint16_t >( ( address >>  8 ) & 0x000000FF ) << "."
	   << static_cast< uint16_t >( ( address >>  0 ) & 0x000000FF ) << " "
	   << static_cast< uint16_t >( protocol ) ;

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


bool daniel::dns::RR::RData_WKS::Load( uint8_t const * pData , uint16_t const & length )
{
	if( nullptr == pData || 1 > length )
	{
		return false ;
	}
	
	if( 6 > length )
	{
		return false ;
	}

	address = ( ( pData[ 0 ] << 24 ) & 0xFF000000 )
			| ( ( pData[ 1 ] << 16 ) & 0x00FF0000 )
			| ( ( pData[ 2 ] <<  8 ) & 0x0000FF00 )
			| ( ( pData[ 3 ] <<  0 ) & 0x000000FF ) ;

	protocol = pData[ 4 ] ;

	return true ;
}