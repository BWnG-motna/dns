#include "dns/RR/RData_PX.h"


#include <sstream>
#include <memory>


daniel::dns::RR::RData_PX::RData_PX( uint8_t const * pRef )
	: RData( pRef ) , preference( 0 ) , pMap822( nullptr ) , pMapx400( nullptr )
{

}


daniel::dns::RR::RData_PX::~RData_PX() 
{
	Initialize() ;
}


void daniel::dns::RR::RData_PX::Initialize()
{
	if( nullptr != pMap822 )
	{
		delete [] pMap822 ;
		pMap822 = nullptr ;
	}

	if( nullptr != pMapx400 )
	{
		delete [] pMapx400 ;
		pMapx400 = nullptr ;
	}

	preference = 0 ;
}


uint16_t daniel::dns::RR::RData_PX::ToNullStr( uint8_t * pStr , uint16_t const & length ) const
{
	if( nullptr == pStr || 1 > length )
	{
		return 0 ;
	}

	if( nullptr == pMap822 || nullptr == pMapx400 )
	{
		return 0 ;
	}


	std::stringstream ss ;

	ss << static_cast< uint16_t >( preference ) << " " 
	   << reinterpret_cast< char const * >( pMap822  ) << " "
	   << reinterpret_cast< char const * >( pMapx400 ) ;

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


bool daniel::dns::RR::RData_PX::Load( uint8_t const * pData , uint16_t const & length )
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

	uint16_t map822len = GetDNDataLen( & ( pData[ 2 ] ) ) ;

	if( 1 > map822len )
	{
		Initialize() ;
		return false ;
	}

	pMap822 = new ( std::nothrow ) uint8_t [ map822len + 1 ] ;
	if( nullptr == pMap822 )
	{
		Initialize() ;
		return false ;
	}

	map822len = GetDNData( pMap822 , map822len + 1 , & ( pData[ 2 ] ) ) ;

	uint16_t pos        = SkipDName( & ( pData[ 2 ] ) , length - 2 ) + 2 ;
	uint16_t mapx400len = GetDNDataLen( & ( pData[ pos ] ) ) ;

	if( 1 > mapx400len )
	{
		Initialize() ;
		return false ;
	}

	pMapx400 = new ( std::nothrow ) uint8_t [ mapx400len + 1 ] ;
	if( nullptr == pMapx400 )
	{
		Initialize() ;
		return false ;
	}

	mapx400len = GetDNData( pMapx400 , mapx400len + 1 , & ( pData[ pos ] ) ) ;

	return true ;
}


uint16_t daniel::dns::RR::RData_PX::GetPreference() const
{
	return preference ;
}


uint8_t const * daniel::dns::RR::RData_PX::GetMap822() const
{
	return pMap822 ;
}


uint8_t const * daniel::dns::RR::RData_PX::GetMapX400() const
{
	return pMapx400 ;
}