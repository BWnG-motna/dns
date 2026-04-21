#pragma once

#include "Common.h"
#include "RData.h"


namespace daniel
{

namespace dns
{

namespace RR
{


class RData_L32 : public RData
{

private :
	uint32_t locator ;

private :
	void Initialize() override ;

public :
	uint16_t ToNullStr( uint8_t * pStr , uint16_t const & length ) const override ;

public :
	bool Load( uint8_t const * pData , uint16_t const & length ) override ;

public :
	uint32_t GetLocator() const ;

public :
	 RData_L32() ;
	~RData_L32() ;

} ; // class RData_L32
	
	
}   // name RR

}   // namespace dns
	
}   // namespace daniel