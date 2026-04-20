#pragma once

#include "Common.h"
#include "RData.h"
#include "CLA/Label.h"

#include "ds/LinkedList.h"


namespace daniel
{

namespace dns
{

namespace RR
{


class RData_CLA : public RData
{

private :
	ds::LinkedList< CLA::Label > * pLabelList ;

private :
	void Initialize() override ;
	
public :
	uint16_t ToNullStr( uint8_t * pStr , uint16_t const & length ) const override ;

public :
	bool Load( uint8_t const * pData , uint16_t const & length ) override ;

public :
	uint8_t const * GetStrData() const ;

public :
	 RData_CLA() ;
	~RData_CLA() ;

} ; // class RData_CLA
	
	
}   // name RR

}   // namespace dns
	
}   // namespace daniel