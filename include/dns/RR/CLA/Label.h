#pragma once

#include "Common.h"


namespace daniel
{

namespace dns
{

namespace RR
{

namespace CLA
{


class Label
{

private :
	uint8_t * pProtocol ;
	uint8_t * pIpVer ;
	uint8_t * pBpVer ;

private :
	mutable uint8_t * pRs ;

private :
	void Initialize() ;

public :
	bool SetProtocol( uint8_t const * pStr , uint16_t const & len ) ;
	bool SetIpVer( uint8_t const * pStr , uint16_t const & len ) ;
	bool SetBpVer( uint8_t const * pStr , uint16_t const & len ) ;

public :
	uint8_t const * GetProtocol() const ;
	uint8_t const * GetIpVer() const ;
	uint8_t const * GetBpVer() const ;

public :
	uint8_t const * GetLabel() const ;

public :
	bool Load( uint8_t const * pStr , uint16_t const & len ) ;

public :
	 Label() ;
	~Label() ;

} ; // class Label

}   // namespace CLA

}   // namespace RR

}   // namespace dns

}   // namespace daniel