#pragma once

#include "Common.h"
#include "RData.h"

#include "HIP/RVS.h"
#include "ds/LinkedList.h"


namespace daniel
{

namespace dns
{

namespace RR
{


class RData_HIP : public RData
{

private :
	uint8_t   hitLen ;
	uint8_t   pkAlgo ;
	uint16_t  pkLen  ;
	uint8_t * pHit   ;
	uint8_t * pKey   ;

	ds::LinkedList< HIP::RVS > * pRvsList ;

private :
	void Initialize() override ;

public :
	uint16_t ToNullStr( uint8_t * pStr , uint16_t const & length ) const override ;

public :
	bool Load( uint8_t const * pData , uint16_t const & length ) override ;

public :
	uint8_t  GetHitLen() const ;
	uint8_t  GetPkAlgo() const ;
	uint16_t GetPkLen()  const ;

	uint8_t const * GetHit()  const ;
	uint8_t const * GetPKey() const ;

public :
	 RData_HIP() ;
	~RData_HIP() ;

} ; // class RData_HIP
	
	
}   // name RR

}   // namespace dns
	
}   // namespace daniel