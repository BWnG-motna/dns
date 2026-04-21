#include "dns/RR/RData_LP.h"


#include <sstream>
#include <memory>


daniel::dns::RR::RData_LP::RData_LP( uint8_t const * pRef )
	: RData( pRef ) , preference( 0 ) , pLocator( nullptr )
{

}


daniel::dns::RR::RData_LP::~RData_LP() 
{
	Initialize() ;
}


void daniel::dns::RR::RData_LP::Initialize()
{
	if( nullptr != pLocator )
	{
		delete [] pLocator ;
		pLocator = nullptr ;
	}

	preference = 0 ;
}


uint16_t daniel::dns::RR::RData_LP::ToNullStr( uint8_t * pStr , uint16_t const & length ) const
{
	if( nullptr == pStr || 1 > length )
	{
		return 0 ;
	}

	if( nullptr == pLocator )
	{
		return 0 ;
	}


	std::stringstream ss ;

	ss << static_cast< uint16_t >( preference ) << " " << reinterpret_cast< char const * >( pLocator ) ;

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


bool daniel::dns::RR::RData_LP::Load( uint8_t const * pData , uint16_t const & length )
{
	if( nullptr == pData || 1 > length )
	{
		return false ;
	}
	
	if( 2 > length )
	{
		return false ;
	}

	Initialize() ;

	preference
		= ( ( pData[ 0 ] << 8 ) & 0xFF00 )
		| ( ( pData[ 1 ] << 0 ) & 0x00FF ) ;

	uint16_t len = GetDNDataLen( & ( pData[ 2 ] ) ) ;

	if( 1 > len )
	{
		Initialize() ;
		return false ;
	}

	pLocator = new ( std::nothrow ) uint8_t [ len + 1 ] ;
	if( nullptr == pLocator )
	{
		Initialize() ;
		return false ;
	}

	len = GetDNData( pLocator , len + 1 , & ( pData[ 2 ] ) ) ;

	return true ;
}


uint16_t daniel::dns::RR::RData_LP::GetPreference() const
{
	return preference ;
}


uint8_t const * daniel::dns::RR::RData_LP::GetLocator() const
{
	return pLocator ;
}