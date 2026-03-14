#pragma once

#include "Common.h"
#include "RData.h"


namespace daniel
{

namespace dns
{

namespace RR
{


class RData_NAPTR : public RData
{

private :
	uint16_t  order ;
	uint16_t  preference ;
	uint8_t * pFlags ;
	uint8_t * pServices ;
	uint8_t * pRegexp ;
	uint8_t * pReplacement ;

private :
	void Initialize() override ;

public :
	uint16_t ToNullStr( uint8_t * pStr , uint16_t const & length ) const override ;

public :
	bool Load( uint8_t const * pData , uint16_t const & length ) override ;

public :
	uint16_t GetOrder()      const ;
	uint16_t GetPreference() const ;

public :
	uint8_t const * GetFlags()       const ;
	uint8_t const * GetServices()    const ;
	uint8_t const * GetRegexp()      const ;
	uint8_t const * GetReplacement() const ;

public :
	 RData_NAPTR( uint8_t const * pRef ) ;
	~RData_NAPTR() ;

} ; // class RData_NAPTR
	
	
}   // name RR

}   // namespace dns
	
}   // namespace daniel