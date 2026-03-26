#pragma once

#include "Common.h"
#include "RData.h"

#include "DHCID/ID.h"
#include "DHCID/DigestType.h"


namespace daniel
{

namespace dns
{

namespace RR
{


class RData_DHCID : public RData
{

private :
	uint16_t  id ;
	uint8_t   digestType ;
	uint8_t * pDigest ;

private :
	uint16_t  digestLen ;

private :
	void Initialize() override ;

public :
	uint16_t ToNullStr( uint8_t * pStr , uint16_t const & length ) const override ;

public :
	bool Load( uint8_t const * pData , uint16_t const & length ) override ;

public :
	uint16_t GetId()         const ;
	uint16_t GetDigestLen()  const ;
	uint8_t  GetDigestType() const ;

public :
	uint8_t const * GetDigest() const ;

public :
	 RData_DHCID() ;
	~RData_DHCID() ;

} ; // class RData_DHCID
	
	
}   // name RR

}   // namespace dns
	
}   // namespace daniel