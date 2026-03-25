#pragma once

#include "Common.h"
#include "RData.h"

#include "IPSECKEY/Algorithm.h"
#include "IPSECKEY/Gateway.h"


namespace daniel
{

namespace dns
{

namespace RR
{


class RData_IPSECKEY : public RData
{

private :
	using GWType    = IPSECKEY::Gateway   ;
	using Algorithm = IPSECKEY::Algorithm ;

private :
	uint8_t   precedence  ;
	GWType    gatewayType ;
	Algorithm algorithm   ;
	
	uint8_t * pGateway    ;
	uint8_t * pKey        ;

private :
	uint16_t pkLen ;

private :
	void Initialize() override ;

public :
	uint16_t ToNullStr( uint8_t * pStr , uint16_t const & length ) const override ;

public :
	bool Load( uint8_t const * pData , uint16_t const & length ) override ;

public :
	uint8_t   GetPrecedence()  const ;
	GWType    GetGatewayType() const ;
	Algorithm GetAlgorithm()   const ;

public :
	uint8_t const * GetGateway()   const ;
	uint8_t const * GetPublicKey() const ; 

public :
	uint16_t GetPublcKeyLen() const ;

public :
	 RData_IPSECKEY() ;
	~RData_IPSECKEY() ;

} ; // class RData_IPSECKEY
	
	
}   // name RR

}   // namespace dns
	
}   // namespace daniel