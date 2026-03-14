#pragma once

#include "Common.h"


namespace daniel
{

namespace baseEncoding
{

	
class Base64
{

private :
	constexpr static uint8_t const encDat[ 64 ] =
		{  'A' , 'B' , 'C' , 'D' , 'E' , 'F' , 'G' , 'H' , 
           'I' , 'J' , 'K' , 'L' , 'M' , 'N' , 'O' , 'P' ,
           'Q' , 'R' , 'S' , 'T' , 'U' , 'V' , 'W' , 'X' ,
           'Y' , 'Z' , 'a' , 'b' , 'c' , 'd' , 'e' , 'f' ,
           'g' , 'h' , 'i' , 'j' , 'k' , 'l' , 'm' , 'n' ,
           'o' , 'p' , 'q' , 'r' , 's' , 't' , 'u' , 'v' ,
           'w' , 'x' , 'y' , 'z' , '0' , '1' , '2' , '3' ,
           '4' , '5' , '6' , '7' , '8' , '9' , '+' , '/' } ;

private :
	bool Read6Bits( uint8_t & res , uint8_t const * pDat , uint16_t const & datlen , uint32_t const & bitPos ) ;

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
	Base64() ;
	
} ; // class Base64


}   // namespace baseEncoding

}   // namespace daniel