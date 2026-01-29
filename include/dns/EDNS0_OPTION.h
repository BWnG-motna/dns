#pragma once


#include "Common.h"
#include "QType.h"
#include "QClass.h"


namespace daniel
{

namespace dns
{

class EDNS0_OPTION
{

private :
	uint16_t  code ;
	uint16_t  len  ;
	uint8_t const * pDat ;

public :
	void SetCode( uint16_t const & code ) ;
	void SetLen ( uint16_t const & len  ) ;
	void SetData( uint8_t  const * pDat ) ;

public :
	uint16_t  GetCode() const ;
	uint16_t  GetLen()  const ;

	uint8_t const * GetData() const ;

public :
	 EDNS0_OPTION( EDNS0_OPTION & opt ) = delete ;
     EDNS0_OPTION & operator=( EDNS0_OPTION const & opt ) = delete ;

public :
	 EDNS0_OPTION( uint16_t const & code , uint16_t const & len , uint8_t const * pDat ) ;
	 EDNS0_OPTION() ;
	~EDNS0_OPTION() ;
	
} ; // class EDNS0

}  // namespace dns
	
}  // namespace daniel