#pragma once

#include "Common.h"
#include "RData.h"


namespace daniel
{

namespace dns
{

namespace RR
{

class RData_DNAME : public RData
{

private :
	uint8_t dname[ 512 ] ;

public :
	uint16_t ToNullStr( uint8_t * pStr , uint16_t const & length ) const override ;

public :
	bool Load( uint8_t const * pData , uint16_t const & length ) override ;
	uint8_t const * GetDName() const ;

public :
	RData_DNAME( uint8_t const * pRef ) ;

} ; // class RData_DNAME
	
}   // name RR

}   // namespace dns
	
}   // namespace daniel