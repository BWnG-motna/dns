#pragma once


#include "Common.h"
#include "dns/QType.h"
#include "dns/QClass.h"

#include "EDNS0_OptCode.h"


namespace daniel
{

namespace dns
{

class EDNS0_OPTION
{

private :
	EDNS0_OptCode  code ;
	uint16_t       len  ;
	uint8_t  *     pDat ;

public :
	void SetCode( EDNS0_OptCode const & code ) ;
	void SetCode(      uint16_t const & code ) ;
	
	void SetData( uint8_t  const * pDat , uint16_t const & len ) ;

public :
	EDNS0_OptCode GetCode() const ;
	uint16_t GetLen()  const ;

	uint8_t const * GetData() const ;

public :
	 EDNS0_OPTION( EDNS0_OPTION & opt ) = delete ;
     EDNS0_OPTION & operator=( EDNS0_OPTION const & opt ) = delete ;

public :
	 EDNS0_OPTION( EDNS0_OptCode const & code , uint16_t const & len , uint8_t const * pDat ) ;
	 EDNS0_OPTION() ;
	~EDNS0_OPTION() ;
	
} ; // class EDNS0

}  // namespace dns
	
}  // namespace daniel