#include "dns/RR/RData_NINFO.h"


#include <string>
#include <memory>


daniel::dns::RR::RData_NINFO::RData_NINFO()
	: RData( nullptr ) , pZsData( nullptr )
{

}


daniel::dns::RR::RData_NINFO::~RData_NINFO()
{
	Initialize() ;
}


void daniel::dns::RR::RData_NINFO::Initialize()
{
	if( nullptr != pZsData )
	{
		delete [] pZsData ;
		pZsData = nullptr ;
	}
}


uint16_t daniel::dns::RR::RData_NINFO::ToNullStr( uint8_t * pStr , uint16_t const & length ) const
{
	if( nullptr == pStr || 1 > length )
	{
		return 0 ;
	}

	if( nullptr == pZsData )
	{
		return 0 ;
	}

	std::string str( reinterpret_cast< char const * >( pZsData ) ) ;
	uint16_t len = static_cast< uint16_t >( str.length() ) ;

	for( uint16_t pos = 0 ; pos < len && pos < length ; ++pos )
	{
		pStr[ pos ] = pZsData[ pos ] ;
	}

	uint16_t less = len < ( length - 1 ) ? len : ( length - 1 ) ;
	pStr[ less ] = '\0' ;

	return less ;
}


bool daniel::dns::RR::RData_NINFO::Load( uint8_t const * pData , uint16_t const & length )
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
	pZsData = new ( std::nothrow ) uint8_t [ tLen + ( 3 * tCnt ) ] ;                                    
	if( nullptr == pZsData )
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
			pZsData[ bPos++ ] = ' ' ;
		}

		pZsData[ bPos++ ] = '\"' ;

		for( uint8_t lpos = 0 ; lpos < len ; ++lpos )
		{
			pZsData[ bPos++ ] = pData[ rPos++ ] ; 
		}

		pZsData[ bPos++ ] = '\"' ;
	}

	pZsData[ bPos++ ] = '\0' ;

	return true ;
}


uint8_t const * daniel::dns::RR::RData_NINFO::GetZSData() const
{
	return pZsData ;
}