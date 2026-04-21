#include "dns/RR/RData_NID.h"


#include <sstream>
#include <iomanip>


daniel::dns::RR::RData_NID::RData_NID()
	: RData( nullptr ) , preference( 0 ) , nodeID( 0 )
{

}


daniel::dns::RR::RData_NID::~RData_NID() 
{
	Initialize() ;
}


void daniel::dns::RR::RData_NID::Initialize()
{
	preference = 0 ;
	nodeID     = 0 ;
}


uint16_t daniel::dns::RR::RData_NID::ToNullStr( uint8_t * pStr , uint16_t const & length ) const
{
	if( nullptr == pStr || 1 > length )
	{
		return 0 ;
	}


	std::stringstream ss ;

	ss << static_cast< uint16_t >( preference ) << "\t" ;

	for( int8_t pos = 3 ; pos >= 0 ; --pos )
	{
		uint16_t val = static_cast< uint16_t >( nodeID >> ( pos * 16 ) ) ;

		if( 3 != pos )
		{
			ss << ":" ;
		}
		ss << std::hex << std::setw( 4 ) << std::setfill( '0' ) << val ;
	}

	ss << std::dec << std::setw( 0 ) ;


	std::string str = ss.str() ;
	uint16_t len = static_cast< uint16_t >( str.length() ) ;

	for( uint16_t pos = 0 ; pos < length && pos < len ; ++pos ) 
	{
		pStr[ pos ] = str[ pos ] ;
	}

	uint16_t less = len < ( length - 1 ) ? len : ( length - 1 ) ;
	pStr[ less ] = '\0' ;

	return less ;
}


bool daniel::dns::RR::RData_NID::Load( uint8_t const * pData , uint16_t const & length )
{
	if( nullptr == pData || 1 > length )
	{
		return false ;
	}
	
	if( 10 != length )
	{
		return false ;
	}

	Initialize() ;

	preference
		= ( ( pData[ 0 ] << 8 ) & 0xFF00 )
		| ( ( pData[ 1 ] << 0 ) & 0x00FF ) ;

	nodeID = ( ( static_cast< uint64_t >( pData[ 2 ] ) << 56 ) & 0xFF00000000000000 )
		   | ( ( static_cast< uint64_t >( pData[ 3 ] ) << 48 ) & 0x00FF000000000000 )
		   | ( ( static_cast< uint64_t >( pData[ 4 ] ) << 40 ) & 0x0000FF0000000000 )
		   | ( ( static_cast< uint64_t >( pData[ 5 ] ) << 32 ) & 0x000000FF00000000 )
	       | ( ( static_cast< uint64_t >( pData[ 6 ] ) << 24 ) & 0x00000000FF000000 )
		   | ( ( static_cast< uint64_t >( pData[ 7 ] ) << 16 ) & 0x0000000000FF0000 )
		   | ( ( static_cast< uint64_t >( pData[ 8 ] ) <<  8 ) & 0x000000000000FF00 )
		   | ( ( static_cast< uint64_t >( pData[ 9 ] ) <<  0 ) & 0x00000000000000FF ) ;

	return true ;
}


uint16_t daniel::dns::RR::RData_NID::GetPreference() const
{
	return preference ;
}


uint64_t daniel::dns::RR::RData_NID::GetNodeID() const
{
	return nodeID ;
}