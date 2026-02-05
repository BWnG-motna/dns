#pragma once

#include "Common.h"
#include "RData.h"


namespace daniel
{

namespace dns
{

namespace RR
{


class RData_HINFO : public RData
{

private :
	uint8_t * pCPU ;
	uint8_t * pOS  ;

private :
	void Initalize() override ;

public :
	uint16_t ToNullStr( uint8_t * pStr , uint16_t const & length ) const override ;

public :
	bool Load( uint8_t const * pData , uint16_t const & length ) override ;
	uint8_t const * GetCPUInfo() const ;
	uint8_t const * GetOSInfo()  const ;

public :
	 RData_HINFO( uint8_t const * pRef ) ;
	~RData_HINFO() ;

} ; // class RData_HINFO

	
}   // name RR

}   // namespace dns
	
}   // namespace daniel