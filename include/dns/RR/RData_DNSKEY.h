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


class RData_DNSKEY : public RData
{

private :
	bool zsk ;
	bool sep ;

	uint16_t     flags ;
	uint8_t      protocol  ;
	SEC::SECAlgo algorithm ;
	uint16_t     pklen ;
	uint8_t    * pk ;

private :
	void Initalize() override ;

public :
	uint16_t ToNullStr( uint8_t * pStr , uint16_t const & length ) const override ;

public :
	bool Load( uint8_t const * pData , uint16_t const & length ) override ;

public :
	bool IsSetZSK() const ;
	bool IsSetSEP() const ;

	SEC::SECAlgo GetAlgorithm() const ;
	uint8_t const * GetPublicKey() const ;

	uint16_t GetFlags() const ;
	uint16_t GetPublicKeyLength() const ;

public :
	 RData_DNSKEY() ;
	~RData_DNSKEY() ;

} ; // class RData_DNSKEY
	
	
}   // name RR

}   // namespace dns
	
}   // namespace daniel