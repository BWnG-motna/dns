#pragma once

#include "Common.h"
#include "RData.h"


namespace daniel
{

namespace dns
{

namespace RR
{


class RData_KX : public RData
{

private :
	uint16_t  preference ;
	uint8_t * pExchange  ;

private :
	void Initialize() override ;

public :
	uint16_t ToNullStr( uint8_t * pStr , uint16_t const & length ) const override ;

public :
	bool Load( uint8_t const * pData , uint16_t const & length ) override ;

public :
	uint16_t GetPreference() const ;
	uint8_t const * GetExchange() const ;

public :
	 RData_KX( uint8_t const * pRef ) ;
	~RData_KX() ;

} ; // class RData_KX
	
	
}   // name RR

}   // namespace dns
	
}   // namespace daniel