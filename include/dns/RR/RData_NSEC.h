#pragma once

#include "Common.h"
#include "RData.h"
#include "SEC/TypeBitMap.h" 

#include "ds/LinkedList.h"


namespace daniel
{

namespace dns
{

namespace RR
{


class RData_NSEC : public RData
{

private :
	uint8_t * pNextDName ;
	ds::LinkedList< SEC::TypeBitMap > * pTbm ;

	uint8_t nextDNameLen ;

private :
	mutable uint16_t * pTypes ;

private :
	bool SetType( uint8_t const & window , uint8_t const & type ) ;	

private :
	void Initalize() override ;

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
	~RData_NSEC() ;

} ; // class RData_NSEC
	
	
}   // name RR

}   // namespace dns
	
}   // namespace daniel