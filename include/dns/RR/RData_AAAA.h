#pragma once

#include "Common.h"
#include "RData.h"


namespace daniel
{

namespace dns
{

namespace RR
{


class RData_AAAA : public RData
{

private :
	uint16_t address[ 8 ] ; // ipv6

private :
	void Initalize() override ;

public :
	uint16_t ToNullStr( uint8_t * pStr , uint16_t const & length ) const override ;

public :
	bool Load( uint8_t const * pData , uint16_t const & length ) override ;
	void GetAddress( uint16_t ( & addr )[ 8 ] ) ;

public :
	 RData_AAAA() ;
	~RData_AAAA() ;

} ; // class RData_AAAA
	
	
}   // name RR

}   // namespace dns
	
}   // namespace daniel