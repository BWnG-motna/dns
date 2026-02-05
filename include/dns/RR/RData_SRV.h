#pragma once

#include "Common.h"
#include "RData.h"


namespace daniel
{

namespace dns
{

namespace RR
{


class RData_SRV : public RData
{

private :
	uint16_t priority ;
	uint16_t weight ;
	uint16_t port ;

	uint8_t * pTarget ;

private :
	void Initalize() override ;

public :
	uint16_t ToNullStr( uint8_t * pStr , uint16_t const & length ) const override ;

public :
	bool Load( uint8_t const * pData , uint16_t const & length ) override ;

public :
	uint16_t GetPriority() const ;
	uint16_t GetWeight()   const ;
	uint16_t GetPort()     const ;

	uint8_t const * GetTarget() const ;

public :
	 RData_SRV( uint8_t const * pRef ) ;
	~RData_SRV() ;

} ; // class RData_SRV
	
	
}   // name RR

}   // namespace dns
	
}   // namespace daniel