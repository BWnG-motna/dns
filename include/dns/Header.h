#pragma once

#include "Common.h"
#include "dns/QR.h"


namespace daniel
{
	
namespace dns
{

class Header
{

private :
	static constexpr uint16_t const slen = 12 ;

private :
	uint16_t id ;          // identifier

	uint16_t qr     : 1 ;  // 0 : query
	                       // 1 : response

	uint16_t opcode : 4 ;  // 0      : a standard query        (  QUERY )
	                       // 1      : an inverse query        ( IQUERY )
	                       // 2      : a server status request ( STATUS ) 
	                       // 3 ~ 15 : reserved for future use

	uint16_t aa     : 1 ;  // authoritative answer
	uint16_t tc     : 1 ;  // trunCation : this message was truncated due to length greater 
	                       //              than that permitted on the transmission channel

	uint16_t rd     : 1 ;  // recursion desired       : it is set, it directs the name server to pursue the query recursively
	uint16_t ra     : 1 ;  // recursion available     : it is set or cleared in a response - in the name server recursive query support is available
	uint16_t z      : 1 ;  // reserved for future use : must be zero in all queries and response
	uint16_t ad     : 1 ;  // authenticated data
	uint16_t cd     : 1 ;  // checking disabled

	uint16_t rcode  : 4 ;  // 0      : no error
	                       // 1      : format error
	                       // 2      : server failure
	                       // 3      : name error
	                       // 4      : not implemented
	                       // 5      : refused
	                       // 6 ~ 15 : reserved for future use

	uint16_t qdcount ;     // number of entries in the question section
	uint16_t ancount ;     // number of resource records in the answer section
	uint16_t nscount ;     // number of name server resource records
	uint16_t arcount ;     // number of resource records in additional records section

public :
	uint16_t Load( uint8_t const * pBuf , uint16_t const & length ) ;
	uint16_t Save( uint8_t       * pBuf , uint16_t const & length ) const ;

public :
	void SetId( uint16_t const & id ) ;
	void SetQR( QR const & qr ) ;
	
	void SetOpCode( uint16_t const & opCode ) ;
	void SetRCode ( uint16_t const &  rCode ) ;
	
	void SetAA( bool const & isSet ) ;
	void SetTC( bool const & isSet ) ;
	void SetRD( bool const & isSet ) ;
	void SetRA( bool const & isSet ) ;
	void SetAD( bool const & isSet ) ;
	void SetCD( bool const & isSet ) ;

	void SetQdCount( uint16_t const & count ) ;
	void SetAnCount( uint16_t const & count ) ;
	void SetNsCount( uint16_t const & count ) ;
	void SetArCount( uint16_t const & count ) ;

public :
	uint16_t GetID()     const ;
	uint16_t GetQR()     const ;
	uint16_t GetOpcode() const ;
	uint16_t GetAA()     const ;
	uint16_t GetTC()     const ;
	uint16_t GetRD()     const ;
	uint16_t GetRA()     const ;
	uint16_t GetZ()      const ;
	uint16_t GetAD()     const ;
	uint16_t GetCD()     const ;
	uint16_t GetRCode()  const ;

public :
	uint16_t GetQdCount() const ;
	uint16_t GetAnCount() const ;
	uint16_t GetNsCount() const ;
	uint16_t GetArCount() const ;

public :
	Header() ;

} ; // class header
	
	
}   // namespace dns

}   // namespace daniel