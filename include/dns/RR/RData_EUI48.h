#pragma once

#include "Common.h"
#include "RData.h"


namespace daniel
{

namespace dns
{

namespace RR
{


class RData_EUI48 : public RData
{

private :
	static constexpr uint8_t addrMaxLen = 6 ;

private :
	uint8_t address[ addrMaxLen ] ;

private :
	void Initialize() override ;

public :
	uint16_t ToNullStr( uint8_t * pStr , uint16_t const & length ) const override ;

public :
	bool Load( uint8_t const * pData , uint16_t const & length ) override ;
	void GetAddress( uint8_t ( & addr )[ addrMaxLen ] ) ;

public :
	 RData_EUI48() ;
	~RData_EUI48() ;

} ; // class RData_EUI48
	
	
}   // name RR

}   // namespace dns
	
}   // namespace daniel