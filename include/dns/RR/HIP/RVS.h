#pragma once

#include "Common.h"


namespace daniel
{

namespace dns
{

namespace RR
{

namespace HIP
{


class RVS 
{

private :
	uint8_t const * pDat ;
	uint16_t len ;

public :
	void Set( uint8_t const * p , uint16_t const & len ) ;

public :
	uint8_t const * Get() const ;
	uint16_t GetLen() const ;

public :
	 RVS() ;
	~RVS() ;

} ; // RVS


}   // namespace HIP

}   // namespace RR

}   // namespace dns

}   // namespace daniel