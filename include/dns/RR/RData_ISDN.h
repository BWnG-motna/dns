#pragma once

#include "Common.h"
#include "RData.h"


namespace daniel
{

namespace dns
{

namespace RR
{


class RData_ISDN : public RData
{

private :
	uint8_t * pAddr ;
	uint8_t * pSA   ;

private :
	void Initialize() override ;

public :
	uint16_t ToNullStr( uint8_t * pStr , uint16_t const & length ) const override ;

public :
	bool Load( uint8_t const * pData , uint16_t const & length ) override ;

public :
	uint8_t const * GetAddress() const ;
	uint8_t const * GetSA()      const ;

public :
	 RData_ISDN() ;
	~RData_ISDN() ;

} ; // class RData_ISDN
	
	
}   // name RR

}   // namespace dns
	
}   // namespace daniel