#pragma once

#include "Common.h"
#include "RData.h"

#include "ZONEMD/Scheme.h"
#include "ZONEMD/HashAlgo.h"


namespace daniel
{

namespace dns
{

namespace RR
{


class RData_ZONEMD : public RData
{

private :
	uint32_t         serial ;
	ZONEMD::Scheme   scheme ;
	ZONEMD::HashAlgo algorithm ;
	uint8_t        * pDigest ;

private :
	uint16_t         digestLen ;

private :
	void Initialize() override ;

public :
	uint16_t ToNullStr( uint8_t * pStr , uint16_t const & length ) const override ;

public :
	bool Load( uint8_t const * pData , uint16_t const & length ) override ;

public :
	void SetSerial  ( uint32_t         const & serial ) ;
	void SetScheme  ( ZONEMD::Scheme   const & scheme ) ;
	void SetHashAlgo( ZONEMD::HashAlgo const & algo   ) ;
	void SetDigest  ( uint8_t          const & p      , uint16_t const & len ) ;

public :
	uint32_t         GetSerial()    const ;
	ZONEMD::Scheme   GetScheme()    const ;
	ZONEMD::HashAlgo GetHashAlgo()  const ;
	uint16_t         GetDigestLen() const ;
	uint8_t const *  GetDigest()    const ;

public :
	 RData_ZONEMD() ;
	~RData_ZONEMD() ;

} ; // class RData_ZONEMD
	
	
}   // name RR

}   // namespace dns
	
}   // namespace daniel