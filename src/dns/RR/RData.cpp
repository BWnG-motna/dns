#include "dns/RR/RData.h"

#include <sstream>
#include <iomanip>


daniel::dns::RR::RData::RData( uint8_t const * pRef )
	: pDataGram( pRef ) 
{

}


bool daniel::dns::RR::RData::GetCompressedIPv6( uint16_t const ( & addr )[ 8 ] , uint8_t * pBuf , uint16_t const & length ) const
{
	uint16_t ipv6[ 8 ][ 3 ] ;
	for( uint8_t pos = 0 ; pos < 8 ; ++pos )
	{
		ipv6[ pos ][ 0 ] = addr[ pos ] ;
		ipv6[ pos ][ 1 ] = 0 ;
		ipv6[ pos ][ 2 ] = 0 ;
	}

	ipv6[ 7 ][ 1 ] = ( 0 == ipv6[ 7 ][ 0 ] ) ? 1 : 0 ;

	for( int8_t pos = 6 ; pos >= 0 ; --pos )
	{
		ipv6[ pos ][ 1 ] = ( 0 == ipv6[ pos ][ 0 ] ) ? ( ipv6[ pos + 1 ][ 1 ] + 1 ) : 0 ;
	}

	uint16_t max    = 0 ;
	uint16_t maxPos = 0 ;
	for( uint8_t pos = 0 ; pos < 8 ; ++pos )
	{
		if( max < ipv6[ pos ][ 1 ] )
		{
			max    = ipv6[ pos ][ 1 ] ;
			maxPos = pos ;
		}
	}

	if( 1 < ipv6[ maxPos ][ 1 ] )
	{
		ipv6[ maxPos ][ 2 ] = 1 ;
		
		for( uint8_t pos = maxPos + 1 ; pos < 8 ; ++pos )
		{
			if( 0 == ipv6[ pos ][ 1 ] )
			{
				break ;
			}

			ipv6[ pos ][ 2 ] = 1 ;
		}
	}

	std::stringstream ss ;

	bool skipped = false ;
	for( uint8_t pos = 0 ; pos < 8 ; ++pos )
	{
		if( 1 == ipv6[ pos ][ 2 ] )
		{
			if( false == skipped )
			{
				if( 0 != pos )
				{
					ss << ":" ;
				}
				ss << ":" ;

				skipped = true ;
			}

			continue ;
		}

		if( 0 != pos && false == skipped )
		{
			ss << ":" ;
		}

		ss << std::hex << std::setfill( ' ' ) << std::setw( 0 ) << ipv6[ pos ][ 0 ]  ; 
	}
	ss << std::dec << std::setfill( ' ' ) << std::setw( 0 ) ;

	std::string dStr = ss.str() ;
	char const * p = dStr.c_str() ;
	uint16_t len = static_cast< uint16_t >( dStr.length() ) ;

	for( uint16_t pos = 0 ; pos < len && pos < length ; ++pos )
	{
		pBuf[ pos ] = p[ pos ] ;
	}

	uint16_t lessPos = ( len < length ) ? len : length ;
	pBuf[ lessPos ] = '\0' ;

	return true ;
}



uint16_t daniel::dns::RR::RData::GetDNData( 
	uint8_t        * pBuf   , 
	uint16_t const & length , 
	uint8_t  const * pRef   ,
	bool     const & fqdn   ) const
{
	if( 1 > length || nullptr == pBuf || nullptr == pRef )
	{
		return 0 ;
	}

	uint8_t const * p  = pRef ;
	uint16_t len  = 0 ;
	uint16_t bPos = 0 ;

	while( '\0' != *p )
	{
		if( 0xC0 <= ( *p & 0xC0 ) )
		{
			uint16_t offset
				= ( ( ( 0x3F & *( p + 0 ) ) << 8 ) & 0xFF00 ) 
				| ( ( ( 0xFF & *( p + 1 ) ) << 0 ) & 0x00FF ) ;

			p = pDataGram + offset ;

			continue ;
		}

		len = ( *p++ ) ;

		for( uint8_t pos = 0 ; pos < len ; ++pos ) 
		{
			if( length <= bPos )
			{
				return bPos ;
			}
			pBuf[ bPos++ ] = *p++ ;
		}

		if( ( true == fqdn || '\0' != *p ) && ( length <= bPos ) )
		{
			return bPos ;
		}

		if( true == fqdn )
		{
			pBuf[ bPos++ ] = '.' ;
		}
		else if( '\0' != *p )
		{
			pBuf[ bPos++ ] = '.' ;
		}
	}

	pBuf[ bPos ] = '\0' ;
	
	return bPos ;
}


uint16_t daniel::dns::RR::RData::SkipDName( uint8_t const * pBuf , uint16_t const & length ) const
{
	if( 1 > length || nullptr == pBuf )
	{
		return 0 ;
	}

	uint16_t bPos = 0 ;

	while( '\0' != pBuf[ bPos ] && bPos < length )
	{
		if( 0xC0 <= ( pBuf[ bPos ] & 0xC0 ) )
		{
			if( length <= bPos + 1 )
			{
				return 0 ;
			}
			else
			{
				return bPos + 2 ;
			}
		}

		uint8_t len = pBuf[ bPos ] ;
		bPos += 1 + len ;
		if( length < bPos )
		{
			return 0 ;
		} 
	}

	if( '\0' == pBuf[ bPos ] && bPos < length )
	{
		++bPos ;
	}

	return bPos ;
}