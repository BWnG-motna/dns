#pragma once

#include "Common.h"
#include "RData.h"

#include "ds/LinkedList.h"


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
	
	ds::LinkedList< uint16_t > * pPorts ;

private :
	void Initialize() override ;

private :
	char const * GetServiceName( uint16_t const & port ) const ;

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