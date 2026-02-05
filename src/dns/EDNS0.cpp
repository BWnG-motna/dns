#include "dns/EDNS0.h"
#include "dns/RR/SEC/SECAlgo.h"


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


bool daniel::dns::EDNS0::InsertOption( EDNS0_OptCode const & optCode , uint8_t const * pDat , uint16_t const & len )
{
	if( 0 != len && nullptr == pDat ) 
	{
		return false ;
	}

	if( nullptr == pOpt )
	{
		pOpt = new ( std::nothrow ) ds::LinkedList< EDNS0_OPTION >() ;
		if( nullptr == pOpt )
		{
			return false ;
		}
	}

	EDNS0_OPTION * pOption = new ( std::nothrow ) EDNS0_OPTION( optCode , len , pDat ) ;
	if( nullptr == pOption )
	{
		return false ;
	}

	pOpt->Insert( pOption ) ;

	return true ;
}


bool daniel::dns::EDNS0::InsertOptPadding( uint8_t const * pDat , uint16_t const & len )
{
	return InsertOption( EDNS0_OptCode::PADDING , pDat , len ) ;
}


bool daniel::dns::EDNS0::InsertOptDAU()
{
	uint8_t  algos[ 256 ] ;
	uint16_t len = 0 ;

	for( uint16_t pos = 0 ; pos < 256 ; ++pos )
	{
		if( true == RR::SEC::IsValidAlgo( pos ) )
		{
			algos[ len++ ] = pos ;
		}
	}

	if( 0 == len )
	{
		return false ;
	}

	return InsertOption( EDNS0_OptCode::DAU , algos , len ) ;
}


bool daniel::dns::EDNS0::InsertOptCookie( uint8_t const * pDat , uint16_t const & len )
{
	if( nullptr == pDat || 8 > len )
	{
		return false ;
	}

	uint16_t clen = len ;

	if( clen > 32 )
	{
		clen = 32 ;
	}

	return InsertOption( EDNS0_OptCode::COOKIE , pDat , clen ) ;
}


uint16_t daniel::dns::EDNS0::Save( uint8_t * pBuf , uint16_t const & length )
{
	// the case what pOpt is not null is not implemented, not handled.
	if( 1 > length || nullptr == pBuf )
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

	if( nullptr == pOpt || ( nullptr != pOpt && 0 == pOpt->GetCount() ) )
	{
		return 11 ;
	}

	uint16_t rdlength = 0 ;

	ds::LinkedList< EDNS0_OPTION >::const_iterator posIter = pOpt->begin() ;
	ds::LinkedList< EDNS0_OPTION >::const_iterator endIter = pOpt->end() ;

	uint16_t pos = 11 ;
	while( posIter != endIter )
	{
		EDNS0_OPTION const & p = *posIter ; 
		
		uint16_t const   code = static_cast< uint16_t >( p.GetCode() ) ;
		uint16_t const    len = p.GetLen() ;
		uint8_t  const * pDat = p.GetData() ; 

		if( ( pos + 4 + len ) > length )
		{
			break ;
		}

		pBuf[ pos + 0 ] = ( code >> 8 ) & 0x00FF ;
		pBuf[ pos + 1 ] = ( code >> 0 ) & 0x00FF ;
		pBuf[ pos + 2 ] = (  len >> 8 ) & 0x00FF ;
		pBuf[ pos + 3 ] = (  len >> 0 ) & 0x00FF ;

		for( uint16_t optPos = 0 ; optPos < len ; ++optPos )
		{
			pBuf[ pos + 4 + optPos ] = pDat[ optPos ] ;
		} 

		pos      += 4 + len ;
		rdlength += 4 + len ;

		++posIter ;
	}

	pBuf[  9 ] = ( rdlength >> 8 ) & 0x00FF ;
	pBuf[ 10 ] = ( rdlength >> 0 ) & 0x00FF; 

	return pos ;
}


daniel::dns::QType daniel::dns::EDNS0::GetType() const
{
	return QType::OPT ;
}


uint32_t daniel::dns::EDNS0::GetOptCount() const
{
	if( nullptr == pOpt )
	{
		return 0 ;
	}

	return pOpt->GetCount() ;
}