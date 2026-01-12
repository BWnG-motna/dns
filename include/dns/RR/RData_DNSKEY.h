#pragma once

#include "Common.h"
#include "RData.h"
#include "DnsSECAlgo.h"


namespace daniel
{

namespace dns
{

namespace RR
{

class RData_DNSKEY : public RData
{

private :
	static constexpr uint16_t const pkMaxLen = 1024 ;

private :
	bool zsk ;
	bool sep ;

	uint16_t   flag ;
	uint8_t    protocol  ;
	DnsSECAlgo algorithm ;
	uint8_t    publicKey[ pkMaxLen ] ;

	uint16_t   pklen ;

public :
	uint16_t ToNullStr( uint8_t * pStr , uint16_t const & length ) const override ;

public :
	bool Load( uint8_t const * pData , uint16_t const & length ) override ;

public :
	RData_DNSKEY() ;

} ; // class RData_DNSKEY
	
}   // name RR

}   // namespace dns
	
}   // namespace daniel