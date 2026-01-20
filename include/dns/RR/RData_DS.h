#pragma once

#include "Common.h"
#include "RData.h"
#include "SECAlgo.h"
#include "SECDigest.h"


namespace daniel
{

namespace dns
{

namespace RR
{

class RData_DS : public RData
{

private :
	static constexpr uint16_t const digestMaxLen = 1024 ;

private :
	uint16_t  keyTag     ;
	SECAlgo   algorithm  ;
	SECDigest digestType ;
	uint8_t   digest[ digestMaxLen ] ;

	uint16_t  digestLen ;

public :
	uint16_t ToNullStr( uint8_t * pStr , uint16_t const & length ) const override ;

public :
	bool Load( uint8_t const * pData , uint16_t const & length ) override ;

public :
	uint16_t GetKeyTag()    const ;
	SECAlgo  GetAlgorithm() const ;
	uint16_t GetDigestLen() const ; 

	uint8_t const * GetDigest() const ;

public :
	RData_DS() ;

} ; // class RData_DS
	
}   // name RR

}   // namespace dns
	
}   // namespace daniel