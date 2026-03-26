#include "dns/RR/RData_SPF.h"


#include <string>
#include <memory>


daniel::dns::RR::RData_SPF::RData_SPF()
	: RData( nullptr ) , pSpfData( nullptr )
{

}


daniel::dns::RR::RData_SPF::~RData_SPF()
{
	Initialize() ;
}


void daniel::dns::RR::RData_SPF::Initialize()
{
	if( nullptr != pSpfData )
	{
		delete [] pSpfData ;
		pSpfData = nullptr ;
	}
}


uint16_t daniel::dns::RR::RData_SPF::ToNullStr( uint8_t * pStr , uint16_t const & length ) const
{
	if( nullptr == pStr || 1 > length )
	{
		return 0 ;
	}

	if( nullptr == pSpfData )
	{
		return 0 ;
	}

	std::string str( reinterpret_cast< char const * >( pSpfData ) ) ;
	uint16_t len = static_cast< uint16_t >( str.length() ) ;

	for( uint16_t pos = 0 ; pos < len && pos < length ; ++pos )
	{
		pStr[ pos ] = pSpfData[ pos ] ;
	}

	uint16_t less = len < ( length - 1 ) ? len : ( length - 1 ) ;
	pStr[ less ] = '\0' ;

	return less ;
}


bool daniel::dns::RR::RData_SPF::Load( uint8_t const * pData , uint16_t const & length )
{
	if( nullptr == pData || 1 > length )
	{
		return false ;
	}


	uint16_t tCnt = 0 ;
	uint16_t tLen = 0 ;
	uint16_t rPos = 0 ;
	uint16_t bPos = 0 ;

	while( rPos < length )
	{
		uint8_t len = pData[ rPos++ ] ;
		tLen += len ;
		++tCnt ; 

		rPos += len ;
	}

	Initialize() ;

	// each term "\" * 2 + ' '   // first term has no ' ' but this space is used for '\0'
	pSpfData = new ( std::nothrow ) uint8_t [ tLen + ( 3 * tCnt ) ] ;                                    
	if( nullptr == pSpfData )
	{
		Initialize() ;
		return false ;
	}

	rPos = 0 ;
	bPos = 0 ;

	while( rPos < length )
	{
		uint8_t len = pData[ rPos++ ] ;

		if( 0 != bPos )
		{
			pSpfData[ bPos++ ] = ' ' ;
		}

		pSpfData[ bPos++ ] = '\"' ;

		for( uint8_t lpos = 0 ; lpos < len ; ++lpos )
		{
			pSpfData[ bPos++ ] = pData[ rPos++ ] ; 
		}

		pSpfData[ bPos++ ] = '\"' ;
	}

	pSpfData[ bPos++ ] = '\0' ;

	return true ;
}


uint8_t const * daniel::dns::RR::RData_SPF::GetSpfData() const
{
	return pSpfData ;
}