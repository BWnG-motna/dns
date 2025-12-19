#pragma once

#include "Common.h"


namespace daniel
{

namespace dns
{

namespace RR
{

class RData 
{

private :
	uint8_t const * pDataGram ; // the entire datagram is required to verify the compressed data

protected :
	bool GetCompressedIPv6( uint16_t const ( & addr )[ 8 ] , uint8_t * pBuf , uint16_t const & length ) const ;
	
protected :
	uint16_t GetDNData( uint8_t       * pBuf , uint16_t const & length , uint8_t const * pRef , bool const & fqdn = true ) const ;
	uint16_t SkipDName( uint8_t const * pBuf , uint16_t const & length ) const ;

public :
	virtual uint16_t ToNullStr( uint8_t * pStr , uint16_t const & length ) const = 0 ;
	virtual bool Load( uint8_t const * pData , uint16_t const & length ) = 0 ;

public :
	virtual ~RData() = default ;

public :
	RData( uint8_t const * pRef ) ;

} ; // class RData
	
}   // name RR

}   // namespace dns
	
}   // namespace daniel