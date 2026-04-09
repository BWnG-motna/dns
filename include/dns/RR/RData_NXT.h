#pragma once

#include "Common.h"
#include "RData.h"


namespace daniel
{

namespace dns
{

namespace RR
{


class RData_NXT : public RData
{

private :
	uint8_t * pNextDName ;
	uint8_t   pTbm[ 16 ] ;

	uint8_t nextDNameLen ;

private :
	mutable uint16_t * pTypes ;

private :
	void Initialize() override ;

public :
	uint16_t ToNullStr( uint8_t * pStr , uint16_t const & length ) const override ;

public :
	bool Load( uint8_t const * pData , uint16_t const & length ) override ;

public :
	uint8_t GetNextDNameLength() const ;
	uint8_t GetTypeCount()       const ;

	uint8_t  const * GetNextDName() const ;
	uint16_t const * GetTypes()     const ;

public :
	 RData_NXT() ;
	~RData_NXT() ;

} ; // class RData_NXT
	
	
}   // name RR

}   // namespace dns
	
}   // namespace daniel