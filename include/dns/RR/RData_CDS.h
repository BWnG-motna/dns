#pragma once

#include "Common.h"
#include "RData.h"

#include "SEC/SECAlgo.h"
#include "SEC/SECDigest.h"


namespace daniel
{

namespace dns
{

namespace RR
{


class RData_CDS : public RData
{

private :
	uint16_t       keyTag ;
	SEC::SECAlgo   algorithm ;
	SEC::SECDigest digestType ;
	uint16_t       digestLen  ;
	uint8_t      * pDigest ;

private :
	void Initialize() override ;

public :
	uint16_t ToNullStr( uint8_t * pStr , uint16_t const & length ) const override ;

public :
	bool Load( uint8_t const * pData , uint16_t const & length ) override ;

public :
	uint16_t GetKeyTag()    const ;
	uint16_t GetDigestLen() const ; 

	uint8_t const * GetDigest() const ;

	SEC::SECAlgo GetAlgorithm() const ;

public :
	 RData_CDS() ;
	~RData_CDS() ;

} ; // class RData_CDS
	
	
}   // name RR

}   // namespace dns
	
}   // namespace daniel