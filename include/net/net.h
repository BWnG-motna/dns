#pragma once

#include "Common.h"


namespace daniel
{
	
namespace net
{

int RequestOnUdp( uint8_t * prBuf , uint16_t const & rbufLen , uint8_t const * psBuf , uint16_t const & sbufLen ) ;
	
}   // namespace net

}   // namespace daniel