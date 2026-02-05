#pragma once

#include "Common.h"
#include "RData_NAME.h"


namespace daniel
{

namespace dns
{

namespace RR
{


class RData_NS : public RData_NAME
{

private :
	void Initalize() override ;

public :
	uint8_t const * GetNSDName() const ;

public :
	 RData_NS( uint8_t const * pRef ) ;
	~RData_NS() ;

} ; // class RData_NS

	
}   // name RR

}   // namespace dns
	
}   // namespace daniel