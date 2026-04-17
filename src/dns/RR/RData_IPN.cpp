#include "dns/RR/RData_IPN.h"


#include <sstream>


daniel::dns::RR::RData_IPN::RData_IPN()
	: RData( nullptr ) , nodeNumber( 0 )
{

}


daniel::dns::RR::RData_IPN::~RData_IPN()
{
	Initialize() ;
}


void daniel::dns::RR::RData_IPN::Initialize()
{
	nodeNumber = 0 ;
}


uint16_t daniel::dns::RR::RData_IPN::ToNullStr( uint8_t * pStr , uint16_t const & length ) const
{
	if( nullptr == pStr || 1 > length )
	{
		return 0 ;
	}

	
	std::stringstream ss ;

	ss << nodeNumber ;

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


bool daniel::dns::RR::RData_IPN::Load( uint8_t const * pData , uint16_t const & length )
{
	if( nullptr == pData || 1 > length )
	{
		return false ;
	}
	
	if( 8 != length )
	{
		return false ;
	}

	nodeNumber = ( ( static_cast< uint64_t >( pData[ 0 ] ) << 56 ) & 0xFF00000000000000ULL )
			   | ( ( static_cast< uint64_t >( pData[ 1 ] ) << 48 ) & 0x00FF000000000000ULL )
			   | ( ( static_cast< uint64_t >( pData[ 2 ] ) << 40 ) & 0x0000FF0000000000ULL )
			   | ( ( static_cast< uint64_t >( pData[ 3 ] ) << 32 ) & 0x000000FF00000000ULL )
	           | ( ( static_cast< uint64_t >( pData[ 4 ] ) << 24 ) & 0x00000000FF000000ULL )
			   | ( ( static_cast< uint64_t >( pData[ 5 ] ) << 16 ) & 0x0000000000FF0000ULL )
			   | ( ( static_cast< uint64_t >( pData[ 6 ] ) <<  8 ) & 0x000000000000FF00ULL )
			   | ( ( static_cast< uint64_t >( pData[ 7 ] ) <<  0 ) & 0x00000000000000FFULL ) ;

	return true ;
}


uint64_t daniel::dns::RR::RData_IPN::GetNodeNumber() const
{
	return nodeNumber ;
}