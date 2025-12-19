#pragma once

#include "Common.h"
#include "RData.h"


namespace daniel
{

namespace dns
{

namespace RR
{

class RData_TXT : public RData
{

private :
	uint8_t txtData[ 512 ] ;

public :
	uint16_t ToNullStr( uint8_t * pStr , uint16_t const & length ) const override ;

public :
	bool Load( uint8_t const * pData , uint16_t const & length ) override ;

public :
	RData_TXT() ;

} ; // class RData_TXT
	
}   // name RR

}   // namespace dns
	
}   // namespace daniel