#pragma once

#include "Common.h"
#include "RData.h"

#include "SEC/SECHashAlgo.h"


namespace daniel
{

namespace dns
{

namespace RR
{


class RData_NSEC3PARAM : public RData
{

private :
	SEC::SECHashAlgo  hashAlgo    ;
	uint8_t           flags       ;
	uint16_t          iterations  ;
	uint8_t           saltLength  ;
	uint8_t         * pSalt       ;

private :
	void Initialize() override ;

public :
	uint16_t ToNullStr( uint8_t * pStr , uint16_t const & length ) const override ;

public :
	bool Load( uint8_t const * pData , uint16_t const & length ) override ;

public :
	SEC::SECHashAlgo GetHashAlgo() const ;

	uint8_t  GetFlags()      const ;
	uint16_t GetIterations() const ;
	uint8_t  GetSaltLength() const ;
	bool     IsOptOut()      const ;

	uint8_t  const * GetSalt() const ;

public :
	 RData_NSEC3PARAM() ;
	~RData_NSEC3PARAM() ;

} ; // class RData_NSEC3PARAM
	
	
}   // name RR

}   // namespace dns
	
}   // namespace daniel