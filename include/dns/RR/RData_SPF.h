#pragma once

#include "Common.h"
#include "RData.h"


namespace daniel
{

namespace dns
{

namespace RR
{


class RData_SPF : public RData
{

private :
	uint8_t * pSpfData ;

private :
	void Initialize() override ;
	
public :
	uint16_t ToNullStr( uint8_t * pStr , uint16_t const & length ) const override ;

public :
	bool Load( uint8_t const * pData , uint16_t const & length ) override ;

public :
	uint8_t const * GetSpfData() const ;

public :
	 RData_SPF() ;
	~RData_SPF() ;

} ; // class RData_SPF
	
	
}   // name RR

}   // namespace dns
	
}   // namespace daniel