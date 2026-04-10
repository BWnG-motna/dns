#pragma once

#include "Common.h"
#include "RData.h"


namespace daniel
{

namespace dns
{

namespace RR
{


class RData_ATMA : public RData
{

private :
	uint8_t   format ;
	uint8_t * pAddress ;

private :
	uint16_t  binlen ;

private :
	void Initialize() override ;

public :
	uint16_t ToNullStr( uint8_t * pStr , uint16_t const & length ) const override ;

public :
	bool Load( uint8_t const * pData , uint16_t const & length ) override ;

public :
	uint8_t GetFormat()  const ;
	uint8_t const * GetAddress() const ;

public :
	 RData_ATMA() ;
	~RData_ATMA() ;

} ; // class RData_ATMA
	
	
}   // name RR

}   // namespace dns
	
}   // namespace daniel