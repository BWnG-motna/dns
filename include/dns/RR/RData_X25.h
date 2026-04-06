#pragma once

#include "Common.h"
#include "RData.h"


namespace daniel
{

namespace dns
{

namespace RR
{


class RData_X25 : public RData
{

private :
	uint8_t * pAddr ;

private :
	void Initialize() override ;

public :
	uint16_t ToNullStr( uint8_t * pStr , uint16_t const & length ) const override ;

public :
	bool Load( uint8_t const * pData , uint16_t const & length ) override ;

public :
	 RData_X25() ;
	~RData_X25() ;

} ; // class RData_X25
	
	
}   // name RR

}   // namespace dns
	
}   // namespace daniel