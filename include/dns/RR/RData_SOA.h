#pragma once

#include "Common.h"
#include "RData.h"


namespace daniel
{

namespace dns
{

namespace RR
{

class RData_SOA : public RData
{

private :
	uint8_t  mname[ 512 ] ;
	uint8_t  rname[ 512 ] ;
	uint32_t serial  ;
	uint32_t refresh ;
	uint32_t retry   ;
	uint32_t expire  ;
	uint32_t minimum ;

public :
	uint16_t ToNullStr( uint8_t * pStr , uint16_t const & length ) const override ;

public :
	bool Load( uint8_t const * pData , uint16_t const & length ) override ;

public :
	RData_SOA( uint8_t const * pRef ) ;

} ; // class RData_SOA
	
}   // name RR

}   // namespace dns
	
}   // namespace daniel