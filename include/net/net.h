#pragma once

#include "Common.h"


namespace daniel
{
	
namespace net
{

int RequestOnTcpV4(
	uint8_t       * prBuf , uint16_t const & rbufMaxLen , 
	uint8_t const * psBuf , uint16_t const & sbufLen    ,
	char    const * svrIp , uint16_t const & svrPort    ) ;

int RequestOnUdpV4( 
	uint8_t       * prBuf , uint16_t const & rbufMaxLen , 
	uint8_t const * psBuf , uint16_t const & sbufLen    ,
	char    const * svrIp , uint16_t const & svrPort    ) ;

int RequestOnTcpV6(
	uint8_t       * prBuf , uint16_t const & rbufMaxLen , 
	uint8_t const * psBuf , uint16_t const & sbufLen    ,
	char    const * svrIp , uint16_t const & svrPort    ) ;

int RequestOnUdpV6( 
	uint8_t       * prBuf , uint16_t const & rbufMaxLen , 
	uint8_t const * psBuf , uint16_t const & sbufLen    ,
	char    const * svrIp , uint16_t const & svrPort    ) ;

}   // namespace net

}   // namespace daniel