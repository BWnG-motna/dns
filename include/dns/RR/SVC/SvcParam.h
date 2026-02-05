#pragma once

#include "Common.h"
#include "SvcKey.h"

#include <string>


namespace daniel
{

namespace dns
{

namespace RR
{

namespace SVC
{


class SvcParam
{

private :
	SvcKey   key ;
	uint16_t len ;
	uint8_t  value[ 65535 ] ;

private :
	bool isSet ;

private :
	bool IsValidValue() const ;

private :
	std::string MandatoryToStr() const ;
	std::string AlpnToStr()      const ;
	std::string PortToStr()      const ;
	std::string EchToStr()       const ;
	std::string Ipv4HintToStr()  const ;
	std::string Ipv6HintToStr()  const ;
	
public :
	bool IsSet() const ;
	void UnSet() ;

public :
	SVC::SvcKey GetKey() const ;
	uint16_t GetLen() const ;
	uint8_t const * GetValue() const ;

public :
	void SetKey  ( uint16_t const & key ) ;
	void SetKey  ( SVC::SvcKey const & key ) ;
	void SetValue( uint8_t const * pDat , uint16_t const & len ) ;

public :
	std::string ToStr() const ;

public :
	SvcParam( SVC::SvcKey const & key , uint8_t const * pDat , uint16_t const & len ) ;
	SvcParam( uint16_t    const & key , uint8_t const * pDat , uint16_t const & len ) ;
	SvcParam() ;

} ; // class SvcParam


}   // namespace SVC

}   // namespace RR

}   // namespace dns

}   // namespace daniel