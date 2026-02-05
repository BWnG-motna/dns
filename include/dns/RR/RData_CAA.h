#pragma once

#include "Common.h"
#include "RData.h"


namespace daniel
{

namespace dns
{

namespace RR
{


class RData_CAA : public RData
{

private :
	uint8_t   flags ;
	uint8_t   taglen ;
	uint8_t * pTag ;
	uint16_t  valuelen ;
	uint8_t * pValue ;

private :
	void Initalize() override ;

public :
	uint16_t ToNullStr( uint8_t * pStr , uint16_t const & length ) const override ;

public :
	bool Load( uint8_t const * pData , uint16_t const & length ) override ;

public :
	bool     IsCritical()  const ;

	uint8_t  GetFlags()    const ;
	uint8_t  GetTagLen()   const ;
	uint16_t GetValueLen() const ;

	uint8_t const * GetTag()   const ;
	uint8_t const * GetValue() const ;

public :
	 RData_CAA() ;
	~RData_CAA() ;

} ; // class RData_CAA
	
	
}   // name RR

}   // namespace dns
	
}   // namespace daniel