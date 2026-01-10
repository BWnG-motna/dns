#include "dns/EDNS0.h"


daniel::dns::EDNS0::EDNS0()
	: payloadSize( 1500 ) , version( 0 ) , extRCode( 0 ) , isDnsSecOk( false ) , pOpt( nullptr )
{
	
}


daniel::dns::EDNS0::~EDNS0()
{
	if( nullptr != pOpt )
	{
		delete pOpt ;
		pOpt = nullptr ;
	}
}


void daniel::dns::EDNS0::SetPayloadSize( uint16_t const & size )
{
	payloadSize = size ;
}


void daniel::dns::EDNS0::SetVersion ( uint8_t const & ver ) 
{
	version = ver ;
}


void daniel::dns::EDNS0::SetExtRCode( uint8_t const & rcode ) 
{
	extRCode = rcode ;
}


void daniel::dns::EDNS0::SetDNSSecOk( bool const & isSet ) 
{
	isDnsSecOk = isSet ;
}


uint16_t daniel::dns::EDNS0::GetPayloadSize() const 
{
	return payloadSize ;
}


uint8_t daniel::dns::EDNS0::GetVersion() const
{
	return version ;
}


uint8_t daniel::dns::EDNS0::GetExtRCode() const 
{
	return extRCode ;
}


bool daniel::dns::EDNS0::IsDnsSecOk() const
{
	return isDnsSecOk ;
}


uint16_t daniel::dns::EDNS0::Load( uint8_t const * pBuf , uint16_t const & length )
{
	if( 1 > length || nullptr == pBuf )
	{
		return 0 ;
	}

	if( 11 > length )
	{
		return 0 ;
	}

	uint16_t type = 0 ;
	type = ( ( pBuf[ 1 ] << 8 ) & 0xFF00 )
	     | ( ( pBuf[ 2 ] << 0 ) & 0x00FF ) ;

	if( 41 != type )
	{
		return 0 ;
	} 

	payloadSize = ( ( pBuf[ 3 ] << 8 ) & 0xFF00 )
	            | ( ( pBuf[ 4 ] << 0 ) & 0x00FF ) ;

	extRCode   = pBuf[ 5 ] ;
	version    = pBuf[ 6 ] ;
	isDnsSecOk = ( 0 < ( pBuf[ 7 ] ^ 0x80 ) ? true : false ) ;

	uint16_t rdlength = 0x00 ;

	rdlength = ( ( pBuf[ 3 ] << 8 ) & 0xFF00 )
	         | ( ( pBuf[ 4 ] << 0 ) & 0x00FF ) ;

	return 11 + 2 + rdlength ;
}


uint16_t daniel::dns::EDNS0::Save( uint8_t * pBuf , uint16_t const & length )
{
	// the case what pOpt is not null is not implemented, not handled.
	if( 1 > length || nullptr == pBuf || nullptr != pOpt )
	{
		return 0 ;
	}

	if( 11 > length )
	{
		return 0 ;
	}

	// name data - resource record 
	pBuf[ 0 ] = '\0' ;  

	uint16_t type = 41 ; // OPT RR - ENDS0

	// type = 41 - OPT RR
	pBuf[ 1 ] = ( type >> 8 ) & 0x00FF ;
	pBuf[ 2 ] = ( type >> 0 ) & 0x00FF ; 

	// class = UDP playload size
	pBuf[ 3 ] = ( payloadSize >> 8 ) & 0x00FF ;
	pBuf[ 4 ] = ( payloadSize >> 0 ) & 0x00FF ; 

	// ttl
	pBuf[ 5 ] = extRCode ;
	pBuf[ 6 ] = version  ;
	pBuf[ 7 ] = ( true == isDnsSecOk ) ? 0x80 : 0x00 ;
	pBuf[ 8 ] = 0x00 ; // z - reserved

	// rdlength
	pBuf[  9 ] = 0x00 ;
	pBuf[ 10 ] = 0x00 ;

	// rdata is not considered because rdlength is 0

	return 11 ;
}


daniel::dns::QType daniel::dns::EDNS0::GetType() const
{
	return QType::OPT ;
}