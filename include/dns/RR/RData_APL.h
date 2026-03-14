#pragma once

#include "Common.h"
#include "RData.h"

#include "APL/APItem.h"
#include "ds/LinkedList.h"


namespace daniel
{

namespace dns
{

namespace RR
{


class RData_APL : public RData
{

private :
	ds::LinkedList< APL::APItem > * pItem ;

private :
	void Initialize() override ;

public :
	uint16_t ToNullStr( uint8_t * pStr , uint16_t const & length ) const override ;

public :
	bool Load( uint8_t const * pData , uint16_t const & length ) override ;

public :
	 RData_APL() ;
	~RData_APL() ;

} ; // class RData_APL
	
	
}   // name RR

}   // namespace dns
	
}   // namespace daniel