#pragma once

#include "Common.h"


namespace daniel
{

namespace baseEncoding
{

	
class Base32Hex
{

private :
	constexpr static uint8_t const encDat[ 32 ] =
		{  '0' , '1' , '2' , '3' , '4' , '5' , '6' , '7' , 
           '8' , '9' , 'A' , 'B' , 'C' , 'D' , 'E' , 'F' ,
           'G' , 'H' , 'I' , 'J' , 'K' , 'L' , 'M' , 'N' ,
           'O' , 'P' , 'Q' , 'R' , 'S' , 'T' , 'U' , 'V' } ;

private :
	bool Read5Bits( uint8_t & res , uint8_t const * pDat , uint16_t const & datlen , uint32_t const & bitPos ) ;

public :
	bool Encode( 
		char           * pEncDat , uint16_t const & enclen , 
		uint8_t  const * pDat    , uint16_t const & datlen ,
		bool     const & padding = false   ,
		uint16_t       * pWbytes = nullptr ) ;

	bool Decode( 
		uint8_t    * pDecDat , uint16_t const & declen , 
		char const * pDat    , uint16_t const & datlen ) ;

public :
	Base32Hex() ;
	
} ; // class Base32Hex


}   // namespace baseEncoding

}   // namespace daniel