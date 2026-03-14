#pragma once

#include "Common.h"
#include "dns/DNpointer.h"


namespace daniel
{

namespace dns
{

namespace RR
{

class RData : public DNpointer
{

private :
	virtual void Initialize() = 0 ;
	
public :
	virtual uint16_t ToNullStr( uint8_t * pStr , uint16_t const & length ) const = 0 ;
	virtual bool Load( uint8_t const * pData , uint16_t const & length ) = 0 ;

public :
	virtual ~RData() = default ;

public :
	RData( uint8_t const * pRef ) ;

} ; // class RData
	
}   // name RR

}   // namespace dns
	
}   // namespace daniel