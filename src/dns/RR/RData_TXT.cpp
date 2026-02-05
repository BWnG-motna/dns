#include "dns/RR/RData_TXT.h"


#include <string>


daniel::dns::RR::RData_TXT::RData_TXT()
	: RData( nullptr ) , pTxtData( nullptr )
{

}


daniel::dns::RR::RData_TXT::~RData_TXT()
{
	Initalize() ;
}


void daniel::dns::RR::RData_TXT::Initalize()
{
	if( nullptr != pTxtData )
	{
		delete [] pTxtData ;
		pTxtData = nullptr ;
	}
}


uint16_t daniel::dns::RR::RData_TXT::ToNullStr( uint8_t * pStr , uint16_t const & length ) const
{
	if( nullptr == pStr || 1 > length )
	{
		return 0 ;
	}

	if( nullptr == pTxtData )
	{
		return 0 ;
	}

	std::string str( reinterpret_cast< char const * >( pTxtData ) ) ;
	uint16_t len = static_cast< uint16_t >( str.length() ) ;

	for( uint16_t pos = 0 ; pos < len && pos < length ; ++pos )
	{
		pStr[ pos ] = pTxtData[ pos ] ;
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

	Initalize() ;

	// each term "\" * 2 + ' '   // first term has no ' ' but this space is used for '\0'
	pTxtData = new ( std::nothrow ) uint8_t [ tLen + ( 3 * tCnt ) ] ;                                    
	if( nullptr == pTxtData )
	{
		Initalize() ;
		return false ;
	}

	rPos = 0 ;
	bPos = 0 ;

	while( rPos < length )
	{
		uint8_t len = pData[ rPos++ ] ;

		if( 0 != bPos )
		{
			pTxtData[ bPos++ ] = ' ' ;
		}

		pTxtData[ bPos++ ] = '\"' ;

		for( uint8_t lpos = 0 ; lpos < len ; ++lpos )
		{
			pTxtData[ bPos++ ] = pData[ rPos++ ] ; 
		}

		pTxtData[ bPos++ ] = '\"' ;
	}

	pTxtData[ bPos++ ] = '\0' ;

	return true ;
}


uint8_t const * daniel::dns::RR::RData_TXT::GetTxtData() const
{
	return pTxtData ;
}