#pragma once

#include "Common.h"
#include "RData.h"
#include "dns/QType.h"
#include "SECAlgo.h"


namespace daniel
{

namespace dns
{

namespace RR
{

class RData_RRSIG : public RData
{

private :
	static constexpr uint16_t const signMaxLen = 1024 ;

private :
	QType    typeCovered ;
	SECAlgo  algorithm   ;
	uint8_t  labels      ;
	uint32_t ttl         ;
	uint32_t expiration  ;
	uint32_t inception   ;
	uint16_t keyTag      ;
	uint8_t  name[  512 ] ;
	uint8_t  sign[ signMaxLen ] ;

	uint16_t signLen ;

public :
	uint16_t ToNullStr( uint8_t * pStr , uint16_t const & length ) const override ;

public :
	bool Load( uint8_t const * pData , uint16_t const & length ) override ;

public :
	QType    GetTypeCovered() const ;
	SECAlgo  GetAlgorithm()   const ;
	
	uint8_t  GetLabels()     const ;
	uint32_t GetTTL()        const ;
	uint32_t GetExpiration() const ;
	uint32_t GetInception()  const ;
	uint16_t GetKeyTag()     const ;
	uint16_t GtetSignLen()   const ; 

	uint8_t const * GetName() const ;
	uint8_t const * GetSign() const ;
	

public :
	RData_RRSIG( uint8_t const * pRef ) ;

} ; // class RData_RRSIG
	
}   // name RR

}   // namespace dns
	
}   // namespace daniel