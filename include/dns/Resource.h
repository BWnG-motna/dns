#pragma once


#include "Common.h"
#include "QType.h"
#include "QClass.h"

#include "RR/RData.h"


namespace daniel
{

namespace dns
{

class Resource
{

private :
	static constexpr uint16_t const nameMaxLen = 255 ;

private :
	uint8_t const * pDataGram ;

private :
	uint8_t  name[ nameMaxLen + 1 ] ;
	uint16_t nameLen ; 

	QType    qtype  ;
	QClass   qclass ;

	 int32_t ttl ;
	uint16_t rdlength ;

	RR::RData * pRDat ;	

private :
	uint16_t GetDNData( uint8_t * pBuf , uint16_t const & length , 
		                uint8_t const * pRef , 
		                bool    const & fqdn = true    ) const ;

private :
	void MakeRData( uint8_t const * pBuf , uint32_t const & length ) noexcept ;

public :
	uint16_t Load( uint8_t const * pBuf , uint16_t const & length , uint8_t const * pRef ) ;
//	uint16_t Save( uint8_t       * pBuf , uint16_t const & length ) ;

public :
	uint16_t GetName ( uint8_t * pBuf , uint16_t const & length ) const ; 
	uint16_t GetRData( uint8_t * pBuf , uint16_t const & length ) const ;

public :
	QType    GetType()  const ;
	QClass   GetClass() const ;
	 int32_t GetTTL()   const ;
	uint16_t GetRdLen() const ;

public :
	RR::RData const * GetRData() const ;

public :
	 Resource() ;
	~Resource() ;

} ; // class Resource


}   // namespace dns

}   // namespace daniel