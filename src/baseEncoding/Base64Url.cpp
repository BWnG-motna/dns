#include "baseEncoding/Base64Url.h"


daniel::baseEncoding::Base64Url::Base64Url()
{

}


bool daniel::baseEncoding::Base64Url::Encode( 
	char           * pEncDat , uint16_t const & enclen , 
	uint8_t  const * pDat    , uint16_t const & datlen ,
	bool     const & padding , 
	uint16_t       * pWbytes )
{
	if( nullptr == pEncDat || 1 > enclen )
	{
		return false ;
	}

	if( nullptr == pDat || 1 > datlen )
	{
		return false ;
	}

	if( nullptr != pWbytes )
	{
		*pWbytes = 0 ;
	}

	uint32_t bitPos    = 0 ;
	uint32_t bitMaxPos = static_cast< uint32_t >( datlen ) * 8 ;

	uint16_t encPos = 0 ;

	while( bitPos < bitMaxPos && encPos < enclen )
	{
		uint8_t bits = 0x00 ;
		
		if( false == Read6Bits( bits , pDat , datlen , bitPos ) )
		{
			return false ;
		}

		if( 63 < bits )
		{
			return false ;
		}

		pEncDat[ encPos++ ] = encDat[ bits ] ;

		bitPos += 6 ;
	}

	if( bitPos < bitMaxPos )
	{
		return false ;
	}

	if( nullptr != pWbytes )
	{
		*pWbytes = encPos ;
	}

	while( padding && ( 0 != encPos % 4 ) && ( encPos < enclen ) )
	{
		pEncDat[ encPos++ ] = '=' ;
	}

	if( padding && ( 0 != encPos % 4 ) )
	{
		return false ;
	}

	return true ;
}


bool daniel::baseEncoding::Base64Url::Read6Bits( uint8_t & res , uint8_t const * pDat , uint16_t const & datlen , uint32_t const & bitPos )
{
	if( nullptr == pDat || 1 > datlen )
	{
		return false ;
	}

	uint32_t bitMaxPos = static_cast< uint32_t >( datlen ) * 8 ;
	if( bitMaxPos < bitPos + 5 )
	{
		return false ;
	}

	uint16_t bytePos = bitPos / 8 ;
	 int16_t ibitPos = 7 - ( bitPos % 8 ) ;

	res = 0 ;
	uint8_t shiftPos = 5 ;
	for( int16_t pos = ibitPos ; pos >= 0 && shiftPos >= 0 ; --pos )
	{
		res |= 0 < ( pDat[ bytePos ] & ( 0x01U << pos ) ) ? ( 0x01U << shiftPos ) : 0 ; 
		--shiftPos ;
	}

	if( 5 > ibitPos && datlen > ( bytePos + 1 ) )
	{
		++bytePos ;
		for( int16_t pos = 7 ; pos >= 0 && shiftPos >= 0 ; --pos )
		{
			res |= 0 < ( pDat[ bytePos ] & ( 0x01U << pos ) ) ? ( 0x01U << shiftPos ) : 0 ; 
			--shiftPos ;
		}
	}

	res &= 0x3F ;

	return true ;  
}