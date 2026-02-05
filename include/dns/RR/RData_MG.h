#pragma once

#include "Common.h"
#include "RData_NAME.h"


namespace daniel
{

namespace dns
{

namespace RR
{


class RData_MG : public RData_NAME
{

private :
	void Initalize() override ;

public :
	uint8_t const * GetMgmName() const ;

public :
	 RData_MG( uint8_t const * pRef ) ;
	~RData_MG() ;

} ; // class RData_MG
	
	
}   // name RR

}   // namespace dns
	
}   // namespace daniel