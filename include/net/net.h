#pragma once

#include "Common.h"


namespace daniel
{
	
namespace net
{

int RequestOnTcp(
	uint8_t       * prBuf , uint16_t const & rbufMaxLen , 
	uint8_t const * psBuf , uint16_t const & sbufLen    ,
	char    const * svrIp , uint16_t const & svrPort    ) ;

int RequestOnUdp( 
	uint8_t       * prBuf , uint16_t const & rbufMaxLen , 
	uint8_t const * psBuf , uint16_t const & sbufLen    ,
	char    const * svrIp , uint16_t const & svrPort    ) ;

}   // namespace net

}   // namespace daniel