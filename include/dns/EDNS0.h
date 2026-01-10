#pragma once


#include "Common.h"
#include "QType.h"
#include "QClass.h"
#include "EDNS0_OPTION.h"


namespace daniel
{

namespace dns
{

class EDNS0
{

private :
	uint16_t payloadSize ;
	uint8_t  version     ;
	uint8_t  extRCode    ;
	bool     isDnsSecOk  ;

	EDNS0_OPTION * pOpt ;

public :
	void SetPayloadSize( uint16_t const & size ) ;
	void SetVersion ( uint8_t const & ver   ) ;
	void SetExtRCode( uint8_t const & rcode ) ;
	void SetDNSSecOk( bool const & isSet ) ;

public :
	uint16_t GetPayloadSize() const ;
	uint8_t  GetVersion()     const ;
	uint8_t  GetExtRCode()    const ;
	bool     IsDnsSecOk()     const ;

public :
	QType GetType() const ;

public :
	uint16_t Load( uint8_t const * pBuf , uint16_t const & length ) ;
	uint16_t Save( uint8_t       * pBuf , uint16_t const & length ) ;

public :
	 EDNS0() ;
	~EDNS0() ;
	
} ; // class EDNS0

}  // namespace dns
	
}  // namespace daniel