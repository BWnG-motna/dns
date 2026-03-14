#include "dns/RR/RData_AFSDB.h"


#include <sstream>
#include <memory>


daniel::dns::RR::RData_AFSDB::RData_AFSDB( uint8_t const * pRef )
	: RData( pRef ) , subtype( 0 ) , pHostname( nullptr )
{

}


daniel::dns::RR::RData_AFSDB::~RData_AFSDB()
{
	Initialize() ;
}


void daniel::dns::RR::RData_AFSDB::Initialize()
{
	if( nullptr != pHostname )
	{
		delete [] pHostname ;
		pHostname = nullptr ;
	}

	subtype = 0 ;
}


uint16_t daniel::dns::RR::RData_AFSDB::ToNullStr( uint8_t * pStr , uint16_t const & length ) const
{
	if( nullptr == pStr || 1 > length )
	{
		return 0 ;
	}

	if( nullptr == pHostname )
	{
		return 0 ;
	}

	
	std::stringstream ss ;

	ss << subtype << " " ;
	ss << reinterpret_cast< char const * >( pHostname ) ;
	
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


bool daniel::dns::RR::RData_AFSDB::Load( uint8_t const * pData , uint16_t const & length )
{
	if( nullptr == pData || 1 > length )
	{
		return false ;
	}
	
	if( 3 > length )
	{
		return false ;
	}

	Initialize() ;

	subtype 
		= ( ( pData[ 0 ] << 8 ) & 0xFF00 )
		| ( ( pData[ 1 ] << 0 ) & 0x00FF ) ;

	uint16_t   hostlen = GetDNDataLen( & ( pData[ 3 ] ) ) ;
	uint16_t allocSize = ( 0 < hostlen ) ? ( hostlen + 1 ) : 2 ;

	pHostname = new ( std::nothrow ) uint8_t [ allocSize ] ;
	if( nullptr == pHostname )
	{
		Initialize() ;
		return false ;
	}

	if( 0 < hostlen )
	{
		GetDNData( pHostname , hostlen , & ( pData[ 2 ] ) ) ;
	}
	else
	{
		pHostname[ 0 ] = '.'  ;
		pHostname[ 1 ] = '\0' ;
	}

	return true ;
}


uint16_t daniel::dns::RR::RData_AFSDB::GetSubtype() const
{
	return subtype ;
}


uint8_t const * daniel::dns::RR::RData_AFSDB::GetHostname() const
{
	return pHostname ;
}