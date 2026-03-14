#pragma once

#include "Common.h"
#include "AddressFamily.h"


namespace daniel
{

namespace dns
{

namespace RR
{

namespace APL
{


class APItem
{

private :
	AddressFamily addrFamily ;
	uint8_t  prefix     ;
	uint8_t  afdLen     ;
	uint8_t  address[ 16 ] ;

public :
	void SetAddressFamily( AddressFamily const & f ) ;
	void SetAddressFamily( uint16_t const & f ) ;
	void SetPrefix( uint8_t const & n ) ;
	void SetAddress( uint8_t const * pAddr , uint8_t const & len ) ;

public :
	AddressFamily GetAddressFamily() const ;

	uint8_t  GetPrefix()         const ;
	uint8_t  GetAFDLen()         const ;
	uint8_t const * GetAddress() const ;

	bool IsNegation() const ;
	bool IsInvalid()  const ;

public :
	 APItem() ;
	 APItem( AddressFamily const & f , uint8_t const & n , uint8_t const * pAddr , uint8_t const & len ) ;
	~APItem() ;

} ; // class APItem


}   // namespace APL

}   // namespace RR

}   // namespace dns

}   // namespace daniel