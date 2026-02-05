#pragma once

#include "Common.h"
#include "RData.h"
#include "dns/QType.h"
#include "SEC/SECAlgo.h"


namespace daniel
{

namespace dns
{

namespace RR
{


class RData_RRSIG : public RData
{

private :
	QType        typeCovered ;
	SEC::SECAlgo algorithm   ;
	uint8_t      labels      ;
	uint32_t     ttl         ;
	uint32_t     expiration  ;
	uint32_t     inception   ;
	uint16_t     keyTag      ;
	uint8_t    * pName ;
	uint8_t    * pSign ;

	uint16_t signLen ;

private :
	void Initalize() override ;

public :
	uint16_t ToNullStr( uint8_t * pStr , uint16_t const & length ) const override ;

public :
	bool Load( uint8_t const * pData , uint16_t const & length ) override ;

public :
	QType    GetTypeCovered() const ;
	
	uint8_t  GetLabels()     const ;
	uint32_t GetTTL()        const ;
	uint32_t GetExpiration() const ;
	uint32_t GetInception()  const ;
	uint16_t GetKeyTag()     const ;
	uint16_t GtetSignLen()   const ; 

	uint8_t const * GetName() const ;
	uint8_t const * GetSign() const ;

	SEC::SECAlgo GetAlgorithm() const ;
	

public :
	 RData_RRSIG( uint8_t const * pRef ) ;
	~RData_RRSIG() ;

} ; // class RData_RRSIG
	
	
}   // name RR

}   // namespace dns
	
}   // namespace daniel