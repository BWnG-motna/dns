#pragma once

#include "Common.h"
#include "RData.h"


namespace daniel
{

namespace dns
{

namespace RR
{


class RData_IPN : public RData
{

private :
	uint64_t nodeNumber ;

private :
	void Initialize() override ;

public :
	uint16_t ToNullStr( uint8_t * pStr , uint16_t const & length ) const override ;

public :
	bool Load( uint8_t const * pData , uint16_t const & length ) override ;

public :
	uint64_t GetNodeNumber() const ;

public :
	 RData_IPN() ;
	~RData_IPN() ;

} ; // class RData_IPN
	
	
}   // name RR

}   // namespace dns
	
}   // namespace daniel