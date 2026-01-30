#pragma once

#include "Common.h"
#include "RData.h"


namespace daniel
{

namespace dns
{

namespace RR
{


class RData_NAME : public RData
{

private :
	uint8_t dname[ 512 ] ;

public :
	uint16_t ToNullStr( uint8_t * pStr , uint16_t const & length ) const override ;

public :
	bool Load( uint8_t const * pData , uint16_t const & length ) override ;
	uint8_t const * GetName() const ;

public :
	RData_NAME( uint8_t const * pRef ) ;

} ; // class RData_NAME
	
	
}   // name RR

}   // namespace dns
	
}   // namespace daniel