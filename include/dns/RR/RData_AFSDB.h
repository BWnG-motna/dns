#pragma once

#include "Common.h"
#include "RData.h"


namespace daniel
{

namespace dns
{

namespace RR
{


class RData_AFSDB : public RData
{

private :
	uint16_t  subtype   ;
	uint8_t * pHostname ;

private :
	void Initialize() override ;

public :
	uint16_t ToNullStr( uint8_t * pStr , uint16_t const & length ) const override ;

public :
	bool Load( uint8_t const * pData , uint16_t const & length ) override ;

public :
	uint16_t GetSubtype() const ;

public :
	uint8_t const * GetHostname() const ;

public :
	 RData_AFSDB( uint8_t const * pRef ) ;
	~RData_AFSDB() ;

} ; // class RData_AFSDB
	
	
}   // name RR

}   // namespace dns
	
}   // namespace daniel