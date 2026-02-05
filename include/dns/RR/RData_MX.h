#pragma once

#include "Common.h"
#include "RData.h"


namespace daniel
{

namespace dns
{

namespace RR
{


class RData_MX : public RData
{

private :
	uint16_t  preference ;
	uint8_t * pExchange  ;

private :
	void Initalize() override ;

public :
	uint16_t ToNullStr( uint8_t * pStr , uint16_t const & length ) const override ;

public :
	bool Load( uint8_t const * pData , uint16_t const & length ) override ;

public :
	uint16_t GetPreference() const ;
	uint8_t const * GetExchange() const ;

public :
	 RData_MX( uint8_t const * pRef ) ;
	~RData_MX() ;

} ; // class RData_MX
	
	
}   // name RR

}   // namespace dns
	
}   // namespace daniel