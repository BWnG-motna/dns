#pragma once

#include "Common.h"
#include "RData.h"

#include "HHIT/CDDL.h"


namespace daniel
{

namespace dns
{

namespace RR
{


class RData_HHIT : public RData
{

private :
	HHIT::CDDL cddl ;

private :
	void Initialize() override ;

public :
	uint16_t ToNullStr( uint8_t * pStr , uint16_t const & length ) const override ;

public :
	bool Load( uint8_t const * pData , uint16_t const & length ) override ;

public :
	 RData_HHIT() ;
	~RData_HHIT() ;

} ; // class RData_HHIT
	
	
}   // name RR

}   // namespace dns
	
}   // namespace daniel