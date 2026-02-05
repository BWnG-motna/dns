#pragma once

#include "Common.h"
#include "RData.h"


namespace daniel
{

namespace dns
{

namespace RR
{


class RData_RP : public RData
{

private :
	uint8_t * pMboxDName ;
	uint8_t *  pTxtDName ;

private :
	void Initalize() override ;

public :
	uint16_t ToNullStr( uint8_t * pStr , uint16_t const & length ) const override ;

public :
	bool Load( uint8_t const * pData , uint16_t const & length ) override ;

public :
	uint8_t const * GetMBoxDName() const ;
	uint8_t const * GetTxtDName()  const ;

public :
	 RData_RP( uint8_t const * pRef ) ;
	~RData_RP() ;

} ; // class RData_RP
	
	
}   // name RR

}   // namespace dns
	
}   // namespace daniel