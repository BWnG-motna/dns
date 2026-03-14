#pragma once

#include "Common.h"
#include "RData.h"

#include "CERT/CertType.h"
#include "SEC/SECAlgo.h"


namespace daniel
{

namespace dns
{

namespace RR
{


class RData_CERT : public RData
{

private :
	static constexpr uint16_t base64exprMaxLen = 4096 ;

private :
	CERT::CertType type      ;
	uint16_t       keyTag    ;
	SEC::SECAlgo   algorithm ;

	uint8_t  * pCert ;
	uint16_t    certlen ;

private :
	void Initialize() override ;

public :
	uint16_t ToNullStr( uint8_t * pStr , uint16_t const & length ) const override ;

public :
	bool Load( uint8_t const * pData , uint16_t const & length ) override ;

public :
	CERT::CertType   GetType()      const ;
	SEC::SECAlgo     GetAlgorithm() const ;
	uint16_t         GetKeyTag()    const ;
	uint8_t  const * GetCert()      const ;

public :
	uint16_t GetCertLen() const ;

public :
	 RData_CERT() ;
	~RData_CERT() ;

} ; // class RData_CERT
	
	
}   // name RR

}   // namespace dns
	
}   // namespace daniel