#pragma once

#include "Common.h"

#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <cstring>


namespace daniel
{
	
namespace net
{

int RequestOnUdp( uint8_t * prBuf , uint16_t const & rbufLen , uint8_t const * psBuf , uint16_t const & sbufLen ) ;
	
}   // namespace net

}   // namespace daniel