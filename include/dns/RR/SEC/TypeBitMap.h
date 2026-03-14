#pragma once

#include "Common.h"


namespace daniel
{

namespace dns
{

namespace RR
{

namespace SEC
{


class TypeBitMap
{

private :
	uint8_t  winNo ;
	uint8_t  len   ;
	uint8_t  bitmap[ 32 ] ;
	bool     isSet ;

private :
	uint16_t types[ 256 ] ;
	uint8_t  typeCount ;

public :

	void    SetBit( uint16_t const & qtype , bool const & isSet = true ) ;

	bool    IsSet()  const ;
	uint8_t GetNo()  const ;
	uint8_t GetLen() const ;
	bool    GetBit( uint16_t const & qtype ) const ;

	uint8_t GetSetCount() const ;
	uint16_t const * GetTypes() const ;

public :
	TypeBitMap() ;

} ; // class TypeBitMap


}   // namespace SEC

}   // namespace RR

}   // namespace dns

}   // namespace daniel