#pragma once

#include "Common.h"
#include "RData.h"

#include "DANE/CertUsage.h"
#include "DANE/Selector.h"
#include "DANE/MatchingType.h"


namespace daniel
{

namespace dns
{

namespace RR
{


class RData_TLSA : public RData
{

private :
	DANE::CertUsage    certUsage    ;
	DANE::Selector     selector     ;
	DANE::MatchingType matchingType ;
	uint8_t * pCert ;

private :
	uint16_t certlen ;

private :
	void Initalize() override ;

public :
	uint16_t ToNullStr( uint8_t * pStr , uint16_t const & length ) const override ;

public :
	bool Load( uint8_t const * pData , uint16_t const & length ) override ;

public :
	DANE::CertUsage    GetCertUsage()    const ;
	DANE::Selector     GetSelector()     const ;
	DANE::MatchingType GetMatchingType() const ;
	
	uint8_t const * GetCertData() const ; 

public :
	 RData_TLSA() ;
	~RData_TLSA() ;

} ; // class RData_TLSA
	
	
}   // name RR

}   // namespace dns
	
}   // namespace daniel