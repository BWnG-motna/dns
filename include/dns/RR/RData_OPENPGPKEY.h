#pragma once

#include "Common.h"
#include "RData.h"


namespace daniel
{

namespace dns
{

namespace RR
{


class RData_OPENPGPKEY : public RData
{

private :
	uint8_t  * pk ;
	uint16_t   pklen ;

private :
	void Initalize() override ;

public :
	uint16_t ToNullStr( uint8_t * pStr , uint16_t const & length ) const override ;

public :
	bool Load( uint8_t const * pData , uint16_t const & length ) override ;

public :
	uint8_t const * GetPublicKey() const ;

public :
	 RData_OPENPGPKEY() ;
	~RData_OPENPGPKEY() ;

} ; // class RData_OPENPGPKEY
	
	
}   // name RR

}   // namespace dns
	
}   // namespace daniel