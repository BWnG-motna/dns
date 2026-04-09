#pragma once

#include "Common.h"
#include "RData.h"


namespace daniel
{

namespace dns
{

namespace RR
{


class RData_GPOS : public RData
{

private :
	uint8_t * pLong ;
	uint8_t * pLat  ;
	uint8_t * pAlt  ;

private :
	void Initialize() override ;

public :
	uint16_t ToNullStr( uint8_t * pStr , uint16_t const & length ) const override ;

public :
	bool Load( uint8_t const * pData , uint16_t const & length ) override ;

public :
	uint8_t const * GetLongitude() const ;
	uint8_t const * GetLatitude()  const ;
	uint8_t const * GetAltitude()  const ;

public :
	 RData_GPOS() ;
	~RData_GPOS() ;

} ; // class RData_GPOS
	
	
}   // name RR

}   // namespace dns
	
}   // namespace daniel