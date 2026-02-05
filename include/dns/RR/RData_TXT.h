#pragma once

#include "Common.h"
#include "RData.h"


namespace daniel
{

namespace dns
{

namespace RR
{


class RData_TXT : public RData
{

private :
	uint8_t * pTxtData ;

private :
	void Initalize() override ;
	
public :
	uint16_t ToNullStr( uint8_t * pStr , uint16_t const & length ) const override ;

public :
	bool Load( uint8_t const * pData , uint16_t const & length ) override ;

public :
	uint8_t const * GetTxtData() const ;

public :
	 RData_TXT() ;
	~RData_TXT() ;

} ; // class RData_TXT
	
	
}   // name RR

}   // namespace dns
	
}   // namespace daniel