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


class RData_CSYNC : public RData
{

private :
	uint32_t serial ;
	uint16_t flags ;

	bool isImmediate ;

	ds::LinkedList< SEC::TypeBitMap > * pTbm ;

private :
	mutable uint16_t * pTypes ;

private :
	bool SetType( uint8_t const & window , uint8_t const & type ) ;	

private :
	void Initialize() override ;

public :
	uint16_t ToNullStr( uint8_t * pStr , uint16_t const & length ) const override ;

public :
	bool Load( uint8_t const * pData , uint16_t const & length ) override ;

public :
	uint32_t GetSerial() const ;
	uint16_t GetFlags()  const ;

	uint16_t GetTypeCount()     const ;
	uint16_t const * GetTypes() const ;

public :
	 RData_CSYNC() ;
	~RData_CSYNC() ;

} ; // class RData_CSYNC
	
	
}   // name RR

}   // namespace dns
	
}   // namespace daniel