#pragma once

#include "Common.h"
#include "RData_NAME.h"


namespace daniel
{

namespace dns
{

namespace RR
{


class RData_MF : public RData_NAME
{

private :
	void Initalize() override ;

public :
	uint8_t const * GetMadName() const ;

public :
	 RData_MF( uint8_t const * pRef ) ;
	~RData_MF() ;

} ; // class RData_MF
	
	
}   // name RR

}   // namespace dns
	
}   // namespace daniel