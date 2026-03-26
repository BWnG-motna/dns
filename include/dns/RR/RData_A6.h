#pragma once

#include "Common.h"
#include "RData.h"


namespace daniel
{

namespace dns
{

namespace RR
{


class RData_A6 : public RData
{

private :
	uint8_t   prefixLen  ;
	uint8_t   addrSuffix[ 16 ] ;
	uint8_t * prefix ;

private :
	uint8_t   addrSuffixBeg = 0 ;

private :
	void Initialize() override ;

public :
	uint16_t ToNullStr( uint8_t * pStr , uint16_t const & length ) const override ;

public :
	bool Load( uint8_t const * pData , uint16_t const & length ) override ;

public :


public :
	 RData_A6() ;
	~RData_A6() ;

} ; // class RData_A6
	
	
}   // name RR

}   // namespace dns
	
}   // namespace daniel