#pragma once

#include "Common.h"
#include "RData.h"

#include "TLSA/CertUsage.h"
#include "TLSA/Selector.h"
#include "TLSA/MatchingType.h"


namespace daniel
{

namespace dns
{

namespace RR
{


class RData_TLSA : public RData
{

private :
	static constexpr uint16_t certMaxLen = 512 ;

private :
	CertUsage    certUsage    ;
	Selector     selector     ;
	MatchingType matchingType ;
	uint8_t      cert[ certMaxLen ]  ;

private :
	uint16_t certlen ;

public :
	uint16_t ToNullStr( uint8_t * pStr , uint16_t const & length ) const override ;

public :
	bool Load( uint8_t const * pData , uint16_t const & length ) override ;

public :
	CertUsage    GetCertUsage()    const ;
	Selector     GetSelector()     const ;
	MatchingType GetMatchingType() const ;
	
	uint8_t const * GetCertData() const ; 

public :
	RData_TLSA() ;

} ; // class RData_TLSA
	
	
}   // name RR

}   // namespace dns
	
}   // namespace daniel