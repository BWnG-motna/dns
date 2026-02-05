#pragma once

#include "Common.h"
#include "RData.h"

#include "SSHFP/Algorithm.h"
#include "SSHFP/FingerprintType.h"


namespace daniel
{

namespace dns
{

namespace RR
{


class RData_SSHFP : public RData
{

private :
	SSHFP::Algorithm algorithmNumber ;
	SSHFP::FingerprintType fingerprintType ;

	uint16_t  fingerprintLen ;
	uint8_t * pFP ;

private :
	void Initalize() override ;

public :
	uint16_t ToNullStr( uint8_t * pStr , uint16_t const & length ) const override ;

public :
	bool Load( uint8_t const * pData , uint16_t const & length ) override ;

public :
	SSHFP::Algorithm GetAlgorithm() const ;
	SSHFP::FingerprintType GetFingerprintType() const ;
	uint8_t  const * GetFingerprint() const ;

public :
	uint16_t GetFingerprintLen() const ;

public :
	 RData_SSHFP() ;
	~RData_SSHFP() ;

} ; // class RData_SSHFP
	
	
}   // name RR

}   // namespace dns
	
}   // namespace daniel