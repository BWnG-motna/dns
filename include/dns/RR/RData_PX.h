#pragma once

#include "Common.h"
#include "RData.h"


namespace daniel
{

namespace dns
{

namespace RR
{


class RData_PX : public RData
{

private :
	uint16_t  preference ;
	uint8_t * pMap822  ;
	uint8_t * pMapx400 ;

private :
	void Initialize() override ;

public :
	uint16_t ToNullStr( uint8_t * pStr , uint16_t const & length ) const override ;

public :
	bool Load( uint8_t const * pData , uint16_t const & length ) override ;

public :
	uint16_t        GetPreference() const ;
	uint8_t const * GetMap822()     const ;
	uint8_t const * GetMapX400()    const ;

public :
	 RData_PX( uint8_t const * pRef ) ;
	~RData_PX() ;

} ; // class RData_PX
	
	
}   // name RR

}   // namespace dns
	
}   // namespace daniel