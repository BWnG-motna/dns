#include "dns/RR/RData_OPENPGPKEY.h"
#include "baseEncoding/Base64.h"


#include <sstream>


daniel::dns::RR::RData_OPENPGPKEY::RData_OPENPGPKEY()
	: RData( nullptr ) , pk( nullptr ) , pklen( 0 )
{

}


daniel::dns::RR::RData_OPENPGPKEY::~RData_OPENPGPKEY()
{
	Initalize() ;
}


void daniel::dns::RR::RData_OPENPGPKEY::Initalize()
{
	if( nullptr != pk )
	{
		delete [] pk ;
		pk = nullptr ;
	}

	pklen = 0 ;
}


uint16_t daniel::dns::RR::RData_OPENPGPKEY::ToNullStr( uint8_t * pStr , uint16_t const & length ) const
{
	if( nullptr == pStr || 1 > length )
	{
		return 0 ;
	}

	if( 0 == pklen || nullptr == pk )
	{
		return 0 ;
	}

	uint16_t pBytes = 0 ;
	baseEncoding::Base64 base64 ;
	base64.Encode( reinterpret_cast< char * >( pStr ) , length , pk , pklen , true , & pBytes ) ;

	return pBytes ;
}


bool daniel::dns::RR::RData_OPENPGPKEY::Load( uint8_t const * pData , uint16_t const & length )
{
	if( nullptr == pData || 1 > length )
	{
		return false ;
	}
	
	Initalize() ;

	pk = new ( std::nothrow ) uint8_t [ length ] ;
	if( nullptr == pk )
	{
		Initalize() ;
		return false ;
	}

	pklen = length ;

	for( uint16_t pos = 0 ; pos < length ; ++pos ) 
	{
		pk[ pos ] = pData[ pos ] ;
	}

	return true ;
}


uint8_t const * daniel::dns::RR::RData_OPENPGPKEY::GetPublicKey() const
{
	return pk ;
}