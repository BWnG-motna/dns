#pragma once

#include "Common.h"
#include "RData_NAME.h"


namespace daniel
{

namespace dns
{

namespace RR
{


class RData_MR : public RData_NAME
{

private :
	void Initalize() override ;

public :
	uint8_t const * GetNewName() const ;

public :
	 RData_MR( uint8_t const * pRef ) ;
	~RData_MR() ;

} ; // class RData_MR
	
	
}   // name RR

}   // namespace dns
	
}   // namespace daniel