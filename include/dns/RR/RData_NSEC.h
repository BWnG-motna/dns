#pragma once

#include "Common.h"
#include "RData.h"
#include "SEC/TypeBitMap.h" 


namespace daniel
{

namespace dns
{

namespace RR
{


class RData_NSEC : public RData
{

private :
	uint8_t     nextDName[ 512 ] ;
	TypeBitMap  tbm[ 256 ] ;

	uint8_t     nextDNameLen ;

private :
	mutable uint16_t types[ 512 ] ;

public :
	uint16_t ToNullStr( uint8_t * pStr , uint16_t const & length ) const override ;

public :
	bool Load( uint8_t const * pData , uint16_t const & length ) override ;

public :
	uint8_t  GetNextDNameLength() const ;
	uint16_t GetTypeCount()       const ;

	uint8_t  const * GetNextDName() const ;
	uint16_t const * GetTypes()     const ;

public :
	RData_NSEC() ;

} ; // class RData_NSEC
	
	
}   // name RR

}   // namespace dns
	
}   // namespace daniel