#pragma once

#include "Common.h"
#include "RData.h"


namespace daniel
{

namespace dns
{

namespace RR
{


class RData_NSAP : public RData
{

private :
	uint16_t  binlen ;
	uint8_t * pBinary ;

private :
	void Initialize() override ;

public :
	uint16_t ToNullStr( uint8_t * pStr , uint16_t const & length ) const override ;

public :
	bool Load( uint8_t const * pData , uint16_t const & length ) override ;

public :
	uint16_t GetLength() const ;
	uint8_t const * GetBinary() const ;

public :
	 RData_NSAP() ;
	~RData_NSAP() ;

} ; // class RData_NSAP
	
	
}   // name RR

}   // namespace dns
	
}   // namespace daniel