#pragma once

#include "Common.h"
#include "RData.h"


namespace daniel
{

namespace dns
{

namespace RR
{


class RData_LP : public RData
{

private :
	uint16_t  preference ;
	uint8_t * pLocator  ;

private :
	void Initialize() override ;

public :
	uint16_t ToNullStr( uint8_t * pStr , uint16_t const & length ) const override ;

public :
	bool Load( uint8_t const * pData , uint16_t const & length ) override ;

public :
	uint16_t GetPreference() const ;
	uint8_t const * GetLocator() const ;

public :
	 RData_LP( uint8_t const * pRef ) ;
	~RData_LP() ;

} ; // class RData_LP
	
	
}   // name RR

}   // namespace dns
	
}   // namespace daniel