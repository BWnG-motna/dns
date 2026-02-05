#pragma once

#include "Common.h"
#include "RData.h"


namespace daniel
{

namespace dns
{

namespace RR
{


class RData_WKS : public RData
{

private :
	uint32_t address ;
	uint8_t  protocol ;

private :
	void Initalize() override ;

public :
	uint16_t ToNullStr( uint8_t * pStr , uint16_t const & length ) const override ;

public :
	bool Load( uint8_t const * pData , uint16_t const & length ) override ;

public :
	 RData_WKS() ;
	~RData_WKS() ;

} ; // class RData_WKS
	
	
}   // name RR

}   // namespace dns
	
}   // namespace daniel