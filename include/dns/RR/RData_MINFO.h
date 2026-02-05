#pragma once

#include "Common.h"
#include "RData.h"


namespace daniel
{

namespace dns
{

namespace RR
{


class RData_MINFO : public RData
{

private :
	uint8_t * pRmailbx ;
	uint8_t * pEmailbx ;

private :
	void Initalize() override ;

public :
	uint16_t ToNullStr( uint8_t * pStr , uint16_t const & length ) const override ;

public :
	bool Load( uint8_t const * pData , uint16_t const & length ) override ;

public :
	uint8_t const * GetRMailBx() const ;
	uint8_t const * GetEMailBx() const ;

public :
	 RData_MINFO( uint8_t const * pRef ) ;
	~RData_MINFO() ;

} ; // class RData_MINFO

	
}   // name RR

}   // namespace dns
	
}   // namespace daniel