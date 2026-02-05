#pragma once

#include "Common.h"
#include "RData.h"
#include "SEC/TypeBitMap.h" 
#include "SEC/SECHashAlgo.h"

#include "ds/LinkedList.h"


namespace daniel
{

namespace dns
{

namespace RR
{


class RData_NSEC3 : public RData
{

private :
	SEC::SECHashAlgo  hashAlgo    ;
	uint8_t           flags       ;
	uint16_t          iterations  ;
	uint8_t           saltLength  ;
	uint8_t         * pSalt       ;
	uint8_t         * pOwnerName  ;

	ds::LinkedList< SEC::TypeBitMap > * pTbm ;

	uint8_t ownerNameLen ;

private :
	mutable uint16_t * pTypes ;

private :
	bool SetType( uint8_t const & window , uint8_t const & type ) ;

private :
	void Initalize() override ;

public :
	uint16_t ToNullStr( uint8_t * pStr , uint16_t const & length ) const override ;

public :
	bool Load( uint8_t const * pData , uint16_t const & length ) override ;

public :
	SEC::SECHashAlgo GetHashAlgo() const ;

	uint8_t  GetFlags()           const ;
	uint16_t GetIterations()      const ;
	uint8_t  GetSaltLength()      const ;
	uint8_t  GetOwnerNameLength() const ;
	uint16_t GetTypeCount()       const ;
	bool     IsOptOut()           const ;

	uint8_t  const * GetSalt()      const ;
	uint8_t  const * GetOwnerName() const ;

	uint16_t const * GetTypes()     const ;

public :
	 RData_NSEC3() ;
	~RData_NSEC3() ;

} ; // class RData_NSEC3
	
	
}   // name RR

}   // namespace dns
	
}   // namespace daniel