#include "dns/RR/RData_NAME.h"


#include <string>
#include <memory>


daniel::dns::RR::RData_NAME::RData_NAME( uint8_t const * pRef )
	: RData( pRef ) , pDName( nullptr )
{

}


daniel::dns::RR::RData_NAME::~RData_NAME()
{
	Initalize() ;
}


void daniel::dns::RR::RData_NAME::Initalize()
{
	if( nullptr != pDName )
	{
		delete [] pDName ;
		pDName = nullptr ;
	}
}


uint16_t daniel::dns::RR::RData_NAME::ToNullStr( uint8_t * pStr , uint16_t const & length ) const
{
	if( nullptr == pStr || 1 > length )
	{
		return 0 ;
	}

	if( nullptr == pDName )
	{
		return 0 ;
	}

	std::string str( reinterpret_cast< char const * >( pDName ) ) ;
	uint16_t const len = static_cast< uint16_t >( str.length() ) ;

	for( uint16_t pos = 0 ; pos < len && pos < length ; ++pos )
	{
		pStr[ pos ] = pDName[ pos ] ;
	}

	uint16_t less = len < ( length - 1 ) ? len : ( length - 1 ) ;
	pStr[ less ] = '\0' ;

	return less ;
}


bool daniel::dns::RR::RData_NAME::Load( uint8_t const * pData , uint16_t const & length )
{
	if( nullptr == pData || 1 > length )
	{
		return false ;
	}

	uint16_t len = GetDNDataLen( pData ) ;
	if( 1 > len )
	{
		return false ;
	}

	Initalize() ;

	pDName = new ( std::nothrow ) uint8_t [ len + 1 ] ;
	if( nullptr == pDName )
	{
		Initalize() ;
		return false ;
	}
	
	GetDNData( pDName , len + 1 , pData ) ;

	return true ;
}


uint8_t const * daniel::dns::RR::RData_NAME::GetName() const
{
	return pDName ;
}