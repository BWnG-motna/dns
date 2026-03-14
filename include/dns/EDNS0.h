#pragma once


#include "Common.h"
#include "QType.h"
#include "QClass.h"
#include "DNpointer.h"
#include "EDNS0/EDNS0_OPTION.h"

#include "ds/LinkedList.h"


namespace daniel
{

namespace dns
{

class EDNS0 : public DNpointer
{

private :
	uint8_t * pName ;

private :
	uint16_t payloadSize ;
	uint8_t  version     ;
	uint8_t  extRCode    ;
	bool     isDnsSecOk  ;

	ds::LinkedList< EDNS0_OPTION > * pOpt ;

private :
	bool MakeOptions( uint8_t const * pRef , uint16_t const & length ) ;

private :
	bool InsertOption( EDNS0_OptCode const & optCode , uint8_t const * pDat , uint16_t const & len ) ;

public :
	void SetPayloadSize( uint16_t const & size ) ;
	void SetVersion ( uint8_t const & ver   ) ;
	void SetExtRCode( uint8_t const & rcode ) ;
	void SetDNSSecOk( bool const & isSet ) ;

public :
	uint32_t GetOptCount()    const ;

public :
	uint16_t GetPayloadSize() const ;
	uint8_t  GetVersion()     const ;
	uint8_t  GetExtRCode()    const ;
	bool     IsDnsSecOk()     const ;

public :
	bool InsertOptPadding( uint8_t const * pDat , uint16_t const & len ) ;
	bool InsertOptDAU() ;
	bool InsertOptCookie( uint8_t const * pDat , uint16_t const & len ) ;

public :
	QType GetType() const ;

public :
	uint8_t const * GetName() const ;

public :
	uint16_t Load( uint8_t const * pBuf , uint16_t const & length , uint8_t const * pRef ) ;
	uint16_t Save( uint8_t       * pBuf , uint16_t const & length ) ;

public :
	 EDNS0() ;
	~EDNS0() ;
	
} ; // class EDNS0

}  // namespace dns
	
}  // namespace daniel