#pragma once

#include "Common.h"


namespace daniel
{

namespace dns
{

namespace RR
{

namespace HHIT
{


class COBLHeader
{

private :
	uint8_t  majorType  ;
	uint8_t  bytes      ; // 0 ~ 8 bytes
	uint8_t  extraBytes ; 
	uint32_t data ;

	bool    isError ;

public :
	uint8_t  GetMajorType()  const ;
	uint8_t  GetBytes()      const ;
	uint8_t  GetExtraBytes() const ;
	uint32_t GetData()       const ;

public :
	bool Load( uint8_t const * p , uint16_t const & len ) ;

public :
	bool IsError() const ;

public :
	COBLHeader() ;

} ; // COBL Header


}   // namespace HHIT

}   // namespace RR

}   // namespace dns

}   // namespace daniel