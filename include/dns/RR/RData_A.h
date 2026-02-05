#pragma once

#include "Common.h"
#include "RData.h"


namespace daniel
{

namespace dns
{

namespace RR
{


class RData_A : public RData
{

private :
	uint32_t address ; // ipv4

private :
	void Initalize() override ;

public :
	uint16_t ToNullStr( uint8_t * pStr , uint16_t const & length ) const override ;

public :
	bool Load( uint8_t const * pData , uint16_t const & length ) override ;
	void GetAddress( uint8_t ( & addr )[ 4 ] ) ;

public :
	 RData_A() ;
	~RData_A() ;

} ; // class RData_A
	
	
}   // name RR

}   // namespace dns
	
}   // namespace daniel