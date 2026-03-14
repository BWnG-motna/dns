#pragma once

#include "Common.h"
#include "dns/QType.h"
#include "dns/QClass.h"


namespace daniel
{

namespace dns
{

class Question
{

private :
	static constexpr uint16_t const qnameMaxLen = 255 ; 

private :
	char     qname[ qnameMaxLen + 1 ] ;
	uint16_t qnameLen ;

	QType  qtype ;
	QClass qclass ;

public :
	bool SetName ( char   const * pBuf , uint16_t const & length ) ;
	void SetType ( QType  const & qtype  ) ;
	void SetClass( QClass const & qclass ) ;

public :
	uint16_t Load( uint8_t const * pBuf , uint16_t const & length ) ;
	uint16_t Save( uint8_t       * pBuf , uint16_t const & length ) ;

public :
	bool   GetName( uint8_t * pBuf , uint16_t const & length ) const ;
	QType  GetType()  const ;
	QClass GetClass() const ;

public :
	Question() ;

} ; // class Question


}   // namespace dns
	
}   // namespace daniel