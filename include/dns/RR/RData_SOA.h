#pragma once

#include "Common.h"
#include "RData.h"


namespace daniel
{

namespace dns
{

namespace RR
{


class RData_SOA : public RData
{

private :
	uint8_t * pMname  ;
	uint8_t * pRname  ;
	uint32_t  serial  ;
	uint32_t  refresh ;
	uint32_t  retry   ;
	uint32_t  expire  ;
	uint32_t  minimum ;

private :
	void Initalize() override ;

public :
	uint16_t ToNullStr( uint8_t * pStr , uint16_t const & length ) const override ;

public :
	bool Load( uint8_t const * pData , uint16_t const & length ) override ;

public :
	uint8_t const * GetMName() const ;
	uint8_t const * GetRName() const ;

	uint32_t GetSerial()  const ;
	uint32_t GetRefresh() const ;
	uint32_t GetRetry()   const ;
	uint32_t GetExpire()  const ;
	uint32_t GetMinimum() const ;

public :
	 RData_SOA( uint8_t const * pRef ) ;
	~RData_SOA() ;

} ; // class RData_SOA
	
	
}   // name RR

}   // namespace dns
	
}   // namespace daniel