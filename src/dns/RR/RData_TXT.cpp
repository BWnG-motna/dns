#include "dns/RR/RData_TXT.h"


#include <cstring>


daniel::dns::RR::RData_TXT::RData_TXT()
	: RData( nullptr )
{
	txtData[ 0 ] = '\0' ;
}


uint16_t daniel::dns::RR::RData_TXT::ToNullStr( uint8_t * pStr , uint16_t const & length ) const
{
	if( nullptr == pStr || 1 > length )
	{
		return 0 ;
	}

	uint16_t len = static_cast< uint16_t >( strlen( reinterpret_cast< char const * >( txtData ) ) ) ;

	for( uint16_t pos = 0 ; pos < len && pos < length ; ++pos )
	{
		pStr[ pos ] = txtData[ pos ] ;
	}

	uint16_t less = len < ( length - 1 ) ? len : ( length - 1 ) ;
	pStr[ less ] = '\0' ;

	return less ;
}


bool daniel::dns::RR::RData_TXT::Load( uint8_t const * pData , uint16_t const & length )
{
	if( nullptr == pData || 1 > length )
	{
		return false ;
	}

	uint16_t bPos = 0 ;
	uint16_t rPos = 0 ;

	while( rPos < length )
	{
		if( bPos >= ( 512 - 1 ) )
		{
			break ;
		}

		uint8_t len = pData[ rPos++ ] ;

		if( ( bPos + len + 2 ) > ( 512 - 1 ) )
		{
			break ;
		}

		if( 0 != bPos )
		{
			txtData[ bPos++ ] = ' ' ;
		}

		txtData[ bPos++ ] = '\"' ;

		for( uint8_t lpos = 0 ; lpos < len ; ++lpos )
		{
			txtData[ bPos++ ] = pData[ rPos++ ] ; 
		}

		txtData[ bPos++ ] = '\"' ;
	}

	txtData[ bPos++ ] = '\0' ;

	return true ;
}


uint8_t const * daniel::dns::RR::RData_TXT::GetTxtData() const
{
	return txtData ;
}