#pragma once

#include "Common.h"
#include "RData.h"
#include "SEC/SECAlgo.h"


namespace daniel
{

namespace dns
{

namespace RR
{


class RData_KEY : public RData
{

private :
	bool noAuth ;
	bool noConf ;
	bool extflg ;
	bool zoneKey ;
	uint8_t sgnfield ;

private :
	uint16_t     flags ;
	uint8_t      protocol  ;
	SEC::SECAlgo algorithm ;
	uint16_t     pklen ;
	uint8_t    * pk ;

private :
	void Initialize() override ;

public :
	uint16_t ToNullStr( uint8_t * pStr , uint16_t const & length ) const override ;

public :
	bool Load( uint8_t const * pData , uint16_t const & length ) override ;

public :
	bool IsNoAuth()  const ;
	bool IsNoConf()  const ;
	bool IsZoneKey() const ;

public :
	uint8_t GetSignField() const ; 

	SEC::SECAlgo GetAlgorithm() const ;
	uint8_t const * GetPublicKey() const ;

	uint16_t GetFlags() const ;
	uint16_t GetPublicKeyLength() const ;

public :
	 RData_KEY() ;
	~RData_KEY() ;

} ; // class RData_KEY
	
	
}   // name RR

}   // namespace dns
	
}   // namespace daniel