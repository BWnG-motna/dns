#pragma once

#include "Common.h"
#include "RData.h"


namespace daniel
{

namespace dns
{

namespace RR
{


class RData_NID : public RData
{

private :
	uint16_t  preference ;
	uint64_t  nodeID     ;

private :
	void Initialize() override ;

public :
	uint16_t ToNullStr( uint8_t * pStr , uint16_t const & length ) const override ;

public :
	bool Load( uint8_t const * pData , uint16_t const & length ) override ;

public :
	uint16_t GetPreference() const ;
	uint64_t GetNodeID()     const ;

public :
	 RData_NID() ;
	~RData_NID() ;

} ; // class RData_NID
	
	
}   // name RR

}   // namespace dns
	
}   // namespace daniel