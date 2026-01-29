#include "dns/EDNS0.h"


#include <memory>


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


uint16_t daniel::dns::EDNS0::Load( uint8_t const * pBuf , uint16_t const & length , uint8_t const * pRef )
{
	if( 1 > length || nullptr == pBuf || nullptr == pRef  )
	{
		return 0 ;
	}

	pDataGram = pRef ;

	uint16_t bPos = 0 ;
	uint16_t nPos = 0 ;

	bool isCompressed = false ;

	while( '\0' != pBuf[ bPos ] && bPos < length )
	{
		if( 0xC0 <= ( pBuf[ bPos ] & 0xC0 ) )
		{
			if( nameMaxLen < ( nPos + 2 ) )
			{
				return 0 ;
			}

			name[ nPos++ ] = pBuf[ bPos++ ] ;
			name[ nPos++ ] = pBuf[ bPos++ ] ;

			isCompressed = true ;
			break ;
		}

		if( nameMaxLen <= nPos )
		{
			return 0 ;
		}

		name[ nPos++ ] = pBuf[ bPos++ ] ;
	}

	if( bPos >= length )
	{
		return 0 ;
	}

	if( false == isCompressed && '\0' == pBuf[ bPos ] )
	{
		++bPos ;
	}

	name[ nPos ] = '\0' ;
	nameLen = nPos ;

	uint16_t type = 0 ;
	type = ( ( pBuf[ bPos + 0 ] << 8 ) & 0xFF00 )
	     | ( ( pBuf[ bPos + 1 ] << 0 ) & 0x00FF ) ;

	if( 41 != type )
	{
		return 0 ;
	} 

	payloadSize = ( ( pBuf[ bPos + 2 ] << 8 ) & 0xFF00 )
	            | ( ( pBuf[ bPos + 3 ] << 0 ) & 0x00FF ) ;

	extRCode   = pBuf[ bPos + 4 ] ;
	version    = pBuf[ bPos + 5 ] ;
	isDnsSecOk = ( 0 < ( pBuf[ bPos + 6 ] & 0x80 ) ? true : false ) ;

	uint16_t rdlength = 0x00 ;

	rdlength = ( ( pBuf[ bPos + 8 ] << 8 ) & 0xFF00 )
	         | ( ( pBuf[ bPos + 9 ] << 0 ) & 0x00FF ) ;

	MakeOptions( & ( pBuf[ bPos + 10 ] ) , rdlength ) ;

	return bPos + 10 + rdlength ;
}


bool daniel::dns::EDNS0::MakeOptions( uint8_t const * pRef , uint16_t const & length )
{
	if( nullptr == pRef || 1 > length )
	{
		return false ;
	}

	if( nullptr != pOpt )
	{
		delete pOpt ;
		pOpt = nullptr ;
	}

	pOpt = new ( std::nothrow ) ds::LinkedList< EDNS0_OPTION >() ;
	if( nullptr == pOpt )
	{
		return false ;
	}

	uint16_t pos = 0 ;
	while( pos + 4 <= length )
	{
		uint16_t code 
			= ( ( pRef[	pos + 0 ] << 8 ) & 0xFF00 )
			| ( ( pRef[	pos + 1 ] << 0 ) & 0x00FF ) ;

		uint16_t len
			= ( ( pRef[	pos + 2 ] << 8 ) & 0xFF00 )
			| ( ( pRef[	pos + 3 ] << 0 ) & 0x00FF ) ;

		if( length < ( pos + 4 + len ) )
		{
			delete pOpt ;
			pOpt = nullptr ;

			return false ;
		}

		if( false == IsValidEDNS0_OptCode( code ) )
		{
			pos += 2 + 2 + len ;
			continue ;
		}

		EDNS0_OptCode optCode = enumFromUint16< EDNS0_OptCode >( code ) ;

		EDNS0_OPTION * pOption = new ( std::nothrow ) EDNS0_OPTION( optCode , len , & ( pRef[ 4 + pos ] ) ) ;
		if( nullptr == pOption )
		{
			delete pOpt ;

			pOpt = nullptr ;

			return false ;
		}

		pOpt->Insert( pOption ) ;

		pos += 2 + 2 + len ;
	}

	return true ;
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